
//------------------------------------------------------------------------------
// ObjectDescManagerTemp.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ObjectDescManagerTemp.h"

//------------------------------------------------------------------------------

void ObjectDescManagerTemp::add(ObjectDesc* objectDesc) {

	m_list.push_back(objectDesc);

}

//------------------------------------------------------------------------------

ObjectDesc* ObjectDescManagerTemp::getByName(string name) {

	for (Iterator itr = m_list.begin(); itr != m_list.end(); itr++)

		if ((*itr)->m_name == name)

			return (*itr);

	return NULL;

}

//------------------------------------------------------------------------------

ObjectDescManagerTemp::Iterator ObjectDescManagerTemp::getFirst() {

	return m_list.begin();

}

//------------------------------------------------------------------------------

ObjectDescManagerTemp::Iterator ObjectDescManagerTemp::getLast() {

	return m_list.end();

}

//------------------------------------------------------------------------------
