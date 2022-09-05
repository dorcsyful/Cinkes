#include "CppUnitTest.h"
#include <memory>
#include <string>
#include <CVector3.h>

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {

			template<>
			static std::wstring ToString<Cinkes::CVector3>(const Cinkes::CVector3& coord) {
				std::wstringstream cls;
				cls << coord[0] << "," << coord[1] << "," << coord[2];
				std::wstring total = cls.str();
				return total;
			}
		}
	}
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Cinkes;

namespace UnitTest {

	TEST_CLASS(CPhysicsTest) {
	};
}