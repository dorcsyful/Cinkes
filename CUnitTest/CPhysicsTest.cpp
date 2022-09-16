#include "CppUnitTest.h"
#include <memory>
#include <string>
#include <CVector3.h>
#include <CRigidBody.h>
#include <CBoxShape.h>
#include <CGravitiyGenerator.h>
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

		TEST_METHOD(GravityForceGenerator) {
			CGravityGenerator gravity = CGravityGenerator();

			std::shared_ptr<CBoxShape> box = std::make_shared<CBoxShape>(2.2, 3.91, 4);
			std::shared_ptr<CRigidBody> rb1 = std::make_shared<CRigidBody>();
			rb1->SetMass(2.5);
			rb1->SetCollisionShape(box);
			rb1->SetTransform(CTransform(CVector3(2.f, 3.5f, 6.1f)));
			gravity.UpdateForce(rb1.get());
			CVector3 actual = rb1->GetForce();
			CVector3 expected = CVector3(0, static_cast<CScalar>(-24.525), 0);
			Assert::IsTrue((expected - actual).Length() < CEPSILON);
		}

		TEST_METHOD(RBAddForce) {
			std::shared_ptr<CBoxShape> box = std::make_shared<CBoxShape>(2.2, 3.91, 4);
			std::shared_ptr<CRigidBody> rb1 = std::make_shared<CRigidBody>();
			rb1->SetMass(2.5);
			rb1->SetCollisionShape(box);
			rb1->SetLinearVelocity(CVector3(4.1, 0, 0));
			rb1->SetTransform(CTransform(CVector3(2.f, 3.5f, 6.1f)));
			rb1->AddForce(CVector3(0, -24.525, 0));
			rb1->Integrate(0.2f);
			CVector3 actual  = rb1->GetLinearVelocity();
			CVector3 expected = CVector3(4.1,-1.962,0);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(RBAddForceAtPoint) {
			std::shared_ptr<CBoxShape> box = std::make_shared<CBoxShape>(2.2, 3.91, 4);
			std::shared_ptr<CRigidBody> rb1 = std::make_shared<CRigidBody>();
			rb1->SetMass(2.5);
			rb1->SetCollisionShape(box);
			rb1->SetTransform(CTransform(CVector3(2.f, 3.5f, 6.1f)));
			rb1->AddForceAtPoint(CVector3(0, 2.6, 0), CVector3(-0.2f, -0.41f, 2.1));
			CVector3 expected = CVector3(10.4, 0, -5.72);
			CVector3 actual = rb1->GetTorque();

			Assert::AreEqual(expected, actual);
		}
	};
}