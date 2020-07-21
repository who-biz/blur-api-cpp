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
#include "blur_api.h"
#include <string>
#include <memory>
#include <stdexcept>
#include <cmath>

#include <jsonrpccpp/client.h>
#include <jsonrpccpp/client/connectors/httpclient.h>


using namespace jsonrpc;
using namespace std;

namespace jsonrpc { class HttpClient; class Client; }

class MyStubServer : public AbstractStubServer, public BlurAPI {
public:
  MyStubServer(AbstractServerConnector &connector, serverVersion_t type);

  std::string username = "user";
  std::string password = "password";
  std::string host = "127.0.0.1";
  int port = 21111;
  int httpTimeout = 500;

  void connect_blur_api(BlurAPI&);

  BlurAPI m_blur_api;
  virtual void notifyServer();
  virtual std::string sayHello(const std::string &name);
  virtual Json::Value getblockchaininfo();
  virtual Json::Value get_notarization_data();
  virtual Json::Value validateaddress(std::string const& address);
  virtual Json::Value getbestblockhash();
  virtual Json::Value getblockhash(int const height);
  virtual Json::Value calc_MoM(int const height, int const MoMdepth);
  virtual int addNumbers(int param1, int param2);
  virtual double addNumbers2(double param1, double param2);
  virtual Json::Value calculate(const Json::Value& args);
  virtual bool isEqual(const std::string &str1, const std::string &str2);
  virtual Json::Value buildObject(const std::string &name, int age);
  virtual std::string methodWithoutParameters();
};

MyStubServer::MyStubServer(AbstractServerConnector &connector,
                           serverVersion_t type)
    : AbstractStubServer(connector, type), m_blur_api(BlurAPI("user","password","127.0.0.1", 21111)) {}

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
  Json::Value result = m_blur_api.getblockchaininfo();
  return result;
}

Json::Value MyStubServer::get_notarization_data() {
  Json::Value result = m_blur_api.get_notarization_data();
  return result;
}

Json::Value MyStubServer::validateaddress(std::string const& address) {
  Json::Value result = m_blur_api.validateaddress(address);
  return result;
}

Json::Value MyStubServer::getbestblockhash() {
  Json::Value result = m_blur_api.getbestblockhash();
  return result;
}

Json::Value MyStubServer::getblockhash(int const height) {
  Json::Value result = m_blur_api.getblockhash(height);
  return result;
}

Json::Value MyStubServer::calc_MoM(int const height, int const MoMdepth) {
  Json::Value result = m_blur_api.calc_MoM(height, MoMdepth);
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

void MyStubServer::connect_blur_api(BlurAPI& blur) {
  m_blur_api = blur;
}

string MyStubServer::methodWithoutParameters() { return "Test"; }

int main() {
  HttpServer httpserver(8383);

  MyStubServer s(httpserver,
                 JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)

  s.connect_blur_api(s.m_blur_api);

  s.StartListening();
  cout << "Hit enter to stop the server" << endl;
  getchar();
  s.StopListening();

  return 0;
}
