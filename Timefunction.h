#ifndef TIMEFUNCTION_H
#define TIMEFUNCTION_H

#include <QObject>
#include <QDateTime>
#include <QTime>
#include <QDate>

class Timefunction: public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE int getCurrentDateTime(){
        QDateTime now = QDateTime::currentDateTime();
        return now.time().msec();
    }
};

#endif // TIMEFUNCTION_H
