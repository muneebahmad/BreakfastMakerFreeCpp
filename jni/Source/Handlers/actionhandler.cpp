/*
 * actionhandler.cpp
 *
 *  Created on: 05-Jun-2015
 *      Author: muneebahmad
 */

#include "actionhandler.h"

/**
 * Global instance for ActionHandler
 */
static ActionHandler* sInstance = NULL;

ActionHandler::ActionHandler() {

}

ActionHandler::~ActionHandler() {

}

ActionHandler* ActionHandler::getInstance() {
	if (sInstance == NULL) {
		sInstance = new ActionHandler();
	}
	return sInstance;
}

wyAction* ActionHandler::getMoveAction(float duration, float startX, float startY, float endX, float endY) {
	return wyMoveTo::make(duration, startX, startY, endX, endY);
}

wyIntervalAction* ActionHandler::getMoveBounceInAction(float duration, float startX, float startY, float endX, float endY,
		int times) {
	return ((wyIntervalAction*) wyRepeat::make(wyEaseBounceIn::make((wyIntervalAction*) wyMoveTo::make(duration,
			startX,startY, endX, endY)), times));
}

wyAction* ActionHandler::getRepeatingBlinkAction(float duration, int times) {
	return ((wyAction*) wyRepeatForever::make((wyIntervalAction*) wyBlink::make(duration, times)));
}

wyAction* ActionHandler::getRepeatingJumpAction(float duration, float startY, float endY, int height) {
	wyIntervalAction* jumpTo = (wyIntervalAction*) wyJumpTo::make(duration, startY,
			endY, startY, endY, height, 1);
	wyIntervalAction* reverse = (wyIntervalAction*) jumpTo->reverse();
	return ((wyAction*) wyRepeatForever::make((wyIntervalAction*) wySequence::make(jumpTo, reverse, NULL)));
}

wyAction* ActionHandler::getRepeatingPointingAction(float duration, float startX, float startY,
		float endX, float endY) {
	wyIntervalAction* move = (wyIntervalAction*) wyMoveTo::make(duration, startX, startY, endX, endY);
	wyIntervalAction* rev = (wyIntervalAction*) move->reverse();
	return ((wyAction*) wyRepeatForever::make((wyIntervalAction*) wySequence::make(move, rev)));
}

