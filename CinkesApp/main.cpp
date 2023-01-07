#pragma once
#include "CRenderWindow.h"
#include "CRenderDefines.h"
#include "CRenderHandler.h"
#include "CCollisionWorld.h"
#include "CBoxShape.h"
int main()
{
    using namespace Cinkes;
    
    CRenderHandler* handler = new CRenderHandler(true);
	CGJKAlgorithm gjk;
	CEPA epa;
	CTransform transform = CTransform(CMat3x3(0.7071068f, -0.7071068f, 0.f,
		0.7071068f, 0.7071068f, 0.f,
		0.f, 0.f, 1.f), CVector3(5, 13, 2));
	std::shared_ptr<CBoxShape> shape1 = std::make_shared<CBoxShape>(5, 5, 5);
	std::shared_ptr<CBoxShape> shape2 = std::make_shared<CBoxShape>(5, 5, 5);
	std::shared_ptr<CCollisionObject> object1 = std::make_shared<CCollisionObject>(CVector3(0, 0, 0), shape2);
	std::shared_ptr<CCollisionObject> object2 = std::make_shared<CCollisionObject>(CVector3(4,4,4), shape1);
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

	std::vector<std::shared_ptr<CRenderShape>> rendershapes;
	for (auto& b : epa.boob) {
		std::vector<CVertex> vertices;
		std::vector<int> indices;
		for (int i = 0; i < b.indices.size(); i += 3) {
			auto vertex0 = b.points[b.indices[i]];
			auto vertex1 = b.points[b.indices[i + 1]];
			auto vertex2 = b.points[b.indices[i + 2]];
			auto highlight = b.closestIndex * 3 == i;
			auto uv = glm::vec2(highlight ? 1 : 0);

			auto v0 = glm::vec3(vertex0[0], vertex0[1], vertex0[2]);
			auto v1 = glm::vec3(vertex1[0], vertex1[1], vertex1[2]);
			auto v2 = glm::vec3(vertex2[0], vertex2[1], vertex2[2]);

			auto edge1 = v0 - v1;
			auto edge2 = v0 - v2;
			auto normal = glm::cross(edge1, edge2);
			normal = glm::normalize(normal);

			vertices.push_back(CVertex(v0, uv, normal));
			vertices.push_back(CVertex(v1, uv, normal));
			vertices.push_back(CVertex(v2, uv, normal));
			indices.push_back(i * 3 + 0);
			indices.push_back(i * 3 + 1);
			indices.push_back(i * 3 + 2);
		}

		auto shape = std::make_shared<CRenderShape>();
		shape->m_Vertices = vertices;
		shape->m_Indices = indices;
		shape->CreateVBO();

		rendershapes.push_back(shape);
	}

	for (auto shape : rendershapes) {
		handler->m_Window->AddRenderShape(shape);
	}

	handler->RegisterObject(object1);
	handler->RegisterObject(object2);

    handler->m_Window->Run();

    delete handler;

    return 0;
}