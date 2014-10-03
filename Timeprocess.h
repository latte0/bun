#ifndef TIMEPROCESS_H

#define TIMEPROCESS_H

#include <QObject>
#include <QTime>
#include <qglobal.h>

class Timeprocess :public QObject
{
        Q_OBJECT
 public:

        explicit Timeprocess(QObject *parent = 0);

        Q_INVOKABLE int read();
        Q_INVOKABLE void start();

private:
    QTime *    game_process_time;
};

#endif // TIMEPROCESS_H
