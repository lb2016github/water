#include "render/opengl/mesh_opengl.h"

namespace water
{
	namespace render
	{
		MeshOpenGL::MeshOpenGL(): MeshData(), is_inited(false)
		{
			glGenBuffers(LOCATION_LENGTH, m_buffers);
		}
		MeshOpenGL::~MeshOpenGL()
		{
		}
		void MeshOpenGL::render()
		{
			// commit buffer data
			commit_data();
			// bind vao
			glBindVertexArray(m_vao);
		}
		void MeshOpenGL::commit_data()
		{
			if (is_inited) return;
			glGenVertexArrays(1, &m_vao);
			glBindVertexArray(m_vao);
			if (pos_data != nullptr)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[LOCATION_POSITION]);
				glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector3), pos_data, GL_STATIC_DRAW);
				glVertexAttribPointer(LOCATION_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(LOCATION_POSITION);
			}
			if (normal_data != nullptr)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[LOCATION_NORMAL]);
				glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector3), normal_data, GL_STATIC_DRAW);
				glVertexAttribPointer(LOCATION_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(LOCATION_NORMAL);
			}
			if (color_data != nullptr)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[LOCATION_COLOR]);
				glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector4), color_data, GL_STATIC_DRAW);
				glVertexAttribPointer(LOCATION_COLOR, 4, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(LOCATION_COLOR);
			}
			if (coord_data != nullptr)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[LOCATION_COORDINATE]);
				glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector2), coord_data, GL_STATIC_DRAW);
				glVertexAttribPointer(LOCATION_COORDINATE, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(LOCATION_COORDINATE);
			}
			if (tangent_data != nullptr)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[LOCATION_TANGENT]);
				glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector3), tangent_data, GL_STATIC_DRAW);
				glVertexAttribPointer(LOCATION_TANGENT, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(LOCATION_TANGENT);
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			is_inited = true;
		}
	}
}