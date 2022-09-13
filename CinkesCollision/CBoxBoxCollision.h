#pragma once
#include "CVector3.h"
#include "CContactInfo.h"
#include "CPlane.h"
namespace Cinkes {

	struct CFace {

		bool isValid = false;
		CVector3 normal;
		std::vector<int> vertices;
	};

	class CBoxBoxCollision {
	public:
		CBoxBoxCollision();

		bool Run(CContactInfo* a_Info);


	private:

		void FindReference();
		void FindIncident();
		void FindSidePlanes();
		void Clip();
		void CreateIncidentLines();

		CFace m_ReferenceFace;
		CFace m_IncidentFace;
		CContactInfo* m_Info;
		std::vector<CPlane> m_Planes;
		std::vector<std::pair<CVector3, CVector3>> m_Lines;
		CVector3 m_Sides[6];
		CVector3 m_LocalNormal;
		std::vector<CVector3> m_ReferenceBox;
		std::vector<CVector3> m_IncidentBox;
		std::vector<std::pair<int, int>> m_LinesReference;
	};
}