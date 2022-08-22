#include "CppUnitTest.h"
#include <memory>
#include <string>
#include "CContactPointCalculator.h"
#include <CVector3.h>
#include <CBoxShape.h>
#include <CGJKAlgorithm.h>
#include <CEPA.h>
#include <CUtils.h>
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

	TEST_CLASS(CAlgorithmTest) {
		TEST_METHOD(GJKBoolFalse)
		{
			CGJKAlgorithm gjk;
			std::shared_ptr<CBoxShape> shape = std::make_shared<CBoxShape>(2, 10.1, 3);
			std::shared_ptr<CCollisionObject> object1 = std::make_shared<CCollisionObject>(CVector3(1.5, 10, 2.5), shape);
			std::shared_ptr<CCollisionObject> object2 = std::make_shared<CCollisionObject>(CVector3(5, -11, 3), shape);
			Assert::IsFalse(gjk.Algorithm(object1.get(), object2.get(), CSimplex()));
		}
		TEST_METHOD(GJKBoolTrue)
		{
			CGJKAlgorithm gjk;
			std::shared_ptr<CBoxShape> shape = std::make_shared<CBoxShape>(2, 10.1, 3);
			std::shared_ptr<CCollisionObject> object1 = std::make_shared<CCollisionObject>(CVector3(4.5, 10, 2.5), shape);
			std::shared_ptr<CCollisionObject> object2 = std::make_shared<CCollisionObject>(CVector3(5, -9, 3), shape);
			Assert::IsTrue(gjk.Algorithm(object1.get(), object2.get(), CSimplex()));
		}
		TEST_METHOD(EPANormal) {
			CGJKAlgorithm gjk;
			CEPA epa;

			std::shared_ptr<CBoxShape> shape = std::make_shared<CBoxShape>(2, 2, 3);
			std::shared_ptr<CBoxShape> shape1 = std::make_shared<CBoxShape>(3, 2, 3);
			std::shared_ptr<CCollisionObject> object1 = std::make_shared<CCollisionObject>(CVector3(5,7,2), shape);

			CTransform transform = CTransform(CMat3x3(/*1.0000000, 0.0000000, 0.0000000,
			0.0000000, 0.7071068, -0.7071068,
			0.0000000, 0.7071068, 0.7071068*/), CVector3(5, 6, 2));
			std::shared_ptr<CCollisionObject> object2 = std::make_shared<CCollisionObject>(transform, shape1);

			CSimplex simplex;
			std::shared_ptr<CContactInfo> info = std::make_shared<CContactInfo>();
			gjk.Algorithm(object1.get(), object2.get(), simplex);

			info->m_First = object1;
			info->m_Second = object2;

			epa.Algorithm(info, simplex);

			Assert::IsTrue(info.get()->m_Normal == CVector3(0, 1, 0) || info.get()->m_Normal == CVector3(0,-1,0));
		}
		TEST_METHOD(EPAPenetrationDepth) {
			CGJKAlgorithm gjk;
			CEPA epa;
			CTransform transform = CTransform(CMat3x3(0.7071068, -0.7071068, 0.0000000,
			0.7071068, 0.7071068, 0.0000000,
			0.0000000, 0.0000000, 1.0000000), CVector3(5, 13, 2));
			std::shared_ptr<CBoxShape> shape1 = std::make_shared<CBoxShape>(5, 5, 5);
			std::shared_ptr<CBoxShape> shape2 = std::make_shared<CBoxShape>(5, 5, 5);
			std::shared_ptr<CCollisionObject> object1 = std::make_shared<CCollisionObject>(CVector3(5, 7, 2), shape1);
			std::shared_ptr<CCollisionObject> object2 = std::make_shared<CCollisionObject>(transform, shape2);
			CSimplex simplex;
			std::shared_ptr<CContactInfo> info = std::make_shared<CContactInfo>();
			gjk.Algorithm(object1.get(), object2.get(), simplex);
			info->m_First = object1;
			object1->SetHasContact(info.get());
			object2->SetHasContact(info.get());
			info->m_Second = object2;
			epa.Algorithm(info, simplex);
			CScalar depth = info.get()->m_PenetrationDepth;
			Assert::AreEqual(6.07f, depth, 0.1f);
		}
		TEST_METHOD(ContactPointTest) {
			CGJKAlgorithm gjk;
			CEPA epa;
			CContactPointCalculator contact;
			CTransform transform = CTransform(CMat3x3(0.7071068, -0.7071068, 0.0000000,
				0.7071068, 0.7071068, 0.0000000,
				0.0000000, 0.0000000, 1.0000000), CVector3(5, 13, 2));
			std::shared_ptr<CBoxShape> shape1 = std::make_shared<CBoxShape>(5, 5, 5);
			std::shared_ptr<CBoxShape> shape2 = std::make_shared<CBoxShape>(5, 5, 5);
			std::shared_ptr<CCollisionObject> object1 = std::make_shared<CCollisionObject>(CVector3(5, 7, 2), shape1);
			std::shared_ptr<CCollisionObject> object2 = std::make_shared<CCollisionObject>(transform, shape2);
			CSimplex simplex;
			std::shared_ptr<CContactInfo> info = std::make_shared<CContactInfo>();
			gjk.Algorithm(object1.get(), object2.get(), simplex);
			info->m_First = object1;
			object1->SetHasContact(info.get());
			object2->SetHasContact(info.get());
			info->m_Second = object2;
			epa.Algorithm(info, simplex);
			contact.GetPoints(info.get());
			CVector3 test = info.get()->m_ContactPoints[0];
			CVector3 expected = CVector3(5, 7.24, 2);
			Assert::IsTrue(test == expected);
		}
	};
}