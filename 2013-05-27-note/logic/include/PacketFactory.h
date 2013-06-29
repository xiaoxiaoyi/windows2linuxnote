﻿#ifndef  _NINJIATRIBE_PACKETFACTORY_H_
#define  _NINJIATRIBE_PACKETFACTORY_H_


class IPacketFactory
{
public:
	IPacketFactory();
	virtual ~IPacketFactory();

public:
	/*
		获得数据包类型
	*/
	virtual  unsigned  int  GetPacketType()  =  0;

public:
	/*
		数据包处理操作
	*/
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen)  =  0;
};


#endif
