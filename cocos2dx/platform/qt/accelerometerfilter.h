/**
* Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* For the applicable distribution terms see the license text file included in
* the distribution.
*/

#ifndef ACCELEROMETERFILTER_H_
#define ACCELEROMETERFILTER_H_

#include <QAccelerometerFilter>
#include <QAccelerometer>
#include <QVariant>

QTM_USE_NAMESPACE

class AccelerometerFilter : public QObject,
                            public QAccelerometerFilter
{
    Q_OBJECT

public:
    explicit AccelerometerFilter();
    virtual ~AccelerometerFilter();

protected: // from QAccelerometerFilter
    bool filter(QAccelerometerReading *reading);

Q_SIGNALS:
    void readingChanged(QVariant x, QVariant y, QVariant z);

private:
    QAccelerometer *m_pAccel;
};

#endif // ACCELEROMETERFILTER_H_
