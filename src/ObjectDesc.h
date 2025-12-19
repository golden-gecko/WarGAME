
//------------------------------------------------------------------------------
// ObjectDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "BodyDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectDesc {

		public:

			enum ObjectDescType {

				ODT_BUILDING_DESC		= 0x0080 + PartDesc::PDT_ARMOUR_DESC + PartDesc::PDT_BODY_DESC + PartDesc::PDT_ENERGY_SHIELD_DESC,
				ODT_FORTIFICATION_DESC	= 0x0100 + PartDesc::PDT_ARMOUR_DESC + PartDesc::PDT_BODY_DESC + PartDesc::PDT_ENERGY_SHIELD_DESC + PartDesc::PDT_WEAPON_DESC,
				ODT_MISSILE_DESC		= 0x0200 + PartDesc::PDT_BODY_DESC + PartDesc::PDT_EXPLOSIVE_DESC,
				ODT_OBJECT_DESC			= 0x0400 + PartDesc::PDT_BODY_DESC,
				ODT_PLANT_DESC			= 0x0800 + PartDesc::PDT_BODY_DESC,
				ODT_POWER_PLANT_DESC	= 0x1000 + PartDesc::PDT_ARMOUR_DESC + PartDesc::PDT_BODY_DESC + PartDesc::PDT_ENERGY_SHIELD_DESC + PartDesc::PDT_POWER_REACTOR_DESC,
				ODT_VEHICLE_DESC		= 0x2000 + PartDesc::PDT_ARMOUR_DESC + PartDesc::PDT_BODY_DESC + PartDesc::PDT_ENERGY_SHIELD_DESC + PartDesc::PDT_ENGINE_DESC + PartDesc::PDT_WEAPON_DESC

			};

			string			m_name;
			ObjectDescType	m_type;
			BodyDesc*		m_bodyDesc;

			ObjectDesc(string name, BodyDesc* bodyDesc)

				:	m_name(name),
					m_type(ODT_OBJECT_DESC),
					m_bodyDesc(bodyDesc) { }

			ObjectDesc* is(ObjectDescType type) { return (m_type == type) ? this : NULL; }
			BuildingDesc* isBuildingDesc() { return (BuildingDesc*)is(ODT_BUILDING_DESC); }
			FortificationDesc* isFortificationDesc() { return (FortificationDesc*)is(ODT_FORTIFICATION_DESC); }
			PowerPlantDesc* isPowerPlantDesc() { return (PowerPlantDesc*)is(ODT_POWER_PLANT_DESC); }
			VehicleDesc* isVehicleDesc() { return (VehicleDesc*)is(ODT_VEHICLE_DESC); }

			bool hasPartDesc(PartDesc::PartDescType partDescType) {

				return (m_type & partDescType) ? true : false;
			}

			virtual string toString() {

				return m_name + "\n\n" + m_bodyDesc->toString();
			}
	};
};

//------------------------------------------------------------------------------
