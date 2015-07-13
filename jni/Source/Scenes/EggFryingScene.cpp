/*
 * EggFryingScene.cpp
 *
 *  Created on: 07-Jun-2015
 *      Author: muneebahmad
 */

#include "scenes.h"
#include "../Util/particle.h"

wySize size;

EggFryingScene::EggFryingScene() {
	this->director = wyDirector::getInstance();
	size = director->getWindowSize();
	this->actionHandler = new ActionHandler();
	setTouchEnabled(true);
	fadingState = EGG_APPEARANCE_LEVEL_1;
	mode = MODE_OPEN_CABNET;
	scheduler = wyScheduler::getInstance();
	setContents();
}

EggFryingScene::~EggFryingScene() {

}

void EggFryingScene::setContents() {
	initializeTimer();
	eggFryingSetBg();
	addStove();
	addPan();
	addCabnet();
	eggAddCabnetItems();
	addMainItems();
	eggAddHudLayer();
}

void EggFryingScene::eggFryingSetBg() {
	this->eggFryingBg = wySprite::make(
			wyTexture2D::make("bgs/bg_eggfrying_scene.png"));
	this->eggFryingBg->setPosition(size.width / 2.0f, size.height / 2.0f);
	this->eggFryingBg->setContentSize(size.width, size.height);
	this->eggFryingBg->setAutoFit(true);
	EggFryingScene::addChild(eggFryingBg, 0, 1);
}

void EggFryingScene::addStove() {
	this->stove = wySprite::make(wyTexture2D::make("art/stove_inverted2.png"));
	this->stove->setPosition(
			size.width / 2.0f + (stove->getWidth() / 4.0f) - 4.0f,
			size.height / 2.0f - 50.0f);
	EggFryingScene::addChild(stove, 1, 1);

	wyIntervalAction* zoomIn = wyScaleTo::make(0.5f, 1.0f, 1.3f);
	wyIntervalAction* delay = wyDelayTime::make(0.5f);
	wyIntervalAction* seq = wySequence::make(delay, zoomIn, NULL);
	this->stove->runAction(seq);
}

void EggFryingScene::addPan() {
	this->pan = wySprite::make(wyTexture2D::make("art/pan3.png"));
	this->pan->setPosition((size.width / 2.0f) - 15.0f, -800.0f);
	EggFryingScene::addChild(pan, 2, 2);

	wyIntervalAction* panMove = wyMoveTo::make(0.2f, pan->getPositionX(),
			-800.0f, pan->getPositionX(), (size.height / 2.0f) - 140.0f);
	wyIntervalAction* delay = wyDelayTime::make(2.0f);
	wyIntervalAction* panSeq = wySequence::make(delay, panMove, NULL);
	this->pan->runAction(panSeq);
}

void EggFryingScene::addCabnet() {
	this->cabnet = wySprite::make(wyTexture2D::make("art/cabnet.png"));
	this->cabnet->setPosition(size.width / 2.0f,
			size.height - ((cabnet->getHeight() / 2.0f) + 5.0f));
	EggFryingScene::addChild(cabnet, 3, 3);

	this->cabnetCover = wySprite::make(
			wyTexture2D::make("art/cabnet_cover2.png"));
	this->cabnetCover->setPosition(size.width / 2.0f, cabnet->getPositionY());
	EggFryingScene::addChild(cabnetCover, 6, 6);
}

void EggFryingScene::eggAddCabnetItems() {
	this->oilBottle = wySprite::make(wyTexture2D::make("art/oil1.png"));
	this->oilBottle->setPosition(120.0f, size.height - 120.0f);
	EggFryingScene::addChild(oilBottle, 4, 4);

	this->eggCabnet = wySprite::make(wyTexture2D::make("art/egg2.png"));
	this->eggCabnet->setPosition(size.width - 120.0f, size.height - 140.0f);
	EggFryingScene::addChild(eggCabnet, 5, 5);
}

void EggFryingScene::addMainItems() {
	this->stoveButtSprite = wySprite::make(wyTexture2D::make("art/knob1.png"));
	this->stoveKnob = wyButton::make(this->stoveButtSprite, stoveButtSprite, NULL, NULL, NULL,
			wyTargetSelector::make(this, SEL(EggFryingScene::onStoveKnobClicked)));
	stoveKnob->setPosition(size.width - 80.0f, size.height / 3.6f - 40.0f);
	EggFryingScene::addChild(stoveKnob, 7, 7);
	this->stoveKnob->setAlpha(0);

	this->oilPan = wySprite::make(wyTexture2D::make("art/oilpan.png"));
	this->oilPan->setPosition(this->pan->getPositionX(), (size.height / 2.0f) + 20.0f);
	EggFryingScene::addChild(oilPan, 7, 7);
	oilPan->setAlpha(0);

	this->fryEgg = wySprite::make(wyTexture2D::make("art/fryegg1.png"));
	this->fryEgg->setPosition(this->pan->getPositionX(), (size.height / 2.0f) + 20.0f);
	EggFryingScene::addChild(fryEgg, 8, 8);
	this->fryEgg->setAlpha(0);

	this->fryEggHalfCooked = wySprite::make(wyTexture2D::make("art/fryegg2.png"));
	this->fryEggHalfCooked->setPosition(fryEgg->getPositionX(), fryEgg->getPositionY());
	EggFryingScene::addChild(fryEggHalfCooked, 9, 9);
	this->fryEggHalfCooked->setAlpha(0);

	this->fryEggFullCooked = wySprite::make(wyTexture2D::make("art/fryegg3.png"));
	this->fryEggFullCooked->setPosition(fryEgg->getPositionX(), fryEgg->getPositionY());
	EggFryingScene::addChild(fryEggFullCooked, 10, 10);
	this->fryEggFullCooked->setAlpha(0);

	this->panStick = wySprite::make(wyTexture2D::make("art/panstick1.png"));
	this->panStick->setPosition(size.width + 500.0f, size.height / 2.0f);
	EggFryingScene::addChild(panStick, 11, 11);
}

void EggFryingScene::executeOilPouring() {
	wyColor3B color;
	color.r = 255;
	color.g = 213;
	color.b = 63;

	this->particleSystem = ParticleLiquid::make();
	this->particleSystem->setPosition(this->oilBottle->getPositionX() + oilBottle->getHeight() / 1.5f,
			this->oilBottle->getPositionY() - 30.0f);
	this->particleSystem->setScale(2.1f);
	this->particleSystem->setDuration(1.8f);
	setPouringParticleColor(color.r, color.g, color.b);
	EggFryingScene::addChild(this->particleSystem, 12, 12);

	wyIntervalAction* action1 = (wyIntervalAction*) wyFadeTo::make(2.0f, 0, 255);
	wyCallFunc* func = (wyCallFunc*) wyCallFunc::make(wyTargetSelector::make(this,
			SEL(EggFryingScene::pourActionCallback)));
	wyFiniteTimeAction* finiteTimeAction[1];
	finiteTimeAction[0] = func;
	wyIntervalAction* action2 = (wyIntervalAction*) wySequence::make(action1, finiteTimeAction[0], NULL);
	this->oilPan->runAction(action2);
}

void EggFryingScene::setPouringParticleColor(int r, int g, int b) {
	this->particleSystem->setStartColorVariance(r/255.0f, g/255.0f, b/255.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

wyAction* EggFryingScene::getRotateActionWithCallback() {
	wyIntervalAction* action = (wyIntervalAction*) wyRotateBy::make(0.7f, 105.0f);
	wyCallFunc* func = (wyCallFunc*) wyCallFunc::make(wyTargetSelector::make(this,
			SEL(EggFryingScene::rotateObjectActionCallback)));
	wyFiniteTimeAction* finiteTimeAction[1];
	finiteTimeAction[0] = func;
	return ((wyIntervalAction*) wySequence::make(action, finiteTimeAction[0], NULL));
}

void EggFryingScene::initializeTimer() {
	this->mixingSelector = wyTargetSelector::make(this, SEL(EggFryingScene::onMixingTick));
	if (this->mixingTimer == NULL) {
		this->mixingTimer = wyTimer::make(mixingSelector, 0.80f);
	} else {
		scheduler->unscheduleLocked(this->mixingTimer);
	}
}

void EggFryingScene::setSpriteAlpha(int alpha1, int alpha2, int alpha3) {
	this->fryEgg->setAlpha(alpha1);
	this->fryEggHalfCooked->setAlpha(alpha2);
	this->fryEggFullCooked->setAlpha(alpha3);
}

void EggFryingScene::showPointingArrow() {
	this->pointingArrow = wySprite::make(wyTexture2D::make("art/arrow_up.png"));
	this->pointingArrow->setPosition(this->stoveKnob->getPositionX(),
			this->stoveKnob->getPositionY() - 80.0f);
	EggFryingScene::addChild(pointingArrow, 13, 13);
	this->pointingArrow->runAction(this->actionHandler->getRepeatingBlinkAction(1.0f, 2));
}

void EggFryingScene::eggDroppedCallback() {
	//soundsHandler->playEggBreakSound();
	this->fryEgg->setAlpha(255);
	this->eggCabnet->setDisplayFrame(this->fryEgg->makeFrame());
	showPointingArrow();
	setEnabled(true);
}

void EggFryingScene::onMixingTick() {
	if (this->fadingState == EGG_APPEARANCE_LEVEL_1) {
		scheduler->scheduleLocked(this->mixingTimer);
	}

	if (fadingState == EGG_APPEARANCE_LEVEL_1) {
		setSpriteAlpha(255, 0, 0);
		fadingState = EGG_APPEARANCE_LEVEL_2;
	} else if (fadingState == EGG_APPEARANCE_LEVEL_2) {
		setSpriteAlpha(170, 80, 0);
		fadingState = EGG_APPEARANCE_LEVEL_3;
	} else if (fadingState == EGG_APPEARANCE_LEVEL_3) {
		setSpriteAlpha(85, 170, 0);
		fadingState = EGG_APPEARANCE_LEVEL_4;
	} else if (fadingState == EGG_APPEARANCE_LEVEL_4) {
		setSpriteAlpha(0, 255, 0);
		fadingState = EGG_APPEARANCE_LEVEL_5;
	} else if (fadingState == EGG_APPEARANCE_LEVEL_5) {
		setSpriteAlpha(0, 170, 85);
		fadingState = EGG_APPEARANCE_LEVEL_6;
	} else if (fadingState == EGG_APPEARANCE_LEVEL_6) {
		setSpriteAlpha(0, 110, 100);
		fadingState = EGG_APPEARANCE_LEVEL_7;
	} else if (fadingState == EGG_APPEARANCE_LEVEL_7) {
		setSpriteAlpha(0, 75, 155);
		fadingState = EGG_APPEARANCE_LEVEL_8;
	} else if (fadingState == EGG_APPEARANCE_LEVEL_8) {
		setSpriteAlpha(0, 50, 200);
		fadingState = EGG_APPEARANCE_LEVEL_9;
	} else if (fadingState == EGG_APPEARANCE_LEVEL_9) {
		setSpriteAlpha(0, 0, 255);
		fadingState = EGG_APPEARANCE_LEVEL_FRIED;
	}

	if (this->fadingState == EGG_APPEARANCE_LEVEL_FRIED) {
		wySprite* knob = wySprite::make(wyTexture2D::make("art/knob1.png"));
		this->stoveButtSprite->setDisplayFrame(knob->makeFrame());
		scheduler->unscheduleLocked(this->mixingTimer);
		this->hudLayer->updateObjectsVisibility(true, true);
		this->hudLayer->setNextButtonPosition(size.width - 90.0f, 60.0f);
		this->hudLayer->startNextButtonAction(HUD_BUTTON_ACTION_POINTING_NEXT);
	}
}

void EggFryingScene::rotateObjectActionCallback() {
	executeOilPouring();
}

void EggFryingScene::pourActionCallback() {
	this->oilBottle->stopAllActions(true);
	wyAction* oilMove = wyMoveTo::make(0.2f, oilBottle->getPositionX(), oilBottle->getPositionY(),
			oilBottle->getPositionX() - 100.0f, 50.0f + oilBottle->getPositionY());
	oilBottle->runAction(oilMove);
	wyIntervalAction* intAct = (wyIntervalAction*) wyRotateBy::make(0.7f, -105.0f);
	oilBottle->runAction(intAct);
	setEnabled(true);
	this->eggCabnet->runAction(actionHandler->getRepeatingJumpAction(0.5f,
			eggCabnet->getPositionX(), eggCabnet->getPositionY(), 30));
}

void EggFryingScene::eggAddHudLayer() {
	this->hudLayer = new HudLayer(this, "ui/back_button_up.png",
			"ui/back_button_down.png", "ui/next_button_up.png",
			"ui/next_button_down.png");
	this->hudLayer->updateObjectsVisibility(true, false);
	this->hudLayer->setBackButtonPosition(90.0f, 60.0f);
	EggFryingScene::addChild(hudLayer, 30, 30);
	EggFryingScene::bringToFront(hudLayer);
}

bool EggFryingScene::keyUp(wyKeyEvent& event) {
	switch (event.keyCode) {
	case KEYCODE_BACK:
		director->popSceneWithTransition(
				(wyTransitionScene*) wyLeftPushInTransition::make(0.5f,
						new MainMenuScene()));
		return true;
	}
}

void EggFryingScene::onStoveKnobClicked() {
	if (mode == MODE_IGNITE_STOVE) {
		this->pointingArrow->stopAllActions(true);
		this->pointingArrow->setVisible(false);
		wySprite* k = wySprite::make(wyTexture2D::make("art/knob2.png"));
		this->stoveButtSprite->setDisplayFrame(k->makeFrame());
		this->stoveKnob->setEnabled(false);
		wyAction* mov = wyMoveTo::make(0.5f, -(cabnetCover->getWidth() / 2.0f - 30.0f), cabnetCover->getPositionY(),
				size.width / 2.0f, cabnet->getPositionY());
		this->cabnetCover->runAction(mov);
		wyAction* stickMove = wyMoveTo::make(0.5f, size.width + 500.0f, size.height / 2.0f,
				size.width / 2.0f, size.height / 2.0f);
		this->panStick->runAction(stickMove);
		mode = MODE_DRAG_STIRRER;
	}
}


HudInterface::~HudInterface() {

}

void HudInterface::onSoftBackButtonClicked() {
	wyDirector::getInstance()->popSceneWithTransition(
					(wyTransitionScene*) wyLeftPushInTransition::make(0.5f,
							new MainMenuScene()));
}

void HudInterface::onSoftNextButtonClicked() {

}
