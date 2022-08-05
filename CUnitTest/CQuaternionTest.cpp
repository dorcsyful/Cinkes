#include "CppUnitTest.h"
#include "../CinkesMath/CUtils.h"
#include "../CinkesMath/CQuaternion.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Cinkes;

namespace UnitTest
{
	TEST_CLASS(CQuaternionTest)
	{
	public:

		TEST_METHOD(EmptyConsturctor)
		{
			CQuaternion example = CQuaternion();

			Assert::AreEqual(example.getX(), static_cast<CScalar>(0));
			Assert::AreEqual(example.getY(), static_cast<CScalar>(0));
			Assert::AreEqual(example.getZ(), static_cast<CScalar>(0));
			Assert::AreEqual(example.getW(), static_cast<CScalar>(1));
		}

		TEST_METHOD(ConstructorWithValues)
		{
			CQuaternion example = CQuaternion(1, 2, 3, 4);

			Assert::AreEqual(example.getX(), static_cast<CScalar>(1));
			Assert::AreEqual(example.getY(), static_cast<CScalar>(2));
			Assert::AreEqual(example.getZ(), static_cast<CScalar>(3));
			Assert::AreEqual(example.getW(), static_cast<CScalar>(4));
		}

		TEST_METHOD(CopyFunction)
		{
			CQuaternion base = CQuaternion(1, 2, 3, 4);
			CQuaternion copy = CQuaternion(base);

			Assert::AreEqual(copy.getX(), static_cast<CScalar>(1));
			Assert::AreEqual(copy.getY(), static_cast<CScalar>(2));
			Assert::AreEqual(copy.getZ(), static_cast<CScalar>(3));
			Assert::AreEqual(copy.getW(), static_cast<CScalar>(4));
		}

		TEST_METHOD(AngleAxis)
		{
			CQuaternion base = CQuaternion(CVector3(1, 0, 0), CScalar(3.14));

			CScalar x = base.getX() - CScalar(0.9999997);
			CScalar y = base.getY() - 0;
			CScalar z = base.getZ() - CScalar(0);
			CScalar w = base.getW() - CScalar(0.0007963);

			Assert::IsTrue(x < CScalar(0.1));
			Assert::IsTrue(y < CScalar(0.1));
			Assert::IsTrue(z < CScalar(0.1));
			Assert::IsTrue(w < CScalar(0.1));
		}

		TEST_METHOD(Getters)
		{
			CQuaternion example = CQuaternion(1, 2, 3, 4);
			Assert::AreEqual(example.getX(), static_cast<CScalar>(1));
			Assert::AreEqual(example.getY(), static_cast<CScalar>(2));
			Assert::AreEqual(example.getZ(), static_cast<CScalar>(3));
			Assert::AreEqual(example.getW(), static_cast<CScalar>(4));
		}

		TEST_METHOD(Setters)
		{
			CQuaternion base = CQuaternion(1, 2, 3, 4);
			base.setX(5);
			base.setY(6);
			base.setZ(7);
			base.setW(8);

			Assert::AreEqual(base.getX(), static_cast<CScalar>(5));
			Assert::AreEqual(base.getY(), static_cast<CScalar>(6));
			Assert::AreEqual(base.getZ(), static_cast<CScalar>(7));
			Assert::AreEqual(base.getW(), static_cast<CScalar>(8));
		}

		TEST_METHOD(YawPitchRoll)
		{
			CQuaternion base = CQuaternion(0, CScalar(1.6), CScalar(3.14));

			CScalar x = base.getX() - CScalar(0.7173559);
			CScalar y = base.getY() - CScalar(0.6967065);
			CScalar z = base.getZ() - CScalar(0.0005712);
			CScalar w = base.getW() - CScalar(0.0005548);

			Assert::IsTrue(x < CScalar(0.1));
			Assert::IsTrue(y < CScalar(0.1));
			Assert::IsTrue(z < CScalar(0.1));
			Assert::IsTrue(w < CScalar(0.1));
		}

		TEST_METHOD(SetAngleAxis)
		{
			CQuaternion base = CQuaternion();
			base.SetFromAngleAxis(CVector3(1, 0, 0), CScalar(3.14));

			CScalar x = base.getX() - CScalar(0.9999997);
			CScalar y = base.getY() - 0;
			CScalar z = base.getZ() - CScalar(0);
			CScalar w = base.getW() - CScalar(0.0007963);

			Assert::IsTrue(x < CScalar(0.1));
			Assert::IsTrue(y < CScalar(0.1));
			Assert::IsTrue(z < CScalar(0.1));
			Assert::IsTrue(w < CScalar(0.1));
		}

		TEST_METHOD(SetFromEuler)
		{
			CQuaternion base;
			base.SetFromEuler(0, CScalar(1.6), CScalar(3.14));

			CScalar x = base.getX() - CScalar(0.696706709346738);
			CScalar y = base.getY() - CScalar(0.7173560908999379);
			CScalar z = base.getZ() - CScalar(4.3925392028473336e-17);
			CScalar w = base.getW() - CScalar(4.26609820772984e-17);

			Assert::IsTrue(x < CScalar(0.1));
			Assert::IsTrue(y < CScalar(0.1));
			Assert::IsTrue(z < CScalar(0.1));
			Assert::IsTrue(w < CScalar(0.1));
		}

		TEST_METHOD(GetEuler)
		{
			CQuaternion base = CQuaternion(0.696706709346738f, 0.7173560908999379f, 4.3925392028473336e-17f, 4.26609820772984e-17f);
			CScalar x, y, z;
			base.GetEuler(x ,y, z);

			Assert::IsTrue((x - CScalar(1.6)) < CScalar(0.1));
			Assert::IsTrue((y - 0) < CScalar(0.1));
			Assert::IsTrue((z - CScalar(3.14))  < CScalar(0.1));
		}

		TEST_METHOD(AddEqual)
		{
			CQuaternion a = CQuaternion(1, 2, 3, 4);
			CQuaternion b = CQuaternion(5, 6, 7, 8);

			a += b;

			Assert::AreEqual(a.getX(), static_cast<CScalar>(6));
			Assert::AreEqual(a.getY(), static_cast<CScalar>(8));
			Assert::AreEqual(a.getZ(), static_cast<CScalar>(10));
			Assert::AreEqual(a.getW(), static_cast<CScalar>(12));
		}

		TEST_METHOD(Addition)
		{
			CQuaternion a = CQuaternion(1, 2, 3, 4);
			CQuaternion b = CQuaternion(5, 6, 7, 8);

			 CQuaternion c = a + b;

			Assert::AreEqual(c.getX(), static_cast<CScalar>(6));
			Assert::AreEqual(c.getY(), static_cast<CScalar>(8));
			Assert::AreEqual(c.getZ(), static_cast<CScalar>(10));
			Assert::AreEqual(c.getW(), static_cast<CScalar>(12));
		}

		TEST_METHOD(SubEqual)
		{
			CQuaternion a = CQuaternion(1, 2, 3, 4);
			CQuaternion b = CQuaternion(5, 2, 8, 5);

			b -= a;

			Assert::AreEqual(b.getX(), static_cast<CScalar>(4));
			Assert::AreEqual(b.getY(), static_cast<CScalar>(0));
			Assert::AreEqual(b.getZ(), static_cast<CScalar>(5));
			Assert::AreEqual(b.getW(), static_cast<CScalar>(1));
		}

		TEST_METHOD(Substract)
		{
			CQuaternion a = CQuaternion(1, 2, 3, 4);
			CQuaternion b = CQuaternion(5, 2, 8, 5);

			CQuaternion c = b - a;

			Assert::AreEqual(c.getX(), static_cast<CScalar>(4));
			Assert::AreEqual(c.getY(), static_cast<CScalar>(0));
			Assert::AreEqual(c.getZ(), static_cast<CScalar>(5));
			Assert::AreEqual(c.getW(), static_cast<CScalar>(1));
		}

		TEST_METHOD(MultiplyWithQuaternion)
		{
			CQuaternion a = CQuaternion(2, 0, 1, 0);
			CQuaternion b = CQuaternion(3, 1, 0, 0);

			CQuaternion c = a * b;

			Assert::AreEqual(c.getX(), static_cast<CScalar>(-1));
			Assert::AreEqual(c.getY(), static_cast<CScalar>(3));
			Assert::AreEqual(c.getZ(), static_cast<CScalar>(2));
			Assert::AreEqual(c.getW(), static_cast<CScalar>(-6));

		}

		TEST_METHOD(MultiplyWithQuaternionEqual)
		{
			CQuaternion a = CQuaternion(2, 0, 1, 0);
			CQuaternion b = CQuaternion(3, 1, 0, 0);

			a *= b;

			Assert::AreEqual(a.getX(), static_cast<CScalar>(-1));
			Assert::AreEqual(a.getY(), static_cast<CScalar>(3));
			Assert::AreEqual(a.getZ(), static_cast<CScalar>(2));
			Assert::AreEqual(a.getW(), static_cast<CScalar>(-6));
		}

		TEST_METHOD(MultiplyWithScalarEqual)
		{
			CQuaternion b = CQuaternion(3, 1, 0, 0);

			b *= 3;

			Assert::AreEqual(b.getX(), static_cast<CScalar>(9));
			Assert::AreEqual(b.getY(), static_cast<CScalar>(3));
			Assert::AreEqual(b.getZ(), static_cast<CScalar>(0));
			Assert::AreEqual(b.getW(), static_cast<CScalar>(0));
		}

		TEST_METHOD(MultiplyWithScalar)
		{
			CQuaternion b = CQuaternion(3, 1, 0, 0);

			CQuaternion c = b * 3;

			Assert::AreEqual(c.getX(), static_cast<CScalar>(9));
			Assert::AreEqual(c.getY(), static_cast<CScalar>(3));
			Assert::AreEqual(c.getZ(), static_cast<CScalar>(0));
			Assert::AreEqual(c.getW(), static_cast<CScalar>(0));
		}

		TEST_METHOD(DivideByScalar)
		{
			CQuaternion b = CQuaternion(3, 9, 0, 0);

			CQuaternion c = b / 3;

			Assert::AreEqual(c.getX(), static_cast<CScalar>(1));
			Assert::AreEqual(c.getY(), static_cast<CScalar>(3));
			Assert::AreEqual(c.getZ(), static_cast<CScalar>(0));
			Assert::AreEqual(c.getW(), static_cast<CScalar>(0));
		}

		TEST_METHOD(Brackets)
		{
			CQuaternion example = CQuaternion(1, 2, 3, 4);

			Assert::AreEqual(example[0], static_cast<CScalar>(1));
			Assert::AreEqual(example[1], static_cast<CScalar>(2));
			Assert::AreEqual(example[2], static_cast<CScalar>(3));
			Assert::AreEqual(example[3], static_cast<CScalar>(4));

		}

		TEST_METHOD(Dot)
		{
			CQuaternion example = CQuaternion(CScalar(-2), CScalar(3), CScalar(2), 1);
			CQuaternion example2 = CQuaternion(CScalar(2), CScalar(0), CScalar(1), CScalar(0));
			CScalar dot = example.Dot(example2);

			Assert::AreEqual(dot, -CScalar(2));
		}

		TEST_METHOD(LengthSquared)
		{
			CQuaternion test = CQuaternion(1,2,3,4);
			CScalar length2 = test.Length2();

			Assert::IsTrue((length2 - 29.997529) < 0.1);
		}

		TEST_METHOD(LengthRegular)
		{
			CQuaternion test = CQuaternion(1, 2, 3, 4);

			Assert::IsTrue((test.Length() - 5.477) < 0.1);
		}

		TEST_METHOD(AngleBetween)
		{
			CQuaternion q1 = CQuaternion(0,0,0,1);
			CQuaternion q2 = CQuaternion(0.5,0.5,0.5,0.5);
			CScalar angle = q1.GetAngleBetween(q2);

			Assert::IsTrue((angle - CScalar(2.094)) < CScalar(0.1));
		}

		TEST_METHOD(Angle)
		{
			CQuaternion example = CQuaternion(0.5, 0.5, 0.5, 0.5);
			CScalar angle = example.GetAngle();

			Assert::IsTrue((angle - 2.0943951023931953) < 0.1);
		}

		TEST_METHOD(Axis)
		{
			CQuaternion example = CQuaternion(0.5, 0.5, 0.5, 0.5);
			CVector3 axis = example.GetAxis();

			bool x = (axis.getX() - 0.5773502691896258) < 0.1;
			bool y = (axis.getY() - 0.5773502691896258) < 0.1;
			bool z = (axis.getZ() - 0.5773502691896258) < 0.1;

			Assert::IsTrue(x && y && z);
		}

		TEST_METHOD(Inverse)
		{
			CQuaternion example = CQuaternion(1, 2, 3, 4);
			CQuaternion inverse = example.GetInverse();

			bool x = (inverse.getX() - 0.033) < 0.1;
			bool y = (inverse.getY() - 0.067) < 0.1;
			bool z = (inverse.getZ() - 0.1) < 0.1;
			bool w = (inverse.getW() - 0.133) < 0.1;

			Assert::IsTrue(x && y && z && w);
		}

		TEST_METHOD(Slerp)
		{
			CQuaternion q1 = CQuaternion(0, 0, 0, 1);
			CQuaternion q2 = CQuaternion(0.5, 0.5, 0.5, 0.5);
			CScalar theta = 0.75;
			CQuaternion q3 = q1.Slerp(q2, theta);

			bool x = (q3.getX() - 0.4082482904638631) < 0.1;
			bool y = (q3.getY() - 0.4082482904638631) < 0.1;
			bool z = (q3.getZ() - 0.4082482904638631) < 0.1;
			bool w = (q3.getW() - 0.7071067811865477) < 0.1;

			Assert::IsTrue(x && y && z && w);
		}

		TEST_METHOD(Identity)
		{
			CQuaternion example = CQuaternion::GetIdentity();

			Assert::AreEqual(example.getX(), CScalar(0));
			Assert::AreEqual(example.getY(), CScalar(0));
			Assert::AreEqual(example.getZ(), CScalar(0));
			Assert::AreEqual(example.getW(), CScalar(1));
		}

		TEST_METHOD(QuatEqualsQuat)
		{
			CQuaternion q1 = CQuaternion(1, 2, 3, 4);
			CQuaternion q2 = CQuaternion(1, 2, 3, 4);

			Assert::IsTrue(q1 == q2);
		}

		TEST_METHOD(QuatNotEqualQuat)
		{
			CQuaternion q1 = CQuaternion(1, 2, 3, 4);
			CQuaternion q2 = CQuaternion(5, 6, 7, 8);

			Assert::IsTrue(q1 != q2);
		}

		TEST_METHOD(Assignment)
		{
			CQuaternion q1 = CQuaternion(1, 2, 3, 4);
			CQuaternion q2 = CQuaternion(5, 6, 7, 8);

			q1 = q2;

			Assert::AreEqual(q1.getX(), CScalar(5));
			Assert::AreEqual(q1.getY(), CScalar(6));
			Assert::AreEqual(q1.getZ(), CScalar(7));
			Assert::AreEqual(q1.getW(), CScalar(8));
		}
	};
}
