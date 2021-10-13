// COTD Entry submitted by Paul Nettle [midnight@FluidStudios.com]
// Corresponds with an Ask MidNight response (http://www.flipcode.com/askmid/)

// -----------------------------------------------------------------------------
// This defines a callback for traversal
// -----------------------------------------------------------------------------

#pragma once
#include "../../CinkesMath/CScalar.h"


namespace Cinkes
{

#include <cstring>
    class   COctree;
    typedef bool            (*callback)(const COctree& a_Octree, void* a_Data);

    // -----------------------------------------------------------------------------
    // This defines a point class (it's incomplete, but the data elements are there)
    // -----------------------------------------------------------------------------


    class   CPoint
    {
    public:
        CPoint() = default;
        CPoint(CScalar a_X, CScalar a_Y, CScalar a_Z, const int a_Code) : m_X(a_X), m_Y(a_Y), m_Z(a_Z), m_N(static_cast<float>(1)), m_Code(a_Code) {}
        CPoint(CScalar a_X, CScalar a_Y, CScalar a_Z) : m_X(a_X), m_Y(a_Y), m_Z(a_Z), m_N(0), m_Code(0) {}

        CScalar m_X, m_Y, m_Z;        // Position
        CScalar          m_N{};              // User's unique identifier
        unsigned int    m_Code{};           // Used during octree generation

        CPoint& operator*(CScalar a_Rhs)
        {
            m_X *= a_Rhs;
            m_Y *= a_Rhs;
            m_Z *= a_Rhs;

            return *this;
        }

        CPoint& operator+(CScalar a_Rhs)
        {
            m_X += a_Rhs;
            m_Y += a_Rhs;
            m_Z += a_Rhs;

            return *this;
        }

        CPoint& operator+(CPoint a_Rhs)
        {
            m_X += a_Rhs.m_X;
            m_Y += a_Rhs.m_Y;
            m_Z += a_Rhs.m_Z;

            return *this;
        }

        CPoint& operator-(CPoint a_Rhs)
        {
            m_X -= a_Rhs.m_X;
            m_Y -= a_Rhs.m_Y;
            m_Z -= a_Rhs.m_Z;

            return *this;
        }
    };

    // -----------------------------------------------------------------------------
    // This defines a cubic bounding volume (center, radius)
    // -----------------------------------------------------------------------------

    struct Bounds
    {
        Bounds() : m_Center(CPoint(0, 0, 0)), m_Radius(0) { }

        CPoint           m_Center;         // Center of a cubic bounding volume
        CScalar          m_Radius;         // Radius of a cubic bounding volume
    };

    // -----------------------------------------------------------------------------
    // The octree class -- almost real code!
    // -----------------------------------------------------------------------------

    class   COctree
    {
    public:
        // Construction/Destruction

        COctree();
        virtual                         ~COctree();

        // Accessors

        inline  const   CPoint* const* Points() const { return m_Points; }
        inline  const   unsigned int    PointCount() const { return m_PointCount; }

        // Implementation

        virtual  bool            Build(CPoint** points,
            const unsigned int a_Count,
            const unsigned int a_Threshold,
            const unsigned int a_MaximumDepth,
            Bounds& a_Bounds,
            const unsigned int a_CurrentDepth = 0);
        static  const   Bounds          CalcCubicBounds(const CPoint* const* a_Points,
            const unsigned int a_Count);
        virtual bool            Traverse(callback a_Proc, void* a_Data) const;

    protected:
        COctree* m_Child[8];
        unsigned int            m_PointCount;
        CPoint** m_Points;
        CPoint                   m_Center;
        CScalar                  m_Radius;
    };

    // -----------------------------------------------------------------------------
    // Construction -- Just "nullify" the class
    // -----------------------------------------------------------------------------

    COctree::COctree()
        : m_PointCount(0), m_Points(nullptr), m_Center(0, 0, 0., 0.), m_Radius(0.0)
    {
        memset(m_Child, 0, sizeof(m_Child));
    }

    // -----------------------------------------------------------------------------
    // Destruction -- free up memory
    // -----------------------------------------------------------------------------

    COctree::~COctree()
    {
        delete[] m_Points;
    }

    // -----------------------------------------------------------------------------
    // Build the octree
    // -----------------------------------------------------------------------------

    bool    COctree::Build(CPoint** points,
        const unsigned int count,
        const unsigned int threshold,
        const unsigned int maximumDepth,
        Bounds& bounds,
        const unsigned int currentDepth)
    {
        // You know you're a leaf when...
        //
        // 1. The number of points is <= the threshold
        // 2. We've recursed too deep into the tree
        //    (currentDepth >= maximumDepth)
        //
        //    NOTE: We specifically use ">=" for the depth comparison so that we
        //          can set the maximumDepth depth to 0 if we want a tree with
        //          no depth.

        if (count <= threshold || currentDepth >= maximumDepth)
        {
            // Just store the points in the node, making it a leaf

            m_PointCount = count;
            m_Points = new CPoint * [count];
            memcpy(m_Points, points, sizeof(CPoint*) * count);
            return true;
        }

        // We'll need this (see comment further down in this source)

        unsigned int    m_ChildPointCounts[8];

        // Classify each point to a child node

        for (unsigned int i = 0; i < count; i++)
        {
            // Current point

            CPoint& p = *points[i];

            // Center of this node

            const CPoint& c = bounds.m_Center;

            // Here, we need to know which child each point belongs to. To
            // do this, we build an index into the _child[] array using the
            // relative position of the point to the center of the current
            // node

            p.m_Code = 0;
            if (p.m_X > c.m_X) p.m_Code |= 1;
            if (p.m_Y > c.m_Y) p.m_Code |= 2;
            if (p.m_Z > c.m_Z) p.m_Code |= 4;

            // We'll need to keep track of how many points get stuck in each
            // child so we'll just keep track of it here, since we have the
            // information handy.

            m_ChildPointCounts[p.m_Code]++;
        }

        // Recursively call build() for each of the 8 children

        for (int i = 0; i < 8; i++)
        {
            // Don't bother going any further if there aren't any points for
            // this child

            if (!m_ChildPointCounts[i]) continue;

            // Allocate the child

            m_Child[i] = new COctree;

            // Allocate a list of points that were coded JUST for this child
            // only

            CPoint** newList = new CPoint * [m_ChildPointCounts[i]];

            // Go through the input list of points and copy over the points
            // that were coded for this child

            CPoint** ptr = newList;

            for (unsigned int j = 0; j < count; j++)
            {
                if (points[j]->m_Code == i)
                {
                    *ptr = points[j];
                    ptr++;
                }
            }

            // At this point, we have a list of points that will belong to
            // this child node. We'll want to remove any point with a
            // duplicate 'n' in them...
            //
            // [We won't need to reallocate the list, since it's temporary]

            int     newCount = 0;
            for (int j = 0; j < m_ChildPointCounts[i]; j++)
            {
                // Remove duplicates from newList
                // ...
                // Keep track of the new count in 'newCount'
            }

            // Generate a new bounding volume -- We do this with a touch of
            // trickery...
            //
            // We use a table of offsets. These offsets determine where a
            // node is, relative to it's parent. So, for example, if want to
            // generate the bottom-left-rear (-x, -y, -z) child for a node,
            // we use (-1, -1, -1).
            // 
            // However, since the radius of a child is always half of its
            // parent's, we use a table of 0.5, rather than 1.0.
            // 
            // These values are stored the following table. Note that this
            // won't compile because it assumes Points are structs, but you
            // get the idea.

            CPoint boundsOffsetTable[8] =
            {
                    {-0.5, -0.5, -0.5},
                    {+0.5, -0.5, -0.5},
                    {-0.5, +0.5, -0.5},
                    {+0.5, +0.5, -0.5},
                    {-0.5, -0.5, +0.5},
                    {+0.5, -0.5, +0.5},
                    {-0.5, +0.5, +0.5},
                    {+0.5, +0.5, +0.5}
            };

            // Calculate our offset from the center of the parent's node to
            // the center of the child's node

            CPoint offset = boundsOffsetTable[i] * bounds.m_Radius;

            // Create a new Bounds, with the center offset and half the
            // radius


            Bounds  newBounds = Bounds();
            newBounds.m_Radius = bounds.m_Radius * CScalar(0.5);
            newBounds.m_Center = bounds.m_Center + offset;

            // Recurse

            m_Child[i]->Build(newList, newCount, threshold, maximumDepth,
                newBounds, currentDepth + 1);

            // Clean up

            delete[] newList;
        }

        return true;
    }

    // -----------------------------------------------------------------------------
    // Determine the [cubic] bounding volume for a set of points
    // -----------------------------------------------------------------------------

    const Bounds COctree::CalcCubicBounds(const CPoint* const* a_Points,
        const unsigned int a_Count)
    {
        // What we'll give to the caller

        Bounds  b;

        // Determine min/max of the given set of points

        CPoint   min = *a_Points[0];
        CPoint   max = *a_Points[0];

        for (unsigned int i = 1; i < a_Count; i++)
        {
            const CPoint& p = *a_Points[i];
            if (p.m_X < min.m_X) min.m_X = p.m_X;
            if (p.m_Y < min.m_Y) min.m_Y = p.m_Y;
            if (p.m_Z < min.m_Z) min.m_Z = p.m_Z;
            if (p.m_X > max.m_X) max.m_X = p.m_X;
            if (p.m_Y > max.m_Y) max.m_Y = p.m_Y;
            if (p.m_Z > max.m_Z) max.m_Z = p.m_Z;
        }

        // The radius of the volume (dimensions in each direction)

        CPoint   radius = max - min;

        // Find the center of this space

        b.m_Center = min + radius * 0.5;

        // We want a CUBIC space. By this, I mean we want a bounding cube, not
        // just a bounding box. We already have the center, we just need a
        // radius that contains the entire volume. To do this, we find the
        // maxumum value of the radius' X/Y/Z components and use that

        b.m_Radius = radius.m_X;
        if (b.m_Radius < radius.m_Y) b.m_Radius = radius.m_Y;
        if (b.m_Radius < radius.m_Z) b.m_Radius = radius.m_Z;

        // Done

        return b;
    }

    // -----------------------------------------------------------------------------
    // Generic tree traversal
    // -----------------------------------------------------------------------------

	bool COctree::Traverse(callback a_Proc, void* a_Data) const
    {
        // Call the callback for this node (if the callback returns false, then
        // stop traversing.

        if (!a_Proc(*this, a_Data)) return false;

        // If I'm a node, recursively traverse my children

        if (!m_PointCount)
        {
            for (const auto i : m_Child)
            {
                // We store incomplete trees (i.e. we're not guaranteed
                // that a node has all 8 children)

                if (!i) continue;

                if (!i->Traverse(a_Proc, a_Data)) return false;
            }
        }

        return true;
    }
}