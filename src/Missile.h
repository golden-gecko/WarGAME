
//------------------------------------------------------------------------------
// Missile.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ObjectTemp.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Missile : public ObjectTemp {

		public:

			ObjectTemp*			m_parent;
			ParticleSystem*	m_explosion;

		public:

			Missile(ObjectTemp* parent);

			virtual ~Missile();

			virtual bool update(float deltaTime);
	};
};

//------------------------------------------------------------------------------
