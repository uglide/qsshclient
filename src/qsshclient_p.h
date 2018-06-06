/****************************************************************************
** Copyright (c) 2006 - 2011, the LibQxt project.
** Copyright (c) Igor Malinovskiy
*****************************************************************************/
#pragma once

#include "qsshclient.h"
#include "qsshchannel.h"
#include <QTcpSocket>
#include <QTimer>
#include <QSharedPointer>

extern "C"{
#include <libssh2.h>
#include <errno.h>
}

static_assert((LIBSSH2_VERSION_MAJOR == 1) && (LIBSSH2_VERSION_MINOR >= 8), "QSSHClient requires libss2 >= 1.8.0");


class QSshClientPrivate : public QTcpSocket{
    Q_OBJECT
public:
    QSshClientPrivate();
    virtual ~QSshClientPrivate();
    void d_tearDown();
    void d_reset();
    void d_getLastError();

    QSshClient * p;
    LIBSSH2_SESSION * d_session;
    LIBSSH2_KNOWNHOSTS * d_knownHosts;
    LIBSSH2_AGENT * d_agent;
    int d_state;
    QString d_hostName;
    int d_port;
    QSshKey  d_hostKey;
    QString d_userName;
    QString d_passphrase;
    QString d_privateKey;
    QString d_publicKey;
    QString d_errorMessage;
    int d_errorCode;
    QSshClient::Error d_delaydError;
    QList<QSshClient::AuthenticationMethod> d_availableMethods;
    QList<QSshClient::AuthenticationMethod> d_failedMethods;
    QSshClient::AuthenticationMethod d_currentAuthTry;
    QSharedPointer<QTimer> d_keepAliveTimer;
    int d_sleepInterval;
    bool d_useSystemClient;

    QList<QSshChannel*> d_channels;
public slots:
    void d_readyRead();
    void d_connected();
    void d_disconnected();
    void d_channelDestroyed();
    void d_delaydErrorEmit();

private:
    int authWithSystemClient();
};
