#include "CCollisionResolver.h"

#include "CCollisionObject.h"
#include "CUtils.h"
#include "CVector3.h"
#include "CContactInfo.h"
#include "CRigidBody.h"

bool Cinkes::CCollisionResolver::Resolve(std::vector<std::shared_ptr<CContactInfo>>& a_Info, CScalar a_T)
{
		StepOne(a_Info, a_T);
		StepTwo(a_Info, a_T);
	return true;
}

Cinkes::CMat3x3 Cinkes::CCollisionResolver::CalculateContactBasis(const CContactInfo* a_Info)
{
	CVector3 tangent[2];
	if(CUtils::Abs(a_Info->m_Normal.getX()) > CUtils::Abs(a_Info->m_Normal.getY()))
	{
		CScalar dist = static_cast<CScalar>(1) / 
					CUtils::Sqrt(a_Info->m_Normal.getZ() * a_Info->m_Normal.getZ() + a_Info->m_Normal.getX() * a_Info->m_Normal.getX());

		tangent[0][0] = a_Info->m_Normal.getZ() * dist;
		tangent[0][1] = 0;
		tangent[0][2] = a_Info->m_Normal.getX() * dist * -1;

		tangent[1][0] = a_Info->m_Normal.getY() * tangent[0].getX();
		tangent[1][1] = a_Info->m_Normal.getZ() * tangent[0].getX() - a_Info->m_Normal.getX() * tangent[0].getZ();
		tangent[1][2] = a_Info->m_Normal.getY() * tangent[0].getX() * -1;
	}
	else
	{
		CScalar dist = static_cast<CScalar>(1) /
			CUtils::Sqrt(a_Info->m_Normal.getZ() * a_Info->m_Normal.getZ() + a_Info->m_Normal.getY() * a_Info->m_Normal.getY());

		tangent[0][0] = 0;
		tangent[0][1] = a_Info->m_Normal.getZ() * dist * -1;
		tangent[0][2] = a_Info->m_Normal.getY() * dist;

		tangent[1][0] = a_Info->m_Normal.getY() * tangent[0].getZ() - a_Info->m_Normal.getZ() * tangent[0].getY();
		tangent[1][1] = a_Info->m_Normal.getX() * tangent[0].getZ() * -1;
		tangent[1][2] = a_Info->m_Normal.getX() * tangent[0].getY();
	}
	CMat3x3 contactToWorld;
	contactToWorld.setFromColumns(a_Info->m_Normal, tangent[0], tangent[1]);
	return contactToWorld;
}

void Cinkes::CCollisionResolver::StepOne(std::vector<std::shared_ptr<CContactInfo>>& a_Info, CScalar a_T)
{
	for (auto current : a_Info)
	{
		current->m_ContactToWorld = CalculateContactBasis(current.get());
		current->m_RelativeContactPosition[0] = current->m_ContactPoints[0] - current->m_First->GetTransform().getOrigin();
		if (current->m_Second)
		{
			current->m_RelativeContactPosition[1] = current->m_ContactPoints[0] - current->m_Second->GetTransform().getOrigin();
		}
		current->m_ContactVelocity = CalculateLocalVelocity(0, a_T, current.get());
		if (current->m_Second)
		{
			current->m_ContactVelocity -= CalculateLocalVelocity(1, a_T, current.get());
		}

		CalculateDeltaVelocity(a_T, current.get());
		current->m_DesiredVelocity = current->m_DeltaVelocity;
	}
}

void Cinkes::CCollisionResolver::StepTwo(std::vector<std::shared_ptr<CContactInfo>>& a_Info, CScalar a_T)
{
	int iterationsUsed = 0;

	while(iterationsUsed < 8)
	{
		for (auto element : a_Info)
		{
			CVector3 linearChange[2];
			CVector3 angularChange[2];
			CScalar maxPenetration = static_cast<CScalar>(0.0001);

			if (element->m_PenetrationDepth > maxPenetration)
			{
				maxPenetration = element->m_PenetrationDepth;
			}
			ApplyPositionChange(linearChange, angularChange, maxPenetration,element.get());
			
			CCollisionObject* temp[2] = { element->m_First.get(), element->m_Second.get() };
			for (unsigned b = 0; b < 2; b++)
			{
				if (temp[b])
				{
					for (unsigned d = 0; d < 2; d++)
					{
						if (temp[b] == temp[d])
						{
							CVector3 deltaPosition = linearChange[d] + angularChange[d].Cross(element->m_RelativeContactPosition[b]);
							element->m_PenetrationDepth += deltaPosition.Dot(element->m_Normal) * CUtils::Sgn(1, static_cast<CScalar>(b));
						}
					}
				}

			}
		}
		

		iterationsUsed++;
	}
}

void Cinkes::CCollisionResolver::StepThree(std::vector<std::shared_ptr<CContactInfo>>& a_Info, CScalar a_T)
{
	CVector3 velocitychange[2];
	CVector3 rotationchange[2];
	CVector3 deltavelocity;

	unsigned iterationsused = 0;
	while(iterationsused < 8)
	{
		CScalar max = static_cast<CScalar>(0.25);
		unsigned index = static_cast<unsigned>(a_Info.size());
		for(unsigned i = 0; i < static_cast<unsigned>(a_Info.size()); i++)
		{
			if(a_Info[i]->m_DesiredVelocity > max)
			{
				max = a_Info[i]->m_DesiredVelocity;
				index = i;
			}
		}
		if (index == static_cast<unsigned>(a_Info.size())) { break; }
		for (unsigned i = 0; i < a_Info.size(); i++)
		{

			CCollisionObject* temp[2] = { a_Info[i]->m_First.get(),a_Info[i]->m_Second.get() };
			CCollisionObject* tempnIndex[2] = { a_Info[index]->m_First.get(),a_Info[index]->m_Second.get() };
			// Check each body in the contact
			for (unsigned b = 0; b < 2; b++) if (temp[b])
			{
				// Check for a match with each body in the newly
				// resolved contact
				for (unsigned d = 0; d < 2; d++)
				{
					if (temp[b] == tempnIndex[d])
					{
						deltavelocity = velocitychange[d] +
							rotationchange[d].Cross(
								a_Info[i]->m_RelativeContactPosition[b]);

						// The sign of the change is negative if we're dealing
						// with the second body in a contact.
						a_Info[i]->m_ContactVelocity +=
							a_Info[i]->m_ContactToWorld.TransformTranspose(deltavelocity)
							* static_cast<CScalar>(b ? -1 : 1);
						CalculateDeltaVelocity(a_T, a_Info[i].get());
					}
				}
			}
		}
		iterationsused++;
	}
}

Cinkes::CVector3 Cinkes::CCollisionResolver::ConvertToRelative(CCollisionObject* a_Object, const CVector3& a_Position)
{
	return  a_Position - a_Object->GetTransform().getOrigin();
}

Cinkes::CVector3 Cinkes::CCollisionResolver::ConvertToWorld(CCollisionObject* a_Object, const CVector3& a_Position)
{
	return a_Object->GetTransform().getBasis().Transpose() * a_Position;
}

void Cinkes::CCollisionResolver::MakeOrthoBasis(CVector3* a_X, CVector3* a_Y, CVector3* a_Z)
{
	CVector3 temp = (*a_X).Cross((*a_Y));
	a_Z->setX(temp.getX());
	a_Z->setY(temp.getY());
	a_Z->setZ(temp.getZ());

	if (a_Z->Length2() < static_cast<CScalar>(0.00001)) { return; }

	temp = (*a_Z).Cross((*a_X));
	a_Y->setX(temp.getX());
	a_Y->setY(temp.getY());
	a_Y->setZ(temp.getZ());

	a_Y->Normalize();
	a_Z->Normalize();
}

void Cinkes::CCollisionResolver::CalculateDeltaVelocity(CScalar a_T, CContactInfo* a_Info)
{
	CScalar velocityformacceleration = 0;

	velocityformacceleration += std::static_pointer_cast<CRigidBody>(a_Info->m_First)->GetLastFrameAcceleration().Dot(a_Info->m_Normal) * a_T;
	if(a_Info->m_Second)
	{
		velocityformacceleration -= std::static_pointer_cast<CRigidBody>(a_Info->m_Second)->GetLastFrameAcceleration().Dot(a_Info->m_Normal) * a_T;
	}
	a_Info->m_DeltaVelocity = (a_Info->m_ContactVelocity * -1).getX() - a_Info->m_Restitution * (a_Info->m_ContactVelocity.getX() - velocityformacceleration);

}

Cinkes::CVector3 Cinkes::CCollisionResolver::CalculateLocalVelocity(unsigned a_Index, CScalar a_T, CContactInfo* a_Info)
{
	CCollisionObject* temp[2] = { a_Info->m_First.get(),a_Info->m_Second.get() };
	CRigidBody* body = static_cast<CRigidBody*>(temp[a_Index]);
	CVector3 velocity = body->GetAngularVelocity().Cross(a_Info->m_RelativeContactPosition[a_Index]);
	velocity += body->GetLinearVelocity();
	CVector3 contactvel = a_Info->m_ContactToWorld.TransformTranspose(velocity);
	CVector3 accumulated = body->GetLastFrameAcceleration() * a_T;
	accumulated = a_Info->m_ContactToWorld.TransformTranspose(accumulated);
	accumulated.setX(0);
	contactvel += accumulated;
	return contactvel;
}


void Cinkes::CCollisionResolver::ApplyPositionChange(CVector3 a_LinearChange[2], CVector3 a_AngularChange[2], CScalar a_Penetration, CContactInfo* a_Info)
{
	CRigidBody* temp[2] = { static_cast<CRigidBody*>(a_Info->m_First.get()),static_cast<CRigidBody*>(a_Info->m_Second.get()) };
	CScalar angularlimit = static_cast<CScalar>(0.2);
	CScalar angularmove[2];
	CScalar linearmove[2];

	CScalar totalintertia = 0;
	CScalar angularintertia[2];
	CScalar linearintertia[2];

	for(unsigned i = 0; i < 2; i++)
	{
		if(temp[i])
		{
			CMat3x3 inverseintertiatensor = temp[i]->GetInverseInertiaTensor();
			CVector3 angularintertiaworld = a_Info->m_RelativeContactPosition[i].Cross(a_Info->m_Normal);
			angularintertiaworld = inverseintertiatensor * angularintertiaworld;
			angularintertiaworld = angularintertiaworld.Cross(a_Info->m_RelativeContactPosition[i]);
			angularintertia[i] = angularintertiaworld.Dot(a_Info->m_Normal);

			linearintertia[i] = temp[i]->GetInverseMass();
			totalintertia += linearintertia[i] + angularintertia[i];
		}
	}

	for(unsigned i = 0; i < 2; i++)
	{
		if(temp[i])
		{
			CScalar sign = CUtils::Sgn(1,static_cast<CScalar>(i));
			angularmove[i] = sign * a_Penetration * (angularintertia[i] / totalintertia);
			linearmove[i] = sign * a_Penetration * (linearintertia[i] / totalintertia);

			CVector3 projection = a_Info->m_RelativeContactPosition[i];
			CScalar toadd = (a_Info->m_RelativeContactPosition[i] * -1).Dot(a_Info->m_Normal);
			projection += a_Info->m_Normal * toadd;
			CScalar maxmagnitude = angularlimit * projection.Length();

			if(angularmove[i] < maxmagnitude * -1)
			{
				CScalar totalmove = angularmove[i] + linearmove[i];
				angularmove[i] = maxmagnitude * -1;
				linearmove[i] = totalmove - angularmove[i];
			}
			else if(angularmove[i] > maxmagnitude)
			{
				CScalar totalmove = angularmove[i] + linearmove[i];
				angularmove[i] = maxmagnitude;
				linearmove[i] = totalmove - angularmove[i];
			}

			if(angularmove[i] > static_cast<CScalar>(-0.001) && angularmove[i] < static_cast<CScalar>(0.001))
			{
				a_AngularChange[i] = CVector3();
			}
			else
			{
				CVector3 tartgetangulardirection = a_Info->m_RelativeContactPosition[i].Cross(a_Info->m_Normal);
				CMat3x3 tensor = temp[i]->GetInverseInertiaTensor();
				a_AngularChange[i] = (tensor * tartgetangulardirection) * (angularmove[i] / angularintertia[i]);
			}

			a_LinearChange[i] = (a_Info->m_Normal) * linearmove[i];
			CVector3 position = temp[i]->GetTransform().getOrigin();
			CMat3x3 rotation = temp[i]->GetTransform().getBasis();
			position += a_Info->m_Normal * linearmove[i];
			temp[i]->SetTransform(CTransform(rotation, position));
			temp[i]->SetInverseInertiaTensorWorld();
		}
	}

}

void Cinkes::CCollisionResolver::ApplyVelocityChange(CContactInfo* a_Info, CVector3 a_VelocityChange[2], CVector3 a_RotationChange[2])
{
	CRigidBody* temp[2] = { static_cast<CRigidBody*>(a_Info->m_First.get()),static_cast<CRigidBody*>(a_Info->m_Second.get()) };

	CMat3x3 inverseInertiaTensor[2];
	inverseInertiaTensor[0] = temp[0]->GetInverseInertiaTensor();
	if (temp[1]) { inverseInertiaTensor[1] = temp[1]->GetInverseInertiaTensor(); }

	CVector3 impulseContact;
	if(a_Info->m_Friction <= static_cast<CScalar>(0.001))
	{
		impulseContact = FrictionlessImpulse(inverseInertiaTensor, a_Info->m_DesiredVelocity,a_Info);
	}
	else { impulseContact = FrictionImpulse(inverseInertiaTensor, a_Info->m_DesiredVelocity, a_Info->m_Friction,a_Info); }
	CVector3 impulse = a_Info->m_ContactToWorld * impulseContact;

	CVector3 impulsivetorque = a_Info->m_RelativeContactPosition[0].Cross(impulse);
	a_RotationChange[0] = inverseInertiaTensor[0] * impulsivetorque;
	a_VelocityChange[0] = impulse * temp[0]->GetInverseMass();

	temp[0]->AddVelocity(a_VelocityChange[0]);
	temp[0]->AddAngularVelocity(a_RotationChange[0]);

	if(temp[1])
	{
		impulsivetorque = a_Info->m_RelativeContactPosition[1].Cross(impulse);
		a_RotationChange[0] = inverseInertiaTensor[1] * impulsivetorque;
		a_VelocityChange[0] = impulse * temp[1]->GetInverseMass();

		temp[1]->AddVelocity(a_VelocityChange[1]);
		temp[1]->AddAngularVelocity(a_RotationChange[1]);
	}
}

Cinkes::CVector3 Cinkes::CCollisionResolver::FrictionlessImpulse(CMat3x3 a_Tensor[2], CScalar a_DesiredVelocity, CContactInfo* a_Info)
{
	CRigidBody* temp[2] = { static_cast<CRigidBody*>(a_Info->m_First.get()),static_cast<CRigidBody*>(a_Info->m_Second.get()) };

	CVector3 impulsecontact;
	CVector3 deltavelocityworld = a_Info->m_RelativeContactPosition[0].Cross(a_Info->m_Normal);
	deltavelocityworld = a_Tensor[0] * deltavelocityworld;
	deltavelocityworld = deltavelocityworld.Cross(a_Info->m_RelativeContactPosition[0]);

	CScalar deltavelocity = deltavelocityworld.Dot(a_Info->m_Normal);

	if(temp[1])
	{
		deltavelocityworld = a_Info->m_RelativeContactPosition[1].Cross(a_Info->m_Normal);
		deltavelocityworld = a_Tensor[1] * deltavelocityworld;
		deltavelocityworld = deltavelocityworld.Cross(a_Info->m_RelativeContactPosition[1]);

		deltavelocityworld += deltavelocityworld.Dot(a_Info->m_Normal);
		deltavelocity += temp[1]->GetInverseMass();
	}

	impulsecontact.setX(a_DesiredVelocity / deltavelocity);
	impulsecontact.setY(0);
	impulsecontact.setZ(0);

	return impulsecontact;
}

Cinkes::CVector3 Cinkes::CCollisionResolver::FrictionImpulse(CMat3x3 a_Tensor[2], CScalar a_DesiredVelocity, CScalar a_Friction, CContactInfo* a_Info)
{
	CRigidBody* temp[2] = { static_cast<CRigidBody*>(a_Info->m_First.get()),static_cast<CRigidBody*>(a_Info->m_Second.get()) };

	CVector3 impulseContact;
	CScalar inverseMass = temp[0]->GetInverseMass();

	// The equivalent of a cross product in matrices is multiplication
	// by a skew symmetric matrix - we build the matrix for converting
	// between linear and angular quantities.
	CMat3x3 impulseToTorque;
	impulseToTorque.setSkewSymmetric(a_Info->m_RelativeContactPosition[0]);

	// Build the matrix to convert contact impulse to change in velocity
	// in world coordinates.
	CMat3x3 deltaVelWorld = impulseToTorque;
	deltaVelWorld *= a_Tensor[0];
	deltaVelWorld *= impulseToTorque;
	deltaVelWorld *= -1;

	// Check if we need to add body two's data
	if (temp[1])
	{
		// Set the cross product matrix
		impulseToTorque.setSkewSymmetric(a_Info->m_RelativeContactPosition[1]);

		// Calculate the velocity change matrix
		CMat3x3 deltaVelWorld2 = impulseToTorque;
		deltaVelWorld2 *= a_Tensor[1];
		deltaVelWorld2 *= impulseToTorque;
		deltaVelWorld2 *= -1;

		// Add to the total delta velocity.
		deltaVelWorld += deltaVelWorld2;

		// Add to the inverse mass
		inverseMass += temp[1]->GetInverseMass();
	}

	// Do a change of basis to convert into contact coordinates.
	CMat3x3 deltaVelocity = a_Info->m_ContactToWorld.Transpose();
	deltaVelocity *= deltaVelWorld;
	deltaVelocity *= a_Info->m_ContactToWorld;

	// Add in the linear velocity change
	deltaVelocity[0][0] += inverseMass;
	deltaVelocity[1][1] += inverseMass;
	deltaVelocity[2][2] += inverseMass;

	// Invert to get the impulse needed per unit velocity
	CMat3x3 impulseMatrix = deltaVelocity.GetInverse();

	// Find the target velocities to kill
	CVector3 velKill(a_DesiredVelocity,
		-a_Info->m_ContactVelocity.getY(),
		-a_Info->m_ContactVelocity.getZ());

	// Find the impulse to kill target velocities
	impulseContact = impulseMatrix * (velKill);

	// Check for exceeding friction
	CScalar planarImpulse = CUtils::Sqrt(
		impulseContact.getY() * impulseContact.getY() +
		impulseContact.getZ() * impulseContact.getZ()
	);
	if (planarImpulse > impulseContact.getX() * a_Friction)
	{
		// We need to use dynamic friction
		impulseContact[1] /= planarImpulse;
		impulseContact[2] /= planarImpulse;

		impulseContact[0] = deltaVelocity[0][0] +
			deltaVelocity[1][0] * a_Friction * impulseContact.getY() +
			deltaVelocity[2][0] * a_Friction * impulseContact.getZ();
		impulseContact[0] = a_DesiredVelocity / impulseContact.getX();
		impulseContact[1] *= a_Friction * impulseContact.getX();
		impulseContact[2] *= a_Friction * impulseContact.getX();
	}
	return impulseContact;
}
