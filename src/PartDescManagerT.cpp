
//------------------------------------------------------------------------------
// PartDescManagerTemp.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartDescManagerT.h"

//------------------------------------------------------------------------------

void PartDescManagerTemp::add(PartDesc* descriptor) {

	m_list.push_back(descriptor);

}

//------------------------------------------------------------------------------

PartDesc* PartDescManagerTemp::getByName(string name) {

	for (Iterator itr = m_list.begin(); itr != m_list.end(); itr++)

		if ((*itr)->m_name == name)

			return (*itr);

	return NULL;

}

//------------------------------------------------------------------------------

PartDescManagerTemp::Iterator PartDescManagerTemp::getFirst() {

	return m_list.begin();

}

//------------------------------------------------------------------------------

PartDescManagerTemp::Iterator PartDescManagerTemp::getLast() {

	return m_list.end();

}

//------------------------------------------------------------------------------
