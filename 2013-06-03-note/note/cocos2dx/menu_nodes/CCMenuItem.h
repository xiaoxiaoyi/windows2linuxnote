/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2011 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCMENU_ITEM_H__
#define __CCMENU_ITEM_H__

#include "base_nodes/CCNode.h"
#include "CCProtocols.h"
#include "cocoa/CCArray.h"
#include "property/CCMenuItemImageNormalFileProperty.h"
#include "property/CCMenuItemImageNormalFrameProperty.h"
#include "property/CCMenuItemImageSelectedFileProperty.h"
#include "property/CCMenuItemImageSelectedFrameProperty.h"
#include "property/CCMenuItemImageDisabledFileProperty.h"
#include "property/CCMenuItemImageDisabledFrameProperty.h"
#include "property/CCMenuItemSpritePushedSelectedFileProperty.h"
#include "property/CCMenuItemSpritePushedSelectedFrameProperty.h"
#include "property/CCMenuItemSpritePushedNormalFileProperty.h"
#include "property/CCMenuItemSpritePushedNormalFrameProperty.h"
#include "property/CCMenuItemSpritePushedDisabledFileProperty.h"
#include "property/CCMenuItemSpritePushedDisabledFrameProperty.h"
#include "property/CCMenuItemSpritePushedSelectedProperty.h"
#include "property/CCMenuItemImageLabelTextProperty.h"
#include "property/CCMenuItemImageLabelFontNameProperty.h"
#include "property/CCMenuItemImageLabelFontSizeProperty.h"
#include "property/CCMenuItemScaleImageNormalFileProperty.h"
#include "property/CCMenuItemScaleImageScaleSizeProperty.h"
#include "property/CCMenuItemScriptEventProperty.h"
#include "property/CCMenuItemSpriteSingleClickDisabledFileProperty.h"
#include "property/CCMenuItemSpriteSingleClickDisabledFrameProperty.h"
#include "property/CCMenuItemSpriteSingleClickNormalFileProperty.h"
#include "property/CCMenuItemSpriteSingleClickNormalFrameProperty.h"
#include "property/CCMenuItemTabSpriteSelectedFileProperty.h"
#include "property/CCMenuItemTabSpriteSelectedFrameProperty.h"
#include "property/CCMenuItemTabSpriteNormalFileProperty.h"
#include "property/CCMenuItemTabSpriteNormalFrameProperty.h"
#include "property/CCMenuItemTabSpriteSelectedProperty.h"

NS_CC_BEGIN
    
class CCLabelTTF;
class CCLabelAtlas;
class CCSprite;
class CCSpriteFrame;
#define kCCItemSize 32
    
/**
 * @addtogroup GUI
 * @{
 * @addtogroup menu
 * @{
 */

/** @brief CCMenuItem base class
 *
 *  Subclass CCMenuItem (or any subclass) to create your custom CCMenuItem objects.
 */
class CC_DLL CCMenuItem : public CCNode
{
protected:
    /** whether or not the item is selected
     @since v0.8.2
     */
    bool m_bIsSelected;
    bool m_bIsEnabled;

public:
    CCMenuItem()
    : m_bIsSelected(false)
    , m_bIsEnabled(false)            
    , m_pListener(NULL)            
    , m_pfnSelector(NULL)
    , m_nScriptTapHandler(0)
	, m_scriptEventName("")
    {
		addProperty(&s_MenuItemScriptEventProperty);
	}
    virtual ~CCMenuItem();

	/** Creates a CCMenuItem with no target/selector */
	static CCMenuItem* create();
    /** Creates a CCMenuItem with a target/selector */
    static CCMenuItem * create(CCObject *rec, SEL_MenuHandler selector);
    /** Initializes a CCMenuItem with a target/selector */
    bool initWithTarget(CCObject *rec, SEL_MenuHandler selector);
    /** Returns the outside box */
    CCRect rect();
    /** Activate the item */
    virtual void activate();
    /** The item was selected (not activated), similar to "mouse-over" */
    virtual void selected();
    /** The item was unselected */
    virtual void unselected();
    
	/** Register menu handler script function */
	virtual void registerScriptTapHandler(int nHandler);
	virtual void unregisterScriptTapHandler(void);
	int getScriptTapHandler() { return m_nScriptTapHandler; };

    virtual bool isEnabled();
    //@note: It's 'setIsEnable' in cocos2d-iphone. 
    virtual void setEnabled(bool value);
    virtual bool isSelected();
    
    /** set the target/selector of the menu item*/
    void setTarget(CCObject *rec, SEL_MenuHandler selector);

	void setScriptEventName(std::string name);

protected:
    CCObject*       m_pListener;
    SEL_MenuHandler m_pfnSelector;
    int             m_nScriptTapHandler;
	std::string     m_scriptEventName;

public:
	static  CCMenuItemScriptEventProperty  s_MenuItemScriptEventProperty;
};

/** @brief An abstract class for "label" CCMenuItemLabel items 
 Any CCNode that supports the CCLabelProtocol protocol can be added.
 Supported nodes:
 - CCBitmapFontAtlas
 - CCLabelAtlas
 - CCLabelTTF
 */
class CC_DLL CCMenuItemLabel : public CCMenuItem, public CCRGBAProtocol
{
    /** the color that will be used to disable the item */
    CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tDisabledColor, DisabledColor);
    /** Label that is rendered. It can be any CCNode that implements the CCLabelProtocol */
    CC_PROPERTY(CCNode*, m_pLabel, Label);
public:
    CCMenuItemLabel()
    : m_pLabel(NULL)
    , m_fOriginalScale(0.0)
    {}
    virtual ~CCMenuItemLabel();

    /** creates a CCMenuItemLabel with a Label, target and selector */
    static CCMenuItemLabel * create(CCNode*label, CCObject* target, SEL_MenuHandler selector);
    /** creates a CCMenuItemLabel with a Label. Target and selector will be nill */
    static CCMenuItemLabel* create(CCNode *label);

    /** initializes a CCMenuItemLabel with a Label, target and selector */
    bool initWithLabel(CCNode* label, CCObject* target, SEL_MenuHandler selector);
    /** sets a new string to the inner label */
    void setString(const char * label);
    // super methods
    virtual void activate();
    virtual void selected();
    virtual void unselected();
    /** Enable or disabled the CCMenuItemFont
     @warning setEnabled changes the RGB color of the font
     */
    virtual void setEnabled(bool enabled);
    virtual void setOpacity(GLubyte opacity);
    virtual GLubyte getOpacity();
    virtual void setColor(const ccColor3B& color);
    virtual const ccColor3B& getColor();
    
    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
protected:
    ccColor3B    m_tColorBackup;
    float        m_fOriginalScale;
};

/** @brief A CCMenuItemAtlasFont
 Helper class that creates a MenuItemLabel class with a LabelAtlas
 */
class CC_DLL CCMenuItemAtlasFont : public CCMenuItemLabel
{
public:
    CCMenuItemAtlasFont(){}
    virtual ~CCMenuItemAtlasFont(){}

    /** creates a menu item from a string and atlas with a target/selector */
    static CCMenuItemAtlasFont* create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap);
    /** creates a menu item from a string and atlas. Use it with MenuItemToggle */
    static CCMenuItemAtlasFont* create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, CCObject* target, SEL_MenuHandler selector);
    /** initializes a menu item from a string and atlas with a target/selector */
    bool initWithString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, CCObject* target, SEL_MenuHandler selector);
};

/** @brief A CCMenuItemFont
 Helper class that creates a CCMenuItemLabel class with a Label
 */
class CC_DLL CCMenuItemFont : public CCMenuItemLabel
{
public:
	CCMenuItemFont() : m_uFontSize(0), m_strFontName("") {}
    virtual ~CCMenuItemFont(){}

public:
    /** set default font size */
    static void setFontSize(unsigned int s);
    /** get default font size */
    static unsigned int fontSize();
    /** set the default font name */
    static void setFontName(const char *name);
    /** get the default font name */
    static const char *fontName();

    /** creates a menu item from a string without target/selector. To be used with CCMenuItemToggle */
    static CCMenuItemFont * create(const char *value);
    /** creates a menu item from a string with a target/selector */
    static CCMenuItemFont * create(const char *value, CCObject* target, SEL_MenuHandler selector);

    /** initializes a menu item from a string with a target/selector */
    bool initWithString(const char *value, CCObject* target, SEL_MenuHandler selector);
    
    /** set font size
     * c++ can not overload static and non-static member functions with the same parameter types
     * so change the name to setFontSizeObj
     */
    void setFontSizeObj(unsigned int s);
    /** get font size */
    unsigned int fontSizeObj();
    
    /** set the font name 
     * c++ can not overload static and non-static member functions with the same parameter types
     * so change the name to setFontNameObj
     */
    void setFontNameObj(const char* name);
    const char* fontNameObj();
    
protected:
    void recreateLabel();
    
protected:
    unsigned int m_uFontSize;
    std::string m_strFontName;
};

/** @brief CCMenuItemSprite accepts CCNode<CCRGBAProtocol> objects as items.
 The images has 3 different states:
 - unselected image
 - selected image
 - disabled image
 
 @since v0.8.0
 */
class CC_DLL CCMenuItemScaleImage : public CCMenuItem, public CCRGBAProtocol
{
public:
	float m_fOriginalScale;
	float m_fScaleSize;
    /** the image used when the item is not selected */
    CC_PROPERTY(CCNode*, m_pNormalImage, NormalImage);

public:
    CCMenuItemScaleImage();
	virtual ~CCMenuItemScaleImage();

public:
    /** initializes a menu item with a normal, selected  and disabled image with target/selector */
    bool initFromSimpleSprite(CCNode* simpleSprite, CCObject* target, SEL_MenuHandler selector);

public:
	/** init */
	virtual bool init();

public:
	// set scale size
	void setScaleSize(float scale);
	// get scale size
	float getScaleSize();

public:
    // super methods
    virtual void setColor(const ccColor3B& color);
    virtual const ccColor3B& getColor();
    virtual void setOpacity(GLubyte opacity);
    virtual GLubyte getOpacity();

	virtual void activate();
    virtual void selected();
    virtual void unselected();
    virtual void setIsEnabled(bool bEnabled);
    
	virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
	virtual bool isOpacityModifyRGB(void) { return false;}

public:
	static  CCMenuItemScaleImageNormalFileProperty  s_MenuItemScaleImageNormalFileProperty;
	static  CCMenuItemScaleImageScaleSizeProperty   s_MenuItemScaleImageScaleSizeProperty;
};

/** @brief CCMenuItemSprite accepts CCNode<CCRGBAProtocol> objects as items.
 The images has 3 different states:
 - unselected image
 - selected image
 - disabled image
 
 @since v0.8.0
 */
class CC_DLL CCMenuItemSprite : public CCMenuItem, public CCRGBAProtocol
{
    /** the image used when the item is not selected */
    CC_PROPERTY(CCNode*, m_pNormalImage, NormalImage);
    /** the image used when the item is selected */
    CC_PROPERTY(CCNode*, m_pSelectedImage, SelectedImage);
    /** the image used when the item is disabled */
    CC_PROPERTY(CCNode*, m_pDisabledImage, DisabledImage);
public:
    CCMenuItemSprite()
    :m_pNormalImage(NULL)
    ,m_pSelectedImage(NULL)
    ,m_pDisabledImage(NULL)
    {}

    /** creates a menu item with a normal, selected and disabled image*/
    static CCMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite = NULL);
    /** creates a menu item with a normal and selected image with target/selector */
    static CCMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    static CCMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);

    /** initializes a menu item with a normal, selected  and disabled image with target/selector */
    bool initWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);
    // super methods
    virtual void setColor(const ccColor3B& color);
    virtual const ccColor3B& getColor();
    virtual void setOpacity(GLubyte opacity);
    virtual GLubyte getOpacity();
    
    /**
     @since v0.99.5
     */
    virtual void selected();
    virtual void unselected();
    virtual void setEnabled(bool bEnabled);
    
    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
protected:
    virtual void updateImagesVisibility();
};

/** @brief CCMenuItemImage accepts images as items.
 The images has 3 different states:
 - unselected image
 - selected image
 - disabled image
 
 For best results try that all images are of the same size
 */
class CC_DLL CCMenuItemImage : public CCMenuItemSprite
{
public:
    CCMenuItemImage();
    virtual ~CCMenuItemImage(){}

    /** creates a menu item with a normal and selected image*/
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage);
    /** creates a menu item with a normal,selected  and disabled image*/
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage, const char *disabledImage);
    /** creates a menu item with a normal and selected image with target/selector */
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector);

public:
    /** initializes a menu item with a normal, selected  and disabled image with target/selector */
    bool initWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector);
    /** sets the sprite frame for the normal image */
    void setNormalSpriteFrame(CCSpriteFrame* frame);
    /** sets the sprite frame for the selected image */
    void setSelectedSpriteFrame(CCSpriteFrame* frame);
    /** sets the sprite frame for the disabled image */
    void setDisabledSpriteFrame(CCSpriteFrame* frame);

    /** Creates an CCMenuItemImage.
     */
    static CCMenuItemImage* create();

public:
	virtual bool init();
	/** The item was selected (not activated), similar to "mouse-over" */
	virtual void selected();
	/** The item was unselected */
	virtual void unselected();

public:
	/** set the target/selector of the menu item*/
	void setSelectedTarget(CCObject *rec, SEL_MenuHandler selector);
	/** set the target/selector of the menu item*/
	void setUnSelectedTarget(CCObject *rec, SEL_MenuHandler selector);

protected:
	CCObject*       m_pSelectedListener;
	SEL_MenuHandler	m_pSelectedfnSelector;
	CCObject*       m_pUnSelectedListener;
	SEL_MenuHandler	m_pUnSelectedfnSelector;

public:
	static  CCMenuItemImageNormalFileProperty    s_MenuItemImageNormalFileProperty;
	static  CCMenuItemImageSelectedFileProperty  s_MenuItemImageSelectedFileProperty;
	static  CCMenuItemImageDisabledFileProperty  s_MenuItemImageDisabledFileProperty;
	static  CCMenuItemImageNormalFrameProperty    s_MenuItemImageNormalFrameProperty;
	static  CCMenuItemImageSelectedFrameProperty  s_MenuItemImageSelectedFrameProperty;
	static  CCMenuItemImageDisabledFrameProperty  s_MenuItemImageDisabledFrameProperty;
};

/** @brief CCMenuItemImage accepts images as items.
 The images has 3 different states:
 - unselected image
 - selected image
 - disabled image
 
 For best results try that all images are of the same size
 */
class CC_DLL CCMenuItemImageLabel : public CCMenuItemImage
{
public:
    CCMenuItemImageLabel()
	{
		m_pLabel = NULL;

		addProperty(&s_MenuItemImageLabelTextProperty);
		addProperty(&s_MenuItemImageLabelFontNameProperty);
		addProperty(&s_MenuItemImageLabelFontSizeProperty);
	}	
    virtual ~CCMenuItemImageLabel()
	{
		
	}

public:
	virtual bool init();

protected:
	virtual void setNormalImage(CCNode* var);

public:
	// set label font size
	void  setLabelFontSize(int size);
	// get label font size
	int   getLabelFontSize();
	// set label font name
	void  setLabelFontName(std::string name);
	// get label font name
	std::string getLabelFontName();
	// set label text
	void  setLabelText(std::string text);
	// get label text
	std::string getLabelText();

protected:
	CCLabelTTF* m_pLabel;

protected:
	static  CCMenuItemImageLabelTextProperty s_MenuItemImageLabelTextProperty;
	static  CCMenuItemImageLabelFontNameProperty s_MenuItemImageLabelFontNameProperty; 
	static  CCMenuItemImageLabelFontSizeProperty s_MenuItemImageLabelFontSizeProperty; 
};

/** @brief A CCMenuItemToggle
 A simple container class that "toggles" it's inner items
 The inner itmes can be any MenuItem
 */
class CC_DLL CCMenuItemToggle : public CCMenuItem, public CCRGBAProtocol
{
    /** conforms with CCRGBAProtocol protocol */
    CC_PROPERTY(GLubyte, m_cOpacity, Opacity);
    /** conforms with CCRGBAProtocol protocol */
    CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color);
    /** returns the selected item */
    CC_PROPERTY(unsigned int, m_uSelectedIndex, SelectedIndex);
    /** CCMutableArray that contains the subitems. You can add/remove items in runtime, and you can replace the array with a new one.
     @since v0.7.2
     */
    CC_PROPERTY(CCArray*, m_pSubItems, SubItems);
public:
    CCMenuItemToggle()
    : m_cOpacity(0)
    , m_uSelectedIndex(0)
    , m_pSubItems(NULL)            
    {}
    virtual ~CCMenuItemToggle();

    /** creates a menu item from a list of items with a target/selector */
    static CCMenuItemToggle* createWithTarget(CCObject* target, SEL_MenuHandler selector, CCMenuItem* item, ...);  

    /** initializes a menu item from a list of items with a target selector */
    bool initWithTarget(CCObject* target, SEL_MenuHandler selector, CCMenuItem* item, va_list args);

	/** creates a menu item with no target/selector and no items */
	static CCMenuItemToggle* create();
    /** creates a menu item with a item */
    static CCMenuItemToggle* create(CCMenuItem *item);

    /** initializes a menu item with a item */
    bool initWithItem(CCMenuItem *item);
    /** add more menu item */
    void addSubItem(CCMenuItem *item);
    
    /** return the selected item */
    CCMenuItem* selectedItem();
    // super methods
    virtual void activate();
    virtual void selected();
    virtual void unselected();
    virtual void setEnabled(bool var);
    
	virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
	virtual bool isOpacityModifyRGB(void) { return false;}
};

/** @brief CCMenuItemSpritePushed accepts CCNode<CCRGBAProtocol> objects as items.
The images has 2 different states:
- unselected image
- selected image

@since v0.8.0
*/
class CC_DLL CCMenuItemSpriteSingleClick: public CCMenuItem, public CCRGBAProtocol
{
	/** the image used when the item is not selected */
	CC_PROPERTY(CCNode*, m_pNormalImage, NormalImage);
	/** the image used when the item is disabled */
	CC_PROPERTY(CCNode*, m_pDisabledImage, DisabledImage);

public:
	CCMenuItemSpriteSingleClick()
		:m_pNormalImage(NULL)
		,m_pDisabledImage(NULL)
	{
		addProperty(&s_MenuItemSpriteSingleClickDisabledFileProperty);
		addProperty(&s_MenuItemSpriteSingleClickDisabledFrameProperty);
		addProperty(&s_MenuItemSpriteSingleClickNormalFileProperty);
		addProperty(&s_MenuItemSpriteSingleClickNormalFrameProperty);
	}

public:
	/** initializes a menu item with a normal, selected with target/selector */
	bool initFromNormalSpriteSingleClick(CCNode* normalSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);

public:
	virtual bool init();

public:
	// super methods
	virtual void setColor(const ccColor3B& color);
	virtual const ccColor3B& getColor();
	virtual void setOpacity(GLubyte opacity);
	virtual GLubyte getOpacity();

	/**
	@since v0.99.5
	*/
	virtual void selected();
	virtual void unselected();
	virtual void activate();
	virtual void setEnabled(bool bEnabled);

	virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
	virtual bool isOpacityModifyRGB(void) { return false;}

protected:
	virtual void updateImagesVisibility();

public:
	/** creates a menu item with a normal, selected and disabled image*/
	static CCMenuItemSpriteSingleClick * itemFromNormalSpriteSingleClick(CCNode* normalSprite, CCNode* disabledSprite = NULL);
	/** creates a menu item with a normal and selected image with target/selector */
	static CCMenuItemSpriteSingleClick * itemFromNormalSpriteSingleClick(CCNode* normalSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);

private:
	static CCMenuItemSpriteSingleClickDisabledFileProperty s_MenuItemSpriteSingleClickDisabledFileProperty;
	static CCMenuItemSpriteSingleClickDisabledFrameProperty s_MenuItemSpriteSingleClickDisabledFrameProperty;
	static CCMenuItemSpriteSingleClickNormalFileProperty s_MenuItemSpriteSingleClickNormalFileProperty;
	static CCMenuItemSpriteSingleClickNormalFrameProperty s_MenuItemSpriteSingleClickNormalFrameProperty;

};

/** @brief CCMenuItemSpritePushed accepts CCNode<CCRGBAProtocol> objects as items.
The images has 2 different states:
- unselected image
- selected image

@since v0.8.0
*/
class CC_DLL CCMenuItemSpritePushed : public CCMenuItem, public CCRGBAProtocol
{
	/** the image used when the item is not selected */
	CC_PROPERTY(CCNode*, m_pNormalImage, NormalImage);
	/** the image used when the item is selected */
	CC_PROPERTY(CCNode*, m_pSelectedImage, SelectedImage);
	/** the image used when the item is disabled */
	CC_PROPERTY(CCNode*, m_pDisabledImage, DisabledImage);

public:
	CCMenuItemSpritePushed()
		:m_pNormalImage(NULL)
		,m_pSelectedImage(NULL)
		,m_pDisabledImage(NULL)
	{
		addProperty(&s_MenuItemSpritePushedNormalFileProperty);
		addProperty(&s_MenuItemSpritePushedSelectedFileProperty);

		addProperty(&s_MenuItemSpritePushedNormalFrameProperty);
		addProperty(&s_MenuItemSpritePushedSelectedFrameProperty);

		addProperty(&s_MenuItemSpritePushedDisabledFileProperty);
		addProperty(&s_MenuItemSpritePushedDisabledFrameProperty);

		addProperty(&s_MenuItemSpritePushedSelectedProperty);
	}

public:
	/** initializes a menu item with a normal, selected with target/selector */
	bool initFromNormalSpritePushed(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);
	
public:
	// set Selected
	void  setSelect(bool bSelect);
	// is selected
	bool  isSelected();

public:
	virtual bool init();

public:
	// super methods
	virtual void setColor(const ccColor3B& color);
	virtual const ccColor3B& getColor();
	virtual void setOpacity(GLubyte opacity);
	virtual GLubyte getOpacity();

	/**
	@since v0.99.5
	*/
	virtual void activate();
	virtual void selected();
	virtual void unselected();
	virtual void setEnabled(bool bEnabled);

	virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
	virtual bool isOpacityModifyRGB(void) { return false;}

protected:
	virtual void updateImagesVisibility();

public:
	/** creates a menu item with a normal, selected and disabled image*/
	static CCMenuItemSpritePushed * itemFromNormalSpritePushed(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite = NULL);
	/** creates a menu item with a normal and selected image with target/selector */
	static CCMenuItemSpritePushed * itemFromNormalSpritePushed(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);

public:
	static  CCMenuItemSpritePushedNormalFileProperty    s_MenuItemSpritePushedNormalFileProperty;
	static  CCMenuItemSpritePushedSelectedFileProperty  s_MenuItemSpritePushedSelectedFileProperty;
	static  CCMenuItemSpritePushedNormalFrameProperty   s_MenuItemSpritePushedNormalFrameProperty;
	static  CCMenuItemSpritePushedSelectedFrameProperty s_MenuItemSpritePushedSelectedFrameProperty;
	static  CCMenuItemSpritePushedDisabledFileProperty  s_MenuItemSpritePushedDisabledFileProperty;
	static  CCMenuItemSpritePushedDisabledFrameProperty s_MenuItemSpritePushedDisabledFrameProperty;
	static  CCMenuItemSpritePushedSelectedProperty      s_MenuItemSpritePushedSelectedProperty;
};

/** @brief CCMenuItemSpritePushed accepts CCNode<CCRGBAProtocol> objects as items.
The images has 2 different states:
- unselected image
- selected image

@since v0.8.0
*/
class CC_DLL CCMenuItemTabSprite : public CCMenuItem, public CCRGBAProtocol
{
	/** the image used when the item is not selected */
	CC_PROPERTY(CCNode*, m_pNormalImage, NormalImage);
	/** the image used when the item is selected */
	CC_PROPERTY(CCNode*, m_pSelectedImage, SelectedImage);

public:
	CCMenuItemTabSprite()
	{
		m_pNormalImage = NULL;
		m_pSelectedImage = NULL;

		addProperty(&s_MenuItemTabSpriteSelectedFileProperty);
		addProperty(&s_MenuItemTabSpriteSelectedFrameProperty);

		addProperty(&s_MenuItemTabSpriteNormalFileProperty);
		addProperty(&s_MenuItemTabSpriteNormalFrameProperty);

		addProperty(&s_MenuItemTabSpriteSelectedProperty);
	}

public:
	/** initializes a menu item with a normal, selected with target/selector */
	bool  initFromNormalTabSprite(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector);
	
public:
	// set Selected
	void  setSelect(bool bSelect);
	// is selected
	bool  isSelected();

public:
	virtual bool init();

public:
	// super methods
	virtual void setColor(const ccColor3B& color);
	virtual const ccColor3B& getColor();
	virtual void setOpacity(GLubyte opacity);
	virtual GLubyte getOpacity();

	/**
	@since v0.99.5
	*/
	virtual void activate();
	virtual void selected();
	virtual void unselected();
	virtual void setEnabled(bool bEnabled);

	virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
	virtual bool isOpacityModifyRGB(void) { return false;}

protected:
	virtual void updateImagesVisibility();

public:
	/** creates a menu item with a normal, selected and disabled image*/
	static CCMenuItemTabSprite * itemFromNormalSpritePushed(CCNode* normalSprite, CCNode* selectedSprite);
	/** creates a menu item with a normal and selected image with target/selector */
	static CCMenuItemTabSprite * itemFromNormalSpritePushed(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector);

public:
	static CCMenuItemTabSpriteSelectedFileProperty s_MenuItemTabSpriteSelectedFileProperty;
	static CCMenuItemTabSpriteSelectedFrameProperty s_MenuItemTabSpriteSelectedFrameProperty;
	static CCMenuItemTabSpriteNormalFileProperty s_MenuItemTabSpriteNormalFileProperty;
	static CCMenuItemTabSpriteNormalFrameProperty s_MenuItemTabSpriteNormalFrameProperty;
	static CCMenuItemTabSpriteSelectedProperty s_MenuItemTabSpriteSelectedProperty;
};

// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCMENU_ITEM_H__
