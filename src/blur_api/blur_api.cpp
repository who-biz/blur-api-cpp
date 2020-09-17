/**
 * @file    bitcoinapi.cpp
 * @author  Krzysztof Okupski
 * @date    29.10.2014
 * @version 1.0
 *
 * Implementation of a C++ wrapper for communication with
 * a running instance of Bitcoin daemon over JSON-RPC.
 ************************************************************************
 * @file    blur_api.cpp
 * @author  Blur Network <contact@blur.cash>
 * @date    03.07.2020
 * @license See attached LICENSE.txt
 *
 * Reimplementation of bitcoin-api-cpp, for communication
 * with a running instance of the Blur Network daemon
 * over JSON-RPC.
 ***********************************************************************/

#include "blur_api.h"

#include <string>
#include <stdexcept>
#include <cmath>
#include <iostream>

#include <jsonrpccpp/client.h>
#include <jsonrpccpp/client/connectors/httpclient.h>

BlurAPI::BlurAPI(const std::string& user, const std::string& password,
                 const std::string& host, int port, int httpTimeout)
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
    Json::Value result, params;
//    std::cout << "before sendcommand getblockchaininfo ------" << std::endl;
    try {
      result = sendcommand("getblockchaininfo", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }
    return result;
}

Json::Value BlurAPI::get_notarization_data()
{
    Json::Value result, params;
    try {
      result = sendcommand("get_notarization_data", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }
    return result;
}

Json::Value BlurAPI::validateaddress(std::string const& address)
{
    Json::Value result, params;
    params.append(address);
    try {
      result = sendcommand("validateaddress", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }
    return result;
}

Json::Value BlurAPI::getbestblockhash()
{
    Json::Value result, params;
    try {
      result = sendcommand("getbestblockhash", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }
    return result;
}

Json::Value BlurAPI::getblockhash(int const& height)
{
    Json::Value result, params;
    params.append(height);
    try {
      result = sendcommand("getblockhash", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }
    return result;
}

Json::Value BlurAPI::calc_MoM(int const& height, int const& MoMdepth)
{
    Json::Value result, params;
    params.append(height);
    params.append(MoMdepth);
    try {
      result = sendcommand("calc_MoM", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }
    return result;
}

Json::Value BlurAPI::sendrawtransaction(std::string const& signedhex)
{
    Json::Value result, params;
    params.append(signedhex);
    try {
      result = sendcommand("sendrawtransaction", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }
    return result;
}

Json::Value BlurAPI::listunspent(int const& minconf, int const& maxconf, std::list<std::string> const& addresses)
{ /* listunspent will not yet work, more changes necessary */
    Json::Value result,params;
    params["minconf"] = minconf;
    params["maxconf"] = maxconf;
    for (const auto& each : addresses) {
      params["addresses"].append(each);
    }
    try {
      result = sendcommand("listunspent", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }
    return result;
}

BlurAPI::BlurAPI() {
    BlurAPI blur(username, password, blur_host, blur_port);
}

Json::Value BlurAPI::sendcommand(std::string const& command, Json::Value const& params)
{
    Json::Value result;
    try {
      result = client->CallMethod(command, params);
    } catch (jsonrpc::JsonRpcException& e) {
       BlurException error(e.GetCode(), e.GetMessage());
       throw error;
    }
    return result;
}
