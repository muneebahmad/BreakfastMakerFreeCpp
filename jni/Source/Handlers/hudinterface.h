/*
 * hudinterface.h
 *
 *  Created on: 24-Jun-2015
 *      Author: muneebahmad
 */

#ifndef HUDINTERFACE_H_
#define HUDINTERFACE_H_

class HudInterface {
public:
	virtual ~HudInterface();
	virtual void onSoftBackButtonClicked();
	virtual void onSoftNextButtonClicked();
};/** end class. */



#endif /* HUDINTERFACE_H_ */
