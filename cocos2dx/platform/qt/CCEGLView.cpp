/**
* Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* For the applicable distribution terms see the license text file included in
* the distribution.
*/

#include "CCEGLView.h"

#include "CCGL.h"

#include "CCSet.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"
#include "CCIMEDispatcher.h"
#include "CCApplication.h"

#ifdef Q_OS_LINUX
#include <QX11Info>
// QEvent::KeyPress/release conflicts with X.h
#undef KeyPress
#undef KeyRelease
#endif

#include <QEvent>

#ifdef Q_OS_SYMBIAN
#include <eikenv.h>
#include <aknappui.h>
#endif

#ifdef MEEGO_EDITION_HARMATTAN
#include <qmeegographicssystemhelper.h>
#endif


bool initExtensions()
{
    const char* extensions = (const char*)glGetString(GL_EXTENSIONS);

    CCLOG(extensions);

    return true;
}

NS_CC_BEGIN


static CCEGLView* s_pMainWindow = NULL;

CCEGLView::CCEGLView(QWidget* parent):
    QWidget(parent),
    bIsInit(false),
    m_eglDisplay(NULL),
    m_eglConfig(NULL),
    m_eglSurface(NULL),
    m_eglContext(NULL)
{
    setAutoFillBackground(false);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_NativeWindow);
    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_StyledBackground, false);
    setAttribute(Qt::WA_PaintUnclipped);

    setAttribute(Qt::WA_InputMethodEnabled, true);
    setAttribute(Qt::WA_KeyboardFocusChange, true);
    setInputMethodHints(Qt::ImhNoPredictiveText);

    qApp->installEventFilter(this);

#ifdef MS_USE_TOUCH_EVENTS
    setAttribute(Qt::WA_AcceptTouchEvents);

    for(int i = 0; i < MAX_TOUCH_POINTS; i++)
        m_pTouch[i] = NULL;
#else
    m_pTouch = NULL;
#endif

#ifdef MEEGO_EDITION_HARMATTAN
    QMeeGoGraphicsSystemHelper::setSwitchPolicy(QMeeGoGraphicsSystemHelper::NoSwitch);

    QInputContext *ic = QInputContextFactory::create("MInputContext", 0);
    if (ic)
    {
        qApp->setInputContext(ic);
    }
#endif // MEEGO_EDITION_HARMATTAN
}

CCEGLView::~CCEGLView()
{
}

void CCEGLView::end()
{
    qApp->exit(0);
}

bool CCEGLView::isOpenGLReady()
{
    return bIsInit;
}

void CCEGLView::swapBuffers()
{
    if(bIsInit)
    {
        eglSwapBuffers(m_eglDisplay, m_eglSurface);
    }
}

void CCEGLView::setIMEKeyboardState(bool bOpen)
{
    QInputContext *ic = qApp->inputContext();

    if(!ic)
        return;

    if(bOpen)
    {
        QWidget* focusWidget = qApp->focusWidget();
        if(focusWidget)
        {
            focusWidget->setInputMethodHints(Qt::ImhNoPredictiveText);
            focusWidget->setAttribute(Qt::WA_InputMethodEnabled, true);
            ic->setFocusWidget(focusWidget);

            QEvent request(QEvent::RequestSoftwareInputPanel);
            ic->filterEvent(&request);
        }
    }
    else
    {
        QEvent close(QEvent::CloseSoftwareInputPanel);
        ic->filterEvent(&close);
        ic->reset();
    }
}

bool CCEGLView::Create()
{
#if defined(Q_OS_SYMBIAN)
    showFullScreen();
#elif !defined(MEEGO_EDITION_HARMATTAN)
    show();
#endif

    CCLOG("Create: width = %d height = %d", width(), height());

    setFrameSize(width(), height());

#ifdef MEEGO_EDITION_HARMATTAN
    showFullScreen();
#endif

    if (!initEGL())
    {
        return false;
    }

    activateWindow();
    setFocus();
    grabKeyboard();

    s_pMainWindow = this;

    return true;
}

void CCEGLView::release()
{
    releaseEGL();

    qApp->exit(0);
}

CCEGLView* CCEGLView::sharedOpenGLView()
{
    static CCEGLView* s_pEglView = NULL;
    if (s_pEglView == NULL)
    {
        s_pEglView = new CCEGLView();
        if(!s_pEglView->Create())
        {
            assert(s_pMainWindow);
        }
    }
    return s_pEglView;
}

void CCEGLView::inputMethodEvent(QInputMethodEvent *event)
{
#if defined(Q_OS_SYMBIAN)
    // This section of code is used when the virtual keyboard is in "keypad"-mode
    static bool charStart = true;
    static char lastChar = 0;

    QString commitString = event->commitString();
    if(commitString.length() > 0)
    {
        charStart = true;
        lastChar = 0;
    }
    else
    {
        QString preeditString = event->preeditString();
        if(preeditString.length() > 0)
        {
            char newChar = preeditString.at(preeditString.length()-1).toAscii();
            if(newChar != lastChar)
            {
                if(!charStart)
                    CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();

                CCIMEDispatcher::sharedDispatcher()->dispatchInsertText(&newChar, 1);
                lastChar = newChar;
            }

            charStart = false;
        }
    }
#elif defined(MEEGO_EDITION_HARMATTAN)
    QString commitString = event->commitString();
    if(commitString.length() > 0)
    {
        char newChar = commitString.at(commitString.length()-1).toAscii();
        CCIMEDispatcher::sharedDispatcher()->dispatchInsertText(&newChar, 1);
    }
#endif
}

bool CCEGLView::eventFilter(QObject *object, QEvent *event)
{
    switch(event->type())
    {
    case QEvent::ActivationChange:
        {
            if(isActiveWindow())
            {
                CCLOG("Activate");
                CCApplication::sharedApplication()->applicationWillEnterForeground();
            }
            else
            {
                CCLOG("Deactivate");
                CCApplication::sharedApplication()->applicationDidEnterBackground();
            }

            return false;
        }break;

    default:
        {
        }break;
    }

    return QObject::eventFilter(object, event);
}

void CCEGLView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}

void CCEGLView::resizeEvent(QResizeEvent *event)
{
    int w = event->size().width();
    int h = event->size().height();

    if(event->size().width() == event->oldSize().width() &&
       event->size().height() == event->oldSize().width()) {
        return;
    }

    CCLOG("Resize viewport to %d x %d", w, h);
    glViewport(0, 0, w, h);

    QWidget::resizeEvent(event);
}

#ifdef MS_USE_TOUCH_EVENTS

bool CCEGLView::handleTouchEvent(QEvent* event)
{
    if(!m_pDelegate)
        return true;

    CCSet beganSet;
    CCSet updateSet;
    CCSet releaseSet;

    QList<QTouchEvent::TouchPoint> touchPoints =
            static_cast<QTouchEvent *>(event)->touchPoints();
    Q_FOREACH(const QTouchEvent::TouchPoint &tp, touchPoints)
    {
        int ind = tp.id();
        if(ind >= MAX_TOUCH_POINTS)
            continue;

        if(m_pTouch[ind])
        {
            if(tp.state() & Qt::TouchPointReleased)
            {
                // release
                m_pTouch[ind]->setTouchInfo(ind, tp.pos().x(), tp.pos().y());
                releaseSet.addObject(m_pTouch[ind]);
                m_pTouch[ind]->release();
                m_pTouch[ind] = NULL;
            }
            else
            {
                // update
                m_pTouch[ind]->setTouchInfo(ind, tp.pos().x(), tp.pos().y());
                updateSet.addObject(m_pTouch[ind]);
            }
        }
        else
        {
            // begin
            m_pTouch[ind] = new CCTouch;
            m_pTouch[ind]->setTouchInfo(ind, tp.pos().x(), tp.pos().y());
            beganSet.addObject(m_pTouch[ind]);
        }
    }

    if(beganSet.count() > 0)
        m_pDelegate->touchesBegan(&beganSet, NULL);
    if(updateSet.count() > 0)
        m_pDelegate->touchesMoved(&updateSet, NULL);
    if(releaseSet.count() > 0)
        m_pDelegate->touchesEnded(&releaseSet, NULL);

    return true;
}

bool CCEGLView::handleKeyEvent(QEvent* event)
{
    QKeyEvent* ke = (QKeyEvent*)event;

    switch(ke->key())
    {
    case Qt::Key_Backspace:
        CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
        return true;

    case Qt::Key_Tab:
        break;

    case Qt::Key_Return:
    case Qt::Key_Enter:
        CCIMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
        return true;

    default:
        {
            QString str = ke->text();

            QByteArray ba = str.toAscii();
            if(ba.size() > 0)
            {
                const char* c = ba.constData();
                CCIMEDispatcher::sharedDispatcher()->dispatchInsertText(c, 1);
            }

            return true;
        }
    }

    return false;
}

bool CCEGLView::event(QEvent* event)
{
    switch(event->type())
    {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
        if (handleTouchEvent(event))
            return true;
        else
            break;

    case QEvent::KeyPress:
        if (handleKeyEvent(event))
            return true;
        else
            break;

    case QEvent::KeyRelease:
        return true;

    default:
        break;
    }

    QWidget::event(event);
}
#else
void CCEGLView::mousePressEvent(QMouseEvent *event)
{
    QMouseEvent* mouseEvent = (QMouseEvent*)event;

    if(m_pTouch)
        m_pTouch->release();

    m_pTouch = new CCTouch;
    m_pTouch->setTouchInfo(0, (float)mouseEvent->x(), (float)mouseEvent->y());

    CCSet set;
    set.addObject(m_pTouch);

    m_pDelegate->touchesBegan(&set, NULL);

    QWidget::mousePressEvent(event);
}

void CCEGLView::mouseReleaseEvent(QMouseEvent *event)
{
    QMouseEvent* mouseEvent = (QMouseEvent*)event;

    if(!m_pTouch)
        m_pTouch = new CCTouch;

    m_pTouch->setTouchInfo(0, (float)mouseEvent->x(), (float)mouseEvent->y());

    CCSet set;
    set.addObject(m_pTouch);

    m_pDelegate->touchesEnded(&set, NULL);

    QWidget::mouseReleaseEvent(event);
}

void CCEGLView::mouseMoveEvent(QMouseEvent *event)
{
    QMouseEvent* mouseEvent = (QMouseEvent*)event;

    if(!m_pTouch)
        m_pTouch = new CCTouch;

    m_pTouch->setTouchInfo(0, (float)mouseEvent->x(), (float)mouseEvent->y());

    CCSet set;
    set.addObject(m_pTouch);

    m_pDelegate->touchesMoved(&set, NULL);

    QWidget::mouseMoveEvent(event);
}
#endif

bool CCEGLView::initEGL()
{
    if(bIsInit)
        return true;

    EGLNativeWindowType nativeWindow = (EGLNativeWindowType)this->winId();
    EGLNativeDisplayType nativeDisplay = EGL_DEFAULT_DISPLAY;

#ifdef Q_OS_LINUX
    nativeDisplay = (EGLNativeDisplayType)x11Info().display();
#endif // Q_OS_LINUX

#ifdef Q_OS_SYMBIAN
    nativeWindow = (EGLNativeWindowType)(winId()->DrawableWindow());
    nativeDisplay = EGL_DEFAULT_DISPLAY;
#endif // Q_OS_SYMBIAN

    m_eglDisplay = eglGetDisplay(nativeDisplay);
    if(!m_eglDisplay)
    {
        return false;
    }

    if(!eglInitialize(m_eglDisplay, NULL, NULL))
    {
        return false;
    }

    eglBindAPI(EGL_OPENGL_ES_API);

    EGLint configAttributes[] =
    {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_DEPTH_SIZE, 16,
        EGL_NONE,
    };

    EGLint configCount = 0;
    if(!eglChooseConfig(m_eglDisplay, configAttributes, &m_eglConfig, 1,
                        &configCount) || configCount != 1)
    {
        CCLOG("eglChooseConfig failed");
        return false;
    }

    m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig,
                                          nativeWindow, NULL);
    if(!m_eglSurface)
    {
        CCLOG("eglCreateWindowSurface failed");
        return false;
    }

    EGLint contextAttributes[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2, // 1
        EGL_NONE,
    };

    m_eglContext = eglCreateContext(m_eglDisplay, m_eglConfig, NULL,
                                    contextAttributes);
    if(m_eglContext == EGL_NO_CONTEXT)
    {
        CCLOG("eglCreateContext failed");
        return false;
    }

    if(!eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext))
    {
        CCLOG("eglMakeCurrent failed");
        return false;
    }

    if(!initExtensions())
    {
        CCLOG("initExtensions failed");
        return false;
    }

    bIsInit = true;

    return true;
}

void CCEGLView::releaseEGL()
{
    if(m_eglContext)
    {
        eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE,
                       EGL_NO_CONTEXT);
        eglDestroyContext(m_eglDisplay, m_eglContext);
        m_eglContext = NULL;
    }

    if(m_eglSurface)
    {
        eglDestroySurface(m_eglDisplay, m_eglSurface);
        m_eglSurface = NULL;
    }

    m_eglConfig = NULL;

    if(m_eglDisplay)
    {
        eglTerminate(m_eglDisplay);
        m_eglDisplay = NULL;
    }

    bIsInit = false;
}

NS_CC_END
