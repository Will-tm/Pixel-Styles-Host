/*
 * bitmap.h - Custom Bitmap class
 *
 * Copyright (C) 2013 William Markezana <william.markezana@me.com>
 *
 */

#pragma once

using namespace std;

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include "hsv_helper.h"

/*
 * public class
 *
 */
class bitmap
{
private:
	vector<vector<rgb_color> > mMemory;
	vector<bitmap*> mLayers;

	int mLocationX;
	int mLocationY;
public:
	int width;
	int height;

	bitmap(int pWidth, int pHeight);
	~bitmap();

	rgb_color get_pixel(int x, int y);
	void set_pixel(int x, int y, rgb_color pColor);

	hsv_color get_hsv_pixel(int x, int y);
	void set_hsv_pixel(int x, int y, hsv_color pColor);

	void fill(rgb_color pColor);
	void clear();

	void move_to(int x, int y);
	void line_to(int x, int y, rgb_color pColor);

	void assign(bitmap *pBitmap);
	string to_string();

	bitmap *add_layer();
	void render();
};

