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
	namespace text
	{
		void Text::set_text(const std::string & text)
		{
			m_text = text;
		}
		std::string Text::get_text()
		{
			return m_text;
		}
		void Text::set_font(Font * fnt)
		{
			m_fnt = fnt;
		}
		void Text::render(const math3d::Vector3& color, const math3d::Vector2& screen_pos)
		{
			m_fnt->draw(m_text, color, screen_pos);
		}
		Font::Font(const std::string & fnt_filepath, const std::string& mat_filepath)
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
			FT_Set_Pixel_Sizes(m_face, 0, 48);
			// init texture
			m_texture = render::get_device()->create_texture(render::TEXTURE_2D);
			// init material
			auto rst = render::Material::load_from_file(mat_filepath);
			assert(rst.size() > 0);
			m_material = rst[0];
		}
		void Font::draw(const std::string & text, const math3d::Vector3& color, const math3d::Vector2& screen_pos)
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
				auto rst = m_texture_map.find(c);
				render::TexturePtr texture = nullptr;
				if (rst == m_texture_map.end())
				{
					if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
					{
						log_error("ERROR::FREETYPE: Failed to load Glyph %s", c);
						continue;
					}
					// create glyph texture
					filesystem::ImagePtr img = std::make_shared<filesystem::Image>();
					auto bitmap = m_face->glyph->bitmap;
					math3d::Vector2 size(bitmap.width, bitmap.rows);
					auto data_size = bitmap.width * bitmap.rows;
					unsigned char* data = new unsigned char[data_size];
					memcpy(data, bitmap.buffer, data_size);
					img->set_data(size.x, size.y, 1, &data);
					render::TextureDataPtr tex_data = std::make_shared<render::TextureData>();
					tex_data->images.push_back(img);
					texture = render::get_device()->create_texture(render::TEXTURE_2D);
					texture->set_tex_data(tex_data);
					m_texture_map[c] = texture;
				}
				else
				{
					texture = rst->second;
				}
				param_map->set_texture("tex", texture);
				// create mesh
				auto mesh = std::make_shared<render::MeshData>(render::TRIANGLES);
				
				auto size = texture->m_data_ptr->get_size();

				mesh->position = 
				{
					{base_pos.x, base_pos.y + size.y, 0 },
					{base_pos.x + 0, base_pos.y + 0, 0},
					{base_pos.x + size.x, base_pos.y + 0, 0},
					{base_pos.x + 0, base_pos.y + size.y, 0 },
					{base_pos.x + size.x, base_pos.y + 0, 0},
					{base_pos.x + size.x, base_pos.y + size.y, 0},
				};
				mesh->coordinate = 
				{
					{0, 1},
					{0, 0},
					{1, 0},
					{0, 1},
					{1, 0},
					{1, 1},
				};
				m_material->render(mesh);
				base_pos.x += size.x;
			}
		}
	}
}
