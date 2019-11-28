#ifndef WATER_TEXT_H
#define WATER_TEXT_H
#include <string>
#include "ft2build.h"
#include FT_FREETYPE_H
#include "render/texture.h"
#include "math3d/math3d.hpp"
#include "render/material.h"
#include <map>

namespace water
{
	namespace text
	{
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
			std::map<char, render::TexturePtr> m_texture_map;
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
