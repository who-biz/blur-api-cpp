/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    test_integration.cpp
 * @date    28.09.2013
 * @author  Peter Spiess-Knafl <dev@spiessknafl.at>
 * @license See attached LICENSE.txt
 ************************************************************************/

#ifdef STUBGEN_TESTING
#include <catch2/catch.hpp>

#ifdef HTTP_TESTING
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <jsonrpccpp/server/connectors/httpserver.h>
#endif

#include "gen/abstractstubserver.h"
#include "gen/stubclient.h"

using namespace jsonrpc;
using namespace std;

#define TEST_PORT 8484
#define CLIENT_URL "http://localhost:8484"

#define TEST_MODULE "[integration]"

#include<algorithm>

char
rand_alnum()
{
    char c;
    while (!std::isalnum(c = static_cast<char>(std::rand())))
        ;
    return c;
}


std::string
rand_alnum_str (std::string::size_type sz)
{
    std::string s;
    s.reserve  (sz);
    generate_n (std::back_inserter(s), sz, rand_alnum);
    return s;
}

class StubServer : public AbstractStubServer {
public:
  StubServer(AbstractServerConnector &connector)
      : AbstractStubServer(connector) {}
  virtual void notifyServer() {}

  virtual std::string sayHello(const std::string &name) {
    return string("Hello ") + name;
  }

 virtual int addNumbers(int param1, int param2) { return param1 + param2; }

  virtual double addNumbers2(double param1, double param2) {
    return param1 + param2;
  }

  virtual bool isEqual(const std::string &str1, const std::string &str2) {
    return str1 == str2;
  }

  virtual Json::Value buildObject(const std::string &name, int age) {
    Json::Value result;
    result["name"] = name;
    result["age"] = age;
    return result;
  }

  virtual std::string methodWithoutParameters() { return "foo"; }

  virtual Json::Value calculate(const Json::Value& args) {
    return Json::Value(args);
  }

  virtual Json::Value getblockchaininfo() {
    Json::Value result;
    result["status"] = "OK";
    result["height"] = 200;
    return result;
  }

  virtual Json::Value getblock(std::string const& blockhash) {
    Json::Value result;
    result["hash"] = "xxxxxxxxxxxx";
    result["solution"] = "xxxxxxxxxxxx";
    result["data"] = "xxxxxxxxxxxx";
    result["previousblockhash"] = "xxxxxxxxxxxx";
    return result;
  }

  virtual Json::Value getinfo() {
    Json::Value result;
    result["status"] = "OK";
    result["height"] = 200;
    return result;
  }

  virtual Json::Value get_notarization_data() {
    Json::Value result;
    result["assetchains_symbol"] = "BLUR";
    result["current_chain_height"] = 1000;
    result["current_chain_hash"] = "xxxxxxxxxxxxxxxx";
    result["current_chain_pow"] = "xxxxxxxxxxxxxxxx";
    result["notarized_height"] = 1000;
    result["notarized_hash"] = "xxxxxxxxxxxxxxxx";
    result["notarized_txid"] = "xxxxxxxxxxxxxxxx";
    result["notarized"] = 10;
    result["embedded_btc_hash"] = "xxxxxxxxxxxxxxx";
    result["notarizations_completed"] = 10;
    result["notarizations_merkle"] = "xxxxxxxxxxxxxxx";
    result["status"] = "OK";
    return result;
  }

  virtual Json::Value validateaddress(std::string const& address) {
    Json::Value result, params;
    params.append(address);
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

  virtual Json::Value sendrawtransaction(std::string const& signedhex) {
    Json::Value result, params;
    params.append(signedhex);
    result["hex"] = "xxxxxxxxxx";
    result["status"] = "OK";
    return result;
  }

  virtual Json::Value signrawtransaction(std::string const& hexstring, Json::Value const& prevtxs) {
    Json::Value result, params, item;
    params["hexstring"] = hexstring;
    for (const auto& each : prevtxs) {
      item["txid"] = each[0u].asString();
      item["vout"] = each[1u].asInt();
      item["scriptPubKey"] = each[2u].asString();
      item["redeemScript"] = each[3u].asString();
      item["amount"] = each[4u].asFloat();
      params["prevtxs"].append(item);
    }
    result["hex"] = "xxxxxxxxxxx";
    result["status"] = "OK";
    result["complete"] = true;
    return result;
  }

  virtual Json::Value listunspent(int const minconf, int const maxconf, Json::Value const& addresses) {
    Json::Value result, itemone, itemtwo, params;
    params["minconf"] = minconf;
    params["maxconf"] = maxconf;
    for (const auto& each: addresses) {
      params["addresses"].append(each.asString());
    }
    itemone["txid"] = "xxxxxxxxxx";
    itemtwo["txid"] = "xxxxxxxxxx";
    result.append(itemone);
    result.append(itemtwo);
    return result;
  }

  virtual std::string getbestblockhash() {
    return "xxxxxxxxxxxxxx";
  }

  virtual std::string getblockhash(int height) {
    Json::Value params;
    params.append(height);
    std::string result = "xxxxxxxxxxxxxxx";
    return result;
  }

  virtual Json::Value calc_MoM(std::string const& height, std::string const& MoMdepth) {
    Json::Value result, params;
    params.append(height), params.append(MoMdepth);
    result["coin"] = "BLUR";
    result["notarized_height"] = 1000;
    result["notarized_MoMdepth"] = 1;
    result["notarized_MoM"] = "xxxxxxxxxxxxxxxxx";
    result["status"] = "OK";
    return result;
  }

};

#ifdef HTTP_TESTING

TEST_CASE("test_integration_http", TEST_MODULE) {
  HttpServer sconn(TEST_PORT);
  HttpClient cconn(CLIENT_URL);
  StubServer server(sconn);
  server.StartListening();
  StubClient client(cconn);

  CHECK(client.addNumbers(3, 4) == 7);
  CHECK(client.addNumbers2(3.2, 4.2) == 7.4);
  CHECK(client.sayHello("Test") == "Hello Test");
  CHECK(client.methodWithoutParameters() == "foo");
  CHECK(client.isEqual("str1", "str1") == true);
  CHECK(client.isEqual("str1", "str2") == false);

  Json::Value result = client.buildObject("Test", 33);
  CHECK(result["name"].asString() == "Test");
  CHECK(result["age"].asInt() == 33);

  server.StopListening();
}

#endif
#ifdef UNIXDOMAINSOCKET_TESTING

#include <jsonrpccpp/client/connectors/unixdomainsocketclient.h>
#include <jsonrpccpp/server/connectors/unixdomainsocketserver.h>

TEST_CASE("test_integration_unixdomain", TEST_MODULE) {
  string filename = "/tmp/jrpcux_" + rand_alnum_str(10);
  UnixDomainSocketServer *sconn = new UnixDomainSocketServer(filename);
  UnixDomainSocketClient *cconn = new UnixDomainSocketClient(filename);

  StubServer *server = new StubServer(*sconn);
  server->StartListening();
  StubClient client(*cconn);

  CHECK(client.addNumbers(3, 4) == 7);
  CHECK(client.addNumbers2(3.2, 4.2) == 7.4);
  CHECK(client.sayHello("Test") == "Hello Test");
  CHECK(client.methodWithoutParameters() == "foo");
  CHECK(client.isEqual("str1", "str1") == true);
  CHECK(client.isEqual("str1", "str2") == false);

  Json::Value result = client.buildObject("Test", 33);
  CHECK(result["name"].asString() == "Test");
  CHECK(result["age"].asInt() == 33);

  server->StopListening();
  delete sconn;
  delete cconn;
  delete server;
}
#endif
#ifdef FILEDESCRIPTOR_TESTING

#include <jsonrpccpp/client/connectors/filedescriptorclient.h>
#include <jsonrpccpp/server/connectors/filedescriptorserver.h>
#include <unistd.h>

TEST_CASE("test_integration_filedescriptor", TEST_MODULE) {
  int c2sfd[2]; // Client to server fd
  int s2cfd[2]; // Server to client fd
  pipe(c2sfd);
  pipe(s2cfd);

  FileDescriptorServer sconn(c2sfd[0], s2cfd[1]);
  FileDescriptorClient cconn(s2cfd[0], c2sfd[1]);

  StubServer server(sconn);
  server.StartListening();
  StubClient client(cconn);

  CHECK(client.addNumbers(3, 4) == 7);
  CHECK(client.addNumbers2(3.2, 4.2) == 7.4);
  CHECK(client.sayHello("Test") == "Hello Test");
  CHECK(client.methodWithoutParameters() == "foo");
  CHECK(client.isEqual("str1", "str1") == true);
  CHECK(client.isEqual("str1", "str2") == false);

  Json::Value result = client.buildObject("Test", 33);
  CHECK(result["name"].asString() == "Test");
  CHECK(result["age"].asInt() == 33);

  server.StopListening();

  close(c2sfd[0]);
  close(c2sfd[1]);
  close(s2cfd[0]);
  close(s2cfd[1]);
}
#endif

#endif
