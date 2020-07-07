#include "blur_api.h"

#include <string>
#include <stdexcept>
#include <cmath>

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
    delete client;
    delete httpClient;
}

BlurAPI* BlurAPI::get_blur_api() {
  return m_blur_api;
}

Json::Value BlurAPI::sendcommand(std::string const& command, Json::Value const& params)
{
    Json::Value result;
    result = client->CallMethod(command, params);
    return result;
}