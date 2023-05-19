#pragma once
#include "CTexture.h"

namespace Cinkes
{
	struct CMaterial
	{
		CMaterial() : m_Color(glm::vec3(1, 1, 1)) {}

		glm::vec3 m_Color;
		CTexture m_BaseColorTexture;
	};
}
