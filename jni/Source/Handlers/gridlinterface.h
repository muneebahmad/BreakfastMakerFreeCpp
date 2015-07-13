/*
 * gridlinterface.h
 *
 *  Created on: 24-Jun-2015
 *      Author: muneebahmad
 */

#ifndef GRIDLINTERFACE_H_
#define GRIDLINTERFACE_H_


class GridInterface {
public:
	GridInterface();
	virtual ~GridInterface();

	virtual void onCrossButtonClicked();
	virtual void onGridItemClicked(const char* itemId);

};/** end class. */


#endif /* GRIDLINTERFACE_H_ */
