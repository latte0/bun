#ifndef IPGET_H
#define IPGET_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#include <QString>
#include <QObject>

#include "FileIO.h"


class Ipget:public QObject{
    Q_OBJECT
public:
    Q_INVOKABLE QString getIp(){
        int fd;
        struct ifreq ifr;
        fd = socket(AF_INET,SOCK_DGRAM,0);
        ifr.ifr_addr.sa_family =AF_INET;
        strncpy(ifr.ifr_name,"wlan0",IFNAMSIZ-1);
        ioctl(fd,SIOCGIFDSTADDR,&ifr);
        close(fd);

        QString ip(inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

        return ip;


    }
};

#endif // IPGET_H
