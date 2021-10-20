#pragma once
#include <vector>

#include "../CinkesMath/CVector3.h"

namespace Cinkes
{

	struct CVertex
	{
		CVector3 m_Position;
		unsigned int m_Index;
		std::vector<unsigned int> m_Adjacent;
	};

}