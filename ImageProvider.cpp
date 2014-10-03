#include "ImageProvider.h"
#include <stdio.h>
#include <string.h>
#include <QDir>
#include <QRect>
#include <QDebug>
#include <QRgb>
#include <QPoint>
#include <QColor>
#include <QBrush>
#include <QRadialGradient>


ImageProvider::ImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}


QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QString hideline_str;
    fontsize = 30;
    int blank = 20;
     QImage image(500,500, QImage::Format_ARGB32_Premultiplied);
    QImage lineimage(700,100,QImage::Format_RGB888);

    QPainter imagep(&lineimage);

    imagep.setPen(QPen(Qt::black));
    imagep.setFont(QFont("Arial",fontsize));

    int linecount=0;

    QString fileName = "/home/sharemen-note/bunkasai/test.cpp";
    qDebug() << fileName;

 //   if(!fileName.isEmpty()){
    //QPixmap pix(800,800);
        //QImage image(this->size(), QImage::Format_ARG32_Premultiplied);
        fprintf(stderr,"checked");
    QPainter codepainter(&image);
    //codeimagePainter.drawImage(100,100,QImage("white.png"));
    //codeimagePainter.setCompositionMode(QPainter::CompositionMode_Xor);
    QRect rect(0,0,800,800);
    codepainter.fillRect(rect,Qt::white);
    imagep.fillRect(rect,Qt::white);
    codepainter.setPen(Qt::black);
    codepainter.setFont(QFont("Arial",fontsize));


    QFile filevar(fileName);
    fprintf(stderr,"test");
    if(!filevar.open(QIODevice::ReadOnly | QIODevice::Text)){}
    QTextStream in(&filevar);
    while(!in.atEnd()){
        linecount++;
        QString line = in.readLine();
        qDebug() << line;
        if(line.contains("@",Qt::CaseInsensitive)){
            hideline = linecount;
            atmark = true;
            hiderow= line.indexOf("@");
            hidenum = line.indexOf("@",hiderow+1);
            line.remove(hiderow,1);
            line.remove(hidenum-1,1);
            hideline_str = line;
            imagep.drawText(0, (fontsize+10)/*Qt::AlignCenter*/, hideline_str);
            hidenum= hidenum;
            qDebug() << hiderow*fontsize << hideline;
        }
        codepainter.drawText(0,(fontsize+10) * linecount, line );
    }









    int count=0;
    QString hideline_former;
    hideline_former = hideline_str.mid(0,hiderow);
    if(hideline_former.contains("\"",Qt::CaseInsensitive)){
        for(int i=0;i<hideline_former.length();i++){
            if(hideline_former.at(i) == 0x22){
                count++;
            }
        }
    }

    int count_inside=0;
    hideline_former = hideline_str.mid(hiderow,hidenum-hiderow-1);
    if(hideline_former.contains("\"",Qt::CaseInsensitive)){
        for(int i=0;i<hideline_former.length();i++){
            if(hideline_former.at(i) == 0x22){
                count_inside++;
            }
        }
    }











    int count_blank=0;
    int count_blank_first = 0;
    int count_blank_first_mark =0;
    int k;
    if(hideline_str.contains(Qt::Key_Space,Qt::CaseInsensitive)){
        for(int i=0;i<hideline_str.length();i++){
            if(hideline_str.at(i) == 0x20){
                count_blank++;
            }else{
                k=i;
                break;
            }
        }
    }

    bool atfirstmark = false;
    if(count_blank == hiderow){
        atfirstmark =true;
        qDebug() << "atfirsttime";
    //    if(count_blank ==0) count_blank_first--;
    }

    if(hideline_str.contains(Qt::Key_Space,Qt::CaseInsensitive)){
        for(int i=k+1;i<hideline_str.length();i++){
            if(hideline_str.at(i) == 0x20 && atfirstmark == false){
                count_blank_first++;
            }else if(i== hiderow|| atfirstmark == true){
                k=i;
                break;
            }
        }
    }

    if(hideline_str.contains(Qt::Key_Space,Qt::CaseInsensitive)){
        for(int i=k+1;i<hideline_str.length();i++){
            if(hideline_str.at(i) == 0x20){
                count_blank_first_mark++;
            }else if(i == hidenum -1){
                k=i;
                break;
            }
        }
    }









    qDebug() << count << count_inside;
    qDebug() << "blankcount" << count_blank;
    qDebug() << "hiderow" << hiderow;
    qDebug() << "hidenum" << hidenum;
    qDebug() << "countblankfirst" << count_blank_first;
    qDebug() << "countblankfirstmark" << count_blank_first_mark;

    bool black = false;
    int characount =0,beginpos=0,finishpos=0;
    for(int i=0;i<700;i++){
        if(image_stright_checker(lineimage,i,hideline_str)){
    //        qDebug()<< "helo";
              if(black == false){
                    black = true;
                    if(atfirstmark == true){
                        qDebug() << "atfirstmark";
                        beginpos = i;
                                break;
                    }
             }
        }else{
            if(black == true){
                black = false;

                characount++;
            }
                if(characount + count /*+ count_blank_first*/ >= hiderow - count_blank && atfirstmark == false){
                        beginpos = i;
                        i=700;
                        qDebug() << "break;";
                        break;
                }
        }
    }

    qDebug() <<"kakunin"<< hiderow << blank;
    qDebug() <<"kakunin" << characount << count;

    black = false;
    characount = 0;

    for(int i=0;i<700;i++){
        if(image_stright_checker(lineimage,i,hideline_str)){
    //        qDebug()<< "helo";
              if(black == false){
                    black = true;
             }
        }else{
            if(black == true){
                black = false;
                characount++;
            }
            if(characount - count_inside -count +count_blank_first + count_blank_first_mark>= hidenum - count_blank-1){
                    finishpos = i;
                    i=700;
                    qDebug() << "break;";
                    break;
            }
        }
    }








    QRect hiderect(beginpos,(fontsize+10) * (hideline-1),finishpos-beginpos,fontsize+10);

    codepainter.fillRect(hiderect,Qt::black);

    qDebug() <<"this is color test" << beginpos << finishpos;

    QRect hiderect2(beginpos,fontsize,finishpos-beginpos,fontsize+10);

    imagep.fillRect(hiderect2,Qt::black);

//    imagep.drawText(lineimage.rect(), Qt::AlignCenter, hideline_former);  //crashes program

    qDebug() << hiderow << hidenum;

    qDebug() << "blank" << count_blank << "count" << count;

    return QPixmap::fromImage(image);

}

bool ImageProvider::image_stright_checker(QImage find,int line, QString text){
    QImage lineimage(700,100,QImage::Format_RGB888);
    int blank = 20;

    QPainter imagep(&lineimage);
   // qDebug() << text;
        QRect rect(0,0,800,800);
    imagep.setPen(QPen(Qt::black));
    imagep.setFont(QFont("Arial",fontsize));
    imagep.fillRect(rect,Qt::white);
    imagep.drawText(0,fontsize+10, text);
    QColor findcolor;
    //qDebug() << "line" << line;
    for(int j=1;j<100;j++){
        findcolor= lineimage.pixel(line,j);
       // qDebug() << findcolor.blue();
        if(findcolor.blue() < 100){
         //   qDebug() << "TRUeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee";
            return true;
        }
    }

    return false;
}

QImage ImageProvider::createSubImage(QImage* image, QRect rect){
    size_t offset = rect.x() * image->depth() /8 + rect.y() * image->bytesPerLine();
    return QImage(image->bits() + offset, rect.width(),rect.height(), image->bytesPerLine(), image->format());
}
