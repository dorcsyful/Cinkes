#include "CRenderHandler.h"
#include "CBoxShape.h"

bool Cinkes::CRenderHandler::RegisterObject(const std::shared_ptr<CCollisionObject>& a_Collision)
{
	CObjectWrapper object = CObjectWrapper();
	object.m_CollisionObject = a_Collision;
	std::shared_ptr<CRenderShape> temp;
	if(a_Collision->GetCollisionShape()->GetType() == ESHAPE_TYPE::SHAPE_BOX)
	{
		glm::vec3 extent = ConvertVectorToGlm(static_cast<CBoxShape*>(a_Collision->GetCollisionShape().get())->GetDimensions());
		std::shared_ptr<CCubeRenderShape> shape1 = std::make_shared<CCubeRenderShape>(ConvertTransformToGLM(a_Collision->GetTransform()), extent);
		temp = std::static_pointer_cast<CRenderShape>(shape1);
		m_Window->AddRenderShape(temp);
	}
	object.m_RenderObject = temp;
	m_Objects.push_back(object);
	return true;
}

void Cinkes::CRenderHandler::RegisterAll(const std::vector<std::shared_ptr<CCollisionObject>>& a_CollisionObjects)
{
	for (auto& current : a_CollisionObjects)
	{

		CObjectWrapper object = CObjectWrapper();
		object.m_CollisionObject = current;
		object.CreateRenderShape();
		m_Window->AddRenderShape(object.m_RenderObject);
		object.m_RenderObject->CreateVBO();
		m_Objects.push_back(object);
	}
}

glm::mat4x4 Cinkes::CRenderHandler::ConvertTransformToGLM(const Cinkes::CTransform& a_Transform)
{

	CVector3 collisionLocation = a_Transform.getOrigin();
	CMat3x3 collisionRotation = a_Transform.getBasis();
	glm::mat4 converted = glm::mat4(1.f);
	glm::vec3 location = glm::vec3(collisionLocation[0], collisionLocation[1], collisionLocation[2]);
	converted = glm::translate(converted, location);

	converted[0][0] = collisionRotation[0][0];
	converted[1][0] = collisionRotation[0][1];
	converted[2][0] = collisionRotation[0][2];

	converted[0][1] = collisionRotation[1][0];
	converted[1][1] = collisionRotation[1][1];
	converted[2][1] = collisionRotation[1][2];

	converted[0][2] = collisionRotation[2][0];
	converted[1][2] = collisionRotation[2][1];
	converted[2][2] = collisionRotation[2][2];

	return converted;
}

glm::vec3 Cinkes::CRenderHandler::ConvertVectorToGlm(const CVector3& a_Vector3)
{
	return {a_Vector3[0], a_Vector3[1], a_Vector3[2]};
}

void Cinkes::CRenderHandler::UpdateObjects()
{
	for(auto& current : m_Objects)
	{
		current.m_RenderObject->SetTransform(ConvertTransformToGLM(current.m_CollisionObject->GetTransform()));
	}
}

void Cinkes::CRenderHandler::CreateWindowObject()
{
	m_Window = std::make_shared<CRenderWindow>();
	m_Window->InitializeWindow();
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

bool Cinkes::CRenderHandler::RemoveWrapperByRef(const CObjectWrapper& a_Wrapper)
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
	return {};
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
	return {};
}

