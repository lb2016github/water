#include "render/opengl/mesh_opengl.h"
#include "common/log.h"

namespace water
{
	namespace render
	{
		MeshProxyManager* instance = nullptr;

		MeshProxyOpenGL::MeshProxyOpenGL(MeshDataPtr mesh_ptr): m_mesh_ptr(mesh_ptr), is_commited(false)
		{
			glGenBuffers(LOCATION_LENGTH, m_buffers);
		}
		MeshProxyOpenGL::~MeshProxyOpenGL()
		{
		}
		void MeshProxyOpenGL::render()
		{
			// commit buffer data
			commit_mesh();
			// bind vao
			glBindVertexArray(m_vao);
			GLuint mode;
			// todo
			switch (m_mesh_ptr->mode)
			{
			case TRIANGLES:
				mode = GL_TRIANGLES;
				break;
			case POINTS:
				mode = GL_POINTS;
				break;
			default:
				mode = GL_TRIANGLES;
				break;
			}
			glDrawElements(mode, m_mesh_ptr->index_data.size(), GL_UNSIGNED_INT, &(m_mesh_ptr->index_data[0]));
		}
		void MeshProxyOpenGL::commit_mesh()
		{
			if (is_commited) return;
			glGenVertexArrays(1, &m_vao);
			glBindVertexArray(m_vao);
			unsigned int num_vertex = m_mesh_ptr->position.size();
			if (m_mesh_ptr->position.size() > 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[LOCATION_POSITION]);
				glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector3), m_mesh_ptr->position.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(LOCATION_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(LOCATION_POSITION);
			}
			if (m_mesh_ptr->normal.size() > 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[LOCATION_NORMAL]);
				glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector3), m_mesh_ptr->normal.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(LOCATION_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(LOCATION_NORMAL);
			}
			if (m_mesh_ptr->color.size() > 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[LOCATION_COLOR]);
				glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector4), m_mesh_ptr->color.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(LOCATION_COLOR, 4, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(LOCATION_COLOR);
			}
			if (m_mesh_ptr->coordinate.size() > 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[LOCATION_COORDINATE]);
				glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector2), m_mesh_ptr->coordinate.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(LOCATION_COORDINATE, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(LOCATION_COORDINATE);
			}
			if (m_mesh_ptr->tangent.size() > 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[LOCATION_TANGENT]);
				glBufferData(GL_ARRAY_BUFFER, num_vertex * sizeof(math3d::Vector3), m_mesh_ptr->tangent.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(LOCATION_TANGENT, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(LOCATION_TANGENT);
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			is_commited = true;
		}
		MeshProxyOpenGLPtr MeshProxyManager::get_proxy(MeshDataPtr mesh_ptr)
		{
			MESH_ID_TYPE mesh_id = mesh_ptr->mesh_id;
			auto iter = m_proxy_map.find(mesh_id);
			if (iter != m_proxy_map.end())
			{
				return iter->second;
			}
			MeshProxyOpenGLPtr proxy_ptr = std::make_shared<MeshProxyOpenGL>(mesh_ptr);
			m_proxy_map[mesh_id] = proxy_ptr;
			return proxy_ptr;
		}
		MeshProxyManager * MeshProxyManager::get_instance()
		{
			if (instance == nullptr)
			{
				instance = new MeshProxyManager();
			}
			return instance;
		}
	}
}