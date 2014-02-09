/********************************************************************************************/
/* Copyright (c) 2013 RGB Styles															*/
/********************************************************************************************/

/********************************************************************************************/
/* This file is the confidential trade secret information and/or proprietary information	*/
/* of RGB Styles, Inc. Code or other information in this program also may be confidential	*/
/* and/or proprietary to RGB Styles, Inc.													*/
/* All rights reserved.																		*/
/********************************************************************************************/

/********************************************************************************************/
/* Name : mode_off.h																		*/
/* Date : Jul 24 2013																		*/
/* Author : William Markezana																*/
/********************************************************************************************/

#ifndef __MODE_OFF_H__
#define __MODE_OFF_H__

using namespace std;

/********************************************************************************************/
/* INCLUDES																					*/
/********************************************************************************************/
#include "mode_interface.h"

/********************************************************************************************/
/* TYPEDEFS																					*/
/********************************************************************************************/

/********************************************************************************************/
/* CLASSES																					*/
/********************************************************************************************/
class mode_off : public mode_interface
{
private:
public:
	mode_off(size_t pWidth, size_t pHeight, string pName, bool pAudioAvailable);
	~mode_off();

	virtual void paint();
};

/********************************************************************************************/
/* END OF FILE																				*/
/********************************************************************************************/
#endif
