/**
 * @file    bitcoinapi.h
 * @author  Krzysztof Okupski
 * @date    29.10.2014
 * @version 1.0
 *
 * Declaration of a C++ wrapper for communication with
 * a running instance of Bitcoin daemon over JSON-RPC.
 ******************************************************
 * @file    blur_api.h
 * @author  Blur Network <contact@blur.cash>
 * @date    03.07.2020
 * @license See attached LICENSE.txt
 *
 * Reimplementation of bitcoin-api-cpp, for communication
 * with a running instance of the Blur Network daemon
 * over JSON-RPC.
 *****************************************************/
#include <string>
#include <list>
#include "exception.h"

namespace jsonrpc { class HttpClient; class Client; }

std::string username;
std::string password;
std::string blur_host;
int blur_port;
int api_port;

class BlurAPI
{

private:
    jsonrpc::HttpClient * httpClient;
    jsonrpc::Client * client;

public:
    BlurAPI(const std::string& user, const std::string& password, const std::string& host, int port, int httpTimeout = 5000);
    BlurAPI* m_blur_api;
    Json::Value getblockchaininfo();
    Json::Value getblock(std::string const& blockhash);
    Json::Value validateaddress(std::string const& address);
    Json::Value getbestblockhash();
    Json::Value get_notarization_data();
    Json::Value getblockhash(int const& height);
    Json::Value calc_MoM(std::string const& height, std::string const& MoMdepth);
    Json::Value sendrawtransaction(std::string const& signedhex);
    Json::Value signrawtransaction(std::string const& hexstring, Json::Value const& prevtxs);
    Json::Value listunspent(int const& minconf, int const& maxconf, std::list<std::string> const& address);
    BlurAPI();
    ~BlurAPI();
    Json::Value sendcommand(std::string const& command, Json::Value const& params);
};
