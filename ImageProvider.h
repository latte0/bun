#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>

#include <QAction>
#include <QLabel>
#include <QMenu>
#include <QScrollArea>
#include <QScrollBar>

#include <QString>
#include <QPainter>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QPlainTextEdit>
#include <QTextStream>

class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider();
    QImage createSubImage(QImage* image, QRect rect);

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

private:
    bool image_stright_checker(QImage find,int line,QString text);
    QLabel *imageLabel;
    QScrollArea *scrollArea;

    QString codelinestring;

    int hideline,hiderow,hidenum;
    int fontsize;
    bool atmark;
signals:

public slots:

};

#endif
