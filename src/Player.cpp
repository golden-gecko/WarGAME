
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Player.h"

//------------------------------------------------------------------------------

string Player::toString() {

	static char str[1024];

	sprintf(
		str,
		"\
		Name                        %s\n\
		Color                       %s\n\
		\n\
		Energy Ratio                %.2f\n\
		Energy Stored               %.2f/%.2f\n\
		Energy Produced             %.2f/%.2f\n\
		Energy Used                 %.2f/%.2f\n\
		\n\
		Armour Defence Modifier     %.2f\n\
		Armour Hit Points Modifier  %.2f\n\
		Body Hit Points Modifier    %.2f\n\
		Engine Hit Points Modifier  %.2f\n\
		Engine Speed Modifier       %.2f\n\
		Weapon Damage Modifier      %.2f\n\
		Weapon Hit Points Modifier  %.2f\n\
		Weapon Power Modifier       %.2f\n\
		Weapon Range Modifier       %.2f\n\
		Weapon Reload Time Modifier %.2f",
		m_name.c_str(),
		m_color.c_str(),
		m_energyRatio,
		m_energyStored,
		m_maxEnergyStored,
		m_energyProduced,
		m_maxEnergyProduced,
		m_energyUsed,
		m_maxEnergyUsed,
		m_armourDefenceModifier,
		m_armourHitPointsModifier,
		m_bodyHitPointsModifier,
		m_engineHitPointsModifier,
		m_engineSpeedModifier,
		m_weaponDamageModifier,
		m_weaponHitPointsModifier,
		m_weaponPowerModifier,
		m_weaponRangeModifier,
		m_weaponReloadTimeModifier);

	return str;
}

//------------------------------------------------------------------------------

string Player::toStringShort() {

	static char str[256];

	sprintf(str, "Name  %s\nColor %s", m_name.c_str(), m_color.c_str());

	return str;
}

//------------------------------------------------------------------------------

string Player::toStringEnemy() {

	static char str[256];

	sprintf(str, "Name  %s\nColor %s", m_name.c_str(), m_color.c_str());

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
