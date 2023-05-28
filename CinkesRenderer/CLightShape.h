#pragma once
#include <memory>

#include "CRenderShape.h"

namespace Cinkes
{
	class CLightShape
	{
	public:
		CLightShape(const glm::mat4& a_Transform)
		{
			m_Shape = std::make_shared<CCubeRenderShape>(a_Transform, glm::vec3(0.4,0.4,0.4));
			
			m_Shape->m_Textured = false;
			m_Shape->SetMaterial(std::make_shared<CMaterial>());
			m_Shape->GetMaterial()->m_Color = glm::vec3(1, 1, 1);
		}

		glm::vec3 m_Intensities; //a.k.a. the color of the light
		float m_Attenuation;
		float m_AmbientCoefficient;
		float m_ConeAngle; // new
		glm::vec3 m_ConeDirection; // new
		std::shared_ptr<CCubeRenderShape> m_Shape;
	};
}

