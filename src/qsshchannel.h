/****************************************************************************
** Copyright (c) 2006 - 2011, the LibQxt project.
** Copyright (c) Igor Malinovskiy
*****************************************************************************/
#pragma once

#include <QIODevice>

class QSshClient;
class QSshChannelPrivate;
class QSshChannel  : public QIODevice {
    Q_OBJECT
public:
    virtual ~QSshChannel();

    void close();
protected:
    QSshChannel(QSshClient*);
    virtual qint64 readData(char*, qint64);
    virtual qint64 writeData(const char*, qint64);
    virtual bool isSequential () const;

    QSshChannelPrivate * d;
    friend class QSshChannelPrivate;
    friend class QSshClientPrivate;
signals:
    void connected();
};
