/**
* Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* For the applicable distribution terms see the license text file included in
* the distribution.
*/

#ifndef CCACCELEROMETER_QT_H_
#define CCACCELEROMETER_QT_H_

#include "CCCommon.h"
#include "CCAccelerometerDelegate.h"

#include <QObject>
#include <QVariant>

class AccelerometerFilter;

namespace   cocos2d {

class CCAccelerometer : public QObject
{
    Q_OBJECT

public:
    explicit CCAccelerometer();
    virtual ~CCAccelerometer();

    static CCAccelerometer* sharedAccelerometer();

    void removeDelegate(CCAccelerometerDelegate* pDelegate);
    void addDelegate(CCAccelerometerDelegate* pDelegate);
    void setDelegate(CCAccelerometerDelegate* pDelegate);
    void setAccelerometerInterval(float interval);

public Q_SLOTS:
    void readingChanged(QVariant x, QVariant y, QVariant z);

private:
    void setEnable(bool bEnable);

private:
    CCAccelerometerDelegate* m_pAccelDelegate;
    AccelerometerFilter *m_pAccelFilter;
};

}//namespace   cocos2d

#endif /* CCACCELEROMETER_QT_H_ */
