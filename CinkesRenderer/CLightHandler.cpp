#include "CLightHandler.h"

void Cinkes::CLightHandler::AddPointLight(const std::shared_ptr<Cinkes::CPointLightShape>& a_PointLight)
{
	assert(std::find(m_PointLights.begin(), m_PointLights.end(), a_PointLight) == m_PointLights.end());
	m_PointLights.push_back(a_PointLight);
}

void Cinkes::CLightHandler::AddDirectionalLight(const std::shared_ptr<CDirectionalLightShape>& a_DirectionalLight)
{
	assert(std::find(m_DirectionalLights.begin(), m_DirectionalLights.end(), a_DirectionalLight) == m_DirectionalLights.end());
	m_DirectionalLights.push_back(a_DirectionalLight);
}

void Cinkes::CLightHandler::AssignPointLightData(std::shared_ptr<CShader>& a_Shader, int a_Index)
{
	assert(a_Index < static_cast<int>(m_PointLights.size()));
	a_Shader->setInt("numberOfPointLights",m_PointLights.size());
	if(a_Index == -1)
	{
		for(int i = 0; i < m_PointLights.size(); i++)
		{

			a_Shader->setVec3("pointLights[" + std::to_string(i) + "].position", m_PointLights[i]->m_Position);
			a_Shader->setVec3("pointLights[" + std::to_string(i) + "].ambient", m_PointLights[i]->m_Color);
			a_Shader->setVec3("pointLights[" + std::to_string(i) + "].diffuse", m_PointLights[i]->m_Diffuse);
			a_Shader->setVec3("pointLights[" + std::to_string(i) + "].specular", m_PointLights[i]->m_Specular);
			a_Shader->setFloat("pointLights[" + std::to_string(i) + "].constant", m_PointLights[i]->m_Constant);
			a_Shader->setFloat("pointLights[" + std::to_string(i) + "].linear", m_PointLights[i]->m_Linear);
			a_Shader->setFloat("pointLights[" + std::to_string(i) + "].quadratic", m_PointLights[i]->m_Quadratic);
		}
	}
	else
	{
		a_Shader->setVec3("pointLights[" + std::to_string(a_Index) + "].position", m_PointLights[a_Index]->m_Position);
		a_Shader->setVec3("pointLights[" + std::to_string(a_Index) + "].ambient", m_PointLights[a_Index]->m_Color);
		a_Shader->setVec3("pointLights[" + std::to_string(a_Index) + "].diffuse", m_PointLights[a_Index]->m_Diffuse);
		a_Shader->setVec3("pointLights[" + std::to_string(a_Index) + "].specular", m_PointLights[a_Index]->m_Specular);
		a_Shader->setFloat("pointLights[" + std::to_string(a_Index) + "].constant", m_PointLights[a_Index]->m_Constant);
		a_Shader->setFloat("pointLights[" + std::to_string(a_Index) + "].linear", m_PointLights[a_Index]->m_Linear);
		a_Shader->setFloat("pointLights[" + std::to_string(a_Index) + "].quadratic", m_PointLights[a_Index]->m_Quadratic);
	}
}

void Cinkes::CLightHandler::AssignDirectionalLightData(std::shared_ptr<CShader>& a_Shader, int a_Index)
{
	assert(a_Index < static_cast<int>(m_DirectionalLights.size()));
	a_Shader->setInt("numberOfDirectionalLights", m_DirectionalLights.size());

	if (a_Index == -1)
	{
		for (int i = 0; i < m_DirectionalLights.size(); i++)
		{

			a_Shader->setVec3("directionalLights[" + std::to_string(i) + "].ambient", m_DirectionalLights[i]->m_Color);
			a_Shader->setVec3("directionalLights[" + std::to_string(i) + "].diffuse", m_DirectionalLights[i]->m_Diffuse);
			a_Shader->setVec3("directionalLights[" + std::to_string(i) + "].specular", m_DirectionalLights[i]->m_Specular);
			a_Shader->setVec3("directionalLights[" + std::to_string(i) + "].constant", m_DirectionalLights[i]->m_Direction);

		}
	}
	else
	{
		a_Shader->setVec3("directionalLights[" + std::to_string(a_Index) + "].ambient", m_DirectionalLights[a_Index]->m_Color);
		a_Shader->setVec3("directionalLights[" + std::to_string(a_Index) + "].diffuse", m_DirectionalLights[a_Index]->m_Diffuse);
		a_Shader->setVec3("directionalLights[" + std::to_string(a_Index) + "].specular", m_DirectionalLights[a_Index]->m_Specular);
		a_Shader->setVec3("directionalLights[" + std::to_string(a_Index) + "].constant", m_DirectionalLights[a_Index]->m_Direction);

	}
}
