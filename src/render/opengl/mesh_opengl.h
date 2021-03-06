#ifndef WATER_MESH_OPENGL_H
#define WATER_MESH_OPENGL_H
#include "render/mesh.h"
#include "render/render_object.h"
#include "glad/glad.h"
#include "render/draw_command.h"


namespace water
{
	namespace render
	{
		class MeshProxyOpenGL
		{
		public:
			MeshProxyOpenGL(MeshDataPtr mesh_ptr);
			~MeshProxyOpenGL();
			virtual void render();
		protected:
			// commit data to gpu
			void commit_mesh();
		private:
			GLuint m_vao;
			GLuint m_buffers[LOCATION_LENGTH];
			MeshDataPtr m_mesh_ptr;
		};

		typedef std::shared_ptr<MeshProxyOpenGL> MeshProxyOpenGLPtr;

		class MeshProxyManager
		{
		public:
			MeshProxyOpenGLPtr get_proxy(MeshDataPtr mesh_ptr);
			static MeshProxyManager* get_instance();
		protected:
			std::map<WATER_ID, MeshProxyOpenGLPtr> m_proxy_map;
		};
	}
}
	
#endif // !WATER_MESH_OPENGL_H

