#pragma once
#include "CInternalContactInfo.h"
#include "CScalar.h"
#include "CMatrix.h"
#include <map>

namespace Cinkes
{
	struct CTempContactPoint {
	public:
		CVector3 m_Point;
		CCollisionObject* m_Objects[2] = { nullptr, nullptr };
		int m_Info;
		CVector3 m_Normal;

		CScalar m_AccumulatedImpulse;
		CScalar m_TangentImpulse; //TODO: for friction
		CScalar m_EffectiveMass;
		CScalar m_EffectiveTangentMass;
		CVector3 m_RelativePosition[2];

		//TODO: figure out a more optimal way
		//these are 2D vectors to allow for easy handling of row and column vectors
		CMatrix m_EffectiveMassJacobian[2];
		CMatrix m_IndividualJacobian[2];
		CMatrix m_Jacobian;
		CMatrix m_InverseMassMatrix;
		CMatrix m_InverseMassMatrixA;
		CMatrix m_InverseMassMatrixB;
	};

	struct CSolverData {
	public:
		CMatrix m_VelocityMatrix;
		CMatrix m_ForceMatrix;
		std::vector<CMatrix> m_TemporaryData;
	};

	class CTestResolver
	{
	public:
		CTestResolver() = default;
		~CTestResolver() = default;
		CTestResolver(CTestResolver&& a_Rhs) = delete;
		CTestResolver(const CTestResolver& a_Rhs) = delete;

		CTestResolver& operator=(CTestResolver&& a_Rhs) noexcept = delete;
		CTestResolver& operator=(const CTestResolver& a_Rhs) = delete;

		void PreSolver(const std::shared_ptr<Cinkes::CInternalContactInfo>& a_Info, CScalar a_T, int a_Id);
		CSolverData Solver(const std::shared_ptr<Cinkes::CInternalContactInfo>& a_Info, CScalar a_T);
		bool PostSolver(const std::shared_ptr<Cinkes::CInternalContactInfo>& a_Info, CScalar a_T);

		void RelativeVelocity(CInternalContactInfo* a_Info, CVector3& a_OutVelocityA, CVector3& a_OutVelocityB);
		void CalculateJacobian(CTempContactPoint* a_Point);
		void CalculateInverseMassMatrices(CTempContactPoint* a_Info);
		std::vector< std::vector< CScalar > > MultiplyJacobians(CTempContactPoint* a_Info);

	private:
		CScalar m_Baumgarte = 0.0035f;
		CScalar m_RestitutionOffset = 0.5f;
		std::vector<std::shared_ptr<CTempContactPoint>> m_Points;
	};

}