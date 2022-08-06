#include "CppUnitTest.h"
#include "../CinkesMath/CTransform.h"
#include "../CinkesMath/CUtils.h"
#include "../CinkesMath/CVector3.h"
#include "../CinkesMath/CMat3x3.h"
#include "../CinkesMath/CQuaternion.h"

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

namespace UnitTest
{
	TEST_CLASS(CTransformTest)
	{
		TEST_METHOD(EmptyConsturctor) {
			CTransform example = CTransform();

			Assert::IsTrue(example.getBasis() == CMat3x3::GetIdentity());
			Assert::IsTrue(example.getOrigin() == CVector3());
		}

		TEST_METHOD(ConstructorWithValues)
		{
			CTransform example = CTransform(CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9), CVector3(10, 11, 12));

			Assert::IsTrue(example.getBasis() == CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9));
			Assert::IsTrue(example.getOrigin() == CVector3(10, 11, 12));
		}

		TEST_METHOD(OperatorMultiplyEqual)
		{
			CTransform base = CTransform(CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9), CVector3(10, 11, 12));
			CTransform multiplier = CTransform(CMat3x3(2, 2, 3, 3, 4, 4, 6, 6, 7), CVector3(8, 9, 9));

			base *= multiplier;

			Assert::IsTrue(base.getBasis() == CMat3x3(26, 28, 32, 59, 64, 74, 92, 100, 116));
			Assert::IsTrue(base.getOrigin() == CVector3(63, 142, 221));
		}

		TEST_METHOD(OperatorMultiply)
		{
			CTransform base = CTransform(CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9), CVector3(10, 11, 12));
			CTransform multiplier = CTransform(CMat3x3(2, 2, 3, 3, 4, 4, 6, 6, 7), CVector3(8, 9, 9));
			CTransform result;
			result = base * multiplier;

			Assert::IsTrue(result.getBasis() == CMat3x3(26, 28, 32, 59, 64, 74, 92, 100, 116));
			Assert::IsTrue(result.getOrigin() == CVector3(63, 142, 221));
		}

		TEST_METHOD(OperatorAssignment)
		{
			CTransform base = CTransform(CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9), CVector3(10, 11, 12));
			CTransform result = CTransform(CMat3x3(2, 2, 3, 3, 4, 4, 6, 6, 7), CVector3(8, 9, 9));

			result = base;

			Assert::IsTrue(result.getBasis() == CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9));
			Assert::IsTrue(result.getOrigin() == CVector3(10, 11, 12));
		}

		TEST_METHOD(OperatorEquals)
		{
			CTransform base = CTransform(CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9), CVector3(10, 11, 12));
			CTransform comparison = CTransform(CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9), CVector3(10, 11, 12));

			Assert::IsTrue(base == comparison);
		}

		TEST_METHOD(OperatorNotEqual)
		{
			CTransform base = CTransform(CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9), CVector3(10, 11, 12));
			CTransform comparison = CTransform(CMat3x3(20, 2, 3, 4, 5, 6, 7, 8, 9), CVector3(10, 13, 12));

			Assert::IsTrue(base != comparison);
		}

		TEST_METHOD(OperatorMultiplyFunction)
		{
			CTransform base = CTransform(CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9), CVector3(10, 11, 12));
			CTransform multiplier = CTransform(CMat3x3(2, 2, 3, 3, 4, 4, 6, 6, 7), CVector3(8, 9, 9));
			CTransform result;
			result.Multiply(base, multiplier);

			Assert::IsTrue(result.getBasis() == CMat3x3(26, 28, 32, 59, 64, 74, 92, 100, 116));
			Assert::IsTrue(result.getOrigin() == CVector3(63, 142, 221));
		}

		TEST_METHOD(Getters)
		{
			CTransform base = CTransform(CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9), CVector3(10, 11, 12));

			Assert::IsTrue(base.getBasis() == CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9));
			Assert::IsTrue(base.getOrigin() == CVector3(10, 11, 12));
		}

		TEST_METHOD(Setters)
		{
			CTransform base = CTransform(CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9), CVector3(10, 11, 12));
			base.setBasis(CMat3x3(13, 14, 15, 16, 17, 18, 19, 20, 21));
			base.setOrigin(CVector3(22, 23, 24));

			Assert::IsTrue(base.getBasis() == CMat3x3(13, 14, 15, 16, 17, 18, 19, 20, 21));
			Assert::IsTrue(base.getOrigin() == CVector3(22, 23, 24));
		}

		TEST_METHOD(Identity)
		{
			CTransform base = CTransform(CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9), CVector3(10, 11, 12));
			base.setIdentity();

			Assert::IsTrue(base.getBasis() == CMat3x3::GetIdentity());
			Assert::IsTrue(base.getOrigin() == CVector3(0, 0, 0));
		}

		TEST_METHOD(Inverse)
		{
			CTransform base = CTransform(CMat3x3(1, 2, 3, 0, 1, 4, 5, 6, 0),CVector3(2, 3, 4));
			CTransform inversed = base.Inverse();

			Assert::IsTrue(inversed.getBasis() == CMat3x3(1, 0, 5, 2, 1, 6, 3, 4, 0));
			Assert::IsTrue(inversed.getOrigin() == CVector3(-22,-31,-18));
		}
	};
}