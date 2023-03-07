#pragma once
#include <vector>

#include "CBoxShape.h"
#include "CCollisionObject.h"
#include "CTransform.h"
#include "CVector3.h"

namespace Cinkes
{
	class CAxisGenerator
	{
	public:
		void BoxBox(CCollisionObject* a_Object1, CCollisionObject* a_Object2,std::vector<CVector3>& a_OutAxes, std::vector<CVector3>& a_Vertices1, std::vector<CVector3>& a_Vertices2)
		{
			CVector3 temp[2] = { static_cast<CBoxShape*>(a_Object1->GetCollisionShape().get())->GetDimensions(),
								 static_cast<CBoxShape*>(a_Object2->GetCollisionShape().get())->GetDimensions() };
			a_OutAxes.push_back(CVector3::Normalize(a_Object1->GetTransform().getBasis() * CVector3(1.f, 0.f, 0.f)));
			a_OutAxes.push_back(CVector3::Normalize(a_Object1->GetTransform().getBasis() * CVector3(0.f, 1.f, 0.f)));
			a_OutAxes.push_back(CVector3::Normalize(a_Object1->GetTransform().getBasis() * CVector3(0.f, 0.f, 1.f)));

			a_OutAxes.push_back(CVector3::Normalize(a_Object2->GetTransform().getBasis() * CVector3(1.f, 0.f, 0.f)));
			a_OutAxes.push_back(CVector3::Normalize(a_Object2->GetTransform().getBasis() * CVector3(0.f, 1.f, 0.f)));
			a_OutAxes.push_back(CVector3::Normalize(a_Object2->GetTransform().getBasis() * CVector3(0.f, 0.f, 1.f)));
			a_Vertices1.push_back( a_Object1->GetTransform().getBasis() *
				CVector3(temp[0][0] * -1, temp[0][1] * -1, temp[0][2] * -1) + a_Object1->GetTransform().getOrigin());
			a_Vertices1.push_back(a_Object1->GetTransform().getBasis() *
				CVector3(temp[0][0] * -1, temp[0][1] * -1, temp[0][2]) + a_Object1->GetTransform().getOrigin());
			a_Vertices1.push_back(a_Object1->GetTransform().getBasis() *
				CVector3(temp[0][0] * -1, temp[0][1], temp[0][2]) + a_Object1->GetTransform().getOrigin());
			a_Vertices1.push_back(a_Object1->GetTransform().getBasis() *
				CVector3(temp[0][0] * -1, temp[0][1], temp[0][2] * -1) + a_Object1->GetTransform().getOrigin());
			a_Vertices1.push_back(a_Object1->GetTransform().getBasis() *
				CVector3(temp[0][0], temp[0][1], temp[0][2]) + a_Object1->GetTransform().getOrigin());
			a_Vertices1.push_back(a_Object1->GetTransform().getBasis() *
				CVector3(temp[0][0], temp[0][1], temp[0][2] * -1) + a_Object1->GetTransform().getOrigin());
			a_Vertices1.push_back(a_Object1->GetTransform().getBasis() *
				CVector3(temp[0][0], temp[0][1] * -1, temp[0][2]) + a_Object1->GetTransform().getOrigin());
			a_Vertices1.push_back(a_Object1->GetTransform().getBasis() *
				CVector3(temp[0][0], temp[0][1] * -1, temp[0][2] * -1) + a_Object1->GetTransform().getOrigin());

			a_Vertices2.push_back(a_Object1->GetTransform().getBasis() *
				CVector3(temp[1][0] * -1, temp[1][1] * -1, temp[1][2] * -1) + a_Object2->GetTransform().getOrigin());
			a_Vertices2.push_back(a_Object1->GetTransform().getBasis() *
				CVector3(temp[1][0] * -1, temp[1][1] * -1, temp[1][2]) + a_Object2->GetTransform().getOrigin());
			a_Vertices2.push_back(a_Object1->GetTransform().getBasis() *
				CVector3(temp[1][0] * -1, temp[1][1], temp[1][2]) + a_Object2->GetTransform().getOrigin());
			a_Vertices2.push_back(a_Object1->GetTransform().getBasis() *
				CVector3(temp[1][0] * -1, temp[1][1], temp[1][2] * -1) + a_Object2->GetTransform().getOrigin());
			a_Vertices2.push_back(a_Object1->GetTransform().getBasis() *
				CVector3(temp[1][0], temp[1][1], temp[1][2]) + a_Object2->GetTransform().getOrigin());
			a_Vertices2.push_back(a_Object1->GetTransform().getBasis() *
				CVector3(temp[1][0], temp[1][1], temp[1][2] * -1) + a_Object2->GetTransform().getOrigin());
			a_Vertices2.push_back(a_Object1->GetTransform().getBasis() *
				CVector3(temp[1][0], temp[1][1] * -1, temp[1][2]) + a_Object2->GetTransform().getOrigin());
			a_Vertices2.push_back(a_Object1->GetTransform().getBasis() *
				CVector3(temp[1][0], temp[1][1] * -1, temp[1][2] * -1) + a_Object2->GetTransform().getOrigin());

			a_OutAxes.push_back(CVector3::Cross(a_OutAxes[0], a_OutAxes[3]));
			a_OutAxes.push_back(CVector3::Cross(a_OutAxes[0], a_OutAxes[4]));
			a_OutAxes.push_back(CVector3::Cross(a_OutAxes[0], a_OutAxes[5]));
			a_OutAxes.push_back(CVector3::Cross(a_OutAxes[1], a_OutAxes[3]));
			a_OutAxes.push_back(CVector3::Cross(a_OutAxes[1], a_OutAxes[4]));
			a_OutAxes.push_back(CVector3::Cross(a_OutAxes[1], a_OutAxes[5]));
			a_OutAxes.push_back(CVector3::Cross(a_OutAxes[2], a_OutAxes[3]));
			a_OutAxes.push_back(CVector3::Cross(a_OutAxes[2], a_OutAxes[4]));
			a_OutAxes.push_back(CVector3::Cross(a_OutAxes[2], a_OutAxes[5]));


		}
		bool ChooseFunction(CCollisionObject* a_Object1, CCollisionObject* a_Object2, std::vector<CVector3>& a_OutAxes, std::vector<CVector3>& a_Vertices1, std::vector<CVector3>& a_Vertices2)
		{
			if(a_Object1->GetCollisionShape()->GetType() == ESHAPE_TYPE::SHAPE_BOX)
			{
				if(a_Object2->GetCollisionShape()->GetType() == ESHAPE_TYPE::SHAPE_BOX)
				{
					BoxBox(a_Object1, a_Object2, a_OutAxes, a_Vertices1, a_Vertices2);
					return true;
				}
			}
			assert(false);
			return false;
		}
	};
	class CSAT
	{
	public:

		CSAT()
		{
			m_Generator = std::make_unique<CAxisGenerator>();
		}

		bool Run(std::vector<CVector3>& a_OutAxes, std::vector<CVector3>& a_Vertices1, std::vector<CVector3>& a_Vertices2)
		{

			bool hasOverlap = false;

			if (ProjectionHasOverlap(a_OutAxes, a_Vertices2, a_Vertices1))
			{
				hasOverlap = true;
			}
			if (ProjectionHasOverlap(a_OutAxes, a_Vertices1, a_Vertices2))
			{
				hasOverlap = true;
			}

			return hasOverlap;
		}

		bool ProjectionHasOverlap(const std::vector<CVector3>& a_AAxes, const std::vector<CVector3>& a_BVertices, const std::vector<CVector3>& a_AVertices)
		{

			m_MinOverlap = std::numeric_limits<float>::max();

			for (auto& axes : a_AAxes)
			{


				float b_proj_min = std::numeric_limits<float>::max(), aProjMin = std::numeric_limits<float>::max();
				float b_proj_max = std::numeric_limits<float>::min(), aProjMax = std::numeric_limits<float>::min();

				CVector3 axis = axes;

				// Handles the cross product = {0,0,0} case
				if (axes == CVector3(0.f, 0.f, 0.f)) return true;

				for (auto& b_vertex : a_BVertices)
				{
					float val = CVector3::Dot(b_vertex, axis);

					if (val < b_proj_min)
					{
						b_proj_min = val;
					}

					if (val > b_proj_max)
					{
						b_proj_max = val;
					}
				}

				for (auto& a_vertex : a_AVertices)
				{
					float val = CVector3::Dot(a_vertex, axis);

					if (val < aProjMin)
					{
						aProjMin = val;
					}

					if (val > aProjMax)
					{
						aProjMax = val;
					}
				}

				float overlap = FindOverlap(aProjMin, aProjMax, b_proj_min, b_proj_max);

				if (overlap < m_MinOverlap)
				{
					m_MinOverlap = overlap;
					m_MinOverlapAxis = axis;

					m_PenetrationAxes.push_back(axis);
					m_PenetrationAxesDistance.push_back(overlap);

				}

				//Debug.Log(overlap);

				if (overlap <= 0)
				{
					// Separating Axis Found Early Out
					return false;
				}
			}

			return true; // A penetration has been found
		}



		/// Calculates the amount of overlap of two intervals.
		float FindOverlap(float a_Astart, float a_Aend, float a_Bstart, float a_Bend)
		{
			if (a_Astart < a_Bstart)
			{
				if (a_Aend < a_Bstart)
				{
					return 0.f;
				}

				return a_Aend - a_Bstart;
			}

			if (a_Bend < a_Astart)
			{
				return 0.f;
			}

			return a_Bend - a_Astart;
		}


		float m_MinOverlap = 0;
		CVector3 m_MinOverlapAxis = CVector3(0.f, 0.f, 0.f);

		std::vector<CVector3> m_PenetrationAxes;
		std::vector<float> m_PenetrationAxesDistance;
		std::unique_ptr<CAxisGenerator> m_Generator;
	};

}