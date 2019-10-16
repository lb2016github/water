#ifndef WATER_TEXTURE_H
#define WATER_TEXTURE_H
#include <string>
#include "render_const.h"
#include "filesystem/image.h"
#include <vector>
#include <memory>
#include <map>
#include "common/common.h"


namespace water
{
	namespace render
	{
		enum TextureParameterName
		{
			WATER_TEXTURE_MIN_FILTER,
			WATER_TEXTURE_MAG_FILTER,
			WATER_TEXTURE_WRAP_T,
			WATER_TEXTURE_WRAP_S,
			WATER_TEXTURE_WRAP_S
		};
		enum TextureParameterValue
		{
			WATER_LINEAR,
			WATER_REPEAT,
			WATER_CLAMP_TO_EDGE,
		};
		
		typedef std::map<TextureParameterName, TextureParameterValue> TextureParameterConfig;

		struct TextureData: public std::enable_shared_from_this<TextureData>
		{
			void load();
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
			virtual void set_tex_param(const TextureParameterConfig& tex_config);

			TextureType m_type;
			TextureDataPtr m_data_ptr = { nullptr };
			TextureParameterConfig m_tex_config;
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
