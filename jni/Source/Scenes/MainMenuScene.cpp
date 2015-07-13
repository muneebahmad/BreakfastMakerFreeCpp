/*
 * MainMenuScene.cpp
 *
 *  Created on: 03-Jan-2015
 *      Author: muneebahmad
 */

#include "scenes.h"
#include "../Handlers/soundshandler.h"
#include "../Handlers/actionhandler.h"

wySize mSize;

MainMenuScene::MainMenuScene() {
	setContents();
	SoundsHandler::getInstance()->playBackgroundMusic();
	this->director = wyDirector::getInstance();
}

MainMenuScene::~MainMenuScene() {
}

void MainMenuScene::setContents() {
	mainMenuSetBackground();
	mainMenuAddLogo();
	mainMenuSetButtons();
}

void MainMenuScene::mainMenuSetBackground() {
	mSize = wyDirector::getInstance()->getWindowSize();
	mainMenuBg = wySprite::make(wyTexture2D::make("bgs/main_menu_bg.png"));
	mainMenuBg->setPosition(mSize.width / 2.0f, mSize.height / 2.0);
	mainMenuBg->setContentSize(mSize.width, mSize.height);
	mainMenuBg->setAutoFit(true);
	MainMenuScene::addChild(mainMenuBg, 0, 1);
}

void MainMenuScene::mainMenuAddLogo() {
	logo = wySprite::make(wyTexture2D::make("art/breakfast_logo.png"));
	logo->setPosition(mSize.width / 2.0f,
			mSize.height - logo->getHeight() + 50.0f);
	MainMenuScene::addChild(logo, 1, 2);

	wyIntervalAction* scale1 = wyScaleTo::make(0.5f, 1.0f, 1.3f);
	wyIntervalAction* scale2 = wyScaleTo::make(0.5f, 1.3f, 1.0f);
	wyAction* action = wyRepeatForever::make(wySequence::make(scale1, scale2, NULL));

	logo->runAction(action);
}

/**
 * BUTTONS.
 */
void MainMenuScene::mainMenuSetButtons() {
	wySprite* playNormal = wySprite::make(wyTexture2D::make("ui/play_butt_up.png"));
	wySprite* playPressed = wySprite::make(wyTexture2D::make("ui/play_butt_down.png"));
	wySprite* rateNormal = wySprite::make(wyTexture2D::make("ui/rate_button_up.png"));
	wySprite* ratePressed = wySprite::make(wyTexture2D::make("ui/rate_button_down.png"));
	wySprite* moreFunNormal = wySprite::make(wyTexture2D::make("ui/morefun_butt_up.png"));
	wySprite* moreFunPressed = wySprite::make(wyTexture2D::make("ui/morefun_butt_down.png"));
	wySprite* infoNormal = wySprite::make(wyTexture2D::make("ui/info_butt_up.png"));
	wySprite* infoPressed = wySprite::make(wyTexture2D::make("ui/info_butt_down.png"));
	wySprite* exitNormal = wySprite::make(wyTexture2D::make("ui/exit_butt_up.png"));
	wySprite* exitPressed = wySprite::make(wyTexture2D::make("ui/exit_butt_down.png"));

	//RATE BUTTON
	rateButton = wyButton::make(rateNormal, ratePressed, NULL, NULL, NULL,
				wyTargetSelector::make(this, SEL(MainMenuScene::onRateButtonClicked)));
	rateButton->setPosition(-500.0f, (mSize.height / 2.0f) - 55.0f);
	MainMenuScene::addChild(rateButton, 2, 4);

	wyIntervalAction* rateButtMove = wyMoveTo::make(0.8f, -500.0f, (mSize.height / 2.0f) - 80.0f, 84.0f,
			(mSize.height / 2.0f) - 55.0f);
	wyIntervalAction* rateButtEase = wyEaseBackOut::make(rateButtMove);
	rateButton->runAction(rateButtEase);

	//PLAY BUTTON
	playButton = wyButton::make(playNormal, playPressed, NULL, NULL, NULL,
			wyTargetSelector::make(this, SEL(MainMenuScene::onPlayButtonClicked)));
	playButton->setPosition(-500, (mSize.height / 2.0f) - 55.0f);
	MainMenuScene::addChild(playButton, 3, 3);

	wyIntervalAction* buttMove = wyMoveTo::make(1.3f, -500.0f, this->rateButton->getPositionY(), mSize.width / 2.0f,
			this->rateButton->getPositionY());
	wyIntervalAction* buttEase = wyEaseBackOut::make(buttMove);
	playButton->runAction(buttEase);

	//MORE FUN BUTTON
	this->moreFunButton = wyButton::make(moreFunNormal, moreFunPressed, NULL, NULL, NULL,
			wyTargetSelector::make(this, SEL(MainMenuScene::onMoreFunButtonClicked)));
	this->moreFunButton->setPosition(-500, this->playButton->getPositionY());
	MainMenuScene::addChild(moreFunButton, 4, 5);

	wyIntervalAction* moreFunMove = wyMoveTo::make(1.8f, -500.0f, this->playButton->getPositionY(), mSize.width - 84.0f,
			this->playButton->getPositionY());
	wyIntervalAction* moreFunEase = wyEaseBackOut::make(moreFunMove);
	this->moreFunButton->runAction(moreFunEase);

	//EXIT BUTT
	this->exitButton = wyButton::make(exitNormal, exitPressed, NULL, NULL, NULL,
			wyTargetSelector::make(this, SEL(MainMenuScene::onExitButtonClicked)));
	this->exitButton->setPosition(mSize.width - 52.0f, -800.0f);
	MainMenuScene::addChild(exitButton, 5, 5);

	wyIntervalAction* exitMove = wyMoveTo::make(2.3f, mSize.width - 52.0f, -800.0f, mSize.width - 52.0f,
			52.0f);
	wyIntervalAction* exitEase = wyEaseBackOut::make(exitMove);
	this->exitButton->runAction(exitEase);

	//INFO BUTTON
	this->infoButton = wyButton::make(infoNormal, infoPressed, NULL, NULL, NULL,
			wyTargetSelector::make(this, SEL(MainMenuScene::onInfoButtonClicked)));
	this->infoButton->setPosition(52.0f, -1200.0f);
	MainMenuScene::addChild(infoButton, 6, 6);

	wyIntervalAction* infoMove = wyMoveTo::make(2.8f, 52.0f, -800.0f, 52.0f,
				52.0f);
	wyIntervalAction* infoEase = wyEaseBackOut::make(infoMove);
	this->infoButton->runAction(infoEase);
}

void MainMenuScene::onPlayButtonClicked() {
	director->pushScene((wyTransitionScene*) wyRightPushInTransition::make(0.5f, new EggFryingScene()));
}

void MainMenuScene::onRateButtonClicked() {

}

void MainMenuScene::onMoreFunButtonClicked() {

}

void MainMenuScene::onInfoButtonClicked() {
	wyToast::make("(c) Muneeb Ahmad", 3.0f)->show(true);
}

void MainMenuScene::onExitButtonClicked() {
	showExitDialog();
}

bool MainMenuScene::keyUp(wyKeyEvent& event) {
	switch (event.keyCode) {
	case KEYCODE_BACK:
		showExitDialog();
		return true;
	}
}

void MainMenuScene::showExitDialog() {
	wyLabel* title = wyLabel::make("Exit Dialog", SP(24));
	wyLabel* content = wyLabel::make("Do you really want to exit?", SP(22));
	title->setColor(wyc3bGreen);
	content->setColor(wyc3bBlack);

	wyNinePatchSprite* bg = wyNinePatchSprite::make(wyTexture2D::make("ui/dialog_bg.png"),
			wyr(DP(130), DP(20), DP(1), DP(1)));

	wySprite* okBtnNormal = wySprite::make(wyTexture2D::make("ui/dialog_btn.png"));
	wyButton* okBtn = wyButton::make(okBtnNormal, NULL, NULL, NULL, NULL, NULL);
	wyLabel* okLabel = wyLabel::make("Yes", SP(20));
	okLabel->setColor(wyc3b(96, 56, 19));

	wySprite* cancelBtnNormal = wySprite::make(wyTexture2D::make("ui/dialog_btn.png"));
	wyButton* cancelBtn = wyButton::make(cancelBtnNormal, NULL, NULL, NULL, NULL, NULL);
	wyLabel* cancelLabel = wyLabel::make("No", SP(20));
	cancelLabel->setColor(wyc3b(96, 56, 19));

	wyDialog* dialog = wyDialog::make();
	dialog->setBackground(bg)
			->setBackgroundPadding(110.0f, 40.0f, 0.0f, 40.0f)
			->setTitle(title)
			->setContent(content)
			->addTwoColumnsButton(okBtn, okLabel, wyTargetSelector::make(this, SEL_p(MainMenuScene::onOKButtonClicked), dialog),
					cancelBtn, cancelLabel, wyTargetSelector::make(this, SEL_p(MainMenuScene::onCancelButtonClicked), dialog))
					->setTransition(wyDialogPopupTransition::make())
					->setBackKeyEquivalentButtonIndex(1)
					->show(true);

}

void MainMenuScene::onOKButtonClicked(wyTargetSelector* ts, void* data) {
	director->popScene();
}

void MainMenuScene::onCancelButtonClicked(wyTargetSelector* ts, void* data) {
	wyDialog* dialog = (wyDialog*) data;
	dialog->dismiss(true);
}

