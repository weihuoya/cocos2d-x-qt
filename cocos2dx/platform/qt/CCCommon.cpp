#include "CCCommon.h"

#define MAX_LEN         (cocos2d::kMaxLogLen + 1)

#include <stdio.h>
#include <QDebug>

NS_CC_BEGIN

void CCLog(const char * pszFormat, ...)
{
    char buf[MAX_LEN];

    va_list args;
    va_start(args, pszFormat);        
    vsprintf(buf, pszFormat, args);
    va_end(args);
	
	qDebug() << "cocos2d-x debug info " << buf;
}

void CCMessageBox(const char * pszMsg, const char * pszTitle)
{
	qDebug() << "cocos2d-x debug message " << pszMsg << pszTitle;
}

void CCLuaLog(const char * pszFormat)
{
	CCLog(pszFormat);
}

NS_CC_END
