#pragma once
namespace Cinkes
{

	enum class ESPRING_TYPE
	{

	};

	class CSpring
	{
	public:
		ESPRING_TYPE GetType() { return m_Type; };
	protected:
		ESPRING_TYPE m_Type;
	};

}