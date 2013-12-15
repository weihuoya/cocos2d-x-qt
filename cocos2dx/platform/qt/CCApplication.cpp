/**
* Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* For the applicable distribution terms see the license text file included in
* the distribution.
*/
#include "CCApplication.h"
#include "CCDirector.h"
#include "CCEGLView.h"
#include "CCApplicationPrivate.h"

#include <QApplication>
#include <Qt/qobject.h>
#include <QTimer>
#include <QSystemInfo>
//#include <unistd.h>
//#include <sys/time.h>

USING_NS_CC;
QTM_USE_NAMESPACE

// sharedApplication pointer
CCApplication * CCApplication::sm_pSharedApplication = NULL;
static const double DEFAULT_ANIMATION_INTERVAL = (1.0f / 60.0f * 1000.0f);


QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CCApplicationPrivate[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   30,   30,   30, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CCApplicationPrivate[] = {
    "CCApplicationPrivate\0update()\0\0"
};

const QMetaObject CCApplicationPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CCApplicationPrivate,
      qt_meta_data_CCApplicationPrivate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CCApplicationPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CCApplicationPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CCApplicationPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CCApplicationPrivate))
        return static_cast<void*>(const_cast< CCApplicationPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int CCApplicationPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: update(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE


CCApplicationPrivate::CCApplicationPrivate(QObject *parent)
    : QObject(parent), m_ptr(NULL), m_timer(NULL), m_interval(DEFAULT_ANIMATION_INTERVAL)
{
    #ifdef Q_OS_SYMBIAN
        QCoreApplication:setAttribute(Qt::AA_S60DisablePartialScreenInputMode, false);
    #endif
}

CCApplicationPrivate::~CCApplicationPrivate()
{
    CC_SAFE_DELETE(m_timer);
}

void CCApplicationPrivate::setInterval(double interval)
{
    m_interval = interval;
    if (m_timer) m_timer->start(m_interval);
}

void CCApplicationPrivate::start()
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(m_interval);
}

void CCApplicationPrivate::update()
{
    m_ptr->update();
}


//-------------------------------------------------
CCApplication::CCApplication():
    m_impl(new CCApplicationPrivate),
    m_refCount(0),
    m_nAnimationInterval(DEFAULT_ANIMATION_INTERVAL)
{
    m_impl->m_ptr = this;
    sm_pSharedApplication = this;
}

CCApplication::~CCApplication()
{
	CC_ASSERT(this == sm_pSharedApplication);
	sm_pSharedApplication = NULL;
	delete m_impl;
}

void CCApplication::lock()
{
    m_refCount++;
}

void CCApplication::unlock()
{
    CC_ASSERT(m_refCount > 0);
    if (m_refCount > 0)
    {
        m_refCount--;
    }
}

void CCApplication::setAnimationInterval(double interval)
{
    m_nAnimationInterval = interval * 1000.0f;
    m_impl->setInterval(m_nAnimationInterval);
}

ccLanguageType CCApplication::getCurrentLanguage()
{
    QSystemInfo sysInfo;
    ccLanguageType ret = kLanguageEnglish;
    QString lang = sysInfo.currentLanguage();
    
    if ("zh" == lang)
	{
		ret = kLanguageChinese;
	}
	else if ("en" == lang)
	{
		ret = kLanguageEnglish;
	}
	else if ("fr" == lang)
	{
		ret = kLanguageFrench;
	}
	else if ("it" == lang)
	{
		ret = kLanguageItalian;
	}
	else if ("de" == lang)
	{
		ret = kLanguageGerman;
	}
	else if ("es" == lang)
	{
		ret = kLanguageSpanish;
	}
	else if ("ru" == lang)
	{
		ret = kLanguageRussian;
	}
	else if ("ko" == lang)
	{
		ret = kLanguageKorean;
	}
	else if ("ja" == lang)
	{
		ret = kLanguageJapanese;
	}
	else if ("hu" == lang)
	{
		ret = kLanguageHungarian;
	}
    else if ("pt" == lang)
	{
		ret = kLanguagePortuguese;
	}
    else if ("ar" == lang)
	{
		ret = kLanguageArabic;
	}
    
    return ret;
}

TargetPlatform CCApplication::getTargetPlatform()
{
    return kTargetQt;
}

int CCApplication::run()
{
    int argc = 1;
    char* argv[] = {"cocos2d", NULL};
    QApplication app(argc, argv);

    // Make sure the view is initialized
    CCEGLView::sharedOpenGLView();
    
    if (!applicationDidFinishLaunching()) return -1;
    
    //start timer
    m_impl->start();
    
    return app.exec();
}

CCApplication* CCApplication::sharedApplication()
{
    CC_ASSERT(sm_pSharedApplication);
    return sm_pSharedApplication;
}

void CCApplication::update()
{
    // m_refCount is here to prevent calling the mainloop from nested event loops
    if (!m_refCount)
    {
        CCDirector::sharedDirector()->mainLoop();
    }
}

