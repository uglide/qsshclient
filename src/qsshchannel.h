/****************************************************************************
** Copyright (c) 2006 - 2011, the LibQxt project.
** Copyright (c) Igor Malinovskiy
*****************************************************************************/
#pragma once

#include <QIODevice>

class QSshClient;
class QxtSshChannelPrivate;
class QxtSshChannel  : public QIODevice {
    Q_OBJECT
public:
    virtual ~QxtSshChannel();

    void close();
protected:
    QxtSshChannel(QSshClient*);
    virtual qint64 readData(char*, qint64);
    virtual qint64 writeData(const char*, qint64);
    virtual bool isSequential () const;

    QxtSshChannelPrivate * d;
    friend class QxtSshChannelPrivate;
    friend class QxtSshClientPrivate;
signals:
    void connected();
};
