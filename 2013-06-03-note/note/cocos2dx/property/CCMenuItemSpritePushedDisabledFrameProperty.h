﻿#ifndef  _COCOS2D_CCMENUITEMSPRITEPUSHEDDISABLEDFRAMEPROPERTY_H_
#define  _COCOS2D_CCMENUITEMSPRITEPUSHEDDISABLEDFRAMEPROPERTY_H_

#include "CCProperty.h"

namespace  cocos2d
{

	class CCMenuItemSpritePushedDisabledFrameProperty : public CCProperty
	{
	public:
		CCMenuItemSpritePushedDisabledFrameProperty();
		virtual ~CCMenuItemSpritePushedDisabledFrameProperty();

	public:
		virtual std::string	get(CCNode* receiver);
		virtual void set(CCNode* receiver, std::string value);
	};

}

#endif
