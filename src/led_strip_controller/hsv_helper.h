/*
 * hsv_helper.h - Colors manipulations helpers
 *
 * Copyright (C) 2013 William Markezana <william.markezana@me.com>
 *
 */

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <string>

#if !defined(min_of)
#define min_of(A,B)	( A < B ? A : B )
#endif

#if !defined(max_of)
#define max_of(A,B)	( A < B ? B : A )
#endif

/*
 * public types
 *
 */
typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t A;
} rgb_color;

typedef struct
{
	uint16_t H;
	uint8_t S;
	uint8_t V;
	uint8_t A;
} hsv_color;

/*
 * public prototypes
 *
 */
rgb_color hsv_to_rgb(hsv_color pHsvColor);
rgb_color hue_to_rgb(uint16_t pHue);
rgb_color inc_hue_of_color(rgb_color pRgbColor, uint16_t pInc);
rgb_color hue_float_to_rgb(float &pHue);
rgb_color hue_val_float_to_rgb(float &pHue, float &pSat);
hsv_color hue_to_hsv(uint16_t pHue);
uint16_t rgb_to_hue(rgb_color pRgbColor);
hsv_color rgb_to_hsv(rgb_color pRgbColor);
uint32_t rgb_to_int(rgb_color pRgbColor);
rgb_color int_to_rgb(uint32_t pIntColor);
hsv_color int_to_hsv(uint32_t pIntColor);
std::string rgb_to_string(rgb_color pRgbColor);

rgb_color alpha_blend(rgb_color pColor1, rgb_color pColor2);

extern rgb_color ColorRed;
extern rgb_color ColorGreen;
extern rgb_color ColorBlue;
extern rgb_color ColorYellow;
extern rgb_color ColorMagenta;
extern rgb_color ColorAqua;
extern rgb_color ColorBlack;
extern rgb_color ColorWhite;
extern rgb_color ColorClear;

