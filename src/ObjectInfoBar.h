
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectInfoBar: public Ogre::Singleton<ObjectInfoBar> {

		protected:

			CEGUI::StaticImage*			m_hoveredImage;
			Ogre::TexturePtr			m_hoveredTexture;

			bool						m_visible;
			vector<CEGUI::StaticImage*>	m_images;
			vector<Ogre::TexturePtr>	m_textures;

		public:

			ObjectInfoBar(): m_hoveredImage(NULL), m_hoveredTexture(NULL), m_visible(false) { }

			void init();

			void setVisible(bool visible) {

				m_visible = visible;
			}

			void changeVisible() {

				m_visible = !m_visible;
			}

			void update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
