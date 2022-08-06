#include "CppUnitTest.h"
#include <memory>
#include <string>
#include "../CinkesMath/CUtils.h"
#include "../CinkesMath/CVector3.h"
#include "../CinkesMath/CMat3x3.h"
#include "../CinkesCollision/CBoxShape.h"
#include "../CinkesCollision/CCollisionObject.h"
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

	TEST_CLASS(CShapeTest) {
		TEST_METHOD(BoxSupport)
		{
			CVector3 direction = CVector3(-4, 30, 0);
			std::unique_ptr<CBoxShape> shape = std::make_unique<CBoxShape>(CVector3(10.5, -0.2, 8));
			
			CVector3 support = shape.get()->Support(direction);
			CVector3 solution = CVector3(-10.5, -0.2, 8);
			Assert::IsTrue(support == solution);
		}
		TEST_METHOD(BoxAABB)
		{
			std::shared_ptr<CBoxShape> shape = std::make_shared<CBoxShape>(1,0.2,13);
			std::unique_ptr<CCollisionObject> object = std::make_unique<CCollisionObject>();
			CVector3 min, max;
			object.get()->SetCollisionShape(shape);
			object.get()->GetCollisionShape().get()->CreateAABB(object.get()->GetTransform().getBasis(), min, max);
			Assert::AreEqual(CVector3(-1, -0.2, -13), min);
			Assert::AreEqual(CVector3(1, 0.2, 13), max);

		}
	};
}