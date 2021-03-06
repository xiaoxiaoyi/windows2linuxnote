#ifndef  _COCOS2D_CCROTATESPRITEPLAYINTERVALPROPERTY_H_
#define  _COCOS2D_CCROTATESPRITEPLAYINTERVALPROPERTY_H_

#include "CCProperty.h"

namespace  cocos2d
{

	class CCRotateSpritePlayIntervalProperty : public CCProperty
	{
	public:
		CCRotateSpritePlayIntervalProperty();
		virtual ~CCRotateSpritePlayIntervalProperty();

	public:
		virtual std::string	get(CCNode* receiver);
		virtual void set(CCNode* receiver, std::string value);
	};

}

#endif