/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 
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
#include "CCEditBoxImplQT.h"

#include <QIntValidator>
#include <QDoubleValidator>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_QT)

#define kLabelZOrder  9999
static const int CC_EDIT_BOX_PADDING = 2;

NS_CC_EXT_BEGIN

CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
{
    return new CCEditBoxImplQT(pEditBox);
}

CCEditBoxImplQT::CCEditBoxImplQT(CCEditBox* pEditText)
  : CCEditBoxImpl(pEditText)
  , m_pLabel(NULL)
  , m_pLabelPlaceHolder(NULL)
  , m_obAnchorPoint(ccp(0.5f, 0.5f))
  , m_systemControl(NULL)
  , m_editValidator(NULL)
  , m_eKeyboardReturnType(kKeyboardReturnTypeDefault)
{
}

CCEditBoxImplQT::~CCEditBoxImplQT()
{
    delete m_systemControl;
}

void CCEditBoxImplQT::doAnimationWhenKeyboardMove(float duration, float distance)
{
}

bool CCEditBoxImplQT::initWithSize(const CCSize& size)
{
    do 
    {
        CCEGLViewProtocol* eglView = CCEGLView::sharedOpenGLView();
        
        m_systemControl = new QLineEdit( (QWidget*)eglView );
        if (!m_systemControl) break;
        m_systemControl->setVisible(false);
        m_systemControl->setFixedSize(size.width * eglView->getScaleX(), size.height * eglView->getScaleY());
        
        initInactiveLabels(size);
        setContentSize(size);
        
        return true;
    }while (0);
    
    return false;
}

void CCEditBoxImplQT::initInactiveLabels(const CCSize& size)
{
    std::string str = m_systemControl->font().family().toStdString();
    const char* pDefaultFontName = str.c_str();

    m_pLabel = CCLabelTTF::create("", "", 0.0f);
    m_pLabel->setAnchorPoint(ccp(0, 0.5f));
    m_pLabel->setColor(ccWHITE);
    m_pLabel->setVisible(false);
    m_pEditBox->addChild(m_pLabel, kLabelZOrder);
	
    m_pLabelPlaceHolder = CCLabelTTF::create("", "", 0.0f);
	// align the text vertically center
    m_pLabelPlaceHolder->setAnchorPoint(ccp(0, 0.5f));
    m_pLabelPlaceHolder->setColor(ccGRAY);
    m_pEditBox->addChild(m_pLabelPlaceHolder, kLabelZOrder);
    
    setFont(pDefaultFontName, size.height*2/3);
    setPlaceholderFont(pDefaultFontName, size.height*2/3);
}

void CCEditBoxImplQT::setInactiveText(const char* pText)
{
    QLineEdit::EchoMode mode = m_systemControl->echoMode();
    if(mode == QLineEdit::Password || mode == QLineEdit::PasswordEchoOnEdit)
    {
        std::string passwordString;
        for(int i = 0; i < strlen(pText); ++i)
            passwordString.append("\u25CF");
        m_pLabel->setString(passwordString.c_str());
    }
    else
        m_pLabel->setString(getText());
	
    // Clip the text width to fit to the text box
    float fMaxWidth = m_pEditBox->getContentSize().width - CC_EDIT_BOX_PADDING * 2;
    CCRect clippingRect = m_pLabel->getTextureRect();
    if(clippingRect.size.width > fMaxWidth) 
    {
        clippingRect.size.width = fMaxWidth;
        m_pLabel->setTextureRect(clippingRect);
    }
}

void CCEditBoxImplQT::setFont(const char* pFontName, int fontSize)
{
    QString fontName(pFontName);
    float scaleFactor = CCEGLView::sharedOpenGLView()->getScaleX();
    QFont textFont(fontName, fontSize * scaleFactor);
    
    m_systemControl->setFont(textFont);
    m_pLabel->setFontName(pFontName);
    m_pLabel->setFontSize(fontSize);
    m_pLabelPlaceHolder->setFontName(pFontName);
    m_pLabelPlaceHolder->setFontSize(fontSize);
}

void CCEditBoxImplQT::setFontColor(const ccColor3B& color)
{
    //m_systemControl.textField.textColor = [UIColor colorWithRed:color.r / 255.0f green:color.g / 255.0f blue:color.b / 255.0f alpha:1.0f];
    CCString* css = new CCString();
    
    css->initWithFormat("background-color: rgb(%d,%d,%d)", color.r, color.g, color.b);
    m_systemControl->setStyleSheet(css->getCString());
    m_pLabel->setColor(color);
    
    css->release();
}

void CCEditBoxImplQT::setPlaceholderFont(const char* pFontName, int fontSize)
{
	// TODO need to be implemented.
}

void CCEditBoxImplQT::setPlaceholderFontColor(const ccColor3B& color)
{
    m_pLabelPlaceHolder->setColor(color);
}

void CCEditBoxImplQT::setInputMode(EditBoxInputMode inputMode)
{
    switch (inputMode)
    {
        case kEditBoxInputModeEmailAddr:
            if(NULL != m_editValidator) {
                delete m_editValidator;
                m_editValidator = NULL;
            }
            m_systemControl->setValidator(m_editValidator);
            m_systemControl->setInputMethodHints(Qt::ImhEmailCharactersOnly);
            break;
        case kEditBoxInputModeNumeric:
            if(NULL != m_editValidator) delete m_editValidator;
            m_editValidator = new  QIntValidator();
            m_systemControl->setValidator(m_editValidator);
            m_systemControl->setInputMethodHints(Qt::ImhDigitsOnly);
            break;
        case kEditBoxInputModePhoneNumber:
            if(NULL != m_editValidator) {
                delete m_editValidator;
                m_editValidator = NULL;
            }
            m_systemControl->setValidator(m_editValidator);
            m_systemControl->setInputMethodHints(Qt::ImhDialableCharactersOnly);
            break;
        case kEditBoxInputModeUrl:
            if(NULL != m_editValidator) {
                delete m_editValidator;
                m_editValidator = NULL;
            }
            m_systemControl->setValidator(m_editValidator);
            m_systemControl->setInputMethodHints(Qt::ImhUrlCharactersOnly);
            break;
        case kEditBoxInputModeDecimal:
            if(NULL != m_editValidator) delete m_editValidator;
            m_editValidator = new  QDoubleValidator();
            m_systemControl->setValidator(m_editValidator);
            m_systemControl->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
            break;
        case kEditBoxInputModeSingleLine:
        default:
            if(NULL != m_editValidator) {
                delete m_editValidator;
                m_editValidator = NULL;
            }
            m_systemControl->setValidator(m_editValidator);
            m_systemControl->setInputMethodHints(Qt::ImhNone);
            break;
    }
}

void CCEditBoxImplQT::setMaxLength(int maxLength)
{
    m_systemControl->setMaxLength(maxLength);
}

int CCEditBoxImplQT::getMaxLength()
{
    return m_systemControl->maxLength();
}

void CCEditBoxImplQT::setInputFlag(EditBoxInputFlag inputFlag)
{
    switch (inputFlag)
    {
        case kEditBoxInputFlagPassword:
            m_systemControl->setEchoMode(QLineEdit::Password);
            break;
        case kEditBoxInputFlagInitialCapsWord:
        case kEditBoxInputFlagInitialCapsSentence:
        case kEditBoxInputFlagInitialCapsAllCharacters:
            m_systemControl->setInputMethodHints(Qt::ImhPreferUppercase);
            break;
        case kEditBoxInputFlagSensitive: 
            m_systemControl->setInputMethodHints(Qt::ImhNoPredictiveText);
        default:
            m_systemControl->setInputMethodHints(Qt::ImhNoAutoUppercase);
            break;
    }
}

void CCEditBoxImplQT::setReturnType(KeyboardReturnType returnType)
{
    m_eKeyboardReturnType = returnType;
}

bool CCEditBoxImplQT::isEditing()
{
    return false;
}

void CCEditBoxImplQT::setText(const char* pText)
{
    m_systemControl->setText(QString(pText));
	if(!m_systemControl->isVisible()) {
		setInactiveText(pText);
		if(strlen(pText) == 0)
		{
			m_pLabel->setVisible(false);
			m_pLabelPlaceHolder->setVisible(true);
		}
		else
		{
			m_pLabel->setVisible(true);
			m_pLabelPlaceHolder->setVisible(false);
		}
	}
}

const char*  CCEditBoxImplQT::getText(void)
{
    return m_pLabel->getString();
}

void CCEditBoxImplQT::setPlaceHolder(const char* pText)
{
    m_systemControl->setPlaceholderText(QString(pText));
    m_pLabelPlaceHolder->setString(pText);
}

void CCEditBoxImplQT::setPosition(const CCPoint& pos)
{
	m_obPosition = pos;
	
  CCSize contentSize = m_pEditBox->getContentSize();
	CCRect rect = CCRectMake(0, 0, contentSize.width, contentSize.height);
  rect = CCRectApplyAffineTransform(rect, m_pEditBox->nodeToWorldTransform());
  
  m_systemControl->move(rect.origin.x, rect.origin.y + rect.size.height);
}

void CCEditBoxImplQT::setVisible(bool visible)
{
      //m_systemControl->setVisible(visible);
}

void CCEditBoxImplQT::setContentSize(const CCSize& size)
{
    QSize content(size.width, size.height), control = m_systemControl->size();
    control -= content;
    control /= 2;
    if(control.isValid()) {
      m_systemControl->setTextMargins(control.width(), control.height(), control.width(), control.height());
    }
}

void CCEditBoxImplQT::setAnchorPoint(const CCPoint& anchorPoint)
{
    CCLOG("[Edit text] anchor point = (%f, %f)", anchorPoint.x, anchorPoint.y);
    m_obAnchorPoint = anchorPoint;
    setPosition(m_obPosition);
}

void CCEditBoxImplQT::visit(void)
{
    
}

void CCEditBoxImplQT::onEnter(void)
{
    const char* pText = getText();
    if (pText) {
        setInactiveText(pText);
    }
}

void CCEditBoxImplQT::openKeyboard()
{
	m_pLabel->setVisible(false);
	m_pLabelPlaceHolder->setVisible(false);

	m_systemControl->setVisible(true);
  m_systemControl->setFocus();
}

void CCEditBoxImplQT::closeKeyboard()
{
    m_systemControl->clearFocus();
    delete m_systemControl;
    m_systemControl = NULL;
}

void CCEditBoxImplQT::onEndEditing()
{
	m_systemControl->setVisible(false);
	if(strlen(getText()) == 0)
	{
		m_pLabel->setVisible(false);
		m_pLabelPlaceHolder->setVisible(true);
	}
	else
	{
		m_pLabel->setVisible(true);
		m_pLabelPlaceHolder->setVisible(false);
		setInactiveText(getText());
	}
}

NS_CC_EXT_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) */


