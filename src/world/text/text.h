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
#include "window/window_interface.h"
#include <set>

namespace water
{
	namespace world
	{
		struct Character: public std::enable_shared_from_this<Character> 
		{
			Character(char c, const math3d::Vector2& size, const math3d::Vector2& bearing, const math3d::Vector2I& advance, unsigned char* buffer);
			render::MeshDataPtr create_mesh(math3d::Vector2 base_pos, float scale);

			math3d::Vector2 size{ 0, 0 };
			math3d::Vector2 bearing{ 0,0 };
			math3d::Vector2I advance{ 0, 0 };
			render::TexturePtr texture{ nullptr };
			math3d::Vector2 pos{ 0, 0 };
			char c;
		};
		DECL_SHARED_PTR(Character);
		class Font: public std::enable_shared_from_this<Font>
		{
		public:
			Font(const std::string& fnt_filepath, const std::string& mat_filepath);
			void draw(const std::string& text, const math3d::Vector3& color, const math3d::Vector2& screen_pos, float scale);
		private:
			FT_Library m_ft;
			FT_Face m_face;
			render::TexturePtr m_texture{ nullptr };
			render::MaterialPtr m_material{ nullptr };
			std::map<char, CharacterPtr> m_char_map;
			unsigned int m_font_height{ 48 };
		};
		DECL_SHARED_PTR(Font);

		class Text
		{
		public:
			Text(const std::string& text, const math3d::Vector3& color, FontPtr font, const math3d::Vector2& screen_pos, float scale);
		public:
			void set_text(const std::string& text);
			void set_color(const math3d::Vector3& color);
			void set_font(FontPtr fnt);
			void set_scale(float scale);
			void set_pos(const math3d::Vector2& screen_pos);
			std::string get_text();
			void render();
		private:
			std::string m_text{ "" };
			FontPtr m_fnt{ nullptr };
			math3d::Vector3 m_color{ 255, 0, 0 };
			math3d::Vector2 m_pos{ 0, 0};
			float m_scale;

		};
		DECL_SHARED_PTR(Text);
		class TextManager
		{
		public:
			TextPtr create_text(const std::string& text, const math3d::Vector3& color, FontPtr font, const math3d::Vector2& screen_pos, float scale);
			void remove_text(TextPtr text);
			void render();
		private:
			std::set<TextPtr> m_tex_set;
		};
	}
}

#endif // !WATER_TEXT_H
