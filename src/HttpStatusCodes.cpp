#include "HttpStatusCodes.h"

QHash<int, QString> HttpStatusCodes::m_codes;

QHash<int, QString> HttpStatusCodes::codes()
{
	if (m_codes.isEmpty())
	{
		m_codes.insert(100, "Continue");
		m_codes.insert(101, "Switching Protocols");
		m_codes.insert(102, "Processing");             // RFC 2518) obsoleted by RFC 4918
		m_codes.insert(200, "OK");
		m_codes.insert(201, "Created");
		m_codes.insert(202, "Accepted");
		m_codes.insert(203, "Non-Authoritative Information");
		m_codes.insert(204, "No Content");
		m_codes.insert(205, "Reset Content");
		m_codes.insert(206, "Partial Content");
		m_codes.insert(207, "Multi-Status");          // RFC 4918
		m_codes.insert(300, "Multiple Choices");
		m_codes.insert(301, "Moved Permanently");
		m_codes.insert(302, "Moved Temporarily");
		m_codes.insert(303, "See Other");
		m_codes.insert(304, "Not Modified");
		m_codes.insert(305, "Use Proxy");
		m_codes.insert(307, "Temporary Redirect");
		m_codes.insert(400, "Bad Request");
		m_codes.insert(401, "Unauthorized");
		m_codes.insert(402, "Payment Required");
		m_codes.insert(403, "Forbidden");
		m_codes.insert(404, "Not Found");
		m_codes.insert(405, "Method Not Allowed");
		m_codes.insert(406, "Not Acceptable");
		m_codes.insert(407, "Proxy Authentication Required");
		m_codes.insert(408, "Request Time-out");
		m_codes.insert(409, "Conflict");
		m_codes.insert(410, "Gone");
		m_codes.insert(411, "Length Required");
		m_codes.insert(412, "Precondition Failed");
		m_codes.insert(413, "Request Entity Too Large");
		m_codes.insert(414, "Request-URI Too Large");
		m_codes.insert(415, "Unsupported Media Type");
		m_codes.insert(416, "Requested Range Not Satisfiable");
		m_codes.insert(417, "Expectation Failed");
		m_codes.insert(418, "I\"m a teapot");            // RFC 2324
		m_codes.insert(422, "Unprocessable Entity");    // RFC 4918
		m_codes.insert(423, "Locked");                 // RFC 4918
		m_codes.insert(424, "Failed Dependency");        // RFC 4918
		m_codes.insert(425, "Unordered Collection");      // RFC 4918
		m_codes.insert(426, "Upgrade Required");       // RFC 2817
		m_codes.insert(500, "Internal Server Error");
		m_codes.insert(501, "Not Implemented");
		m_codes.insert(502, "Bad Gateway");
		m_codes.insert(503, "Service Unavailable");
		m_codes.insert(504, "Gateway Time-out");
		m_codes.insert(505, "HTTP Version not supported");
		m_codes.insert(506, "Variant Also Negotiates");  // RFC 2295
		m_codes.insert(507, "Insufficient Storage");    // RFC 4918
		m_codes.insert(509, "Bandwidth Limit Exceeded");
		m_codes.insert(510, "Not Extended");           // RFC 2774
	}
	return m_codes;
}
