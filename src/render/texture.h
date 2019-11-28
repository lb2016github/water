#ifndef WATER_TEXTURE_H
#define WATER_TEXTURE_H
#include <string>
#include "render_const.h"
#include "filesystem/image.h"
#include <vector>
#include <memory>
#include <map>
#include "common/common.h"
#include "math3d/math3d.hpp"


namespace water
{
	namespace render
	{
		struct TextureData: public std::enable_shared_from_this<TextureData>
		{
			void load();
			math3d::Vector2 get_size();
			TextureType tex_type;
			std::vector<filesystem::ImagePtr> images;
		};

		DECL_SHARED_PTR(TextureData);

		struct Texture
		{
			Texture(TextureType tex_type);
			~Texture();
			virtual void bind(TextureUnit tex_unit) = 0;
			virtual void set_tex_data(TextureDataPtr ptr);

			TextureType m_type;
			TextureDataPtr m_data_ptr = { nullptr };
		};

		DECL_SHARED_PTR(Texture);

		class TextureManager
		{
		public:
			static TextureManager* get_instance();
			TexturePtr get_texture(TextureDataPtr tex_ptr);

		private:
			std::map<TextureDataPtr, TexturePtr> tex_map;
		};
	}
}

#endif // !WATER_TEXTURE_H
