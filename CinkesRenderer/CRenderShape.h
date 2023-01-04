#pragma once
#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "CTexture.h"
namespace Cinkes
{
	struct CVertex {
		CVertex(const glm::vec3& a_Position, const glm::vec2& a_UV, const glm::vec3& a_Normal) {
			position = a_Position;
			uv = a_UV;
			normal = a_Normal;
		}
		CVertex(float a_PX, float a_PY, float a_PZ, float a_UVX, float a_UVY, float a_NX = 1.f, float a_NY = 1.f, float a_NZ = 1.f) {
			position = glm::vec3(a_PX, a_PY, a_PZ);
			uv = glm::vec2(a_UVX, a_UVY);
			normal = glm::vec3(a_NX, a_NY, a_NZ);
		}
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
	};

	class CRenderShape
	{
	public:
		CRenderShape();
		~CRenderShape() {}


		int CreateVBO();
		bool LoadTexture(std::string a_Path, CShader* a_Shader);
		GLuint GetVAO() { return m_VAO; }
		void UpdateBuffers(std::vector<CVertex>& a_Vertices, std::vector<int> a_Indices) {
			m_Indices  = a_Indices;
			m_Vertices = a_Vertices;
		}

		glm::mat4 Convert();
		CVertex& operator[](int a_Rhs) { return m_Vertices[a_Rhs]; }
		void SetTransform(const glm::mat4& a_In) {
			m_Transform = a_In;
		}
		glm::mat4 GetTransform() { return m_Transform; }
		CTexture* GetTexture() { return m_Texture.get(); }

		std::vector<CVertex> m_Vertices;
		std::vector<int> m_Indices;

	private:
		std::shared_ptr<CTexture> m_Texture;
		glm::mat4 m_Transform;

		GLuint m_VBO;
		GLuint m_VAO;
		GLuint m_EBO;

	};
};

