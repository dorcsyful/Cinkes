#pragma once
#include <memory>

#include "../CinkesMath/CVector3.h"

namespace Cinkes
{
	class CTriangleStorage;
	class CTriangle;
	//these are NOT actual collision shapes!

	class CEdge {
		CTriangle* m_Triangle;
		int       m_Index;

	public:
		CEdge() = default;
		CEdge(CTriangle* a_Triangle, int a_Index)
			: m_Triangle(a_Triangle),
			m_Index(a_Index)
		{}

		bool silhouette(const CVector3* a_Vertices, unsigned a_Index, CTriangleStorage& a_Storage) const;

		CTriangle* getTriangle() const { return m_Triangle; }
		int       getIndex()    const { return m_Index; }

		unsigned  getSource() const;
		unsigned  getTarget() const;
	};

	class CTriangle
	{
	public:
		CTriangle(): m_Indices{}, m_AdjascentEdges{}, m_Determinant(0), m_Lambda1(0), m_Lambda2(0), m_DistanceSqrd(0)
		{
			m_Obsolete = false;
		}

		CTriangle(int a_0, int a_1, int a_2)
			: m_AdjascentEdges{}, m_Obsolete(false), m_Determinant(0), m_Lambda1(0), m_Lambda2(0), m_DistanceSqrd(0)
		{
			m_Indices[0] = a_0;
			m_Indices[1] = a_1;
			m_Indices[2] = a_2;
		}

		unsigned operator[](int i) const { return m_Indices[i]; }

		bool isObsolete() const { return m_Obsolete; }
		void setObsolete(bool a_Rhs) { m_Obsolete = a_Rhs; }
		bool ComputeClosest(const CVector3* verts);
		const CVector3& getClosest() const { return m_Closest; }
		bool isClosestInternal() const;
		bool isVisibleFrom(const CVector3* a_Vertices, unsigned a_Index) const;
		CScalar getDist2() const { return m_DistanceSqrd; }
		CEdge& getAdjascentEdge(int i) { return m_AdjascentEdges[i]; }
		CVector3 getClosestPoint(const CVector3* a_Points) const;

		bool silhouette(const CVector3* a_Vertices, unsigned a_Index, CTriangleStorage& a_TriangleStorage);

	private:
		unsigned     m_Indices[3]{};
		CEdge        m_AdjascentEdges[3];

		bool        m_Obsolete;

		CScalar   m_Determinant;
		CScalar   m_Lambda1;
		CScalar   m_Lambda2;
		CVector3  m_Closest;
		CScalar   m_DistanceSqrd;
	};

	class CTriangleStorage
	{
	public:
		void clear() { m_Free = 0; }

		int getFree() const { return m_Free; }

		CTriangle& operator[](int a_Rhs) { return m_Triangles[a_Rhs]; }
		CTriangle& Last() { return m_Triangles[m_Free - 1]; }

		void setFree(int a_Backup) { m_Free = a_Backup; }
		CTriangle* newTriangle(const CVector3* a_Vertices, int a_A, int a_B, int a_C);

	private:
		CTriangle m_Triangles[100];
		int      m_Free = 0;
	};

	class TriangleComp
	{
	public:

		bool operator()(const CTriangle* a_Face1, const CTriangle* a_Face2) const
		{
			return a_Face1->getDist2() > a_Face2->getDist2();
		}
	};

	bool Link(const CEdge& a_Edge1, const CEdge& a_Edge2);
	void Half_Link(const CEdge& a_Edge1, const CEdge& a_Edge2);
}

