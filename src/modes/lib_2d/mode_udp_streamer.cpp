/*
 * mode_udp_streamer.cpp
 *
 * Copyright (C) 2014 William Markezana <william.markezana@me.com>
 *
 */

#include "mode_udp_streamer.h"

#define UDP_TIMEOUT_DELAY					(2000000) // us
/*
 * public library interface
 *
 */
extern "C" mode_interface* create_mode(size_t pWidth, size_t pHeight, bool pAudioAvailable, vector<size_t> pSegments)
{
  return new mode_udp_streamer(pWidth, pHeight, "UDP Stream", pAudioAvailable, pSegments);
}

extern "C" void destroy_mode(mode_interface* object)
{
  delete object;
}
/* * constructor
 *
 */
mode_udp_streamer::mode_udp_streamer(size_t pWidth, size_t pHeight, string pName, bool pAudioAvailable, vector<size_t> pSegments)
: mode_interface(pWidth, pHeight, pName, pAudioAvailable, pSegments)
{	
	mLastTickCount = 0;

	mUdpBuffer = new uint8_t[mWidth * mHeight * 3];
}

/*
 * destructor
 *
 */
mode_udp_streamer::~mode_udp_streamer()
{
	
}

/*
 * public functions
 *
 */
void mode_udp_streamer::handle_udp_receive(uint8_t *pData, size_t pLength)
{
	if (pLength == mWidth * mHeight * 3)
	{
		mLastTickCount = get_tick_us();
		memcpy(mUdpBuffer, pData, pLength);
	}
}

void mode_udp_streamer::paint()
{
	rgb_color color;
	int bufferPtr = 0;
	
	if (get_tick_us() - mLastTickCount < UDP_TIMEOUT_DELAY)
	{
		for (size_t y = 0; y < mHeight; y++)
		{
			for (size_t x = 0; x < mWidth; x++)
			{
				color.R = mUdpBuffer[bufferPtr++];
				color.G = mUdpBuffer[bufferPtr++];
				color.B = mUdpBuffer[bufferPtr++];
				mBitmap->set_pixel(x, y, color);
			}
		}
	}
	else
	{
		mBitmap->clear();
		mLastTickCount = get_tick_us() - UDP_TIMEOUT_DELAY;
	}
}
