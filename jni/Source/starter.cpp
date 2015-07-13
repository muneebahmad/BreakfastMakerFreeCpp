/*
 * starter.cpp
 *
 *  Created on: 03-Jan-2015
 *      Author: muneebahmad
 */

#include "starter.h"
#include "Scenes/scenes.h"

const bool SHOW_FPS = true;

/**
 *
 */
void Java_com_algorithmi_maker_breakfast_free_main_MainActivity_nativeKick(JNIEnv* env, jobject thiz) {
	MainMenuScene* mainMenuScene = new MainMenuScene();
	startGame(mainMenuScene);
}

void startGame(wyScene* scene) {
	wyDirector* director = wyDirector::getInstance();
	director->setShowFPS(SHOW_FPS);

	//run with scene

	director->runWithScene(scene);
}


