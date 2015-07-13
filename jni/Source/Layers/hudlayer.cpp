/*
 * hudlayer.cpp
 *
 *  Created on: 24-Jun-2015
 *      Author: muneebahmad
 */

#include "hudlayer.h"
#include "../Handlers/hudinterface.h"
#include "../Handlers/actionhandler.h"


HudLayer::HudLayer(HudInterface* hudInterface, const char* bckNormal, const char* bckPressed,
		const char* nextNormal, const char* nextPressed) {
	this->hudInterface = hudInterface;
	director = wyDirector::getInstance();
	size = director->getWindowSize();
	setContents(bckNormal, bckPressed, nextNormal, nextPressed);
}

HudLayer::~HudLayer() {

}

void HudLayer::setContents(const char* bckNormal, const char* bckPressed,
		const char* nextNormal, const char* nextPressed) {
	this->bckButtNormal = wySprite::make(wyTexture2D::make(bckNormal));
	this->bckButtPressed = wySprite::make(wyTexture2D::make(bckPressed));
	this->nextButtNormal = wySprite::make(wyTexture2D::make(nextNormal));
	this->nextButtPressed = wySprite::make(wyTexture2D::make(nextPressed));

	this->backButton = wyButton::make(bckButtNormal, bckButtPressed, NULL, NULL, NULL,
			wyTargetSelector::make(this, SEL(HudLayer::backsButton)));
	this->backButton->setPosition(10.0f + this->backButton->getWidth() / 2.0f,
			85.0f + this->backButton->getHeight() / 2.0f);
	HudLayer::addChild(this->backButton, 1, 1);

	this->nextButton = wyButton::make(nextButtNormal, nextButtPressed, NULL, NULL, NULL,
			wyTargetSelector::make(this, SEL(HudLayer::nextsButton)));
	this->nextButton->setPosition(size.width - this->nextButton->getWidth() / 2.0f - 10.0f,
			85.0f + this->nextButton->getHeight() / 2.0f);
	HudLayer::addChild(this->nextButton, 2, 2);
	this->nextButton->setVisible(false);
}

void HudLayer::setNextButtonPosition(float x, float y) {
	this->nextButton->setPosition(x, y);
}

void HudLayer::setBackButtonPosition(float x, float y) {
	this->backButton->setPosition(x, y);
}

void HudLayer::updateObjectsVisibility(bool bckButtVisible, bool nextButtVisible) {
	this->backButton->setVisible(bckButtVisible);
	this->nextButton->setVisible(nextButtVisible);
}

void HudLayer::startNextButtonAction(int actionType) {
	ActionHandler* actionHandler = new ActionHandler();
	switch (actionType) {
	case HUD_BUTTON_ACTION_BLINK:
		this->nextButton->runAction(actionHandler->getRepeatingBlinkAction(1.0f, 2));
		break;
	case HUD_BUTTON_ACTION_JUMP:
		this->nextButton->runAction(actionHandler->getRepeatingJumpAction(1.0f, this->nextButton->getPositionX(),
				this->nextButton->getPositionY(), 20));
		break;
	case HUD_BUTTON_ACTION_POINTING_NEXT:
		this->nextButton->runAction(actionHandler->getRepeatingPointingAction(0.5f,
				this->nextButton->getPositionX() - 30.0f,
				this->nextButton->getPositionY(),
				this->nextButton->getPositionX(),
				this->nextButton->getPositionY()));
		break;
	default:
		break;
	}
}

void HudLayer::backsButton() {
	hudInterface->onSoftBackButtonClicked();
}

void HudLayer::nextsButton() {
	hudInterface->onSoftNextButtonClicked();
}

