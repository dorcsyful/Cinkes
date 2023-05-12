#pragma once
#include "CVector3.h"
#include "CInternalContactInfo.h"
#include "CPlane.h"
namespace Cinkes {

	struct CFace
	{
		bool isValid = false;
		CVector3 normal;
		std::vector<int> vertices;
	};


	class CBoxBoxCollision
	{
	public:
		CBoxBoxCollision();

		bool Run(CInternalContactInfo* a_Info);


	private:
		
		void FindReference();
		void FindIncident();
		void FindRefSidePlanes();
		void FindIncSidePlanes();
		void Clip(CFace& a_Face, std::vector<CVector3>& a_Box, std::vector<CPlane>& a_Planes, int a_Index);
		void CreateIncidentLines();

		CFace m_ReferenceFace;
		CFace m_IncidentFace;
		CInternalContactInfo* m_Info;
		std::vector<CPlane> m_RefSidePlanes;
		std::vector<CPlane> m_IncSidePlanes;
		std::vector<std::pair<CVector3, CVector3>> m_Lines;
		CVector3 m_Sides[6];
		CVector3 m_LocalNormal;
		std::vector<CVector3> m_ReferenceBox;
		std::vector<CVector3> m_IncidentBox;
		std::vector<std::pair<int, int>> m_LinesReference;
	};
}