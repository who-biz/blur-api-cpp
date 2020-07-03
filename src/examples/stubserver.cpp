/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    stubserver.cpp
 * @date    02.05.2013
 * @author  Peter Spiess-Knafl <dev@spiessknafl.at>
 * @license See attached LICENSE.txt
 ************************************************************************/
#include <iostream>

#include "gen/abstractstubserver.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <stdio.h>

using namespace jsonrpc;
using namespace std;

class MyStubServer : public AbstractStubServer {
public:
  MyStubServer(AbstractServerConnector &connector, serverVersion_t type);

  virtual void notifyServer();
  virtual std::string sayHello(const std::string &name);
  virtual Json::Value getblockchaininfo();
  virtual Json::Value validateaddress(std::string const& address);
  virtual Json::Value getbestblockhash();
  virtual Json::Value getblockhash(int height);
  virtual Json::Value calc_MoM(int height, int MoMdepth);
  virtual int addNumbers(int param1, int param2);
  virtual double addNumbers2(double param1, double param2);
  virtual Json::Value calculate(const Json::Value& args);
  virtual bool isEqual(const std::string &str1, const std::string &str2);
  virtual Json::Value buildObject(const std::string &name, int age);
  virtual std::string methodWithoutParameters();
};

MyStubServer::MyStubServer(AbstractServerConnector &connector,
                           serverVersion_t type)
    : AbstractStubServer(connector, type) {}

void MyStubServer::notifyServer() { cout << "Server got notified" << endl; }

/*Json::Value sendcommand(const std::string& command, const Json::Value& params)
{
};*/


string MyStubServer::sayHello(const string &name) {
  if (name == "")
    throw JsonRpcException(-32100, "Name was empty");
  return "Hello " + name;
}

Json::Value MyStubServer::getblockchaininfo() {
  Json::Value result;
  result["status"] = "OK";
  result["height"] = 2000;
  result["target_height"] = 2001;
  result["difficulty"] = 100000000;
  result["target"] = 100000000;
  result["tx_count"] = 1234;
  result["notarization_count"] = 3;
  result["notarizedhash"] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  result["notarizedtxid"] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  result["notarized"] = 1800;
  result["prevMoMheight"] = 0;
  result["notarized_MoMdepth"] = 0;
  result["notarized_MoM"] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  result["tx_pool_size"] = 3;
  result["alt_blocks_count"] = 0;
  result["outgoing_connections_count"] = 8;
  result["incoming_connections_count"] = 8;
  result["rpc_connections_count"] = 1;
  result["white_peerlist_size"] = 8;
  result["grey_peerlist_size"] = 8;
  result["mainnet"] = true;
  result["testnet"] = false;
  result["stagenet"] = false;
  result["top_block_hash"] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  result["cumulative_difficulty"] = 10230502020;
  result["block_size_limit"] = 292000;
  result["block_size_median"] = 1000;
  result["start_time"] = 0;
  result["free_space"] = 0;
  result["offline"] = false;
  result["untrusted"] = false;
  result["bootstrap_daemon_address"] = "address";
  result["height_without_bootstrap"] = 2000;
  result["was_bootstrap_ever_used"] = false;
  result["version"] = "v0.1.9.9.4";

  return result;
}

Json::Value MyStubServer::validateaddress(std::string const& address) {
  Json::Value result;
  result["isvalid"] = true;
  result["address"] = "xxxxxxxxxx";
  result["scriptPubKey"] = "xxxxxxxxxx";
  result["segid"] = 1;
  result["ismine"] = true;
  result["iswatchonly"] = false;
  result["isscript"] = false;
  result["status"] = "OK";
  return result;
}

Json::Value MyStubServer::getbestblockhash() {
  Json::Value result;
  result["hex"] = "xxxxxxxxxxxxxxxxxxxxxx";
  result["status"] = "OK";
  return result;
}

Json::Value MyStubServer::getblockhash(int height) {
  Json::Value result;
  result["hex"] = "xxxxxxxxxxxxxxxxxxxxxx";
  result["status"] = "OK";
  return result;
}

Json::Value MyStubServer::calc_MoM(int height, int MoMdepth) {
  Json::Value result;
  result["coin"] = "BLUR";
  result["notarized_height"] = 1000;
  result["notarized_MoMdepth"] = 1;
  result["notarized_MoM"] = "xxxxxxxxxxxxxxxxx";
  result["status"] = "OK";
  return result;
}

int MyStubServer::addNumbers(int param1, int param2) { return param1 + param2; }


double MyStubServer::addNumbers2(double param1, double param2) {
  return param1 + param2;
}

bool MyStubServer::isEqual(const string &str1, const string &str2) {
  return str1 == str2;
}

Json::Value MyStubServer::calculate(const Json::Value& args) {
  Json::Value result;
  if((args.isMember("arg1") && args["arg1"].isInt()) &&
    (args.isMember("arg2") && args["arg2"].isInt()) &&
    (args.isMember("operator") && args["operator"].isString()))
  {
    int calculated = 0;

    switch(args["operator"].asString()[0])
    {
      case '+':
      {
        calculated = args["arg1"].asInt() + args["arg2"].asInt();
        break;
      }
      case '-':
      {
        calculated = args["arg1"].asInt() - args["arg2"].asInt();
        break;
      }
      case '*':
      {
        calculated = args["arg1"].asInt() * args["arg2"].asInt();
        break;
      }
      case '/':
      {
        if(args["arg2"].asInt() != 0)
        {
          calculated = args["arg1"].asInt() / args["arg2"].asInt();
        }
        break;
      }
      default:
        break;
    }
  
    result.append(calculated);
  }

  return result;
}

Json::Value MyStubServer::buildObject(const string &name, int age) {
  Json::Value result;
  result["name"] = name;
  result["year"] = age;
  return result;
}

string MyStubServer::methodWithoutParameters() { return "Test"; }

int main() {
  HttpServer httpserver(8383);
  MyStubServer s(httpserver,
                 JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();

  return 0;
}