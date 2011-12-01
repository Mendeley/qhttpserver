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

#include "qhttpresponse.h"

#include "qhttpserver.h"
#include "qhttpconnection.h"
#include "HttpStatusCodes.h"

QHttpResponse::QHttpResponse(QHttpConnection *connection)
    : QObject(connection)
    , m_connection(connection)
    , m_headerWritten(false)
    , m_sentConnectionHeader(false)
    , m_sentContentLengthHeader(false)
    , m_sentTransferEncodingHeader(false)
    , m_keepAlive(true)
    , m_last(false)
    , m_useChunkedEncoding(false)
	, m_isDone(false)
{
}

QHttpResponse::~QHttpResponse()
{
}

void QHttpResponse::setHeader(const QString &field, const QString &value)
{
	Q_ASSERT(! m_isDone);
	Q_ASSERT(m_connection);

    m_headers[field] = value;
}

void QHttpResponse::writeHeaders()
{
	Q_ASSERT(! m_isDone);
	Q_ASSERT(m_connection);

	QHashIterator<QString, QString> headerIterator(m_headers);

	while( headerIterator.hasNext() )
    {
		headerIterator.next();
		const QString& name = headerIterator.key();
		const QString& value = headerIterator.value();

        if( name.compare("connection", Qt::CaseInsensitive) == 0 ) 
        {
            m_sentConnectionHeader = true;
            if( value == "close" )
                m_last = true;
            else
                m_keepAlive = true;
        }
        else if( name.compare("transfer-encoding", Qt::CaseInsensitive) == 0 )
        {
            m_sentTransferEncodingHeader = true;
            if( value == "chunked" )
                m_useChunkedEncoding = true;
        }
        else if( name.compare("content-length", Qt::CaseInsensitive) == 0 )
        {
            m_sentContentLengthHeader = true;
        }
        //TODO: Expect case

        m_connection->writeHeader(name.toAscii(), value.toAscii());
    }

    if( !m_sentConnectionHeader )
    {
        if( m_keepAlive &&
                ( m_sentContentLengthHeader || m_useChunkedEncoding ) )
        {
            m_connection->writeHeader("Connection", "keep-alive");
        }
        else
        {
            m_last = true;
            m_connection->writeHeader("Connection", "close");
       } 
    }

    if( !m_sentContentLengthHeader && !m_sentTransferEncodingHeader )
    {
        if( m_useChunkedEncoding )
            m_connection->writeHeader("Transfer-Encoding", "chunked");
        else
            m_last = true;
    }
}

bool QHttpResponse::writeHead(int status)
{
	Q_ASSERT(! m_isDone);
	Q_ASSERT(m_connection);

    if( m_headerWritten ) 
	{
		return false;
	}

	const QHash<int, QString>& codes = HttpStatusCodes::codes();

	if( ! codes.contains(status) )
	{
		qDebug() << "Invalid status code"<<status;
		return false;
	}
    m_connection->write(QString("HTTP/1.1 %1 %2\r\n").arg(status).arg(codes.value(status)).toAscii());
    
    writeHeaders();

    m_connection->write("\r\n");
    m_headerWritten = true;
	return true;
}

bool QHttpResponse::write(const QByteArray &data)
{
	Q_ASSERT(! m_isDone);
	Q_ASSERT(m_connection);


    if( !m_headerWritten )
    {
        return false;
    }

	return m_connection->write(data);
}

bool QHttpResponse::write(const QString &data)
{
	Q_ASSERT(! m_isDone);
	Q_ASSERT(m_connection);


    return m_connection->write(data.toUtf8());
}

void QHttpResponse::end(const QString &data)
{
	Q_ASSERT(! m_isDone);
	Q_ASSERT(m_connection);

    write(data);

	m_isDone = true;
    emit done();

    deleteLater();
    // TODO: end connection and delete ourselves
}
