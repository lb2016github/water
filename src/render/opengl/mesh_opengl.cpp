#include "render/opengl/mesh_opengl.h"

namespace water
{
	namespace render
	{
		MeshOpenGL::MeshOpenGL(): MeshData(), is_inited(false)
		{
			glGenBuffers(INDEX_LENGTH, m_buffers);
		}
		MeshOpenGL::~MeshOpenGL()
		{
		}
		void MeshOpenGL::render()
		{
		}
		void MeshOpenGL::commit_data()
		{
			if (is_inited) return;
			if (base_pos >= 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[POSITION_INDEX]);
				//glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector3), )
			}

			is_inited = true;
		}
	}
}