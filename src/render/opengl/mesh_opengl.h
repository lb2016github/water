#ifndef WATER_MESH_OPENGL_H
#define WATER_MESH_OPENGL_H
#include "render/mesh.h"
#include "render/render_object.h"
#include "glad/glad.h"

namespace water
{
	namespace render
	{
		enum GLBuffIndex {
			POSITION_INDEX = 0,
			NORMAL_INDEX,
			COORD_INDEX,
			TANGENT_INDEX,
			INDEX_LENGTH,
		};
		class MeshOpenGL : public IMesh, public MeshData
		{
		public:
			MeshOpenGL();
			~MeshOpenGL();
			virtual void render() = 0;
		protected:
			// commit data to gpu
			void commit_data();
		private:
			GLuint m_buffers[INDEX_LENGTH];
			bool is_inited;
		};
	}
}
	
#endif // !WATER_MESH_OPENGL_H

