/**
* Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* For the applicable distribution terms see the license text file included in
* the distribution.
*/

#include <math.h>
#include "accelerometerfilter.h"

QTM_USE_NAMESPACE

AccelerometerFilter::AccelerometerFilter()
{
    m_pAccel = new QAccelerometer(this);
    m_pAccel->addFilter(this);
    m_pAccel->setDataRate(50);
    m_pAccel->start();
}

AccelerometerFilter::~AccelerometerFilter()
{
    delete m_pAccel;
}

bool AccelerometerFilter::filter(QAccelerometerReading *reading)
{
    // Harmattan landscape
    qreal rx = reading->y();
    qreal ry = -reading->x();
    qreal rz = reading->z();

    Q_EMIT readingChanged(rx, ry, rz);

    return false;
}
