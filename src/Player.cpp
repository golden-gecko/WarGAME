
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Player.h"

//------------------------------------------------------------------------------

string Player::toString() {

	static char str[512];

	sprintf(
		str,
		"player\n  n\tame - %s\n  color - %s\nenergy\n  ratio - %.2f\n  stored - %.2f/%.2f\n  produced - %.2f/%.2f\n  used - %.2f/%.2f",
		m_name.c_str(),
		m_color.c_str(),
		m_energyRatio,
		m_energyStored,
		m_maxEnergyStored,
		m_energyProduced,
		m_maxEnergyProduced,
		m_energyUsed,
		m_maxEnergyUsed);

	return str;
}

//------------------------------------------------------------------------------

bool Player::update(float deltaTime) {

	m_energyStored += (m_energyProduced - m_energyUsed) * deltaTime;

	if (m_energyUsed > 0.0f)

		if (m_energyStored > 0.0f)

			m_energyRatio = 1.0f;

		else

			m_energyRatio = m_energyProduced / m_energyUsed;

	if (m_energyStored < 0.0f)

		m_energyStored = 0.0f;

	else if (m_energyStored > m_maxEnergyStored)

		m_energyStored = m_maxEnergyStored;

	return true;
}

//------------------------------------------------------------------------------
