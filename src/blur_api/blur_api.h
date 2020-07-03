#include "types.h"

namespace jsonrpc { class HttpClient; class Client; }

class BlurAPI
{

private:
    jsonrpc::HttpClient * httpClient;
    jsonrpc::Client * client;

public:
    /* === Constructor and Destructor === */
    BlurAPI(const std::string& user, const std::string& password, const std::string& host, int port, int httpTimeout = 500);
    ~BlurAPI();
};