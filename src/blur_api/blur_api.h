#include <string>
#include "exception.h"

namespace jsonrpc { class HttpClient; class Client; }

class BlurAPI
{

private:
    jsonrpc::HttpClient * httpClient;
    jsonrpc::Client * client;

public:
    /* === Constructor and Destructor === */
    BlurAPI(const std::string& user, const std::string& password, const std::string& host, int port, int httpTimeout = 500);
    BlurAPI* m_blur_api;
    Json::Value getblockchaininfo();
    Json::Value validateaddress(std::string const& address);
    Json::Value getbestblockhash();
    Json::Value get_notarization_data();
    Json::Value getblockhash(int const& height);
    Json::Value calc_MoM(int const& height, int const& MoMdepth);
    BlurAPI get_blur_api();
    BlurAPI();
    ~BlurAPI();
    Json::Value sendcommand(std::string const& command, Json::Value const& params);
};

BlurAPI blur_api_init();
