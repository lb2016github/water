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
			virtual void render(DrawCommand draw_command);
		protected:
			// commit data to gpu
			void commit_mesh();
		private:
			GLuint m_vao;
			GLuint m_buffers[LOCATION_LENGTH];
			MeshDataPtr m_mesh_ptr;
			bool is_commited;
		};
	}
}
	
#endif // !WATER_MESH_OPENGL_H

