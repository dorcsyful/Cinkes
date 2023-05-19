#pragma once
#include <glad/glad.h>
#include "CShader.h"
namespace Cinkes
{
	class CTexture
	{
	public:
		CTexture() : isValid(0) {}
		~CTexture() = default;

		bool CreateTexture(const std::string& a_Path);
		glm::uint isValid;
		GLuint m_Texture{};
	};
};
