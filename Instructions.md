# How to Create a StubServer

1. Clone this repo, and move into directory: `git clone https://github.com/blur-network/blur-libjson-rpc-cpp && cd blur-libjson-rpc-cpp`
2. Create build directory, and compile the library: `mkdir build && cd build && cmake .. && make`
3. Copy stubserver & spec example to build directory: `cp ../src/examples/stubserver.cpp ./ && cp ../src/examples/spec.json ./`
4. Create stubserver headers: `jsonrpcstub spec.json --cpp-server=AbstractStubServer --cpp-client=StubClient`
5. Move generated headers to gen directory: `mkdir -p gen && mv abstractstubserver.h gen/ && mv stubclient.h gen/`
6. Compile stubserver: `g++ stubserver.cpp -ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -o sampleserver`

# How to Call RPC Methods

1. Run the newly created sampleserver: `./sampleserver`
2. Call an RPC method


# Existing RPC Methods & Examples

- `getblockchaininfo`

```
 curl --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getblockchaininfo", "params":[]}' http://localhost:8383
```

- `getbestblockhash`

```
 curl --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getbestblockhash", "params":[]}' http://localhost:8383
```

- `getblockhash`**: (**`params` = `[ height ]`**)**

```
 curl --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getblockhash", "params":[1000]}' http://localhost:8383
```

- `calc_MoM`**: (**`params` = `[ height, MoMdepth ]`**)**

```
 curl --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "calc_MoM", "params":[1000, 1]}' http://localhost:8383
```

- `validateaddress`**: (**`params`: `[ "address" ]`**)**

```
 curl --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getblockhash", "params":["xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"]}' http://localhost:8383
```
