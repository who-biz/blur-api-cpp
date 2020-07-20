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

#include <string>
#include <stdexcept>
#include <cmath>
#include <iostream>

#include <jsonrpccpp/client.h>
#include <jsonrpccpp/client/connectors/httpclient.h>


BlurAPI::BlurAPI(const std::string& user, const std::string& password, const std::string& host, int port, int httpTimeout)
: httpClient(new jsonrpc::HttpClient("http://" + host + ":" + std::to_string(port) + "/json_rpc")),
  client(new jsonrpc::Client(*httpClient, jsonrpc::JSONRPC_CLIENT_V2))
{
    httpClient->SetTimeout(httpTimeout);
}

BlurAPI::~BlurAPI()
{
    delete client;
    delete httpClient;
}

Json::Value BlurAPI::getblockchaininfo()
{
    Json::Value result;
    Json::Value params;
    std::cout << "before sendcommand getblockchaininfo ------" << std::endl;

    try {
      result = sendcommand("getblockchaininfo", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }

    return result;
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
