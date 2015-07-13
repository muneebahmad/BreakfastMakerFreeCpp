/*
 * soundshandler.cpp
 *
 *  Created on: 05-Jun-2015
 *      Author: muneebahmad
 */

#include "soundshandler.h"

/**
 * Global instance for SoundsHandler
 */
static SoundsHandler* sInstance = NULL;

SoundsHandler::SoundsHandler() {

}

SoundsHandler::~SoundsHandler() {

}

/**
 * Create new instance of sounds handler
 */
SoundsHandler* SoundsHandler::getInstance() {
	if (sInstance == NULL) {
		sInstance = new SoundsHandler();
	}
	return sInstance;
}

void SoundsHandler::preLoadSounds() {

}

void SoundsHandler::playBackgroundMusic() {
	wyAudioManager::getInstance()->playBackgroundMusic(RES("R.raw.algo_main_menu.mp3"), FORMAT_MP3, -1);
}

