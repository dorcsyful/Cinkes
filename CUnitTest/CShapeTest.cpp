#include "CppUnitTest.h"
#include <memory>
#include "../CinkesMath/CTransform.h"
#include "../CinkesMath/CUtils.h"
#include "../CinkesMath/CVector3.h"
#include "../CinkesMath/CMat3x3.h"
#include "../CinkesMath/CQuaternion.h"
#include "../CinkesCollision/CBoxShape.h"

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {

			template<>
			static std::wstring ToString<Cinkes::CVector3>(const Cinkes::CVector3& coord) {
				return L"Some string representing coordinate.";
			}

			template<>
			static std::wstring ToString<Cinkes::CMat3x3>(const Cinkes::CMat3x3& coord) {
				return L"Some string representing coordinate.";
			}

		}
	}
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Cinkes;

namespace UnitTest {

	TEST_CLASS(CShapeTest) {

		TEST_METHOD(BoxSupport)
		{
			CVector3 direction = CVector3(-4, 30, 0);
			std::unique_ptr<CBoxShape> shape = std::make_unique<CBoxShape>(CVector3(10.5, -0.2, 8));
			
			CVector3 support = shape.get()->Support(direction);
			CVector3 solution = CVector3(10.5, -0.2, 0);
			Assert::IsTrue(support == solution);
		}
	};
}