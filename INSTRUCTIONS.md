# Supported Command-Line Options for BlurAPI Sever

```
./blurapiserver --help

Supported command line options are:
  --help                Show help text for server startup flags
  --blur-host arg       Host address for blur daemon 
                         (Example: --host="127.0.0.1")
  --blur-port arg       Port for communcation with blur daemon 
                         (Example: --port=52542)
  --api-port arg        Port for communcation with blurapiserver 
                         (Example: --port=8383)
```

# Compiling and Running the BlurAPI Server

**First, install dependencies:** `sudo apt install libjsoncpp-dev curl libboost-program-options-dev`

**Then, perform the following steps to compile and run the BlurAPI server:**

1. Clone this repo, and move into directory: `git clone https://github.com/who-biz/blur-api-cpp && cd blur-api-cpp`
2. Create build directory, and compile: `mkdir build && cd build && cmake .. && make`


*Note: You may specify* `-DCMAKE_BUILD_TYPE=Debug`*, to enable prettyprinted stack traces, courtesy of <a href="https://github.com/bombela/backward-cpp">bombela/backward-cpp</a>, but you will need to install both the* `libdwarf-dev libelf-dev` *packages.*


3. Start the BlurAPI server, including `--blur-port` startup flag (this should be the port your Blur daemon will be running on): `./bin/blurapiserver --blur-port=21111`
4. Launch the Blur Network daemon with the following options: `./blurd --testnet`


*Note: Ensure that your `blurd` was built from the <a href="https://github.com/blur-network/dpow-blur">blur-network/dpow-blur repository</a>, `testnet` branch*


**Finally, call an RPC method from below**

# RPC Methods/Examples

*Please note: the data in responses for* `validateaddress` *and* `calc_MoM` *methods are merely placeholders with default values, for compatibility with iguana. Response fields (for these two methods, only) will not change with different parameter values.*

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

---

**Method: `get_notarization_data`**

```
curl --data-binary '{"jsonrpc":"1.0", "id":"curltest", "method":"get_notarization_data", "params":[]}' http://localhost:8383
```

Response:

```
{"error":null,"id":"curltest","result":{"assetchains_symbol":"BLUR","current_chain_hash":"b60bea9387bfbc24b59998762cff7a8b71de75728d29e7824c6cdb959d84decb","current_chain_height":3075,"current_chain_pow":"e93cd8caa74d386768672c33612f757ec8a798e782a67892b6d46f68dbc36604","embedded_btc_hash":"313031a1ed2dbe12a20706dff48d3dffb0e39d15e3e4ff936d01f091fb3b8556","notarizations_completed":7,"notarizations_merkle":"92fbf297fb1ba553f37a9bcaab93ba34b3bb352ae99a190852804a21a7e4a343","notarized_hash":"0873d25c15a0ec2e08af077113a939a07ee8d87caea3c13680d3ef18fcd0ba06","notarized_height":2939,"notarized_txid":"a85701183ace0baa3334c327ee3e871422615fa4f65e35df889ff4ad3aea4e13"}}
```
