/****************************************************************************
** Copyright (c) 2006 - 2011, the LibQxt project.
** Copyright (c) Igor Malinovskiy
*****************************************************************************/
#pragma once

#include <QObject>
#include <QList>
#include <libssh2.h>

class QSshKey{
 public:
    QByteArray hash;
    QByteArray key;
    int  type;
};


class QSshTcpSocket;
class QSshClientPrivate;
class QSshClient : public QObject{
    Q_OBJECT
public:
    enum AuthenticationMethod{
        PasswordAuthentication,
        PublicKeyAuthentication
    };
    enum KnownHostsFormat{
        OpenSslFormat
    };
    enum Error{
        AuthenticationError,
        HostKeyUnknownError,
        HostKeyInvalidError,
        HostKeyMismatchError,
        ConnectionRefusedError,
        UnexpectedShutdownError,
        HostNotFoundError,
        SocketError,
        UnknownError
    };

    QSshClient(QObject * parent=0);
    ~QSshClient();

    void connectToHost(const QString & username,const QString & hostname,
                       int port = 22, bool useSystemClient = false);
    void disconnectFromHost ();
    void resetState();
    void setPassphrase(const QString & pass);
    void setKeyFiles(const QString & publicKey,const QString & privateKey);

    bool loadKnownHosts(const QString & file,KnownHostsFormat c = OpenSslFormat);
    bool saveKnownHosts(const QString & file,KnownHostsFormat c = OpenSslFormat) const;
    bool addKnownHost(const QString & hostname,const QSshKey & key);

    QSshKey hostKey() const;
    QString hostName() const;

    QSshTcpSocket * openTcpSocket(const QString & hostName,quint16 port);

    QString getLastError() const;
signals:
    void connected();
    void disconnected();
    void error (QSshClient::Error error);
    void authenticationRequired(QList<QSshClient::AuthenticationMethod> availableMethods);
private:
    QSshClientPrivate * d;
    friend class QSshClientPrivate;
    friend class QSshChannelPrivate;
};

inline QString getSshErrorString(QSshClient::Error error)
{
    switch (error) {
        case QSshClient::AuthenticationError: return "Authentication Error";
        case QSshClient::HostKeyUnknownError: return "Host Key Unknown Error";
        case QSshClient::HostKeyInvalidError: return "HostKey Invalid";
        case QSshClient::HostKeyMismatchError: return "HostKey Mismatch";
        case QSshClient::ConnectionRefusedError: return "Connection Refused";
        case QSshClient::UnexpectedShutdownError: return "Unexpected Shutdown";
        case QSshClient::HostNotFoundError: return "Host Not Found";
        case QSshClient::SocketError: return "Socket Error";
        default:
        case QSshClient::UnknownError: return "Unknown Error";
    }
}
