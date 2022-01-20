#pragma once

namespace Cinkes
{
	class CForceGenerator
	{
	public:
		CForceGenerator() = default;
		virtual ~CForceGenerator() = default;

		virtual void UpdateForce() {}
	};
}
