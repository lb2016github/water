#ifndef WATER_MESH_OPENGL_H
#define WATER_MESH_OPENGL_H
#include "render/mesh.h"
#include "render/render_object.h"
#include "glad/glad.h"
#include "render/draw_command.h"
GL_DEPTH_ATTACHMENT

namespace water
{
	namespace render
	{
		class MeshProxyOpenGL
		{
		public:
			MeshProxyOpenGL(MeshDataPtr mesh_ptr);
			~MeshProxyOpenGL();
			virtual void render(DrawCommand draw_command);
		protected:
			// commit data to gpu
			void commit_mesh();
		private:
			GLuint m_vao;
			GLuint m_buffers[LOCATION_LENGTH];
			MeshDataPtr m_mesh_ptr;
			bool is_commited = { false };
		};

		typedef std::shared_ptr<MeshProxyOpenGL> MeshProxyOpenGLPtr;

		class MeshProxyManager
		{
		public:
			MeshProxyOpenGLPtr get_proxy(MeshDataPtr mesh_ptr);
			static MeshProxyManager* get_instance();
		protected:
			std::map<MESH_ID_TYPE, MeshProxyOpenGLPtr> m_proxy_map;
		};
	}
}
	
#endif // !WATER_MESH_OPENGL_H

