# Compiling and Running the BlurAPI Server

Perform the following steps to compile and run the BlurAPI server:

1. Clone this repo, and move into directory: `git clone https://github.com/who-biz/blur-api-cpp && cd blur-api-cpp`
2. Create build directory, and compile: `mkdir build && cd build && cmake .. && make`

*Note: You may specify* `-DCMAKE_BUILD_TYPE=Debug`*, to enable prettyprinted stack traces, courtesy of <a href="https://github.com/bombela/backward-cpp">bombela/backward-cpp</a>, but you will need to install both the* `libdwarf-dev libelf-dev` *packages.*

3. Start the BlurAPI server: `./bin/blurapiserver`
4. Call an RPC method from below

# RPC Methods/Examples

**Method: `getblockchaininfo`**

```
 curl --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getblockchaininfo", "params":[]}' http://localhost:8383
```

Response:

```
{"error":null,"id":"curltest","result":{"alt_blocks_count":0,"block_size_limit":600000,"block_size_median":83,"bootstrap_daemon_address":"","cumulative_difficulty":50279071,"difficulty":29,"free_space":56456196096,"grey_peerlist_size":0,"height":3076,"height_without_bootstrap":3076,"incoming_connections_count":0,"mainnet":false,"notarization_count":7,"notarized":2939,"notarized_MoM":"92fbf297fb1ba553f37a9bcaab93ba34b3bb352ae99a190852804a21a7e4a343","notarizedhash":"0873d25c15a0ec2e08af077113a939a07ee8d87caea3c13680d3ef18fcd0ba06","notarizedtxid":"a85701183ace0baa3334c327ee3e871422615fa4f65e35df889ff4ad3aea4e13","offline":false,"outgoing_connections_count":8,"prevMoMheight":2918,"rpc_connections_count":1,"stagenet":false,"start_time":1595282181,"status":"OK","target":60,"target_height":0,"testnet":true,"top_block_hash":"b60bea9387bfbc24b59998762cff7a8b71de75728d29e7824c6cdb959d84decb","tx_count":32,"tx_pool_size":0,"untrusted":false,"version":"0.1.9.8.1","was_bootstrap_ever_used":false,"white_peerlist_size":7}}
```


---


**Method: `getbestblockhash`**

```
 curl --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getbestblockhash", "params":[]}' http://localhost:8383
```

Response:

```
{"error":null,"id":"curltest","result":{"hex":"b60bea9387bfbc24b59998762cff7a8b71de75728d29e7824c6cdb959d84decb","status":"OK"}}
```


---


**Method: `getblockhash`**

Parameters: `[ height ]`

```
 curl --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getblockhash", "params":[1000]}' http://localhost:8383
```

Response:

```
{"error":null,"id":"curltest","result":{"hash":"59b031d83bd562a36a355d5a0ff223f55a28134bb1ebb82da7d4afa92c06644c","status":"OK"}}
```


---


**Method: `calc_MoM`**

Parameters: `[ height, MoMdepth ]`

```
 curl --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "calc_MoM", "params":[1000, 1]}' http://localhost:8383
```

Response:

```
{"error":null,"id":"curltest","result":{"coin":"BLUR","notarized_MoM":"92fbf297fb1ba553f37a9bcaab93ba34b3bb352ae99a190852804a21a7e4a343","notarized_MoMdepth":1,"notarized_height":1000,"status":"OK"}}
```


---


**Method: `validateaddress`**

Parameters: `[ "address" ]`

```
 curl --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getblockhash", "params":["xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"]}' http://localhost:8383
```

Response:

```
{"error":null,"id":"curltest","result":{"address":"xxxxxxxxxxxxxxxxxxxxxxxxxx","ismine":true,"isscript":false,"isvalid":true,"iswatchonly":false,"scriptPubKey":"76a9140ba28b34ebd21d0b18e8753e71c2663c171bec9888ac","segid":4,"status":"OK"}}
```
