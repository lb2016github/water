#ifndef WATER_TEXTURE_H
#define WATER_TEXTURE_H
#include <string>
#include "render_const.h"
#include "filesystem/image.h"
#include <vector>
#include <memory>
#include "common/common.h"


namespace water
{
	namespace render
	{
		struct TextureData: public std::enable_shared_from_this<TextureData>
		{
			void load();
			TextureType tex_type;
			std::vector<filesystem::ImagePtr> images;
		};

		DECL_SHARED_PTR(TextureData);

		struct Texture
		{
			virtual void bind(TextureUnit tex_unit) = 0;
		};

		DECL_SHARED_PTR(Texture);
	}
}

#endif // !WATER_TEXTURE_H
