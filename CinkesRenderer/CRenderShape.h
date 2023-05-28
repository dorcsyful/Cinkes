#pragma once
#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <memory>
#include <utility>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "CMaterial.h"
namespace Cinkes
{
	struct CVertex {
		CVertex(const glm::vec3& a_Position, const glm::vec2& a_UV, const glm::vec3& a_Normal) {
			m_Position = a_Position;
			m_UV = a_UV;
			m_Normal = a_Normal;
		}
		CVertex(float a_PX, float a_PY, float a_PZ)
		{
			m_Position = glm::vec3(a_PX, a_PY, a_PZ);
		}
		CVertex(float a_PX, float a_PY, float a_PZ, float a_UVX, float a_UVY, float a_NX, float a_NY, float a_NZ) {
			m_Position = glm::vec3(a_PX, a_PY, a_PZ);
			m_UV = glm::vec2(a_UVX, a_UVY);
			m_Normal = glm::vec3(a_NX, a_NY, a_NZ);
		}
		glm::vec3 m_Position;
		glm::vec2 m_UV;
		glm::vec3 m_Normal;
	};

	class CRenderShape
	{
	public:
		CRenderShape() = default;
		~CRenderShape() = default;


		int CreateVBO();
		GLuint GetVAO() { return m_VAO; }
		void UpdateBuffers(std::vector<CVertex>& a_Vertices, std::vector<unsigned> a_Indices) {
			m_Indices = std::move(a_Indices);
			m_Vertices = a_Vertices;
		}
		glm::mat4 Convert();
		CVertex& operator[](int a_Rhs) { return m_Vertices[a_Rhs]; }
		void SetTransform(const glm::mat4& a_In) {
			m_Transform = a_In;
		}
		glm::mat4 GetTransform() { return m_Transform; }
		std::shared_ptr<CMaterial>& GetMaterial() { return m_Material; }
		void SetMaterial(std::shared_ptr<CMaterial> a_Material) { m_Material = std::move(a_Material); }
		std::vector<CVertex> m_Vertices;
		std::vector<unsigned> m_Indices;
		bool m_Textured{};


	protected:
		std::shared_ptr<CMaterial> m_Material;
		glm::mat4 m_Transform{};
		GLuint m_VBO{};
		GLuint m_VAO{};

	};


	class CCubeRenderShape : public CRenderShape
	{
	public:
		CCubeRenderShape(glm::mat4 a_Transform, glm::vec3 a_Extents)
		{
			m_Transform = a_Transform;
			glm::vec3 dimensions = a_Extents;
			m_Vertices = {
				CVertex(-dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 0.0f,  0.0f,  0.0f, -1.0f),
				 CVertex(dimensions[0], -dimensions[1], -dimensions[2],  1.0f, 0.0f,  0.0f,  0.0f, -1.0f),
				CVertex(dimensions[0],  dimensions[1], -dimensions[2],  1.0f, 1.0f,  0.0f,  0.0f, -1.0f),
				CVertex(dimensions[0],  dimensions[1], -dimensions[2],  1.0f, 1.0f,  0.0f,  0.0f, -1.0f),
				CVertex(-dimensions[0],  dimensions[1], -dimensions[2],  0.0f, 1.0f,  0.0f,  0.0f, -1.0f),
				CVertex(-dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 0.0f,  0.0f,  0.0f, -1.0f),

				CVertex(-dimensions[0], -dimensions[1],  dimensions[2],  0.0f, 0.0f,  0.0f,  0.0f,  1.0f),
				CVertex(dimensions[0], -dimensions[1],  dimensions[2],  1.0f, 0.0f,  0.0f,  0.0f,  1.0f),
				CVertex(dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 1.0f,  0.0f,  0.0f,  1.0f),
				CVertex(dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 1.0f,  0.0f,  0.0f,  1.0f),
				CVertex(-dimensions[0],  dimensions[1],  dimensions[2],  0.0f, 1.0f,  0.0f,  0.0f,  1.0f),
				CVertex(-dimensions[0], -dimensions[1],  dimensions[2],  0.0f, 0.0f,  0.0f,  0.0f,  1.0f),

				CVertex(-dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 0.0f, -1.0f,  0.0f,  0.0f),
				CVertex(-dimensions[0],  dimensions[1], -dimensions[2],  1.0f, 1.0f, -1.0f,  0.0f,  0.0f),
				CVertex(-dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 1.0f, -1.0f,  0.0f,  0.0f),
				CVertex(-dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 1.0f, -1.0f,  0.0f,  0.0f),
				CVertex(-dimensions[0], -dimensions[1],  dimensions[2],  0.0f, 0.0f, -1.0f,  0.0f,  0.0f),
				CVertex(-dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 0.0f, -1.0f,  0.0f,  0.0f),

				CVertex(dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 0.0f,  1.0f,  0.0f,  0.0f),
				CVertex(dimensions[0],  dimensions[1], -dimensions[2],  1.0f, 1.0f,  1.0f,  0.0f,  0.0f),
				CVertex(dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 1.0f,  1.0f,  0.0f,  0.0f),
				CVertex(dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 1.0f,  1.0f,  0.0f,  0.0f),
				CVertex(dimensions[0], -dimensions[1],  dimensions[2],  0.0f, 0.0f,  1.0f,  0.0f,  0.0f),
				CVertex(dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 0.0f,  1.0f,  0.0f,  0.0f),

				CVertex(-dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 1.0f,  0.0f, -1.0f,  0.0f),
				CVertex(dimensions[0], -dimensions[1], -dimensions[2],  1.0f, 1.0f,  0.0f, -1.0f,  0.0f),
				CVertex(dimensions[0], -dimensions[1],  dimensions[2],  1.0f, 0.0f,  0.0f, -1.0f,  0.0f),
				CVertex(dimensions[0], -dimensions[1],  dimensions[2],  1.0f, 0.0f,  0.0f, -1.0f,  0.0f),
				CVertex(-dimensions[0], -dimensions[1],  dimensions[2],  0.0f, 0.0f,  0.0f, -1.0f,  0.0f),
				CVertex(-dimensions[0], -dimensions[1], -dimensions[2],  0.0f, 1.0f,  0.0f, -1.0f,  0.0f),

				CVertex(-dimensions[0],  dimensions[1], -dimensions[2],  0.0f, 1.0f,  0.0f,  1.0f,  0.0f),
				CVertex(dimensions[0],  dimensions[1], -dimensions[2],  1.0f, 1.0f,  0.0f,  1.0f,  0.0f),
				CVertex(dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 0.0f,  0.0f,  1.0f,  0.0f),
				CVertex(dimensions[0],  dimensions[1],  dimensions[2],  1.0f, 0.0f,  0.0f,  1.0f,  0.0f),
				CVertex(-dimensions[0],  dimensions[1],  dimensions[2],  0.0f, 0.0f,  0.0f,  1.0f,  0.0f),
				CVertex(-dimensions[0],  dimensions[1], -dimensions[2],  0.0f, 1.0f,  0.0f,  1.0f,  0.0f)
			};
			m_Indices = {
				0, 1, 3, // first triangle
				1, 2, 3  // second triangle
			};
			CreateVBO();
		}
	};

	class CLineRendered
	{
	public:
		CLineRendered(const glm::vec3& a_Start, const glm::vec3& a_End, const glm::vec3& a_Color = glm::vec3(1.f, 0.f, 0.f), float a_Width = 5.f);

		int CreateVBO();

		std::vector<float> m_Full;
		float m_Width;
		glm::vec3 m_Vertices[2];
		glm::vec3 m_Color;
		GLuint m_VBO;
		GLuint m_VAO;
	};
};

