/*
 * scenes.h
 *
 *  Created on: 03-Jan-2015
 *      Author: muneebahmad
 */

#ifndef SCENES_H_
#define SCENES_H_

#include <WiEngine.h>
#include "../Handlers/hudinterface.h"
#include "../Handlers/actionhandler.h"
#include "../Layers/hudlayer.h"
#include "../Util/particle.h"

class SplashScene: public wyScene {

public:
	SplashScene();
	~SplashScene();

};
/** end class SplashScene */

class MainMenuScene: public wyScene {

private:
	void mainMenuSetButtons();
	void setContents();
	void mainMenuSetBackground();
	void mainMenuAddLogo();
	void mainMenuSetFire();

	wySprite* mainMenuBg;
	wySprite* logo;
	wyButton* playButton;
	wyButton* moreFunButton;
	wyButton* rateButton;
	wyButton* infoButton;
	wyButton* exitButton;

	wyDirector* director;

public:
	MainMenuScene();
	~MainMenuScene();

	void onPlayButtonClicked();
	void onRateButtonClicked();
	void onMoreFunButtonClicked();
	void onExitButtonClicked();
	void onInfoButtonClicked();

	bool keyUp(wyKeyEvent& event);
	void showExitDialog();
	void onOKButtonClicked(wyTargetSelector* ts, void* data);
	void onCancelButtonClicked(wyTargetSelector* ts, void* data);

};
/** end class MainMenuScene. */

class EggFryingScene: public wyScene, public HudInterface {
private:
	void setContents();
	void eggFryingSetBg();
	void addStove();
	void addPan();
	void addCabnet();
	void eggAddCabnetItems();
	void addMainItems();
	void executeOilPouring();
	void setPouringParticleColor(int r, int g, int b);
	wyAction* getRotateActionWithCallback();
	void initializeTimer();
	void setSpriteAlpha(int alpha1, int alpha2, int alpoha3);
	void showPointingArrow();
	void fireParticleBegin();
	void setParticlePosition();
	void eggAddHudLayer();

	wySprite* eggFryingBg;
	wySprite* stove;
	wySprite* pan;
	wySprite* oilPan;
	wySprite* oilBottle;
	wySprite* eggCabnet;
	wySprite* cabnet;
	wySprite* cabnetCover;
	wySprite* panStick;
	wySprite* fryEgg;
	wySprite* fryEggHalfCooked;
	wySprite* fryEggFullCooked;
	wySprite* stoveButtSprite;
	wySprite* pointingArrow;

	wyButton* stoveKnob;
	HudLayer* hudLayer;
	wyParticleSystem* particleSystem;
	ActionHandler* actionHandler;

	wyDirector* director;
	wyScheduler* scheduler;

	static const int EGG_APPEARANCE_LEVEL_1 = 0x06;
	static const int EGG_APPEARANCE_LEVEL_2 = 0x07;
	static const int EGG_APPEARANCE_LEVEL_3 = 0x08;
	static const int EGG_APPEARANCE_LEVEL_4 = 0x09;
	static const int EGG_APPEARANCE_LEVEL_5 = 0xa;
	static const int EGG_APPEARANCE_LEVEL_6 = 0xb;
	static const int EGG_APPEARANCE_LEVEL_7 = 0xc;
	static const int EGG_APPEARANCE_LEVEL_8 = 0xd;
	static const int EGG_APPEARANCE_LEVEL_9 = 0xe;
	static const int EGG_APPEARANCE_LEVEL_FRIED = 0xf;
	static const int MODE_OPEN_CABNET = 0x5b;
	static const int MODE_DRAG_STIRRER = 0x5c;
	static const int MODE_DROP_EGG = 0x5d;
	static const int MODE_IGNITE_STOVE = 0x5e;
	static const int MODE_POUR_OIL = 0x5f;
	int fadingState;
	int mode;

	wyTargetSelector* mixingSelector;
	wyTimer* mixingTimer;

public:
	EggFryingScene();
	~EggFryingScene();

	bool keyUp(wyKeyEvent& event);

	virtual bool touchesBegan(wyMotionEvent& event) {
		wyPoint point = wyp(event.x[0], event.y[0]);
		wyRect stirrerRect = panStick->getBoundingBoxRelativeToWorld();
		wyRect oilBottleRect = oilBottle->getBoundingBoxRelativeToWorld();
		wyRect eggRect = eggCabnet->getBoundingBoxRelativeToWorld();

		switch (this->mode) {
		case MODE_IGNITE_STOVE:
			if (this->fadingState <= EGG_APPEARANCE_LEVEL_9) {
				scheduler->unscheduleLocked(this->mixingTimer);
			}
			break;
		case MODE_POUR_OIL:
			if (wyrContains(oilBottleRect, point)) {
				this->oilBottle->stopAllActions(true);
				wyAction* oilMove = wyMoveTo::make(0.2f,
						oilBottle->getPositionX(), oilBottle->getPositionY(),
						100.0f + oilBottle->getPositionX(),
						oilBottle->getPositionY() - 50.0f);
				this->oilBottle->runAction(oilMove);
				this->oilBottle->runAction(getRotateActionWithCallback());
				//soundsHandler->playPouringSound();
				//this->oilPan->setVisible(true);
				//this->oilPan->setAlpha(0);
				setEnabled(true);
				this->mode = MODE_DROP_EGG;
			}
			break;
		case MODE_DROP_EGG:
			if (wyrContains(eggRect, point)) {
				eggCabnet->stopAllActions(true);
				wyIntervalAction* eM = wyMoveTo::make(0.5f,
						eggCabnet->getPositionX(), eggCabnet->getPositionY(),
						fryEgg->getPositionX(), fryEgg->getPositionY());
				wyCallFunc* localFunc = wyCallFunc::make(
						wyTargetSelector::make(this,
								SEL(EggFryingScene::eggDroppedCallback)));
				wyFiniteTimeAction* aFinite[1];
				aFinite[0] = localFunc;
				wySequence* localSeq = (wySequence*) wySequence::make(eM,
						aFinite[0], NULL);
				eggCabnet->runAction(localSeq);
				setEnabled(false);
				wyAction* knobFadeIn = wyFadeIn::make(0.5f, true);
				stoveKnob->runAction(knobFadeIn);
				this->mode = MODE_IGNITE_STOVE;
			}
			break;
		case MODE_DRAG_STIRRER:
			scheduler->scheduleLocked(this->mixingTimer);
			break;
		default:
			break;
		}

		return true;
	}

	virtual bool touchesEnded(wyMotionEvent& event) {
		wyPoint point = wyp(event.x[0], event.y[0]);
		switch (this->mode) {
		case MODE_DRAG_STIRRER:
			scheduler->unscheduleLocked(this->mixingTimer);
			break;
		}
		return true;
	}

	virtual bool touchesMoved(wyMotionEvent& event) {
		wyPoint point = wyp(event.x[0], event.y[0]);
		wyRect rect = this->cabnetCover->getBoundingBoxRelativeToWorld();
		wyRect doodle = this->panStick->getBoundingBoxRelativeToWorld();

		switch (this->mode) {
		case MODE_OPEN_CABNET:
			if (wyrContains(rect, point)) {
				wyIntervalAction* coverMove = wyMoveTo::make(0.5f,
						cabnetCover->getPositionX(),
						cabnetCover->getPositionY(),
						-(cabnetCover->getWidth() / 2.0f - 30.0f),
						cabnetCover->getPositionY());
				this->cabnetCover->runAction(coverMove);
				this->cabnetCover->setTouchEnabled(false);
				this->oilBottle->runAction(
						actionHandler->getRepeatingJumpAction(0.5f,
								oilBottle->getPositionX(),
								oilBottle->getPositionY(), 30));
				this->mode = MODE_POUR_OIL;
			}
			break;
		case MODE_DRAG_STIRRER:
			if (wyrContains(doodle, point)) {
				panStick->setPosition(point.x, point.y);
			}
			break;
		default:
			break;
		}
		return true;
	}

	void eggDroppedCallback();
	void onMixingTick();
	void onStoveKnobClicked();
	void pourActionCallback();
	void rotateObjectActionCallback();

};
/** end class EggFryingScene */

#endif /* SCENES_H_ */
