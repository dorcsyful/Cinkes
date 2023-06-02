#pragma once
#include <memory>

#include "CLightShape.h"

namespace Cinkes
{

	class CLightHandler
	{
	public:
		CLightHandler() = default;
		~CLightHandler() = default;

		void AddPointLight(const std::shared_ptr<Cinkes::CPointLightShape>& a_PointLight);
		void AddDirectionalLight(const std::shared_ptr<CDirectionalLightShape>& a_DirectionalLight);

		//Sends necessary data to the shader. Specify a_Index if you only need to use a point light at a specfic index, leave it if you want to add every point light currently in the scene
		void AssignPointLightData(std::shared_ptr<CShader>& a_Shader, int a_Index = -1);
		//Sends necessary data to the shader. Specify a_Index if you only need to use a directional light at a specfic index, leave it if you want to add every directional light currently in the scene
		void AssignDirectionalLightData(std::shared_ptr<CShader>& a_Shader, int a_Index = -1);

		std::vector<std::shared_ptr<CPointLightShape>> m_PointLights;
		std::vector<std::shared_ptr<CDirectionalLightShape>> m_DirectionalLights;
	};

}