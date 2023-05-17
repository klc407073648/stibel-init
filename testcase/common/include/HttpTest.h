#ifndef HttpTest_H_
#define HttpTest_H_

#include <Poco/Types.h>
#include <string>

const std::string BACKEND_IP = "81.68.132.31";
const int BACKEND_PORT = 8082;

class HttpTest
{
public:
	HttpTest(const std::string &host, Poco::UInt16 port, const std::string &method, const std::string &uri,
			 const std::string &version, const std::string &contentType, 
			 const std::string &reqJsonFile, const std::string &respJsonFile);
	~HttpTest();

public:
	std::string readStringFromJson(const std::string &file);
	std::string readArrayStringFromJson(const std::string &file);
	std::string sendRequest();
	std::string sendPostRequest();
	std::string sendGetRequest();

	const std::string &getReqJsonFile() const
	{
		return _reqJsonFile;
	}
	const std::string &getRespJsonFile() const
	{
		return _respJsonFile;
	}

private:
	// HTTPClientSession
	std::string _host;
	Poco::UInt16 _port;

	// HTTPRequest
	std::string _method;
	std::string _uri;
	std::string _version;
	std::string _contentType;

	// json
	std::string _reqJsonFile;
	std::string _respJsonFile;
};

#endif /* HttpTest_H_ */
