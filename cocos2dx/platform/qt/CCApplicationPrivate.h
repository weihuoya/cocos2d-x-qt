#ifndef CCAPPLICATION_PRIVATE_QT_H_
#define CCAPPLICATION_PRIVATE_QT_H_

#include <QObject>
#include <QTimer>

NS_CC_BEGIN

class CCApplication;

class CCApplicationPrivate : public QObject
{
    Q_OBJECT
    friend class CCApplication;
    
public:
    CCApplicationPrivate(QObject *parent=0);
    virtual ~CCApplicationPrivate();
    void setInterval(double interval);
    void start();

protected Q_SLOTS:
    void update();
        
private:
    CCApplication *m_ptr;
    QTimer* m_timer;
    long m_interval;
};

NS_CC_END

#endif /* CCAPPLICATION_PRIVATE_QT_H_ */
