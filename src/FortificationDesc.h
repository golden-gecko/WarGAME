
//------------------------------------------------------------------------------
// FortificationDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "ObjectDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class FortificationDesc : public ObjectDesc {

		public:

			ArmourDesc*	m_armourDesc;
			WeaponDesc*	m_weaponDesc;

			FortificationDesc(	string name,
								ArmourDesc* armourDesc,
								BodyDesc* bodyDesc,
								WeaponDesc* weaponDesc)

				:	ObjectDesc(name, bodyDesc),
					m_armourDesc(armourDesc),
					m_weaponDesc(weaponDesc)
			
			{

				m_type = ODT_FORTIFICATION_DESC;
			
			}

	};

};

//------------------------------------------------------------------------------
