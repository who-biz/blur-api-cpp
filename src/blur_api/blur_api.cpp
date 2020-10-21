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
    try {
      result = sendcommand("btc_getblockchaininfo", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }
    return result;
}

Json::Value BlurAPI::getblock(std::string const& blockhash)
{
    Json::Value result, params;
    params["blockhash"] = blockhash;
    try {
      result = sendcommand("btc_getblock", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }
    return result;
}

Json::Value BlurAPI::get_notarization_data()
{
    Json::Value result, params;
    try {
      result = sendcommand("btc_get_notarization_data", params);
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
      result = sendcommand("btc_validateaddress", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }
    return result;
}

Json::Value BlurAPI::getbestblockhash()
{
    Json::Value result, params;
    try {
      result = sendcommand("btc_getbestblockhash", params);
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
      result = sendcommand("btc_getblockhash", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }
    return result;
}

Json::Value BlurAPI::calc_MoM(std::string const& height, std::string const& MoMdepth)
{
    Json::Value result, params;
    params.append(height);
    params.append(MoMdepth);
    try {
      result = sendcommand("btc_calc_MoM", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }
    return result;
}

Json::Value BlurAPI::sendrawtransaction(std::string const& signedhex)
{
    Json::Value result, params;
    params["hexstring"] = signedhex;
    try {
      result = sendcommand("btc_sendrawtransaction", params);
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
      result = sendcommand("btc_listunspent", params);
    } catch (BlurException& error) {
      std::cerr << error.getMessage() << std::endl;
    }
    return result;
}

Json::Value BlurAPI::signrawtransaction(std::string const& hexstring, Json::Value const& prevtxs)
{
    Json::Value result, params, item;
/*    params["hexstring"] = hexstring;
    for (const auto& each : prevtxs) {
      item["txid"] = each[0u].asString();
      item["vout"] = each[1u].asInt();
      item["scriptPubKey"] = each[2u].asString();
      item["redeemScript"] = each[3u].asString();
      item["amount"] = (each[4u].asFloat()*100000000);
      params["prevtxs"].append(item);
    }*/

    try {
      result = sendcommand("btc_signrawtransaction", params);
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
    printf("--  Called method: %s  --\n", command.c_str());
    return result;
}
