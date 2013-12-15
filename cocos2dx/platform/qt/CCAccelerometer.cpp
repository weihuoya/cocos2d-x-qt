/**
* Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* For the applicable distribution terms see the license text file included in
* the distribution.
*/

#include "CCAccelerometer.h"
#include "ccMacros.h"
#include "accelerometerfilter.h"

#include "CCApplication.h"
#include "CCDirector.h"
#include "CCEGLView.h"

#include <QAccelerometer>

QTM_USE_NAMESPACE

NS_CC_BEGIN;

CCAccelerometer::CCAccelerometer()
    : m_pAccelDelegate(NULL),
      m_pAccelFilter(NULL)
{
}

CCAccelerometer::~CCAccelerometer()
{
    CC_SAFE_DELETE(m_pAccelFilter);
}

CCAccelerometer* CCAccelerometer::sharedAccelerometer()
{
    static CCAccelerometer s_CCAccelerometer;
    return &s_CCAccelerometer;
}

void CCAccelerometer::setDelegate(CCAccelerometerDelegate* pDelegate)
{
    m_pAccelDelegate = pDelegate;
    setEnable((pDelegate != NULL));
}

void CCAccelerometer::setAccelerometerInterval(float interval)
{

}

void CCAccelerometer::readingChanged(QVariant x, QVariant y, QVariant z)
{
    if (!m_pAccelDelegate)
    {
        return;
    }

    const time_t theTime = time(NULL);
    const double timestamp = (double)theTime / 100.0;

    CCAcceleration AccValue;

#if defined(Q_OS_SYMBIAN)
    switch(CCApplication::sharedApplication().getOrientation())
    {
    case CCApplication::kOrientationPortrait:
    case CCApplication::kOrientationPortraitUpsideDown:
        AccValue.x = y.toDouble();
        AccValue.y =-x.toDouble();
        AccValue.z = z.toDouble();
        break;

    case CCApplication::kOrientationLandscapeLeft:
    case CCApplication::kOrientationLandscapeRight:
        AccValue.x = x.toDouble();
        AccValue.y = y.toDouble();
        AccValue.z = z.toDouble();
        break;

    default:
        break;
    }
#elif defined(MEEGO_EDITION_HARMATTAN)
    AccValue.x = x.toDouble();
    AccValue.y = y.toDouble();
    AccValue.z = z.toDouble();
#endif

    m_pAccelDelegate->didAccelerate(&AccValue);
}

void CCAccelerometer::setEnable(bool bEnable)
{
    if (!bEnable)
    {
        delete m_pAccelFilter;
        m_pAccelFilter = NULL;
    }
    else if (!m_pAccelFilter)
    {
        m_pAccelFilter = new AccelerometerFilter;
        connect(m_pAccelFilter, SIGNAL(readingChanged(QVariant, QVariant, QVariant)),
                this, SLOT(readingChanged(QVariant, QVariant, QVariant)));
    }
}

NS_CC_END;
