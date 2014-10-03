
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "Timeprocess.h"

Timeprocess::Timeprocess(QObject *parent)
    :QObject(parent)
{
}

void Timeprocess::start(){
    game_process_time = new QTime();
    game_process_time->start();
}

int Timeprocess::read(){
    return game_process_time->elapsed();
}
