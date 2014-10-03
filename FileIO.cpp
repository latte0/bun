#include "FileIO.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

FileIO::FileIO(QObject *parent) :
    QObject(parent)
{
    mNetwork = false;
}

int FileIO::randint(int low, int high){
    return qrand() % ((high + 1) - low) + low;
}

int FileIO::readline(){
        if (mSource.isEmpty()){
            emit error("source is empty");
            return -1;
        }
        int i = 1;
        QFile file(mSource);
        if ( file.open(QIODevice::ReadOnly) ) {
            QString line;
            QTextStream t( &file );
                do{
                    line = t.readLine();
                    i++;
                } while(!line.isNull());
            file.close();
        } else {
            emit error("Unable to open the file");
            return -1;
        }
        return i-2;
}



QString FileIO::read(int const &line_num)
{
         if (mSource.isEmpty()){
            emit error("source is empty");
            return QString();
        }
        qDebug() << line_num;
        int i = 1;
        QFile file(mSource);
        QString fileContent;
        if ( file.open(QIODevice::ReadOnly) ) {
            QString line;
            QTextStream t( &file );
            if(line_num == 0){
                do {
                    line = t.readLine();
                    fileContent += line;
                 } while (!line.isNull());
            }else{
                do{
                    line = t.readLine();
                    if(line_num == i) fileContent += line;
                    i++;
                    qDebug()<< fileContent;

                } while(!line.isNull());
            }
            file.close();
        } else {
            emit error("Unable to open the file");
            return QString();
        }
        //qDebug() << fileContent;
        return fileContent;

}

QString FileIO::word_find(const QString& data){
    int data_length = data.length();

    QFile file(mSource);
    QString fileContent;
    QList<QString> list;
    int count=0;
    bool finish=false;

    if( file.open(QIODevice::ReadOnly)){
        QString line;
        QTextStream t(&file);
        do{
           line = t.readLine();
           if(line.at(0) == data.at(0)){
               list << line;
               count++;
               finish = true;
           }else{
               if(finish == true) break;
           }
        }while(!line.isNull());
    }

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    int randomValue = randint(0,count);

    fileContent = list.at(randomValue);



    return fileContent;
}

bool FileIO::write(const QString& data)
{
    if (mSource.isEmpty())
        return false;

    QFile file(mSource);
    if (!file.open(QFile::WriteOnly | QFile::Truncate))
        return false;

    QTextStream out(&file);
    out << data;

    file.close();

    return true;
}

bool FileIO::remove(){
    QFile file(mSource);
    if(!file.open(QFile::ReadWrite | QFile::Truncate))
    return false;

    file.remove();

    return true;
}
