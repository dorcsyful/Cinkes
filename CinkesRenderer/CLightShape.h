#pragma once
#include <memory>
#include <glm/ext/matrix_transform.hpp>

#include "CRenderShape.h"

namespace Cinkes
{
	enum class ELIGHT_TYPE
	{
		TYPE_POINT,
		TYPE_DIRECTIONAL,
		TYPE_SPOTLIGHT
	};

	class CLightShape
	{
	public:
		CLightShape() = default;
		glm::vec3 m_Color{};
		glm::vec3 m_Diffuse{};
		glm::vec3 m_Specular{};
		glm::vec3 m_Position{};
		std::shared_ptr<CCubeRenderShape> m_Shape;
		bool m_DrawLightSource;
	};

	class CPointLightShape : public CLightShape
	{
	public:
		CPointLightShape(const glm::vec3& a_Position, const glm::vec3& a_Color = glm::vec3(1.f, 1.f, 1.f), bool a_DrawLightSource = true, const glm::vec3& a_Diffuse = glm::vec3(0, 0, 0),
			const glm::vec3& a_Specular = glm::vec3(1.f, 1.f, 1.f), float a_Constant = 1.f, float a_Linear = 0.09f, float a_Quadratic = 0.032f):
			CLightShape()
		{
			glm::mat4 transform = glm::mat4(1);
			transform = glm::translate(transform, a_Position);
			m_Shape = std::make_shared<CCubeRenderShape>(transform, glm::vec3(0.4, 0.4, 0.4));
			m_Position = a_Position;
			m_Shape->m_Textured = false;
			m_Shape->SetMaterial(std::make_shared<CMaterial>());
			m_Shape->GetMaterial()->m_Color = a_Color;
			m_Color = a_Color;
			m_DrawLightSource = a_DrawLightSource;
			m_Diffuse = a_Diffuse;
			m_Constant = a_Constant;
			m_Linear = a_Linear;
			m_Quadratic = a_Quadratic;
			m_Specular = a_Specular;
		}


		float m_Constant;
		float m_Linear;
		float m_Quadratic;
	};

	class CDirectionalLightShape : public CLightShape
	{
	public:
		CDirectionalLightShape(const glm::vec3& a_Direction, const glm::vec3& a_Color = glm::vec3(1.f, 1.f, 1.f), bool a_DrawLightSource = false, const glm::vec3& a_Position = glm::vec3(0.f, 0.f, 0.f), 
			const glm::vec3& a_Diffuse = glm::vec3(0, 0, 0), const glm::vec3& a_Specular = glm::vec3(1.f, 1.f, 1.f))
		{
			glm::mat4 transform = glm::mat4(1);
			glm::translate(transform, a_Position);
			m_Shape = std::make_shared<CCubeRenderShape>(transform, glm::vec3(0.4, 0.4, 0.4));

			m_Shape->m_Textured = false;
			m_Shape->SetMaterial(std::make_shared<CMaterial>());
			m_Shape->GetMaterial()->m_Color = a_Color;
			m_Position = a_Position;
			m_Color = a_Color;

			m_DrawLightSource = a_DrawLightSource;
			m_Diffuse = a_Diffuse;
			m_Specular = a_Specular;
			m_Direction = a_Direction;
		}

		glm::vec3 m_Direction;
	};
}

