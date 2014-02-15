/*
 * pixel_styles_controller.h
 *
 * Copyright (C) 2014 William Markezana <william.markezana@me.com>
 *
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <muduo/base/Logging.h>
/*
 * public defines
 *
 */

#define TCP_CONNECTION_PORT				(56615)
#define UDP_BROADCAST_PORT				(56616)
#define MODE_UDP_STREAMER_PORT			(58618)

#define CONFIGURATION_DIRECTORY			"/etc/pixel_styles/"

#define LOG_FILE						"/var/log/pixel_styles.log"
#define PID_FILE						"/var/run/pixel_styles.pid"

#define DEFAULT_LOG_LEVEL				muduo::Logger::DEBUG

#endif