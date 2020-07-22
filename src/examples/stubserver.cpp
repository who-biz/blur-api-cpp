/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    stubserver.cpp
 * @date    02.05.2013
 * @author  Peter Spiess-Knafl <dev@spiessknafl.at>
 * @license See attached LICENSE.txt
 ************************************************************************/
#include <iostream>
#include <stdio.h>
#include <string>
#include <memory>
#include <stdexcept>
#include <cmath>

#include <jsonrpccpp/client.h>
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <boost/program_options.hpp>

#include "gen/abstractstubserver.h"
#include "blur_api.h"

using namespace jsonrpc;

namespace jsonrpc { class HttpClient; class Client; }

class MyStubServer : public AbstractStubServer, public BlurAPI {
public:
  MyStubServer(AbstractServerConnector &connector, serverVersion_t type);

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

std::string username;
std::string password;
std::string host;
int port;

MyStubServer::MyStubServer(AbstractServerConnector &connector,
                           serverVersion_t type)
    : AbstractStubServer(connector, type), m_blur_api(BlurAPI(username, password, host, port)) {}

void MyStubServer::notifyServer() { std::cout << "Server got notified" << std::endl; }

/*Json::Value sendcommand(const std::string& command, const Json::Value& params)
{
};*/

std::string MyStubServer::sayHello(const std::string &name) {
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

bool MyStubServer::isEqual(const std::string &str1, const std::string &str2) {
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

Json::Value MyStubServer::buildObject(const std::string &name, int age) {
  Json::Value result;
  result["name"] = name;
  result["year"] = age;
  return result;
}

std::string MyStubServer::methodWithoutParameters() { return "Test"; }

int main(int ac, char** av) {

  try {

    boost::program_options::options_description desc("Supported command line options are: ");
    desc.add_options()
      ("help", "Show help text for server startup flags")
      ("host", boost::program_options::value<std::string>(), "Host address for blur daemon \n (Example: --host=\"127.0.0.1\")")
      ("port", boost::program_options::value<int>(), "Port for communcation with blur daemon \n (Example: --port=52542)")
      ("username", boost::program_options::value<std::string>(), "Username for blur daemon rpc login \n (Example: --user=\"username\")")
      ("password", boost::program_options::value<std::string>(), "Password for blur daemon rpc login \n (Example: --password=\"password\")");

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(ac, av, desc), vm);
    boost::program_options::notify(vm);

    if(vm.count("help")) {
      std::cout << desc << std::endl;
      return 0;
    }

    if (vm.count("host")) {
      std::cout << "Host address set to " << vm["host"].as<std::string>() << ", for blur daemon." << std::endl;
      host = vm["host"].as<std::string>();
    } else {
      std::cout << "No host provided, assuming localhost..." << std::endl;
      host = "127.0.0.1";
    }

    if (vm.count("port")) {
      std::cout << "Port set to " << std::to_string(vm["port"].as<int>()) << ", for blur daemon..." << std::endl;
      port = vm["port"].as<int>();
    } else {
      std::cout << "ERROR: No port number provided for blur daemon... Please use \"--port\" startup flag to specify." << std:: endl;
      return 1;
    }

    if (vm.count("username")) {
      username = vm["username"].as<std::string>();
      if (vm.count("password") == 0) {
        std::cout << "ERROR: Username provided for blur daemon RPC login, but no password!" << std::endl;
        return 1;
      } else {
        password = vm["password"].as<std::string>();
      }
    }

    if (vm.count("password")) {
      password = vm["password"].as<std::string>();
      if (vm.count("username") == 0) {
        std::cout << "ERROR: Password provided for blur daemon RPC login, but no username!" << std::endl;
        return 1;
      } else {
        username = vm["username"].as<std::string>();
      }
    }
  } catch (std::exception& e) {
    std::cout << "ERROR: Exception when parsing program options: " << e.what() << std::endl;
    return 1;
  }

  HttpServer httpserver(8383);

  MyStubServer s(httpserver,
                 JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)

  s.StartListening();
  std::cout << std::endl << "Hit enter to stop the server" << std::endl;
  getchar();
  s.StopListening();

  return 0;
}
