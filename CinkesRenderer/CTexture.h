#pragma once
#include <glad/glad.h>
#include "CShader.h"
namespace Cinkes
{
	class CTexture
	{
	public:
		CTexture() = default;
		~CTexture() = default;

		bool CreateTexture(CShader* a_Shader, const std::string& a_Path);

		GLuint m_Texture;
	};
};
