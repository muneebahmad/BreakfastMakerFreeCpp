/*
 * actionhandler.h
 *
 *  Created on: 05-Jun-2015
 *      Author: muneebahmad
 */

#ifndef ACTIONHANDLER_H_
#define ACTIONHANDLER_H_

#include "WiEngine.h"

class ActionHandler {
public:
	ActionHandler();
	~ActionHandler();

	/**
	 * get new instance of ActionHandler
	 */
	static ActionHandler* getInstance();
	wyAction* getMoveAction(float duration, float startX, float startY, float endX, float endY);
	wyIntervalAction* getMoveBounceInAction(float duration, float startX, float startY, float endX, float endY, int times);
	wyAction* getRepeatingBlinkAction(float duration, int times);
	wyAction* getRepeatingJumpAction(float duration, float startY, float endY, int height);
	wyAction* getRepeatingPointingAction(float duration, float startX, float startY, float endX, float endY);
	wyAction* getRepeatingRotateAction(float duration, int endAngle);
	wyAction* getRepeatingScaleAction(float duration, float startScale, float endScale);
};/** end ActionHandler **/

#endif /* ACTIONHANDLER_H_ */
