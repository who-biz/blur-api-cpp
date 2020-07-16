#include "blur_api.h"

#include <string>
#include <stdexcept>
#include <cmath>
#include <iostream>

#include <jsonrpccpp/client.h>
#include <jsonrpccpp/client/connectors/httpclient.h>


BlurAPI::BlurAPI(const std::string& user, const std::string& password, const std::string& host, int port, int httpTimeout)
: httpClient(new jsonrpc::HttpClient("http://" + user + ":" + password + "@" + host + ":" + std::to_string(port))),
  client(new jsonrpc::Client(*httpClient, jsonrpc::JSONRPC_CLIENT_V2)), m_blur_api(new BlurAPI(user,password,host,port,httpTimeout))
{
    httpClient->SetTimeout(httpTimeout);
}

BlurAPI::~BlurAPI()
{
    delete m_blur_api;
    delete client;
    delete httpClient;
}

getinfo_t BlurAPI::getblockchaininfo()
{
    Json::Value result;
    Json::Value params;
    std::cout << "before sendcommand getblockchaininfo ------" << std::endl;
    result = sendcommand("getblockchaininfo", params);
    getinfo_t info;
    info.version = result["version"].asString();
    info.status = result["status"].asString();
    std::cout << "Version: " << info.version << " ||  Status: " << info.status << info.status << std::endl;
    return info;
}


BlurAPI blur_api_init() {
  std::string username = "user";
  std::string password = "password";
  std::string host = "127.0.0.1";
  int port = 21111;

  BlurAPI blur(username, password, host, port);
  return blur;
}

BlurAPI BlurAPI::get_blur_api() {
  return *m_blur_api;
}

Json::Value BlurAPI::sendcommand(std::string const& command, Json::Value const& params)
{
    Json::Value result;
    result = client->CallMethod(command, params);
    return result;
}
