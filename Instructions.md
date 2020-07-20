# How to Create a StubServer

1. Clone this repo, and move into directory: `git clone https://github.com/who-biz/blur-api-cpp && cd blur-api-cpp`
2. Create build directory, and compile: `mkdir build && cd build && cmake .. && make`
- *Note: You may specify* `-DCMAKE_BUILD_TYPE=Debug`*, to enable prettyprinted stack traces, courtesy of <a href="https://github.com/bombela/backward-cpp">bombela/backward-cpp</a>, but you will need to install both the* `libdwarf-dev libelf-dev` *packages.*
3. Start the BlurAPI server: `./bin/blurapiserver`
4. Call an RPC method from below

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
