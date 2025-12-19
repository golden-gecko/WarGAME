#pragma once

#include "Dependencies.h"
#include "Graphics.h"
#include "TemplateManager.h"

enum InterfaceState
{
	IS_PLACE_STRUCTURE,
	IS_SELECT_OBJECT,
	IS_GIVE_ORDER
};

class GUI : public Ogre::Singleton<GUI>
{
public:
	bool init();
	void shutdown();
	void update(float time);

	void clearLastOrder()
	{
		mLastOrder = OT_NONE;
	}
	bool isMouseOver() const
	{
		return mMouseOver;
	}
	void toggleEditor()
	{
		mEditor->setVisible(!(mEditor->isVisible()));
	}
	void toggleVisible()
	{
		mSystem->getGUISheet()->setVisible(!(mSystem->getGUISheet()->isVisible()));
	}

	unsigned int getLastOrder() const
	{
		return mLastOrder;
	}
	CEGUI::OgreCEGUIRenderer* getRenderer() const
	{
		return mRenderer;
	}
	bool getVisible() const
	{
		return mSystem->getGUISheet()->isVisible();
	}

	void setLastOrder(unsigned int order)
	{
		mLastOrder = order;
	}
	void setPlayerText(const std::string& text)
	{
		mResources->setText(text);
	}
	void setStatusText(const std::string& text)
	{
		mStatus->setText(text);
	}
	void setState(unsigned int state)
	{
		mState = state;
	}

protected:
	unsigned int				mLastOrder;
	bool						mMouseOver;
	unsigned int				mState;
	StructureTemplate*			mStructure;

	CEGUI::OgreCEGUIRenderer*	mRenderer;
	CEGUI::System*				mSystem;

	CEGUI::Window*				mConsole;
	CEGUI::Window*				mMinimap;
	CEGUI::Window*				mResources;
	CEGUI::Window*				mStatus;
	CEGUI::Window*				mEditor;

	CEGUI::Window*				mGroups;
	CEGUI::PushButton*			mGroupButtons[10];

	CEGUI::Listbox*				mObjectList;
	CEGUI::Window*				mObjectDetails;

	CEGUI::Listbox*				mPlayerList;
	CEGUI::Listbox*				mPlayerResources;
	CEGUI::Window*				mPlayerDetails;

	CEGUI::Listbox*				mTemplateList;
	CEGUI::Window*				mTemplateDetails;
	CEGUI::Window*				mTemplatePicture;

	std::map<std::string, CEGUI::PushButton*>	mOrders;
	CEGUI::Checkbox*							mSafe;
	CEGUI::Window*								mAbilities[8];
	std::map<std::string, CEGUI::RadioButton*>	mBehaviours;
	CEGUI::Window*								mStructures[8];
	CEGUI::Window*								mUnits[8];


	bool mouseClick(const CEGUI::EventArgs& e);
	bool mouseEnters(const CEGUI::EventArgs& e);
	bool mouseLeaves(const CEGUI::EventArgs& e);
	bool mouseMove(const CEGUI::EventArgs& e);

	void mouseLeftClick(const CEGUI::MouseEventArgs& args);
	void mouseRightClick(const CEGUI::MouseEventArgs& args);

	bool minimapClick(const CEGUI::EventArgs& e);
	bool groupButtonClick(const CEGUI::EventArgs& e);
	bool orderClick(const CEGUI::EventArgs& e);
	bool behaviourClick(const CEGUI::EventArgs& e);
	bool structureClick(const CEGUI::EventArgs& e);
	bool unitClick(const CEGUI::EventArgs& e);

	bool playerListSelectionChanged(const CEGUI::EventArgs& e);
	bool playerResourcesSelectionChanged(const CEGUI::EventArgs& e);
	bool safeClick(const CEGUI::EventArgs& e);
	bool objectListSelectionChanged(const CEGUI::EventArgs& e);
	bool templateListSelectionChanged(const CEGUI::EventArgs& e);
};
