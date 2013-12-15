/**
* Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* For the applicable distribution terms see the license text file included in
* the distribution.
*/

#ifndef CCAPPLICATION_QT_H_
#define CCAPPLICATION_QT_H_

#include "CCApplicationProtocol.h"
#include "CCCommon.h"
#include "CCGeometry.h"

NS_CC_BEGIN

class CCApplicationPrivate;

class CC_DLL CCApplication: public CCApplicationProtocol
{
public:
    CCApplication();
    virtual ~CCApplication();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching() = 0;

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground() = 0;

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground() = 0;

    /**
    @brief    Callback by CCDirector for limit FPS.
    @interval       The time, which expressed in second in second, between current frame and next.
    */
    virtual void setAnimationInterval(double interval);

    /**
    @brief Get current language config
    @return Current language config
    */
    virtual ccLanguageType getCurrentLanguage();
    
    /**
     @brief Get target platform
     */
    virtual TargetPlatform getTargetPlatform();

	/**
	 @brief	Run the message loop.
	 */
	int run();

	/**
	 @brief	Get current applicaiton instance.
	 @return Current application instance pointer.
	 */
	static CCApplication* sharedApplication();

    void lock();
    void unlock();
    void update();

protected:
    CCApplicationPrivate *const m_impl;
    int m_refCount;
    long m_nAnimationInterval;
	static CCApplication * sm_pSharedApplication;
};

NS_CC_END

#endif /* CCAPPLICATION_QT_H_ */
