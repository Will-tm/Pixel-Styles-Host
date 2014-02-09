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
/* Name : tcp_server.cpp																	*/
/* Date : Jan 25 2012																		*/
/* Author : William Markezana																*/
/********************************************************************************************/

/********************************************************************************************/
/* INCLUDES																					*/
/********************************************************************************************/
#include "tcp_server.h"

#include <muduo/base/Logging.h>
#include <boost/bind.hpp>
#include <zlib.h>

using namespace muduo;
using namespace muduo::net;

/********************************************************************************************/
/* PRIVATE VARIABLES																		*/
/********************************************************************************************/
//#define DEBUG

/********************************************************************************************/
/* PRIVATE FUNCTIONS																		*/
/********************************************************************************************/

/********************************************************************************************/
/* PRIVATE PROTOTYPES																		*/
/********************************************************************************************/

/********************************************************************************************/
/* CONSTRUCTOR																				*/
/********************************************************************************************/
tcp_server::tcp_server(EventLoop* loop, const InetAddress& listenAddr, int maxConnections) : loop_(loop), server_(loop, listenAddr, "tcp_server"), numConnected_(0), kMaxConnections_(maxConnections)
{
	server_.setConnectionCallback(boost::bind(&tcp_server::onConnection, this, _1));
	server_.setMessageCallback(boost::bind(&tcp_server::onMessage, this, _1, _2, _3));
}

/********************************************************************************************/
/* PRIVATE FUNCTIONS																		*/
/********************************************************************************************/

/********************************************************************************************/
/* PUBLIC FUNCTIONS																			*/
/********************************************************************************************/
void tcp_server::run(void)
{
	server_.start();
}

void tcp_server::onConnection(const TcpConnectionPtr& conn)
{
	LOG_DEBUG << "tcp_server - " << conn->peerAddress().toIpPort() << " -> "	<< conn->localAddress().toIpPort() << " is " << (conn->connected() ? "UP" : "DOWN");

	if (conn->connected())
	{
		++numConnected_;
		//mConnectedAddresses.push_back(conn->peerAddress().toIp());
		if (numConnected_ > kMaxConnections_)
		{
			conn->shutdown();
		}
		else
		{
			conn->setTcpNoDelay(true);
		}
	}
	else
	{
		--numConnected_;
		//mConnectedAddresses.erase(std::remove(mConnectedAddresses.begin(), mConnectedAddresses.end(), conn->peerAddress().toIp()), mConnectedAddresses.end());
	}

	LOG_DEBUG << "numConnected = " << numConnected_;
}

void tcp_server::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
{
	muduo::string msg(buf->retrieveAllAsString());

	std::string query = "";
	for (muduo::string::iterator it=msg.begin(); it!=msg.end(); ++it)
		query += *it;

	std::string::size_type pos_r = query.find(char(0x0A));
	std::string::size_type pos_n = query.find(char(0x0D));
	std::string::size_type pos = pos_r < pos_n ? pos_r : pos_n;

	std::string subquery;
	if (pos != std::string::npos)
		subquery = query.substr(0, pos);

	LOG_DEBUG << "Received: " << subquery;

	std::string answer;
	if(tcpReceptionCallback)
		tcpReceptionCallback(subquery, answer, 0, mCallbackParent);

	if(answer.length())
	{
		unsigned int sourceSize = answer.size();
		const char * source = answer.c_str();
		unsigned long dsize = sourceSize + (sourceSize * 0.1f) + 16;
		char * destination = new char[dsize];
		int result = compress2((unsigned char *)destination, &dsize, (const unsigned char *)source, sourceSize, Z_DEFAULT_COMPRESSION);
		if(result != Z_OK) LOG_ERROR << "Compress error occured! Error code: " << result;

		answer = string(destination, dsize);
		answer.append("\r\n");
		conn->send(answer);

		LOG_DEBUG << "Replied " << answer.size() << " bytes : " << answer;
	}
}

std::string tcp_server::mac_address()
{
	if(mMacAddress.size() == 12)
		return mMacAddress;
	char MAC_str[13];
    #define HWADDR_len 6
    int s,i;
    struct ifreq ifr;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, "eth0");
    ioctl(s, SIOCGIFHWADDR, &ifr);
    for (i=0; i<HWADDR_len; i++)
        sprintf(&MAC_str[i*2],"%02X",((unsigned char*)ifr.ifr_hwaddr.sa_data)[i]);
    MAC_str[12]='\0';
    mMacAddress = MAC_str;
    close(s);
    return MAC_str;
}

std::vector<std::string> *tcp_server::connectedAddresses()
{
	mConnectedAddresses.clear();
	for (TcpServer::ConnectionMap::iterator it(server_.connections_.begin());it != server_.connections_.end(); ++it)
	{
		TcpConnectionPtr conn = it->second;
		mConnectedAddresses.push_back(conn->peerAddress().toIp());
	}
	return &mConnectedAddresses;
}

/********************************************************************************************/
/* END OF FILE																				*/
/********************************************************************************************/
