#include "texture.h"

namespace water
{
	namespace render
	{
		void TextureData::load()
		{
			for each (auto img in images)
			{
				if (!img->m_loaded)
				{
					img->load();
				}
			}
		}
	}
}