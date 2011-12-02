/*
 * Copyright 2011 Nikhil Marathe <nsm.nikhil@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE. 
 */

#include "qhttpserver.h"

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QVariant>
#include <QDebug>

#include "qhttpconnection.h"

QHash<int, QString> STATUS_CODES;

QHttpServer::QHttpServer(QObject *parent)
    : QObject(parent)
    , m_tcpServer(0)
{
}

QHttpServer::~QHttpServer()
{
	delete m_tcpServer;
}

void QHttpServer::newConnection()
{
    Q_ASSERT(m_tcpServer);
    while(m_tcpServer->hasPendingConnections()) {
        QHttpConnection *connection = new QHttpConnection(m_tcpServer->nextPendingConnection(), this);
        connect(connection, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
                this, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)));
    }
}

bool QHttpServer::listen(const QHostAddress &address, quint16 port)
{
	if( m_tcpServer )
	{
		delete m_tcpServer;
	}

    m_tcpServer = new QTcpServer;

    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
    return m_tcpServer->listen(address, port);
}

bool QHttpServer::listen(quint16 port)
{
    return listen(QHostAddress::Any, port);
}
