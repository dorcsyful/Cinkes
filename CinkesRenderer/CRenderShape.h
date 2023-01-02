#pragma once
#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "CTexture.h"
namespace Cinkes
{
	class CRenderShape
	{
	public:
		CRenderShape();
		~CRenderShape() {}


		int CreateVBO();
		bool LoadTexture(std::string a_Path, CShader* a_Shader);
		GLuint GetVAO() { return m_VAO; }
		void UpdateVertices(std::vector<float>& a_Vertices) {
			m_Vertices = a_Vertices;
		}
		glm::mat4 Convert();
		float& operator[](int a_Rhs) { return m_Vertices[a_Rhs]; }
		void SetTransform(const glm::mat4& a_In) {
			m_Transform = a_In;
		}
		glm::mat4 GetTransform() { return m_Transform; }
		CTexture* GetTexture() { return m_Texture.get(); }

		std::vector<float> m_Vertices;
		std::vector<int> m_Indices;

	private:
		std::shared_ptr<CTexture> m_Texture;
		glm::mat4 m_Transform;

		GLuint m_VBO;
		GLuint m_VAO;
		GLuint m_EBO;

	};
};

