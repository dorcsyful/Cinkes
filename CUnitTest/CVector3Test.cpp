#include "CppUnitTest.h"
#include "../CinkesMath/CVector3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Cinkes;

namespace UnitTest
{
	TEST_CLASS(CVector3Test)
	{		
		TEST_METHOD(EmptyConsturctor)
		{
			CVector3 example = CVector3();

			Assert::AreEqual(example.getX(), static_cast<CScalar>(0));
			Assert::AreEqual(example.getY(), static_cast<CScalar>(0));
			Assert::AreEqual(example.getY(), static_cast<CScalar>(0));
		}
		TEST_METHOD(ContructorWithValues)
		{
			CVector3 example = CVector3(1, 2, 3);

			Assert::AreEqual(example.getX(), static_cast<CScalar>(1));
			Assert::AreEqual(example.getY(), static_cast<CScalar>(2));
			Assert::AreEqual(example.getZ(), static_cast<CScalar>(3));
		}
		TEST_METHOD(CopyConstructor)
		{
			CVector3 original = CVector3(1, 2, 3);
			CVector3 copied = CVector3(4, 5, 6);

			original = copied;

			Assert::AreEqual(original.getX(), static_cast<CScalar>(4));
			Assert::AreEqual(original.getY(), static_cast<CScalar>(5));
			Assert::AreEqual(original.getZ(), static_cast<CScalar>(6));
		}
		TEST_METHOD(Getters)
		{
			CVector3 example = CVector3(1, 2, 3);
			Assert::AreEqual(example.getX(), static_cast<CScalar>(1));
			Assert::AreEqual(example.getY(), static_cast<CScalar>(2));
			Assert::AreEqual(example.getZ(), static_cast<CScalar>(3));

			Assert::AreEqual(example[0], static_cast<CScalar>(1));
			Assert::AreEqual(example[1], static_cast<CScalar>(2));
			Assert::AreEqual(example[2], static_cast<CScalar>(3));
		}
		TEST_METHOD(Setters)
		{
			CVector3 example = CVector3(1, 2, 3);
			example.setX(4);
			example.setY(5);
			example.setZ(6);

			Assert::AreEqual(example.getX(), static_cast<CScalar>(4));
			Assert::AreEqual(example.getY(), static_cast<CScalar>(5));
			Assert::AreEqual(example.getZ(), static_cast<CScalar>(6));
		}
		TEST_METHOD(AddEqual)
		{
			CVector3 original = CVector3(1, 2, 3);
			CVector3 add = CVector3(4, 5, 6);
			original += add;

			Assert::AreEqual(original.getX(), static_cast<CScalar>(5));
			Assert::AreEqual(original.getY(), static_cast<CScalar>(7));
			Assert::AreEqual(original.getZ(), static_cast<CScalar>(9));
		}
		TEST_METHOD(MinusEqual)
		{
			CVector3 original = CVector3(1, 2, 3);
			CVector3 subtract = CVector3(4, 5, 6);
			original -= subtract;

			Assert::AreEqual(original.getX(), static_cast<CScalar>(-3));
			Assert::AreEqual(original.getY(), static_cast<CScalar>(-3));
			Assert::AreEqual(original.getZ(), static_cast<CScalar>(-3));
		}
		TEST_METHOD(MultiplyEqual)
		{
			CVector3 original = CVector3(1, 2, 3);
			CVector3 multiply = CVector3(4, 5, 6);

			original *= multiply;

			Assert::AreEqual(original.getX(), static_cast<CScalar>(4));
			Assert::AreEqual(original.getY(), static_cast<CScalar>(10));
			Assert::AreEqual(original.getZ(), static_cast<CScalar>(18));
		}
		TEST_METHOD(DivideEqual)
		{
			CVector3 original = CVector3(4, 5, 6);
			CVector3 divide = CVector3(1, 2, 3);

			original /= divide;

			Assert::AreEqual(original.getX(), static_cast<CScalar>(4));
			Assert::AreEqual(original.getY(), static_cast<CScalar>(2.5));
			Assert::AreEqual(original.getZ(), static_cast<CScalar>(2));
		}
		TEST_METHOD(Add)
		{
			CVector3 Lhs = CVector3(1, 2, 3);
			CVector3 Rhs = CVector3(4, 5, 6);
			CVector3 result = Lhs + Rhs;

			Assert::AreEqual(result.getX(), static_cast<CScalar>(5));
			Assert::AreEqual(result.getY(), static_cast<CScalar>(7));
			Assert::AreEqual(result.getZ(), static_cast<CScalar>(9));
		}
		TEST_METHOD(Subtract)
		{
			CVector3 Lhs = CVector3(1, 2, 3);
			CVector3 Rhs = CVector3(4, 5, 6);
			CVector3 result = Lhs - Rhs;

			Assert::AreEqual(result.getX(), static_cast<CScalar>(-3));
			Assert::AreEqual(result.getY(), static_cast<CScalar>(-3));
			Assert::AreEqual(result.getZ(), static_cast<CScalar>(-3));
		}
		TEST_METHOD(Multiply)
		{
			CVector3 Lhs = CVector3(1, 2, 3);
			CVector3 Rhs = CVector3(4, 5, 6);
			CVector3 result = Lhs * Rhs;

			Assert::AreEqual(result.getX(), static_cast<CScalar>(4));
			Assert::AreEqual(result.getY(), static_cast<CScalar>(10));
			Assert::AreEqual(result.getZ(), static_cast<CScalar>(18));
		}
		TEST_METHOD(Division)
		{
			CVector3 Lhs = CVector3(1, 2, 3);
			CVector3 Rhs = CVector3(4, 5, 6);
			CVector3 result = Rhs / Lhs;

			Assert::AreEqual(result.getX(), static_cast<CScalar>(4));
			Assert::AreEqual(result.getY(), static_cast<CScalar>(2.5));
			Assert::AreEqual(result.getZ(), static_cast<CScalar>(2));
		}
		TEST_METHOD(Equal)
		{
			CVector3 Lhs = CVector3(1, 2, 3);
			CVector3 Rhs = CVector3(1, 2, 3);

			Assert::IsTrue(Lhs == Rhs);
		}
		TEST_METHOD(NotEqual)
		{
			CVector3 Lhs = CVector3(1, 2, 3);
			CVector3 Rhs = CVector3(4, 5, 6);
			Assert::IsTrue(Lhs != Rhs);
		}
		TEST_METHOD(Length2)
		{
			CVector3 vector = CVector3(1,2,3);
			CScalar length2 = vector.Length2();

			Assert::AreEqual(length2, static_cast<CScalar>(14));
		}
		TEST_METHOD(Length)
		{
			CVector3 vector = CVector3(1, 2, 3);
			CScalar length = vector.Length();

			Assert::IsTrue(length - static_cast<CScalar>(3.742) <= std::numeric_limits<CScalar>::epsilon());
		}
		TEST_METHOD(Normalize)
		{
			// doing it like this to reduce chance of false positive/negative due to floating point errors
			CVector3 vector = CVector3(0, 0, 5);

			vector.Normalize();
			CVector3 expected = CVector3(static_cast<CScalar>(0), static_cast<CScalar>(0), static_cast<CScalar>(1));

			Assert::IsTrue((vector - expected).Length() <= std::numeric_limits<CScalar>::epsilon());
		}
		TEST_METHOD(Dot)
		{
			CVector3 a = CVector3(1, 2, 3);
			CVector3 b = CVector3(1, 5, 7);

			CScalar dot = a.Dot(b);

			Assert::AreEqual(dot, static_cast<CScalar>(32));
		}
		TEST_METHOD(Cross)
		{
			CVector3 a = CVector3(3, -4, -1);
			CVector3 b = CVector3(-4, 1, 3);

			CVector3 cross = a.Cross(b);

			CVector3 expected = CVector3(-11, -5, -13);

			Assert::IsTrue(cross == expected);
		}
		TEST_METHOD(Lerp)
		{
			CVector3 a = CVector3();
			CVector3 b = CVector3(4, 5, 6);

			CVector3 lerp = a.Lerp(b, static_cast<CScalar>(0.5));
			CVector3 expected = CVector3(static_cast<CScalar>(2), static_cast<CScalar>(2.5), static_cast<CScalar>(3));

			Assert::AreEqual((lerp - expected).Length(), static_cast<CScalar>(0));
		}
		TEST_METHOD(AddEqualsScalar)
		{
			CVector3 vector = CVector3(1, 2, 3);
			vector += 4;
			CVector3 expected = CVector3(5, 6, 7);
			Assert::IsTrue(vector == expected);
		}
		TEST_METHOD(SubtractEqualsScalar)
		{
			CVector3 vector = CVector3(1, 2, 3);
			vector -= 4;
			CVector3 expected = CVector3(-3, -2, -1);
			Assert::IsTrue(vector == expected);
		}
		TEST_METHOD(MultiplyEqualsScalar)
		{
			CVector3 vector = CVector3(1, 2, 3);
			vector *= 4;
			CVector3 expected = CVector3(4, 8, 12);
			Assert::IsTrue(vector == expected);
		}
		TEST_METHOD(DivideEqualsScalar)
		{
			CVector3 vector = CVector3(2, 4, 6);
			vector /= 2;
			CVector3 expected = CVector3(1, 2, 3);
			Assert::IsTrue(vector == expected);
		}
		TEST_METHOD(AddScalar)
		{
			CVector3 a = CVector3(1, 2, 3);
			CVector3 b = a + 2;
			CVector3 expected = CVector3(3, 4, 5);
			Assert::IsTrue(b == expected);
		}
		TEST_METHOD(SubtractScalar)
		{
			CVector3 a = CVector3(4, 5, 6);
			CVector3 b = a - 2;
			CVector3 expected = CVector3(2, 3, 4);
			Assert::IsTrue(b == expected);
		}
		TEST_METHOD(MultiplyScalar)
		{
			CVector3 a = CVector3(1, 2, 3);
			CVector3 b = a * 2;
			CVector3 expected = CVector3(2, 4, 6);
			Assert::IsTrue(b == expected);
		}
		TEST_METHOD(DivideScalar)
		{
			CVector3 a = CVector3(2, 4, 6);
			CVector3 b = a / 2;
			CVector3 expected = CVector3(1, 2, 3);
			Assert::IsTrue(b == expected);
		}
	};
}
