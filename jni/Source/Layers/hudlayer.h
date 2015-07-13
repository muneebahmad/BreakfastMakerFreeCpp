/*
 * hudlayer.h
 *
 *  Created on: 24-Jun-2015
 *      Author: muneebahmad
 */

#ifndef HUDLAYER_H_
#define HUDLAYER_H_

#include <WiEngine.h>
#include "../Handlers/hudinterface.h"

const int HUD_BUTTON_ACTION_BLINK = 0x01;
const int HUD_BUTTON_ACTION_JUMP = 0x02;
const int HUD_BUTTON_ACTION_POINTING_NEXT = 0x03;
const int HUD_BUTTON_ACTION_SCALE = 0x04;

class HudLayer : public wyLayer {
protected:
	wyButton* backButton;
	wyButton* nextButton;
private:
	HudInterface* hudInterface;
	wySprite* bckButtNormal;
	wySprite* bckButtPressed;
	wySprite* nextButtNormal;
	wySprite* nextButtPressed;
	wyDirector* director;
	wySize size;

	void setContents(const char* bckButtNormal, const char* bckButtPressed,
				const char* nextButtNormal, const char* nextButtPressed);
	void backsButton();
	void nextsButton();
public:
	HudLayer();
	HudLayer(HudInterface* hudInterface, const char* bckButtNormal, const char* bckButtPressed,
			const char* nextButtNormal, const char* nextButtPressed);
	~HudLayer();

	void setBackButtonPosition(float x, float y);
	void setNextButtonPosition(float x, float y);
	void startNextButtonAction(int actionType);
	void updateObjectsVisibility(bool bckButtVisible, bool nextButtVisible);

};/** end class. */

#endif /* HUDLAYER_H_ */
