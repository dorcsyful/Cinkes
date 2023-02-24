#include "CppUnitTest.h"
#include <memory>
#include <string>
#include <CVector3.h>
#include <CBoxShape.h>
#include <CGJKAlgorithm.h>
#include <CEPA.h>
#include "CBoxBoxCollision.h"
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

	TEST_CLASS(CCollisionAlgorithmTest) {
		TEST_METHOD(GJKBoolFalse)
		{

			std::shared_ptr<CBoxShape> shape = std::make_shared<CBoxShape>(2, 2, 3);
			std::shared_ptr<CBoxShape> shape1 = std::make_shared<CBoxShape>(3, 2, 3);
			std::shared_ptr<CCollisionObject> object1 = std::make_shared<CCollisionObject>(CVector3(5, 7, 2), shape);

			CTransform transform = CTransform(CMat3x3(0.7071068f, -0.7071068f, 0.0000000,
				0.7071068f, 0.7071068f, 0.0000000,
				0.0000000, 0.0000000, 1.0000000), CVector3(5, 13, 2));
			std::shared_ptr<CCollisionObject> object2 = std::make_shared<CCollisionObject>(transform, shape1);

			CSimplex simplex;
			std::shared_ptr<CInternalContactInfo> info = std::make_shared<CInternalContactInfo>();
			Assert::IsFalse(CGJKAlgorithm::Algorithm(object1.get(), object2.get(), simplex));
		}
		TEST_METHOD(GJKBoolTrue)
		{
			std::shared_ptr<CBoxShape> shape1 = std::make_shared<CBoxShape>(2, 3, 3);
			std::shared_ptr<CCollisionObject> object1 = std::make_shared<CCollisionObject>(CVector3(2, 7, 0), shape1);


			CTransform transform = CTransform(CMat3x3(0.7071068f, -0.7071068f, 0.f,
				0.7071068f, 0.7071068f, 0.f,
				0.f, 0.f, 1.f), CVector3(5, 13, 2));
			std::shared_ptr<CBoxShape> shape2 = std::make_shared<CBoxShape>(3, 4, 3);
			std::shared_ptr<CCollisionObject> object2 = std::make_shared<CCollisionObject>(transform, shape2);

			CSimplex simplex;
			std::shared_ptr<CInternalContactInfo> info = std::make_shared<CInternalContactInfo>();
			Assert::IsTrue(CGJKAlgorithm::Algorithm(object1.get(), object2.get(), simplex));
		}
		TEST_METHOD(EPANormal) {
			CGJKAlgorithm gjk;
			CEPA epa;
			CTransform transform = CTransform(CMat3x3(0.7071068f, -0.7071068f, 0.f,
				0.7071068f, 0.7071068f, 0.f,
				0.f, 0.f, 1.f), CVector3(5, 13, 2));
			std::shared_ptr<CBoxShape> shape1 = std::make_shared<CBoxShape>(2, 3, 3);
			std::shared_ptr<CBoxShape> shape2 = std::make_shared<CBoxShape>(3, 4, 3);
			std::shared_ptr<CCollisionObject> object1 = std::make_shared<CCollisionObject>(CVector3(3, 7, 0), shape2);
			std::shared_ptr<CCollisionObject> object2 = std::make_shared<CCollisionObject>(transform, shape1);
			CSimplex simplex;
			std::shared_ptr<CInternalContactInfo> info = std::make_shared<CInternalContactInfo>();
			bool algo = gjk.Algorithm(object1.get(), object2.get(), simplex);
			if (algo) {
				info->m_First = object1;
				object1->SetHasContact(info.get());
				object2->SetHasContact(info.get());
				info->m_Second = object2;
	
				epa.Algorithm(info.get(), simplex);
			}
		

			Assert::IsTrue(info->m_Normal == CVector3(0, 1, 0) || info->m_Normal == CVector3(0,-1,0));
		}
		TEST_METHOD(EPAPenetrationDepth) {
			CGJKAlgorithm gjk;
			CEPA epa;
			CTransform transform = CTransform(CMat3x3(0.7071068f, -0.7071068f, 0.0000000,
			0.7071068f, 0.7071068f, 0.0000000,
			0.0000000, 0.0000000, 1.0000000), CVector3(5, 13, 2));
			std::shared_ptr<CBoxShape> shape1 = std::make_shared<CBoxShape>(5, 5, 5);
			std::shared_ptr<CBoxShape> shape2 = std::make_shared<CBoxShape>(5, 5, 5);
			std::shared_ptr<CCollisionObject> object1 = std::make_shared<CCollisionObject>(CVector3(2, 7, 2), shape1);
			std::shared_ptr<CCollisionObject> object2 = std::make_shared<CCollisionObject>(transform, shape2);
			CSimplex simplex;
			std::shared_ptr<CInternalContactInfo> info = std::make_shared<CInternalContactInfo>();
			bool algo =CGJKAlgorithm::Algorithm(object1.get(), object2.get(), simplex);
			if(algo)
			{
			info->m_First = object1;
			object1->SetHasContact(info.get());
			object2->SetHasContact(info.get());
			info->m_Second = object2;
			epa.Algorithm(info.get(), simplex);				
			}

			CScalar depth = info->m_PenetrationDepth;
			Assert::AreEqual(6.07f, depth, 0.1f);
		}
		TEST_METHOD(ContactPointTest) {
			CEPA epa;
			CBoxBoxCollision contact;
			CTransform transform = CTransform(CMat3x3(0.7071068f, -0.7071068f, 0.0000000,
				0.7071068f, 0.7071068f, 0.0000000,
				0.0000000, 0.0000000, 1.0000000), CVector3(5, 13, 2));
			std::shared_ptr<CBoxShape> shape1 = std::make_shared<CBoxShape>(5, 5, 5);
			std::shared_ptr<CBoxShape> shape2 = std::make_shared<CBoxShape>(5, 5, 5);
			std::shared_ptr<CCollisionObject> object1 = std::make_shared<CCollisionObject>(CVector3(2.f, 7, 2), shape1);
			std::shared_ptr<CCollisionObject> object2 = std::make_shared<CCollisionObject>(transform, shape2);
			CSimplex simplex;
			std::shared_ptr<CInternalContactInfo> info = std::make_shared<CInternalContactInfo>();
			CGJKAlgorithm::Algorithm(object1.get(), object2.get(), simplex);
			info->m_First = object1;
			object1->SetHasContact(info.get());
			object2->SetHasContact(info.get());
			info->m_Second = object2;
			epa.Run(info.get(), simplex);
			contact.Run(info.get());
			size_t test = info->m_RelativeContactPosition[1].size();
			size_t expected = 2;

			const wchar_t* pwcs_name = L"";

			//Correct values:
			//A: 
			Assert::AreEqual(expected,test,pwcs_name);
		}
	};
}