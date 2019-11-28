#ifndef WATER_TEXT_H
#define WATER_TEXT_H
#include <string>
#include "ft2build.h"
#include FT_FREETYPE_H
#include "render/texture.h"
#include "math3d/math3d.hpp"
#include "render/material.h"
#include <map>
#include "common/common.h"
#include <memory>

namespace water
{
	namespace text
	{
		struct Character: public std::enable_shared_from_this<Character> 
		{
			Character(char c, const math3d::Vector2& size, const math3d::Vector2& bearing, const math3d::IVector2& advance, unsigned char* buffer);
			render::MeshDataPtr create_mesh(math3d::Vector2 base_pos);

			math3d::Vector2 size{ 0, 0 };
			math3d::Vector2 bearing{ 0,0 };
			math3d::IVector2 advance{ 0 };
			render::TexturePtr texture{ nullptr };
			math3d::Vector2 pos{ 0, 0 };
			char c;
		};
		DECL_SHARED_PTR(Character);
		class Font
		{
		public:
			Font(const std::string& fnt_filepath, const std::string& mat_filepath);
			void draw(const std::string& text, const math3d::Vector3& color, const math3d::Vector2& screen_pos);
		private:
			FT_Library m_ft;
			FT_Face m_face;
			render::TexturePtr m_texture{ nullptr };
			render::MaterialPtr m_material{ nullptr };
			std::map<char, CharacterPtr> m_char_map;
			unsigned int m_font_height{ 48 };
		};
		class Text
		{
		public:
			void set_text(const std::string& text);
			std::string get_text();
			void set_font(Font* fnt);
			void render(const math3d::Vector3& color, const math3d::Vector2& screen_pos);
		private:
			std::string m_text{ "" };
			Font* m_fnt{ nullptr };
		};

	}
}

#endif // !WATER_TEXT_H
