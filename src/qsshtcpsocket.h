/****************************************************************************
** Copyright (c) 2006 - 2011, the LibQ project.
** Copyright (c) Igor Malinovskiy
*****************************************************************************/
#pragma once
#include "qsshchannel.h"

class QSshTcpSocket : public QSshChannel {
    Q_OBJECT
 private:
    QSshTcpSocket(QSshClient*);
    friend class QSshClient;
};
