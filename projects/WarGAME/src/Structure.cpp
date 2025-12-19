#include "Dependencies.h"
#include "Structure.h"

Structure::Structure(unsigned int id, unsigned int type, const std::string& mesh) : Unit(id, type, mesh)
{
}

void Structure::onCreate(unsigned int creator)
{
	setHealth(1.0f);
	setState(OS_UNDER_CONSTRUCTION);
}

void Structure::onDestroy(unsigned int destroyer)
{
}

void Structure::update(float time)
{
	switch (mState)
	{
		case OS_RECEIVE_ORDER:
		{
			switch (mOrders.front().getType())
			{
				case OT_CONSTRUCT:
				case OT_DESTROY:
				case OT_DISABLE:
				case OT_ENABLE:
				case OT_REPAIR:
				case OT_STOP:

					break;
			}

			break;
		}

		case OS_REMOVE_ORDER:
		{
			mOrders.pop_front();

			if (mOrders.size())
			{
				setState(OS_RECEIVE_ORDER);
			}

			break;
		}

		case OS_UNDER_CONSTRUCTION:
		{
			if (mHealth < mMaxHealth)
			{
				mHealth += 10.0f * time;

				if (mHealth >= mMaxHealth)
				{
					setState(OS_DEFAULT);
				}
			}

			break;
		}
	}
}
