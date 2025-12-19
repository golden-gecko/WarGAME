
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ObjectOrder.h"

#include "Object.h"
#include "ObjectDesc.h"

//------------------------------------------------------------------------------

string ObjectOrder::toString() {

	static char str[512];

	switch (m_type) {

		case OOT_ATTACK_OBJECT:

			sprintf(
				str,
				"attack object (%s at %.2f, %.2f, %.2f)",
				((Object*)m_param)->getName().c_str(),
				((Object*)m_param)->getPosition().x,
				((Object*)m_param)->getPosition().y,
				((Object*)m_param)->getPosition().z);

			break;

		case OOT_ATTACK_POSITION:

			sprintf(
				str,
				"attack position (%.2f, %.2f, %.2f)",
				m_vector.x, m_vector.y, m_vector.z);

			break;

		case OOT_CONSTRUCT:

			sprintf(str, "construct (%s)",
				((ObjectDesc*)m_param)->getName().c_str());

			break;

		case OOT_FOLLOW:

			sprintf(
				str,
				"follow (%s at %.2f, %.2f, %.2f)",
				((Object*)m_param)->getName().c_str(),
				((Object*)m_param)->getPosition().x,
				((Object*)m_param)->getPosition().y,
				((Object*)m_param)->getPosition().z);

			break;

		case OOT_MOVE_TO_OBJECT:

			sprintf(
				str,
				"move to object (%s at %.2f, %.2f, %.2f)",
				((Object*)m_param)->getName().c_str(),
				((Object*)m_param)->getPosition().x,
				((Object*)m_param)->getPosition().y,
				((Object*)m_param)->getPosition().z);

			break;

		case OOT_MOVE_TO_POSITION:

			sprintf(
				str,
				"move to position (%.2f, %.2f, %.2f)",
				m_vector.x, m_vector.y, m_vector.z);

			break;

		case OOT_PATROL:

			sprintf(
				str,
				"patrol (%.2f, %.2f, %.2f)",
				m_vector.x, m_vector.y, m_vector.z);

			break;

		case OOT_RESUPPLY:

			sprintf(
				str,
				"resupply (%s at %.2f, %.2f, %.2f)",
				((Object*)m_param)->getName().c_str(),
				((Object*)m_param)->getPosition().x,
				((Object*)m_param)->getPosition().y,
				((Object*)m_param)->getPosition().z);

			break;

		case OOT_REPAIR:

			sprintf(
				str,
				"repair (%s at %.2f, %.2f, %.2f)",
				((Object*)m_param)->getName().c_str(),
				((Object*)m_param)->getPosition().x,
				((Object*)m_param)->getPosition().y,
				((Object*)m_param)->getPosition().z);

			break;

		case OOT_STOP:

			sprintf(str, "stop");

			break;
	}

	return str;
}

//------------------------------------------------------------------------------
