/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    stubserver.cpp
 * @date    02.05.2013
 * @author  Peter Spiess-Knafl <dev@spiessknafl.at>
 * @license See attached LICENSE.txt
 ************************************************************************
 * @date    07.03.2020
 * @author  Blur Network <contact@blur.cash>
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

  std::unique_ptr<BlurAPI> m_blur_api;
  virtual void notifyServer();
  virtual Json::Value getblockchaininfo();
  virtual Json::Value getblock(std::string const& blockhash);
  virtual Json::Value getinfo();
  virtual Json::Value get_notarization_data();
  virtual Json::Value validateaddress(std::string const& address);
  virtual std::string getbestblockhash();
  virtual std::string getblockhash(int const height);
  virtual Json::Value sendrawtransaction(std::string const& signedhex);
  virtual Json::Value signrawtransaction(std::string const& hexstring, Json::Value const& prevtxs);
  virtual Json::Value listunspent(int const minconf, int const maxconf, Json::Value const& addresses);
  virtual Json::Value calc_MoM(std::string const& height, std::string const& MoMdepth);
  virtual ~MyStubServer();
};

MyStubServer::MyStubServer(AbstractServerConnector &connector,
                           serverVersion_t type)
    : AbstractStubServer(connector, type), m_blur_api(new BlurAPI(username, password, blur_host, blur_port)) {}

MyStubServer::~MyStubServer() { }

void MyStubServer::notifyServer() { std::cout << "Server got notified" << std::endl; }

Json::Value MyStubServer::getblockchaininfo() {
  Json::Value result = m_blur_api->getblockchaininfo();
  return result;
}

Json::Value MyStubServer::getblock(std::string const& blockhash) {
  Json::Value result = m_blur_api->getblock(blockhash);
  return result;
}

Json::Value MyStubServer::getinfo() {
  Json::Value result = m_blur_api->getblockchaininfo();
  return result;
}

Json::Value MyStubServer::get_notarization_data() {
  Json::Value result = m_blur_api->get_notarization_data();
  return result;
}

Json::Value MyStubServer::validateaddress(std::string const& address) {
  Json::Value result = m_blur_api->validateaddress(address);
  return result;
}

std::string MyStubServer::getbestblockhash() {
  Json::Value temp = m_blur_api->getbestblockhash();
  return temp["hex"].asString();
}

std::string MyStubServer::getblockhash(int const height) {
  Json::Value result = m_blur_api->getblockhash(height);
  std::string ret = result["hash"].asString();
  return ret;
}

Json::Value MyStubServer::calc_MoM(std::string const& height, std::string const& MoMdepth) {
  Json::Value result = m_blur_api->calc_MoM(height, MoMdepth);
  return result;
}

Json::Value MyStubServer::sendrawtransaction(std::string const& signedhex) {
  Json::Value result = m_blur_api->sendrawtransaction(signedhex);
  return result;
}

Json::Value MyStubServer::signrawtransaction(std::string const& hex, Json::Value const& prevtxs) {
  Json::Value result = m_blur_api->signrawtransaction(hex, prevtxs);
  return result;
}

Json::Value MyStubServer::listunspent(int const minconf, int const maxconf, Json::Value const& addresses) {
  std::list<std::string> addr_list;
  for (const auto & each: addresses) {
    addr_list.push_back(each.asString());
  }
  Json::Value blurapi_result = m_blur_api->listunspent(minconf, maxconf, addr_list);
  Json::Value result, itemone, itemtwo;
  for (auto& each : blurapi_result["entries"]) {
    each["amount"] = 0.0001;
    each["vout"] = 2;
    result.append(each);
  }
  return result;
}

int main(int ac, char** av) {

  try {

    boost::program_options::options_description desc("Supported command line options are");
    desc.add_options()
      ("help", "Show help text for server startup flags")
      ("blur-host", boost::program_options::value<std::string>(), "Host address for blur daemon \n (Example: --blur-host=\"127.0.0.1\")")
      ("blur-port", boost::program_options::value<int>(), "Port for communcation with blur daemon \n (Example: --blur-port=52542)")
      ("api-port", boost::program_options::value<int>(), "Port for communcation with blurapi stubserver \n (Example: --api-port=8383)");
/*      ("username", boost::program_options::value<std::string>(), "Username for blur daemon rpc login \n (Example: --user=\"username\")")
      ("password", boost::program_options::value<std::string>(), "Password for blur daemon rpc login \n (Example: --password=\"password\")");*/

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(ac, av, desc), vm);
    boost::program_options::notify(vm);

    if(vm.count("help")) {
      std::cout << desc << std::endl;
      return 0;
    }

    if (vm.count("blur-host")) {
      std::cout << "Host address set to " << vm["blur-host"].as<std::string>() << ", for blur daemon." << std::endl;
      blur_host = vm["blur-host"].as<std::string>();
    } else {
      std::cout << "No host provided, assuming localhost..." << std::endl;
      blur_host = "127.0.0.1";
    }

    if (vm.count("blur-port")) {
      std::cout << "Port set to " << std::to_string(vm["blur-port"].as<int>()) << ", for blur daemon..." << std::endl;
      blur_port = vm["blur-port"].as<int>();
    } else {
      std::cout << "ERROR: No port number provided for blur daemon... Please use \"--blur-port\" startup flag to specify." << std:: endl;
      return 1;
    }

    if (vm.count("api-port")) {
      std::cout << "Port set to " << std::to_string(vm["api-port"].as<int>()) << ", for blurapiserver..." << std::endl;
      api_port = vm["api-port"].as<int>();
    } else {
      std::cout << "No api-port set, using default port 8383..." << std::endl;
      api_port = 8383;
    }

/*    if (vm.count("username")) {
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
    }*/

  } catch (std::exception& e) {
    std::cout << "ERROR: Exception when parsing program options: " << e.what() << std::endl;
    return 1;
  }

  HttpServer httpserver(api_port);

  MyStubServer s(httpserver,
                 JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)

  s.StartListening();
  std::cout << std::endl << "Hit enter to stop the server" << std::endl;
  getchar();
  s.StopListening();

  return 0;
}
