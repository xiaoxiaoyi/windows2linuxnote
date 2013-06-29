#ifndef  _COCOS2D_CCLABELWIDTHPROPERTY_H_
#define  _COCOS2D_CCLABELWIDTHPROPERTY_H_

#include "CCProperty.h"

namespace  cocos2d
{

class CCLabelWidthProperty : public CCProperty
{
public:
	CCLabelWidthProperty();
	virtual ~CCLabelWidthProperty();

public:
	virtual std::string	get(CCNode* receiver);
	virtual void set(CCNode* receiver, std::string value);
};

}

#endif
