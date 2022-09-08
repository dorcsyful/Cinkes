#pragma once
#include "CVector3.h"
#include "CContactInfo.h"
#include "CPlane.h"
namespace Cinkes {

	struct CFace {

		bool isValid = false;
		unsigned int id;
		CVector3 normal;
		std::vector<CVector3> vertices;
		std::vector<int> ids;
	};

	class CBoxBoxCollision {
	public:
		CBoxBoxCollision();

		bool Run(CContactInfo* a_Info);
		void FindReference();
		void FindIncident();
		void FindSidePlanes();
		void Clip();

	private:
		CFace m_ReferenceFace;
		CFace m_IncidentFace;
		CContactInfo* m_Info;
		std::vector<CPlane> m_Planes;
		std::vector<CVector3> m_Points;
		CVector3 m_Sides[6];
		CVector3 m_LocalNormal;
	};
}