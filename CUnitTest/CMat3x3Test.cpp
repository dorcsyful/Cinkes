#include "pch.h"
#include "CppUnitTest.h"
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
	TEST_CLASS(CMat3x3Test)
	{
	public:

		TEST_METHOD(EmptyConsturctor) {
			const CMat3x3 matrix = CMat3x3();

			Assert::IsTrue(matrix[0] == CVector3(1, 0, 0));
			Assert::IsTrue(matrix[1] == CVector3(0, 1, 0));
			Assert::IsTrue(matrix[2] == CVector3(0, 0, 1));
		}

		TEST_METHOD(ConstructorWithRows)
		{
			CMat3x3  matrix = CMat3x3(CVector3(1, 2, 3), CVector3(5, 6, 7), CVector3(8, 9, 10));

			Assert::AreEqual(matrix[0], CVector3(1, 2, 3));
			Assert::AreEqual(matrix[1], CVector3(5, 6, 7));
			Assert::AreEqual(matrix[2], CVector3(8, 9, 10));
		}

		TEST_METHOD(ConstructorWithAllValues)
		{
			CMat3x3  matrix = CMat3x3(1, 2, 3, 5, 6, 7, 8, 9, 10);

			Assert::AreEqual(matrix[0], CVector3(1, 2, 3));
			Assert::AreEqual(matrix[1], CVector3(5, 6, 7));
			Assert::AreEqual(matrix[2], CVector3(8, 9, 10));
		}

		TEST_METHOD(CopyConstructor)
		{
			CMat3x3  toCopy = CMat3x3(1, 2, 3, 5, 6, 7, 8, 9, 10);
			CMat3x3 matrix = CMat3x3(toCopy);

			Assert::AreEqual(matrix[0], CVector3(1, 2, 3));
			Assert::AreEqual(matrix[1], CVector3(5, 6, 7));
			Assert::AreEqual(matrix[2], CVector3(8, 9, 10));
		}

		TEST_METHOD(OperatorEqual)
		{
			CMat3x3  first = CMat3x3(1, 2, 3, 5, 6, 7, 8, 9, 10);
			CMat3x3  second = CMat3x3(1, 2, 3, 5, 6, 7, 8, 9, 10);

			Assert::IsTrue(first == second);
		}

		TEST_METHOD(OperatorNotEqual)
		{
			CMat3x3  first = CMat3x3(1, 2, 3, 5, 6, 7, 8, 9, 1);
			CMat3x3  second = CMat3x3(1, 2, 3, 5, 6, 7, 8, 9, 10);
			bool result = first != second;
			Assert::IsTrue(result);
		}

		TEST_METHOD(OperatorAssignment)
		{
			CMat3x3  toCopy = CMat3x3(1, 2, 3, 5, 6, 7, 8, 9, 10);
			CMat3x3 matrix = toCopy;

			Assert::AreEqual(matrix[0], CVector3(1, 2, 3));
			Assert::AreEqual(matrix[1], CVector3(5, 6, 7));
			Assert::AreEqual(matrix[2], CVector3(8, 9, 10));
		}

		TEST_METHOD(OperatorAddEqualScalar)
		{
			CMat3x3  matrix = CMat3x3(1, 2, 3, 5, 6, 7, 8, 9, 10);
			matrix += CScalar(2);

			Assert::AreEqual(matrix[0], CVector3(3, 4, 5));
			Assert::AreEqual(matrix[1], CVector3(7, 8, 9));
			Assert::AreEqual(matrix[2], CVector3(10, 11, 12));
		}

		TEST_METHOD(OperatorAddScalar)
		{
			CMat3x3  toAdd = CMat3x3(1, 2, 3, 5, 6, 7, 8, 9, 10);
			CScalar scalarToAdd = 2;
			CMat3x3 matrix = toAdd + CScalar(2);

			Assert::AreEqual(matrix[0], CVector3(3, 4, 5));
			Assert::AreEqual(matrix[1], CVector3(7, 8, 9));
			Assert::AreEqual(matrix[2], CVector3(10, 11, 12));
		}

		TEST_METHOD(OperatorSubstranctEqualScalar)
		{
			CMat3x3 matrix = CMat3x3(3, 4, 5, 7, 8, 9, 10, 11, 12);
			matrix -= CScalar(2);

			Assert::AreEqual(matrix[0], CVector3(1, 2, 3));
			Assert::AreEqual(matrix[1], CVector3(5, 6, 7));
			Assert::AreEqual(matrix[2], CVector3(8, 9, 10));
		}

		TEST_METHOD(OperatorSubstranctScalar)
		{
			CMat3x3 matrix = CMat3x3(3, 4, 5, 7, 8, 9, 10, 11, 12);
			matrix -= CScalar(2);

			Assert::AreEqual(matrix[0], CVector3(1, 2, 3));
			Assert::AreEqual(matrix[1], CVector3(5, 6, 7));
			Assert::AreEqual(matrix[2], CVector3(8, 9, 10));
		}

		TEST_METHOD(OperatorAddEqualMatrix)
		{
			CMat3x3 first = CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
			CMat3x3 second = CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);

			first += second;

			Assert::IsTrue(first == CMat3x3(2, 4, 6, 8, 10, 12, 14, 16, 18));
		}

		TEST_METHOD(OperatorAddMatrix)
		{
			CMat3x3 first = CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
			CMat3x3 second = CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);

			CMat3x3 third = first + second;

			Assert::IsTrue(third == CMat3x3(2, 4, 6, 8, 10, 12, 14, 16, 18));
		}

		TEST_METHOD(OperatorSubstractMatrix)
		{
			CMat3x3 toSubstract = CMat3x3(5, 6, 7, 8, 9, 10, 11, 12, 13);
			CMat3x3 base =		  CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);

			CMat3x3 examplpe = base - toSubstract;

			Assert::AreEqual(examplpe, CMat3x3(-4, -4, -4, -4, -4, -4, -4, -4, -4));
		}

		TEST_METHOD(OperatorSubstractEqualMatrix)
		{
			CMat3x3 example = CMat3x3(5, 6, 7, 8, 9, 10, 11, 12, 13);
			CMat3x3 toSubstract = CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);

			example -= toSubstract;

			Assert::AreEqual(example, CMat3x3(4, 4, 4, 4, 4, 4, 4, 4, 4));
		}

		TEST_METHOD(OperatorMultiplyMatrix)
		{
			CMat3x3 first = CMat3x3(1, 2, 3, 
									4, 5, 6, 
									7, 8, 9);
			CMat3x3 second = CMat3x3(10, 11, 12, 
									13, 14, 15, 
									16, 17, 18);

			CMat3x3 result = first * second;


			Assert::AreEqual(result, CMat3x3(84, 90, 96, 201, 216, 231, 318, 342, 366));
		}

		TEST_METHOD(OperatorMultiplyEqualMatrix)
		{
			CMat3x3 first = CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
			CMat3x3 second = CMat3x3(10, 11, 12, 13, 14, 15, 16, 17, 18);

			first *= second;


			Assert::AreEqual(first, CMat3x3(84, 90, 96, 201, 216, 231, 318, 342, 366));
		}

		TEST_METHOD(OperatorMultiplyVector)
		{
			CMat3x3 matrix = CMat3x3(1, 2, 3, 0, 1, 4, 5, 6, 0);
			CVector3 vector = CVector3(-2, -3, -4);
			CVector3 result = matrix * vector;

			Assert::IsTrue(result == CVector3(-20, -19, -28));
		}

		TEST_METHOD(OperatorMultiplyScalar)
		{
			CMat3x3 matrix = CMat3x3(2, 7, 3, 1, 5, 8, 0, 4, 1);
			CMat3x3 multiplied = matrix * 2;

			Assert::AreEqual(multiplied, CMat3x3(4, 14, 6, 2, 10, 16, 0, 8, 2));
		}

		TEST_METHOD(OperatorMultiplyEqualScalar)
		{
			CMat3x3 matrix = CMat3x3(2, 7, 3, 1, 5, 8, 0, 4, 1);
			matrix *= 2;

			Assert::AreEqual(matrix, CMat3x3(4, 14, 6, 2, 10, 16, 0, 8, 2));
		}

		TEST_METHOD(OperatorBracket)
		{
			CMat3x3 example = CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
			
			int counter = 1;
			for(int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++) {
					Assert::AreEqual(int(example[i][j]), counter);
					counter++;
				}
			}
		}

		TEST_METHOD(GetRowColumn)
		{
			CMat3x3 example = CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);

			Assert::AreEqual(example.getRow(0), CVector3(1, 2, 3));
			Assert::AreEqual(example.getRow(1), CVector3(4, 5, 6));
			Assert::AreEqual(example.getRow(2), CVector3(7, 8, 9));

			Assert::AreEqual(example.getColumn(0), CVector3(1, 4, 7));
			Assert::AreEqual(example.getColumn(1), CVector3(2, 5, 8));
			Assert::AreEqual(example.getColumn(2), CVector3(3, 6, 9));
		}

		TEST_METHOD(TransposeMatrix)
		{
			CMat3x3 base = CMat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
			CMat3x3 transposed = base.Transpose();

			Assert::AreEqual(transposed, CMat3x3(1, 4, 7, 2, 5, 8, 3, 6, 9));
		}

		TEST_METHOD(InverseMatrix)
		{
			CMat3x3 base = CMat3x3(1,2,3,0,1,4,5,6,0);
			CMat3x3 inversed = base.GetInverse();

			Assert::AreEqual(inversed, CMat3x3(-24, 18, 5, 20, -15, -4, -5, 4, 1));
		}

		TEST_METHOD(Identity)
		{
			CMat3x3 example = CMat3x3(1, 0, 0, 0, 1, 0, 0, 0, 1);

			Assert::IsTrue(example == CMat3x3::GetIdentity());
		}

		TEST_METHOD(FullDeterminant)
		{
			CMat3x3 example = CMat3x3(1, 2, 3, 0, 1, 4, 5, 6, 0);

			Assert::AreEqual(example.Determinant(), CScalar(1));
		}

		TEST_METHOD(MinorDeterminant)
		{
			CMat3x3 temp;
			CScalar detOfMinor = temp.DeterminantOfMinor(1, 4, 6, 0);

			Assert::AreEqual(detOfMinor, CScalar(-24));
		}

		TEST_METHOD(MatrixToQuaternion)
		{
			CMat3x3 example = CMat3x3(1, 0, 0, 0, 2, 0, 0, 0, 1);
			CQuaternion quat = example.ToQuaternion();

			Assert::IsTrue(quat.getX() - CScalar(0) < CScalar(0.1));
			Assert::IsTrue(quat.getY() - CScalar(0) < CScalar(0.1));
			Assert::IsTrue(quat.getZ() - CScalar(0) < CScalar(0.1));
			Assert::IsTrue(quat.getW() - CScalar(1) < CScalar(0.2));
		}

		TEST_METHOD(MakeAbs)
		{
			CMat3x3 base = CMat3x3(-1, -3, -3, 1, 3, -4, 0, 6, -10);
			CMat3x3 abs = base.Abs();

			Assert::IsTrue(abs == CMat3x3(1, 3, 3, 1, 3, 4, 0, 6, 10));
		}

		TEST_METHOD(Euler)
		{
			CMat3x3 example = CMat3x3(1, 0, 0, 0, 2, 0, 0, 0, 1);
			CScalar yaw, pitch, roll;

			example.GetEuler(yaw, pitch, roll);
			Assert::IsTrue(yaw - CScalar(3.14) < CScalar(0.01));
			Assert::IsTrue(pitch - CScalar(3.14) < CScalar(0.01));
			Assert::IsTrue(roll - CScalar(3.14) < CScalar(0.01));
		}
	};
}