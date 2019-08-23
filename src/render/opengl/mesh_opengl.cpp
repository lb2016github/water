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
		void MeshOpenGL::render(DrawMode draw_mode)
		{
			// commit buffer data
			commit_data();
			// bind vao
			glBindVertexArray(m_vao);
			// todo draw
		}
		void MeshOpenGL::commit_data()
		{
			if (is_inited) return;
			glGenVertexArrays(1, &m_vao);
			glBindVertexArray(m_vao);
			unsigned int num_vertex = position.size();
			if (position.size() > 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[LOCATION_POSITION]);
				glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector3), position.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(LOCATION_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(LOCATION_POSITION);
			}
			if (normal.size() > 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[LOCATION_NORMAL]);
				glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector3), normal.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(LOCATION_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(LOCATION_NORMAL);
			}
			if (color.size() > 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[LOCATION_COLOR]);
				glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector4), color.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(LOCATION_COLOR, 4, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(LOCATION_COLOR);
			}
			if (coordinate.size() > 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[LOCATION_COORDINATE]);
				glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector2), coordinate.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(LOCATION_COORDINATE, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(LOCATION_COORDINATE);
			}
			if (tangent.size() > 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[LOCATION_TANGENT]);
				glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector3), tangent.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(LOCATION_TANGENT, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(LOCATION_TANGENT);
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			is_inited = true;
		}
	}
}