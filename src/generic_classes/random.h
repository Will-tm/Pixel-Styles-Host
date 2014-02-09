/********************************************************************************************/
/* Copyright (c) 2012 RGB Styles															*/
/********************************************************************************************/

/********************************************************************************************/
/* This file is the confidential trade secret information and/or proprietary information	*/
/* of RGB Styles, Inc. Code or other information in this program also may be confidential	*/
/* and/or proprietary to RGB Styles, Inc.													*/
/* All rights reserved.																		*/
/********************************************************************************************/

/********************************************************************************************/
/* Name : random.h																		*/
/* Date : Nov 20 2012																		*/
/* Author : Adrien Deola																	*/
/********************************************************************************************/

#ifndef __RANDOM_H__
#define __RANDOM_H__

using namespace std;

/********************************************************************************************/
/* INCLUDES																					*/
/********************************************************************************************/
#include <stdlib.h>
#include <cmath>

/********************************************************************************************/
/* TYPEDEFS																					*/
/********************************************************************************************/

/********************************************************************************************/
/* PUBLIC PROTOTYPES																		*/
/********************************************************************************************/
void initialize_random(void);
unsigned int random(unsigned int range);

/********************************************************************************************/
/* END OF FILE																				*/
/********************************************************************************************/
#endif
