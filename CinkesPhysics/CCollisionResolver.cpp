#include "CCollisionResolver.h"

#include <cassert>

#include "CCollisionObject.h"
#include "CUtils.h"
#include "CVector3.h"
#include "CContactInfo.h"
#include "CRigidBody.h"

bool Cinkes::CCollisionResolver::Resolve(const std::vector<CContactInfo*>& a_Info, CScalar a_T)
{
	for (auto element : a_Info)
	{
		m_Info = element;
		SetRigidBodies();
		StepOne(element, a_T);
	}

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

void Cinkes::CCollisionResolver::StepOne(CContactInfo* a_Info, CScalar a_T)
{
	{
		m_Info = a_Info;
		m_ContactToWorld = CalculateContactBasis(a_Info);
		m_RelativeContactPosition[0] = a_Info->m_ContactPoints[0] - m_Body[0]->GetTransform().getOrigin();
		if (m_Body[1])
		{
			m_RelativeContactPosition[1] = a_Info->m_ContactPoints[0] - m_Body[1]->GetTransform().getOrigin();
		}
		m_ContactVelocity = CalculateLocalVelocity(0, a_T);
		if (m_Body[1])
		{
			m_ContactVelocity -= CalculateLocalVelocity(1, a_T);
		}

		CalculateDeltaVelocity(a_T);
		a_Info->m_DesiredVelocity = m_DeltaVelocity;
	}
}

void Cinkes::CCollisionResolver::StepTwo(std::vector<CContactInfo*> a_Info, CScalar a_T)
{
	int iterationsUsed = 0;

	while(iterationsUsed < 8)
	{
		CVector3 linearChange[2];
		CVector3 angularChange[2];
		CScalar maxPenetration = static_cast<CScalar>(0.0001);
		int index = static_cast<int>(a_Info.size());
		for(int i = 0; i < static_cast<int>(a_Info.size()); i++)
		{
			if(a_Info[i]->m_PenetrationDepth > maxPenetration)
			{
				maxPenetration = a_Info[i]->m_PenetrationDepth;
				index = i;
			}
		}
		if (index == static_cast<int>(a_Info.size())) { break; }
		m_Info = a_Info[index];
		SetRigidBodies();
		ApplyPositionChange(linearChange, angularChange, maxPenetration);

		for (auto& i : a_Info)
		{
			m_Info = i;
			SetRigidBodies();
			for(unsigned b = 0; b < 2; b++)
			{
				if(m_Body[b])
				{
					for(unsigned d = 0; d < 2; d++)
					{
						if(m_Body[b] == m_Body[d])
						{
							CVector3 deltaPosition = linearChange[d] + angularChange[d].Cross(m_RelativeContactPosition[b]);
							m_Info->m_PenetrationDepth += deltaPosition.Dot(*m_Normal) * CUtils::Sgn(1, static_cast<CScalar>(b));
						}
					}
				}
			}
		}

		iterationsUsed++;
	}
}

void Cinkes::CCollisionResolver::StepThree(std::vector<CContactInfo*> a_Info, CScalar a_T)
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

void Cinkes::CCollisionResolver::CalculateDeltaVelocity(CScalar a_T)
{
	CScalar velocityformacceleration = 0;

	velocityformacceleration += m_Body[0]->GetLastFrameAcceleration().Dot(*m_Normal) * a_T;
	if(m_Body[1])
	{
		velocityformacceleration -= m_Body[1]->GetLastFrameAcceleration().Dot(*m_Normal) * a_T;
	}
	m_DeltaVelocity = (m_ContactVelocity * -1).getX() - m_Info->m_Restitution * (m_ContactVelocity.getX() - velocityformacceleration);

}

Cinkes::CVector3 Cinkes::CCollisionResolver::CalculateLocalVelocity(unsigned a_Index, CScalar a_T)
{
	CRigidBody* body = m_Body[a_Index];
	CVector3 velocity = body->GetAngularVelocity().Cross(m_RelativeContactPosition[a_Index]);
	velocity += body->GetLinearVelocity();
	CVector3 contactvel = m_ContactToWorld.TransformTranspose(velocity);
	CVector3 accumulated = body->GetLastFrameAcceleration() * a_T;
	accumulated = m_ContactToWorld.TransformTranspose(accumulated);
	accumulated.setX(0);
	contactvel += accumulated;
	return contactvel;
}

bool Cinkes::CCollisionResolver::SetRigidBodies()
{
	assert(m_Info->m_First);
	assert(m_Info->m_Second);
	if(m_Info->m_First->GetType() == EOBJECT_TYPE::TYPE_RIGID)
	{
		m_Body[0] = static_cast<CRigidBody*>(m_Info->m_First.get());
		m_Normal = &m_Info->m_Normal;
		if(m_Info->m_Second->GetType() == EOBJECT_TYPE::TYPE_RIGID)
		{
			m_Body[1] = static_cast<CRigidBody*>(m_Info->m_Second.get());
		}
		else { m_Body[1] = nullptr; }
	return true;

	}
	if(m_Info->m_Second->GetType() == EOBJECT_TYPE::TYPE_RIGID && m_Info->m_First->GetType() != EOBJECT_TYPE::TYPE_RIGID)
	{
		m_Body[0] = static_cast<CRigidBody*>(m_Info->m_Second.get());
		m_Body[1] = nullptr;
		m_Info->m_Normal *= -1;
		m_Normal = &m_Info->m_Normal;
		return true;
	}
	return false;
}

void Cinkes::CCollisionResolver::ApplyPositionChange(CVector3 a_LinearChange[2], CVector3 a_AngularChange[2], CScalar a_Penetration)
{
	CScalar angularlimit = static_cast<CScalar>(0.2);
	CScalar angularmove[2];
	CScalar linearmove[2];

	CScalar totalintertia = 0;
	CScalar angularintertia[2];
	CScalar linearintertia[2];

	for(unsigned i = 0; i < 2; i++)
	{
		if(m_Body[i])
		{
			CMat3x3 inverseintertiatensor = m_Body[i]->GetInverseInertiaTensor();
			CVector3 angularintertiaworld = m_RelativeContactPosition[i].Cross(*m_Normal);
			angularintertiaworld = inverseintertiatensor * angularintertiaworld;
			angularintertiaworld = angularintertiaworld.Cross(m_RelativeContactPosition[i]);
			angularintertia[i] = angularintertiaworld.Dot(*m_Normal);

			linearintertia[i] = m_Body[i]->GetInverseMass();
			totalintertia += linearintertia[i] + angularintertia[i];
		}
	}

	for(unsigned i = 0; i < 2; i++)
	{
		if(m_Body[i])
		{
			CScalar sign = CUtils::Sgn(1,static_cast<CScalar>(i));
			angularmove[i] = sign * a_Penetration * (angularintertia[i] / totalintertia);
			linearmove[i] = sign * a_Penetration * (linearintertia[i] / totalintertia);

			CVector3 projection = m_RelativeContactPosition[i];
			CScalar toadd = (m_RelativeContactPosition[i] * -1).Dot(*m_Normal);
			projection += *m_Normal * toadd;
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
				CVector3 tartgetangulardirection = m_RelativeContactPosition[i].Cross(*m_Normal);
				CMat3x3 tensor = m_Body[i]->GetInverseInertiaTensor();
				a_AngularChange[i] = (tensor * tartgetangulardirection) * (angularmove[i] / angularintertia[i]);
			}

			a_LinearChange[i] = (*m_Normal) * linearmove[i];
			CVector3 position = m_Body[i]->GetTransform().getOrigin();
			CMat3x3 rotation = m_Body[i]->GetTransform().getBasis();
			position += *m_Normal * linearmove[i];
			m_Body[i]->SetTransform(CTransform(rotation, position));
			m_Body[i]->SetInverseInertiaTensorWorld();
		}
	}

}

void Cinkes::CCollisionResolver::ApplyVelocityChange(CContactInfo* a_Info, CVector3 a_VelocityChange[2], CVector3 a_RotationChange[2])
{
	CMat3x3 inverseInertiaTensor[2];
	inverseInertiaTensor[0] = m_Body[0]->GetInverseInertiaTensor();
	if (m_Body[1]) { inverseInertiaTensor[1] = m_Body[1]->GetInverseInertiaTensor(); }

	CVector3 impulseContact;
	if(a_Info->m_Friction == static_cast<CScalar>(0))
	{
		impulseContact = FrictionlessImpulse(inverseInertiaTensor, a_Info->m_DesiredVelocity);
	}
	else { impulseContact = FrictionImpulse(inverseInertiaTensor, a_Info->m_DesiredVelocity, a_Info->m_Friction); }
	CVector3 impulse = m_ContactToWorld * impulseContact;

	CVector3 impulsivetorque = m_RelativeContactPosition[0].Cross(impulse);
	a_RotationChange[0] = inverseInertiaTensor[0] * impulsivetorque;
	a_VelocityChange[0] = impulse * m_Body[0]->GetInverseMass();

	m_Body[0]->AddVelocity(a_VelocityChange[0]);
	m_Body[0]->AddAngularVelocity(a_RotationChange[0]);

	if(m_Body[1])
	{
		impulsivetorque = m_RelativeContactPosition[1].Cross(impulse);
		a_RotationChange[0] = inverseInertiaTensor[1] * impulsivetorque;
		a_VelocityChange[0] = impulse * m_Body[1]->GetInverseMass();

		m_Body[1]->AddVelocity(a_VelocityChange[1]);
		m_Body[1]->AddAngularVelocity(a_RotationChange[1]);
	}
}

Cinkes::CVector3 Cinkes::CCollisionResolver::FrictionlessImpulse(CMat3x3 a_Tensor[2], CScalar a_DesiredVelocity)
{
	CVector3 impulsecontact;
	CVector3 deltavelocityworld = m_RelativeContactPosition[0].Cross(*m_Normal);
	deltavelocityworld = a_Tensor[0] * deltavelocityworld;
	deltavelocityworld = deltavelocityworld.Cross(m_RelativeContactPosition[0]);

	CScalar deltavelocity = deltavelocityworld.Dot(*m_Normal);

	if(m_Body[1])
	{
		deltavelocityworld = m_RelativeContactPosition[1].Cross(*m_Normal);
		deltavelocityworld = a_Tensor[1] * deltavelocityworld;
		deltavelocityworld = deltavelocityworld.Cross(m_RelativeContactPosition[1]);

		deltavelocityworld += deltavelocityworld.Dot(*m_Normal);
		deltavelocity += m_Body[1]->GetInverseMass();
	}

	impulsecontact.setX(a_DesiredVelocity / deltavelocity);
	impulsecontact.setY(0);
	impulsecontact.setZ(0);

	return impulsecontact;
}

Cinkes::CVector3 Cinkes::CCollisionResolver::FrictionImpulse(CMat3x3 a_Tensor[2], CScalar a_DesiredVelocity, CScalar a_Friction)
{
	CVector3 impulseContact;
	CScalar inverseMass = m_Body[0]->GetInverseMass();

	// The equivalent of a cross product in matrices is multiplication
	// by a skew symmetric matrix - we build the matrix for converting
	// between linear and angular quantities.
	CMat3x3 impulseToTorque;
	impulseToTorque.setSkewSymmetric(m_RelativeContactPosition[0]);

	// Build the matrix to convert contact impulse to change in velocity
	// in world coordinates.
	CMat3x3 deltaVelWorld = impulseToTorque;
	deltaVelWorld *= a_Tensor[0];
	deltaVelWorld *= impulseToTorque;
	deltaVelWorld *= -1;

	// Check if we need to add body two's data
	if (m_Body[1])
	{
		// Set the cross product matrix
		impulseToTorque.setSkewSymmetric(m_RelativeContactPosition[1]);

		// Calculate the velocity change matrix
		CMat3x3 deltaVelWorld2 = impulseToTorque;
		deltaVelWorld2 *= a_Tensor[1];
		deltaVelWorld2 *= impulseToTorque;
		deltaVelWorld2 *= -1;

		// Add to the total delta velocity.
		deltaVelWorld += deltaVelWorld2;

		// Add to the inverse mass
		inverseMass += m_Body[1]->GetInverseMass();
	}

	// Do a change of basis to convert into contact coordinates.
	CMat3x3 deltaVelocity = m_ContactToWorld.Transpose();
	deltaVelocity *= deltaVelWorld;
	deltaVelocity *= m_ContactToWorld;

	// Add in the linear velocity change
	deltaVelocity[0][0] += inverseMass;
	deltaVelocity[1][1] += inverseMass;
	deltaVelocity[2][2] += inverseMass;

	// Invert to get the impulse needed per unit velocity
	CMat3x3 impulseMatrix = deltaVelocity.GetInverse();

	// Find the target velocities to kill
	CVector3 velKill(a_DesiredVelocity,
		-m_ContactVelocity.getY(),
		-m_ContactVelocity.getZ());

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
