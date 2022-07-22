#pragma once
#include <CVector3.h>

namespace Cinkes {
	struct CLine {
		CLine(const CVector3& a_Start, const CVector3 a_End) {
			start = a_Start;
			end =   a_End;
		}

		CLine() {
			start = CVector3(0, 0, 0);
			end =   CVector3(0, 0, 0);
		}

		CLine(CLine&& a_Rhs) noexcept {
			start = a_Rhs.start;
			end =   a_Rhs.end;
		}
		CLine(const CLine& a_Rhs) {
			start = a_Rhs.start;
			end =   a_Rhs.end;
		}
		CLine& operator=(CLine&& a_Rhs) noexcept {
			start = a_Rhs.start;
			end = a_Rhs.end;
		}

		static void GetClosestpoint(const CLine& a_Line1, const CLine& a_Line2, CVector3& a_OutPoint1, CVector3& a_OutPoint2);
		CScalar GetLength() { return (end - start).Length(); }
		CScalar GetLength2() { return (end - start).Length2(); }

		CVector3 start;
		CVector3 end;
	};
}