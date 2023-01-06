#include "CRenderHandler.h"
#include "CBoxShape.h"
#include "CQuaternion.h"
void Cinkes::CObjectWrapper::CreateRenderShape()
{
	m_RenderObject = std::make_shared<CRenderShape>();
	RunVertexConverter();
}
void Cinkes::CObjectWrapper::RunVertexConverter()
{
	if (m_CollisionObject->GetCollisionShape()->GetType() == ESHAPE_TYPE::SHAPE_BOX) {
		ConvertBoxToVertices();
	}
}
void Cinkes::CObjectWrapper::ConvertBoxToVertices()
{
	CVector3 dimensions = static_cast<CBoxShape*>(m_CollisionObject->GetCollisionShape().get())->GetDimensions();
	//CVertex first = CVertex(-3.7071f, 1.9497f,6.f);
	m_RenderObject->m_Vertices = {
		CVertex(-dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 0.0f),
		 CVertex(dimensions[0], -dimensions[1], -dimensions[2],  1.0f, 0.0f),
		CVertex(dimensions[0],  dimensions[1], -dimensions[2],  1.0f, 1.0f),
		CVertex(dimensions[0],  dimensions[1], -dimensions[2],  1.0f, 1.0f),
		CVertex(-dimensions[0],  dimensions[1], -dimensions[2],  0.0f, 1.0f),
		CVertex(-dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 0.0f),

		CVertex(-dimensions[0], -dimensions[1],  dimensions[2],  0.0f, 0.0f),
		CVertex(dimensions[0], -dimensions[1],  dimensions[2],  1.0f, 0.0f),
		CVertex(dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 1.0f),
		CVertex(dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 1.0f),
		CVertex(-dimensions[0],  dimensions[1],  dimensions[2],  0.0f, 1.0f),
		CVertex(-dimensions[0], -dimensions[1],  dimensions[2],  0.0f, 0.0f),

		CVertex(-dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 0.0f),
		CVertex(-dimensions[0],  dimensions[1], -dimensions[2],  1.0f, 1.0f),
		CVertex(-dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 1.0f),
		CVertex(-dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 1.0f),
		CVertex(-dimensions[0], -dimensions[1],  dimensions[2],  0.0f, 0.0f),
		CVertex(-dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 0.0f),

		CVertex(dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 0.0f),
		CVertex(dimensions[0],  dimensions[1], -dimensions[2],  1.0f, 1.0f),
		CVertex(dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 1.0f),
		CVertex(dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 1.0f),
		CVertex(dimensions[0], -dimensions[1],  dimensions[2],  0.0f, 0.0f),
		CVertex(dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 0.0f),

		CVertex(-dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 1.0f),
		CVertex(dimensions[0], -dimensions[1], -dimensions[2],  1.0f, 1.0f),
		CVertex(dimensions[0], -dimensions[1],  dimensions[2],  1.0f, 0.0f),
		CVertex(dimensions[0], -dimensions[1],  dimensions[2],  1.0f, 0.0f),
		CVertex(-dimensions[0], -dimensions[1],  dimensions[2],  0.0f, 0.0f),
		CVertex(-dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 1.0f),

		CVertex(-dimensions[0],  dimensions[1], -dimensions[2],  0.0f, 1.0f),
		CVertex(dimensions[0],  dimensions[1], -dimensions[2],  1.0f, 1.0f),
		CVertex(dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 0.0f),
		CVertex(dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 0.0f),
		CVertex(-dimensions[0],  dimensions[1],  dimensions[2],  0.0f, 0.0f),
		CVertex(-dimensions[0],  dimensions[1], -dimensions[2],  0.0f, 1.0f)
	};
	m_RenderObject->m_Indices = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
}

Cinkes::CRenderHandler::CRenderHandler(bool a_CreateWindow)
{
	if (a_CreateWindow) {
		CreateWindowObject();
	}
}

Cinkes::CRenderHandler::~CRenderHandler()
{
}

bool Cinkes::CRenderHandler::RegisterObject(std::shared_ptr<CCollisionObject> a_Collision)
{
	for (auto& current : m_Objects) 
	{
		if (current.m_CollisionObject.get() == a_Collision.get())
		{
			CVector3 location = a_Collision->GetTransform().getOrigin();
			std::cout << "Collision object at location " << location[0] << " " << location[1];
			std::cout << " " << location[2] << " already exists" << std::endl;
			return false;
		}
	}
		CObjectWrapper object = CObjectWrapper();
		object.m_CollisionObject = a_Collision;
		object.CreateRenderShape();
		m_Window->AddRenderShape(object.m_RenderObject);
		object.m_RenderObject->CreateVBO();
		object.m_RenderObject->LoadTexture(TEXTURE, m_Window->m_Shader.get());
		m_Objects.push_back(object);
		ConvertTransforms();
	return true;
}

void Cinkes::CRenderHandler::RegisterAll(std::vector<std::shared_ptr<CCollisionObject>> a_CollisionObjects, bool a_DuplicatesAllowed)
{
	for (auto& current : a_CollisionObjects)
	{
		if (!a_DuplicatesAllowed) {
			CVector3 location = current->GetTransform().getOrigin();
			std::cout << "Collision object at location " << location[0] << " " << location[1];
			std::cout << " " << location[2] << " already exists" << std::endl;
		}
		CObjectWrapper object = CObjectWrapper();
		object.m_CollisionObject = current;
		object.CreateRenderShape();
		m_Window->AddRenderShape(object.m_RenderObject);
		object.m_RenderObject->CreateVBO();
		object.m_RenderObject->LoadTexture(TEXTURE, m_Window->m_Shader.get());
		m_Objects.push_back(object);
	}
}

void Cinkes::CRenderHandler::ConvertTransforms()
{
	for (auto& current : m_Objects)
	{
		CVector3 collisionLocation = current.m_CollisionObject->GetTransform().getOrigin();
		CMat3x3 collisionRotation = current.m_CollisionObject->GetTransform().getBasis();
		glm::mat4 converted = glm::mat4(1.f);
		glm::vec3 location = glm::vec3(collisionLocation[0], collisionLocation[1], collisionLocation[2]);
		converted = glm::translate(converted, location);

		converted[0][0] = collisionRotation[0][0]; converted[0][1] = collisionRotation[1][0]; converted[0][2] = collisionRotation[2][0];
		converted[1][0] = collisionRotation[0][1]; converted[1][1] = collisionRotation[1][1]; converted[1][2] = collisionRotation[2][1];
		converted[2][0] = collisionRotation[0][2]; converted[2][1] = collisionRotation[1][2]; converted[2][2] = collisionRotation[2][2];

		current.m_RenderObject->SetTransform(converted);
	}
}

void Cinkes::CRenderHandler::CreateWindowObject()
{
	m_Window = std::make_shared<CRenderWindow>();
	m_Window->InitializeWindow();
}

void Cinkes::CRenderHandler::TerminateWindow()
{
}

bool Cinkes::CRenderHandler::RemoveWrapperByCollisionRef(std::shared_ptr<CCollisionObject>& a_Collision)
{
	for (auto& current : m_Objects) {
		if (current.m_CollisionObject.get() == a_Collision.get()) {
			m_Objects.erase(std::find(m_Objects.begin(), m_Objects.end(), current));
			return true;
		}
	}
	return false;
}

bool Cinkes::CRenderHandler::RemoveWrapperByRenderRef(std::shared_ptr<CRenderShape>& a_Render)
{
	for (auto& current : m_Objects) {
		if (current.m_RenderObject.get() == a_Render.get()) {
			m_Objects.erase(std::find(m_Objects.begin(), m_Objects.end(), current));
			return true;
		}
	}
	return false;
}

bool Cinkes::CRenderHandler::RemoveWrapperByRef(CObjectWrapper a_Wrapper)
{
	m_Objects.erase(std::find(m_Objects.begin(), m_Objects.end(), a_Wrapper));

	return true;
}

bool Cinkes::CRenderHandler::RemoveWrapperByIndex(int a_Index)
{
	m_Objects.erase(std::find(m_Objects.begin(), m_Objects.end(), m_Objects[a_Index]));
	return true;
}

Cinkes::CObjectWrapper Cinkes::CRenderHandler::GetWrapperByCollisionRef(std::shared_ptr<CCollisionObject>& a_Collision)
{
	for (auto& current : m_Objects) 
	{
		if (current.m_CollisionObject.get() == a_Collision.get()) 
		{
			return current;
		}
	}
	std::cout << "Cannot find wrapper associated with this collision object!" << std::endl;
	return CObjectWrapper();
}

Cinkes::CObjectWrapper Cinkes::CRenderHandler::GetWrapperByRenderRef(std::shared_ptr<CRenderShape>& a_Render)
{
	for (auto& current : m_Objects)
	{
		if (current.m_RenderObject.get() == a_Render.get())
		{
			return current;
		}
	}
	std::cout << "Cannot find wrapper associated with this render object!" << std::endl;
	return CObjectWrapper();
}

void Cinkes::CRenderHandler::DebugDraw(const std::vector<std::vector<CVector3>>& a_Vertices, const std::vector<std::vector<int>>& a_Indices, const std::vector<std::vector<CVector3>>& a_Normals, const std::vector<CTransform>& a_Transforms, float a_Wait, CRenderWindow* a_Window)
{
	if (a_Window == nullptr) 
	{

	}
}

