#include "CTestResolver.h"

#include <iostream>

#include "CRigidBody.h"

void Cinkes::CTestResolver::PreSolver(const std::shared_ptr<Cinkes::CInternalContactInfo>& a_Info, CScalar a_T, int a_Id)
{
	CScalar inverse_mass_a = 0;
	CScalar inverse_mass_b = 0;
	CMat3x3 inverse_inertia_a = CMat3x3().GetIdentity();
	CMat3x3 inverse_inertia_b = CMat3x3().GetIdentity();

	if (a_Info->m_First->GetType() == EOBJECT_TYPE::TYPE_RIGID) {
		inverse_inertia_a = static_cast<CRigidBody*>(a_Info->m_First.get())->GetInverseInertiaTensorWorld();
		inverse_mass_a = static_cast<CRigidBody*>(a_Info->m_First.get())->GetInverseMass();
	}
	if (a_Info->m_Second->GetType() == EOBJECT_TYPE::TYPE_RIGID) {
		inverse_inertia_b = static_cast<CRigidBody*>(a_Info->m_Second.get())->GetInverseInertiaTensorWorld();
		inverse_mass_b = static_cast<CRigidBody*>(a_Info->m_Second.get())->GetInverseMass();
	}

	for (const auto& point : a_Info->m_ContactPoints) {
		std::shared_ptr<CTempContactPoint> temp = std::make_shared<CTempContactPoint>();
		temp->m_Point = point;
		temp->m_Objects[0] = a_Info->m_First.get();
		temp->m_Objects[1] = a_Info->m_Second.get();
		temp->m_Info = a_Id;
		temp->m_RelativePosition[0] = point - a_Info->m_First->GetTransform().getOrigin();
		temp->m_RelativePosition[1] = point - a_Info->m_Second->GetTransform().getOrigin();
		temp->m_Normal = a_Info->m_Normal;
		CalculateJacobian(temp.get());
	}
}

Cinkes::CSolverData Cinkes::CTestResolver::Solver(const std::shared_ptr<Cinkes::CInternalContactInfo>& a_Info, CScalar a_T)
{
	CSolverData data;

	CScalar contraint_epsilon = static_cast<CScalar>(0);

		return data;
}

void Cinkes::CTestResolver::CalculateJacobian(CTempContactPoint* a_Point)
{
	CVector3 normal = a_Point->m_Normal;
	CVector3 a_relative_position = a_Point->m_RelativePosition[0];
	CVector3 b_relative_position = a_Point->m_RelativePosition[1];
	
	CVector3 cross_product_a = CVector3::Cross(a_relative_position, normal);
	CVector3 cross_product_b = CVector3::Cross(b_relative_position, normal);

	a_Point->m_IndividualJacobian[0] = CMatrix(1, 6);
	a_Point->m_IndividualJacobian[1] = CMatrix(1, 6);
	if (a_Point->m_Objects[0]->GetType() == EOBJECT_TYPE::TYPE_RIGID)
	{
		a_Point->m_IndividualJacobian[0][0] = { -normal[0], -normal[1], -normal[2], -cross_product_a[0], -cross_product_a[1], -cross_product_a[2] };
	}
	if (a_Point->m_Objects[1]->GetType() == EOBJECT_TYPE::TYPE_RIGID)
	{
		a_Point->m_IndividualJacobian[1][0] = { normal[0],  normal[1],  normal[2],  cross_product_a[0],  cross_product_a[1],  cross_product_a[2] };
	}

	a_Point->m_Jacobian = CMatrix(1, 12);
	for (int i = 0; i < 6; i++) { a_Point->m_Jacobian[0][i] = a_Point->m_IndividualJacobian[0][0][i]; }
	for (int i = 0; i < 6; i++) { a_Point->m_Jacobian[1][5 + i] = a_Point->m_IndividualJacobian[1][0][i]; }

	a_Point->m_EffectiveMassJacobian[0] = a_Point->m_InverseMassMatrix * a_Point->m_Jacobian.Transpose();
	CMatrix temp = a_Point->m_Jacobian * a_Point->m_EffectiveMassJacobian[0];
	assert(temp.GetNumAll() == 0);
	a_Point->m_EffectiveMass = temp[0][0];
}

void Cinkes::CTestResolver::CalculateInverseMassMatrices(CTempContactPoint* a_Info)
{
	CMat3x3 inverse_inertia_tensor_a = CMat3x3::GetIdentity();
	CMat3x3 inverse_inertia_tensor_b = CMat3x3::GetIdentity();
	CMat3x3 mass_matrix_a = CMat3x3::GetIdentity();
	CMat3x3 mass_matrix_b = CMat3x3::GetIdentity();
	CMat3x3 zero = CMat3x3::GetZero();
	if (a_Info->m_Objects[0]->GetType() == EOBJECT_TYPE::TYPE_RIGID) {
		inverse_inertia_tensor_a = static_cast<CRigidBody*>(a_Info->m_Objects[0])->GetInverseInertiaTensorWorld();
		mass_matrix_a *= static_cast<CRigidBody*>(a_Info->m_Objects[0])->GetMass();
		mass_matrix_a = mass_matrix_a.GetInverse();
	}
	if (a_Info->m_Objects[1]->GetType() == EOBJECT_TYPE::TYPE_RIGID) {
		inverse_inertia_tensor_b = static_cast<CRigidBody*>(a_Info->m_Objects[1])->GetInverseInertiaTensorWorld();
		mass_matrix_b *= static_cast<CRigidBody*>(a_Info->m_Objects[1])->GetMass();
		mass_matrix_b = mass_matrix_b.GetInverse();
		
	}

	a_Info->m_InverseMassMatrix = CMatrix(12, 12);
	a_Info->m_InverseMassMatrix[0] = { mass_matrix_a[0][0], mass_matrix_a[0][1], mass_matrix_a[0][2], 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	a_Info->m_InverseMassMatrix[1] = { mass_matrix_a[1][0], mass_matrix_a[1][1], mass_matrix_a[1][2], 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	a_Info->m_InverseMassMatrix[2] = { mass_matrix_a[2][0], mass_matrix_a[2][1], mass_matrix_a[2][2], 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	a_Info->m_InverseMassMatrix[3] = { 0, 0, 0, inverse_inertia_tensor_a[0][0], inverse_inertia_tensor_a[0][1], inverse_inertia_tensor_a[0][2], 0, 0, 0, 0, 0, 0 };
	a_Info->m_InverseMassMatrix[4] = { 0, 0, 0, inverse_inertia_tensor_a[1][0], inverse_inertia_tensor_a[1][1], inverse_inertia_tensor_a[1][2], 0, 0, 0, 0, 0, 0 };
	a_Info->m_InverseMassMatrix[5] = { 0, 0, 0, inverse_inertia_tensor_a[2][0], inverse_inertia_tensor_a[2][1], inverse_inertia_tensor_a[2][2], 0, 0, 0, 0, 0, 0 };
	a_Info->m_InverseMassMatrix[6] = { 0, 0, 0, 0, 0, 0, mass_matrix_b[0][0], mass_matrix_b[0][1], mass_matrix_b[0][2], 0, 0, 0 };
	a_Info->m_InverseMassMatrix[7] = { 0, 0, 0, 0, 0, 0, mass_matrix_b[1][0], mass_matrix_b[1][1], mass_matrix_b[1][2], 0, 0, 0 };
	a_Info->m_InverseMassMatrix[8] = { 0, 0, 0, 0, 0, 0, mass_matrix_b[2][0], mass_matrix_b[2][1], mass_matrix_b[2][2], 0, 0, 0 };
	a_Info->m_InverseMassMatrix[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, inverse_inertia_tensor_b[0][0], inverse_inertia_tensor_b[0][1], inverse_inertia_tensor_b[0][2] };
	a_Info->m_InverseMassMatrix[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, inverse_inertia_tensor_b[1][0], inverse_inertia_tensor_b[1][1], inverse_inertia_tensor_b[1][2] };
	a_Info->m_InverseMassMatrix[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, inverse_inertia_tensor_b[2][0], inverse_inertia_tensor_b[2][1], inverse_inertia_tensor_b[2][2] };

	a_Info->m_InverseMassMatrixA = CMatrix(6, 6);
	a_Info->m_InverseMassMatrixA[0] = { mass_matrix_a[0][0],mass_matrix_a[0][1],mass_matrix_a[0][2], 0, 0, 0 };
	a_Info->m_InverseMassMatrixA[1] = { mass_matrix_a[1][0],mass_matrix_a[1][1],mass_matrix_a[1][2], 0, 0, 0 };
	a_Info->m_InverseMassMatrixA[2] = { mass_matrix_a[2][0],mass_matrix_a[2][1],mass_matrix_a[2][2], 0, 0, 0 };
	a_Info->m_InverseMassMatrixA[3] = { 0, 0, 0, inverse_inertia_tensor_a[0][0], inverse_inertia_tensor_a[0][1], inverse_inertia_tensor_a[0][2] };
	a_Info->m_InverseMassMatrixA[4] = { 0, 0, 0, inverse_inertia_tensor_a[1][0], inverse_inertia_tensor_a[1][1], inverse_inertia_tensor_a[1][2] };
	a_Info->m_InverseMassMatrixA[5] = { 0, 0, 0, inverse_inertia_tensor_a[2][0], inverse_inertia_tensor_a[2][1], inverse_inertia_tensor_a[2][2] };


	a_Info->m_InverseMassMatrixB = CMatrix(6, 6);
	a_Info->m_InverseMassMatrixB[0] = { mass_matrix_b[0][0],mass_matrix_b[0][1],mass_matrix_b[0][2], 0, 0, 0 };
	a_Info->m_InverseMassMatrixB[1] = { mass_matrix_b[1][0],mass_matrix_b[1][1],mass_matrix_b[1][2], 0, 0, 0 };
	a_Info->m_InverseMassMatrixB[2] = { mass_matrix_b[2][0],mass_matrix_b[2][1],mass_matrix_b[2][2], 0, 0, 0 };
	a_Info->m_InverseMassMatrixB[3] = { 0, 0, 0, inverse_inertia_tensor_b[0][0], inverse_inertia_tensor_b[0][1], inverse_inertia_tensor_b[0][2] };
	a_Info->m_InverseMassMatrixB[4] = { 0, 0, 0, inverse_inertia_tensor_b[1][0], inverse_inertia_tensor_b[1][1], inverse_inertia_tensor_b[1][2] };
	a_Info->m_InverseMassMatrixB[5] = { 0, 0, 0, inverse_inertia_tensor_b[2][0], inverse_inertia_tensor_b[2][1], inverse_inertia_tensor_b[2][2] };
}