#include "text.h"
#include "common/log.h"
#include "ft2build.h"
#include "render/device.h"
#include "render/material.h"
#include "render/mesh.h"
#include "filesystem/filesystem.h"
#include "world/gameobjects/world.h"


namespace water
{
	namespace world
	{
		Text::Text(const std::string& text, const math3d::Vector3& color, FontPtr font, const math3d::Vector2& screen_pos, float scale)
			:m_text(text), m_color(color), m_fnt(font), m_pos(screen_pos), m_scale(scale)
		{
		}
		void Text::set_text(const std::string& text)
		{
			m_text = text;
		}
		void Text::set_color(const math3d::Vector3& color)
		{
			m_color = color;
		}
		std::string Text::get_text()
		{
			return m_text;
		}
		void Text::set_font(FontPtr fnt)
		{
			m_fnt = fnt;
		}
		void Text::set_scale(float scale)
		{
			m_scale = scale;
		}
		void Text::set_pos(const math3d::Vector2& screen_pos)
		{
			m_pos = screen_pos;
		}
		void Text::render()
		{
			m_fnt->draw(m_text, m_color, m_pos, m_scale);
		}
		Font::Font(const std::string& fnt_filepath, const std::string& mat_filepath)
		{
			// init ft library
			if (FT_Init_FreeType(&m_ft))
			{
				log_error("ERROR::FREETYPE: Could not init FreeType Library");
			}
			// init font as face
			auto abs_path = filesystem::FileSystem::get_instance()->get_absolute_path(fnt_filepath);
			if (FT_New_Face(m_ft, abs_path.c_str(), 0, &m_face))
			{
				log_error("ERROR::FREETYPE: Faild to load font");
			}
			// set size to load glyphs as
			FT_Set_Pixel_Sizes(m_face, 0, m_font_height);
			// init texture
			m_texture = render::get_device()->create_texture(render::TEXTURE_2D);
			// init material
			auto rst = render::Material::load_from_file(mat_filepath);
			assert(rst.size() > 0);
			m_material = rst[0];
		}
		void Font::draw(const std::string& text, const math3d::Vector3& color, const math3d::Vector2& screen_pos, float scale)
		{
			math3d::Vector2 base_pos = screen_pos;
			// init material
			auto param_map = m_material->get_param_map(0);
			param_map->set_param("color", color);
			auto world_ptr = world::World::get_instance();
			math3d::Vector2 screen_size = world_ptr->get_window()->get_window_size();
			param_map->set_param("screen_size", screen_size);
			// Create Render Tasks
			// mesh, program, render_state, param_map, dependent
			for each (auto c in text)
			{
				auto rst = m_char_map.find(c);
				CharacterPtr char_ptr = nullptr;
				if (rst == m_char_map.end())
				{
					if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
					{
						log_error("ERROR::FREETYPE: Failed to load Glyph %s", c);
						continue;
					}
					auto glyph = m_face->glyph;
					char_ptr = std::make_shared<Character>(
						c,
						math3d::Vector2(glyph->bitmap.width, glyph->bitmap.rows),
						math3d::Vector2(glyph->bitmap_left, glyph->bitmap_top),
						math3d::IVector2(glyph->advance.x, glyph->advance.y),
						glyph->bitmap.buffer
						);
					m_char_map[c] = char_ptr;
				}
				else
				{
					char_ptr = rst->second;
				}
				param_map->set_texture("tex", char_ptr->texture);
				auto mesh = char_ptr->create_mesh(base_pos, scale);
				m_material->render(mesh);

				base_pos.x += (char_ptr->advance.x >> 6) * scale;
			}
		}
		Character::Character(char c, const math3d::Vector2& size, const math3d::Vector2& bearing, const math3d::IVector2& advance, unsigned char* buffer)
			: size(size), bearing(bearing), advance(advance), pos(bearing.x, bearing.y - size.y)
		{
			// create glyph texture
			filesystem::ImagePtr img = std::make_shared<filesystem::Image>();
			auto data_size = size.x * size.y;
			unsigned char* data = new unsigned char[data_size];
			memcpy(data, buffer, data_size);
			img->set_data(size.x, size.y, 1, &data);
			render::TextureDataPtr tex_data = std::make_shared<render::TextureData>();
			tex_data->images.push_back(img);
			texture = render::get_device()->create_texture(render::TEXTURE_2D);
			texture->set_tex_data(tex_data);
		}
		render::MeshDataPtr Character::create_mesh(math3d::Vector2 base_pos, float scale)
		{
			// create mesh
			auto mesh = std::make_shared<render::MeshData>(render::TRIANGLES);
			math3d::Vector2 p1 = {
				base_pos.x + pos.x * scale,
				base_pos.y + pos.y * scale
			};
			math3d::Vector2 p2 = {
				p1.x + size.x * scale,
				p1.y + size.y * scale
			};

			mesh->position =
			{
				{p1.x, p2.y, 0},
				{p1.x, p1.y, 0},
				{p2.x, p1.y, 0},
				{p1.x, p2.y, 0},
				{p2.x, p1.y, 0},
				{p2.x, p2.y, 0},
			};
			mesh->coordinate =
			{
				{0, 0},
				{0, 1},
				{1, 1},
				{0, 0},
				{1, 1},
				{1, 0},
			};
			return mesh;
		}

		TextPtr TextManager::create_text(const std::string& text, const math3d::Vector3& color, FontPtr font, const math3d::Vector2& screen_pos, float scale)
		{
			auto text_ptr = std::make_shared<Text>(text, color, font, screen_pos, scale);
			m_tex_set.emplace(text_ptr);
			return text_ptr;
		}
		void TextManager::remove_text(TextPtr text)
		{
			auto rst = m_tex_set.find(text);
			if (rst != m_tex_set.end())
			{
				m_tex_set.erase(rst);
			}
		}
		void TextManager::render()
		{
			for (auto iter : m_tex_set)
			{
				iter->render();
			}
		}
}
}
