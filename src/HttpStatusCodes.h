#ifndef HTTP_STATUS_CODES
#define HTTP_STATUS_CODES

#include <QtCore/QString>
#include <QtCore/QHash>

/**
 * HttpStatusCodes
 *
 * Small wrapper around a hash mapping status codes to
 * their description
 *
 */
class HttpStatusCodes
{

	public:
		static QHash<int, QString> codes();

	private:
		static QHash<int, QString> m_codes;
};

#endif
