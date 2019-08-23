#ifndef WATER_MESH_OPENGL_H
#define WATER_MESH_OPENGL_H
#include "render/mesh.h"
#include "render/render_object.h"
#include "glad/glad.h"

namespace water
{
	namespace render
	{
		class MeshOpenGL : public IMesh, public MeshData
		{
		public:
			MeshOpenGL();
			~MeshOpenGL();
			virtual void render(DrawMode draw_mode=TRIANGLES);
		protected:
			// commit data to gpu
			void commit_data();
		private:
			GLuint m_vao;
			GLuint m_buffers[LOCATION_LENGTH];
			bool is_inited;
		};
	}
}
	
#endif // !WATER_MESH_OPENGL_H

