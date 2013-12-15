#include <QApplication>
#include <QDesktopWidget>
#include "platform/CCDevice.h"

NS_CC_BEGIN

int CCDevice::getDPI()
{
	static int dpi = -1;
	if (dpi == -1)
	{
	    dpi = (int) QApplication::desktop()->physicalDpiX();
	}
	return dpi;
}

NS_CC_END
