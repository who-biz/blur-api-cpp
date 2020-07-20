/**
 * @file    bitcoinapi.cpp
 * @author  Krzysztof Okupski
 * @date    29.10.2014
 * @version 1.0
 *
 * Implementation of a C++ wrapper for communication with
 * a running instance of Bitcoin daemon over JSON-RPC.
 */

#include "blur_api.h"
#include "exception.h"

#include <string>
#include <stdexcept>
#include <cmath>
#include <iostream>

#include <jsonrpccpp/client.h>
#include <jsonrpccpp/client/connectors/httpclient.h>


BlurAPI::BlurAPI(const std::string& user, const std::string& password, const std::string& host, int port, int httpTimeout)
: httpClient(new jsonrpc::HttpClient("http://" + host + ":" + IntegerToString(port) + "/json_rpc")),
  client(new jsonrpc::Client(*httpClient, jsonrpc::JSONRPC_CLIENT_V2))
{
    httpClient->SetTimeout(httpTimeout);
}

BlurAPI::~BlurAPI()
{
    delete client;
    delete httpClient;
}

std::string BlurAPI::IntegerToString(int num)
{
   std::ostringstream ss;
   ss << num;
   return ss.str();
}

getinfo_t BlurAPI::getblockchaininfo()
{
    Json::Value result;
    Json::Value params;
    std::cout << "before sendcommand getblockchaininfo ------" << std::endl;
    try {
      result = sendcommand("getblockchaininfo", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }
    getinfo_t info;
    info.version = result["version"].asString();
    info.status = result["status"].asString();
    std::cout << "Version: " << info.version << " ||  Status: " << info.status << info.status << std::endl;
    return info;
}


BlurAPI::BlurAPI() {
  std::string username = "user";
  std::string password = "password";
  std::string host = "127.0.0.1";
  int port = 21111;

  BlurAPI blur(username, password, host, port);
}

BlurAPI BlurAPI::get_blur_api() {
  return *m_blur_api;
}

Json::Value BlurAPI::sendcommand(std::string const& command, Json::Value const& params)
{
    BlurAPI blur("user","password","127.0.0.1",21111);
    Json::Value result;
    try {
      result = client->CallMethod(command, params);
    } catch (jsonrpc::JsonRpcException& e) {
       BlurException error(e.GetCode(), e.GetMessage());
       throw error;
    }
    return result;
}
