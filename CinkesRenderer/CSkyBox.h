#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <glad/glad.h>
#include <glm/vec3.hpp>

#include "CRenderDefines.h"
#include "stb_image.h"

namespace Cinkes
{

	class CSkyBox
	{
	public:
		CSkyBox(const std::string& a_Folder = BASE_SKYBOX_FOLDER)
		{
			m_Faces[0] = a_Folder + "SkyBox_Right.jpg";
			m_Faces[1] = a_Folder + "SkyBox_Left.jpg";
			m_Faces[2] = a_Folder + "SkyBox_Top.jpg";
			m_Faces[3] = a_Folder + "SkyBox_Bottom.jpg";
			m_Faces[4] = a_Folder + "SkyBox_Front.jpg";
			m_Faces[5] = a_Folder + "SkyBox_Back.jpg";

                // positions          
            m_Vertices[0] =  -1.0f; m_Vertices[1] =   1.0f; m_Vertices[2] =  -1.0f;
            m_Vertices[3] =  -1.0f; m_Vertices[4] =  -1.0f; m_Vertices[5] =  -1.0f;
			m_Vertices[6] =   1.0f; m_Vertices[7] =  -1.0f; m_Vertices[8] =  -1.0f;
			m_Vertices[9] =   1.0f; m_Vertices[10] = -1.0f; m_Vertices[11] = -1.0f;
			m_Vertices[12] =  1.0f; m_Vertices[13] =  1.0f; m_Vertices[14] = -1.0f;
			m_Vertices[15] = -1.0f; m_Vertices[16] =  1.0f; m_Vertices[17] = -1.0f;

            m_Vertices[18] = -1.0f; m_Vertices[19] = -1.0f; m_Vertices[20] =  1.0f;
            m_Vertices[21] = -1.0f; m_Vertices[22] = -1.0f; m_Vertices[23] = -1.0f;
            m_Vertices[24] = -1.0f; m_Vertices[25] =  1.0f; m_Vertices[26] = -1.0f;
            m_Vertices[27] = -1.0f; m_Vertices[28] =  1.0f; m_Vertices[29] = -1.0f;
            m_Vertices[30] = -1.0f; m_Vertices[31] =  1.0f; m_Vertices[32] =  1.0f;
            m_Vertices[33] = -1.0f; m_Vertices[34] = -1.0f; m_Vertices[35] =  1.0f;

            m_Vertices[36] = 1.0f; m_Vertices[37] = -1.0f; m_Vertices[38] = -1.0f;
            m_Vertices[39] = 1.0f; m_Vertices[40] = -1.0f; m_Vertices[41] =  1.0f;
            m_Vertices[42] = 1.0f; m_Vertices[43] =  1.0f; m_Vertices[44] =  1.0f;
            m_Vertices[45] = 1.0f; m_Vertices[46] =  1.0f; m_Vertices[47] =  1.0f;
            m_Vertices[48] = 1.0f; m_Vertices[49] =  1.0f; m_Vertices[50] = -1.0f;
            m_Vertices[51] = 1.0f; m_Vertices[52] = -1.0f; m_Vertices[53] = -1.0f;

            m_Vertices[54] = -1.0f; m_Vertices[55] = -1.0f; m_Vertices[56] = 1.0f;
            m_Vertices[57] = -1.0f; m_Vertices[58] =  1.0f; m_Vertices[59] = 1.0f;
            m_Vertices[60] =  1.0f; m_Vertices[61] =  1.0f; m_Vertices[62] = 1.0f;
            m_Vertices[63] =  1.0f; m_Vertices[64] =  1.0f; m_Vertices[65] = 1.0f;
            m_Vertices[66] =  1.0f; m_Vertices[67] = -1.0f; m_Vertices[68] = 1.0f;
            m_Vertices[69] = -1.0f; m_Vertices[70] = -1.0f; m_Vertices[71] = 1.0f;

            m_Vertices[72] = -1.0f; m_Vertices[73] = 1.0f; m_Vertices[74] = -1.0f;
            m_Vertices[75] =  1.0f; m_Vertices[76] = 1.0f; m_Vertices[77] = -1.0f;
            m_Vertices[78] =  1.0f; m_Vertices[79] = 1.0f; m_Vertices[80] =  1.0f;
            m_Vertices[81] =  1.0f; m_Vertices[82] = 1.0f; m_Vertices[83] =  1.0f;
            m_Vertices[84] = -1.0f; m_Vertices[85] = 1.0f; m_Vertices[86] =  1.0f;
            m_Vertices[87] = -1.0f; m_Vertices[88] = 1.0f; m_Vertices[89] = -1.0f;

            m_Vertices[90] =  -1.0f; m_Vertices[91] =  -1.0f; m_Vertices[92] =  -1.0f;
            m_Vertices[93] =  -1.0f; m_Vertices[94] =  -1.0f; m_Vertices[95] =   1.0f;
            m_Vertices[96] =   1.0f; m_Vertices[97] =  -1.0f; m_Vertices[98] =  -1.0f;
            m_Vertices[99] =   1.0f; m_Vertices[100] = -1.0f; m_Vertices[101] = -1.0f;
            m_Vertices[102] = -1.0f; m_Vertices[103] = -1.0f; m_Vertices[104] =  1.0f;
            m_Vertices[105] =  1.0f; m_Vertices[106] = -1.0f; m_Vertices[107] =  1.0f;

            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);
            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), &m_Vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

            glGenTextures(1, &m_TextureID);
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);

            int width, height, nrChannels;
            for (unsigned int i = 0; i < 6; i++)
            {
                unsigned char* data = stbi_load(m_Faces[i].c_str(), &width, &height, &nrChannels, 0);
                if (data)
                {
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    stbi_image_free(data);
                }
                else
                {
                    std::cout << "Cubemap texture failed to load at path: " << m_Faces[i] << std::endl;
                    stbi_image_free(data);
                }
            }
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


		}
        unsigned int m_VAO;
        unsigned int m_TextureID;
	private:
        unsigned int m_VBO;
		float m_Vertices[108];
		std::string m_Faces[6];
	};
}
