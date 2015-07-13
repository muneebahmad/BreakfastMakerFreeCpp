/*
 * soundshandler.h
 *
 *  Created on: 05-Jun-2015
 *      Author: muneebahmad
 */

#ifndef SOUNDSHANDLER_H_
#define SOUNDSHANDLER_H_


#include "WiEngine.h"
#include "WiEngine-WiSound.h"

class SoundsHandler {
public:
	SoundsHandler();
	~SoundsHandler();

	static SoundsHandler* getInstance();
	void preLoadSounds();
	void playBackgroundMusic();
};/** end class */

#endif /* SOUNDSHANDLER_H_ */
