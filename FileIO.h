#ifndef FILEIO_H
#define FILEIO_H

#include <QObject>
#include <QString>
#include <QList>
#include <QTime>
#include <qglobal.h>


class FileIO: public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(bool network READ network WRITE setNetwork NOTIFY networkChanged)

    explicit FileIO(QObject *parent = 0);

    Q_INVOKABLE QString read(const int &line_num);
    Q_INVOKABLE bool write(const QString& data);
    Q_INVOKABLE bool remove();

    Q_INVOKABLE int readline();

    Q_INVOKABLE QString word_find(const QString& data );

    QString source() { return mSource; };
    bool network() { return mNetwork;};

private:
    int randint(int low, int high);

public slots:
    void setSource(const QString& source){ mSource = source; };
    void setNetwork(const bool &source){ mNetwork = source; };

signals:
    void sourceChanged(const QString& source);
    void networkChanged(const bool& network);
    void error(const QString& msg);

private:
    QString mSource;
    bool mNetwork;

};

#endif // FILEIO_H
