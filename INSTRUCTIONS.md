# Supported Command-Line Options for BlurAPI Server

```
./blurapiserver --help

Supported command line options are:
  --help                Show help text for server startup flags
  --blur-host arg       Host address for blur daemon 
                         (Example: --blur-host="127.0.0.1")
  --blur-port arg       Port for communcation with blur daemon 
                         (Example: --blur-port=52542)
  --api-port arg        Port for communcation with blurapi stubserver 
                         (Example: --api-port=8383)
```

# Compiling and Running the BlurAPI Server

**First, install dependencies:** `sudo apt install libjsoncpp-dev curl libboost-program-options-dev libmicrohttpd-dev libargtable2-dev cmake`

**Next, compile and install `libjson-rpc-cpp`:**

```
git clone git clone https://github.com/cinemast/libjson-rpc-cpp.git
mkdir build && cd build && cmake .. && make -j4
sudo make install
```

**Then, perform the following steps to compile and run the BlurAPI server:**

1. Clone this repo, and move into directory: `git clone https://github.com/blur-network/blur-api-cpp && cd blur-api-cpp`
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
 curl --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "calc_MoM", "params":["1000", "1"]}' http://localhost:8383
```

Response:

```
{"error":null,"id":"curltest","result":{"coin":"BLUR","notarized_MoM":"92fbf297fb1ba553f37a9bcaab93ba34b3bb352ae99a190852804a21a7e4a343","notarized_MoMdepth":1,"notarized_height":1000,"status":"OK"}}
```


---


**Method: `validateaddress`**

Parameters: `[ "address" ]`

```
 curl --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "validateaddress", "params":["xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"]}' http://localhost:8383
```

Response:

```
{"error":null,"id":"curltest","result":{"address":"xxxxxxxxxxxxxxxxxxxxxxxxxx","ismine":true,"isscript":false,"isvalid":true,"iswatchonly":false,"scriptPubKey":"76a9140ba28b34ebd21d0b18e8753e71c2663c171bec9888ac","segid":4,"status":"OK"}}
```

---

**Method: `getblock`**

```
curl --data-binary '{"jsonrpc":"1.0", "id":"curltest", "method":"getblock", "params":["530ff48d3ec8b9944af6c9872bab3216108f9a252c294165ad6ff196fbea7f08"]}' http://localhost:8383

```

Response:

```
{"error":null,"id":"curltest","result":{"chainwork":"3d40b03591a4f676a15c4b3ee41ad9ee28b191e460749dcbef3a6a395b63ac0e","confirmations":4965,"data":"0b0bfde396f90585e42f3002518fed05a82bcbed095d329f5f93528a55c0e0da1b2cd6ce2ec73a29ee936401bb1a01ffa21a019f80a3c390f80102049f7fbc1226eb70ec63b555bc96fe4d91c694f292d01517717c2b55c2c4486a2101aa1fe96208acdc8f41b561d51acf8ff6791f395f71f44679970e19a7bf8f28ac0001f2767b2c9c6004f03d29776a790d8ecc5e88117e160fb602ed33e0d81255cbdf","difficulty":1,"hash":"530ff48d3ec8b9944af6c9872bab3216108f9a252c294165ad6ff196fbea7f08","height":3362,"last_notarized_height":3362,"merkleroot":"b89e000db673d61adb5ed1665f60ea6c8334a6a0c95ca94038e67816b958d053","previousblockhash":"45555c3040be65b164630e4fcd2ac888956189f9f2cfe8f47007762f10aafa64","rawconfirmations":4965,"size":53084,"solution":"0b0bfde396f90585e42f3002518fed05a82bcbed095d329f5f93528a55c0e0da1b2cd6ce2ec73a29ee936401bb1a01ffa21a019f80a3c390f80102049f7fbc1226eb70ec63b555bc96fe4d91c694f292d01517717c2b55c2c4486a2101aa1fe96208acdc8f41b561d51acf8ff6791f395f71f44679970e19a7bf8f28ac0001f2767b2c9c6004f03d29776a790d8ecc5e88117e160fb602ed33e0d81255cbdf","status":"OK","time":1596305917,"tx":["08d047de58400d8e8cf9470ea5d0851045f94e661c2144e15c45956aa22ffdf3","f2767b2c9c6004f03d29776a790d8ecc5e88117e160fb602ed33e0d81255cbdf"],"version":11}}
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

---


**Method: `listunspent`**

```
curl --data-binary '{"jsonrpc":"1.0", "id":"curltest", "method":"listunspent", "params":[1, 99999, ["RVJ1UYh4452z66Tu7yRGWsKY3zALGtYZ4hQroQAXfeiwkzw9naj48awDA9y2r"]]}' http://localhost:8383
```

Response:

```
{"error":null,"id":"curltest","result":[{"address":"RVJ1UYh4452z66Tu7yRGWsKY3zALGtYfqo","amount":100,"confirmations":1000,"redeemScript":"76a9140ba28b34ebd21d0b18e8753e71c2663c171bec9888ac","safe":true,"scriptPubKey":"76a9140ba28b34ebd21d0b18e8753e71c2663c171bec9888ac","solvable":true,"spendable":true,"txid":"2ff9dd22f0d5d3e99feb3abc9917c6a0b6afa9797696faf3d4bdb5e306597695","vout":1},{"address":"RQNvZ4hQroQAXfeiwkzw9naj48awDA9y2r","amount":100,"confirmations":1000,"redeemScript":"76a9140ba28b34ebd21d0b18e8753e71c2663c171bec9888ac","safe":true,"scriptPubKey":"76a9140ba28b34ebd21d0b18e8753e71c2663c171bec9888ac","solvable":true,"spendable":true,"txid":"2ff9dd22f0d5d3e99feb3abc9917c6a0b6afa9797696faf3d4bdb5e306597695","vout":1}]}
```

---

**Method: `sendrawtransaction`**

```
curl --data-binary '{"jsonrpc":"1.0", "id":"curltest", "method":"sendrawtransaction", "params":["010000000dd42b2132cc0f6bea63ad6e94015e5fd988ea0370c519fb04aa3c91afac1cc90a0100000048473044022037abbb3ced70a8cd9c2f5c5dea1f4484140aa189b8911bd76340941462ecd4cd0220646879ec97649d121c6d7bcd1714f5a5cbe050216249eea0d94a7029791a8c8c01ffffffff4f2cb08342da314fac56bb95a1b5bb8f7c7f9505026e7f065a8049a568f6bf0b060000004847304402200c8f0746c945c4b72c2115049be8ccd184971ded8f35ffb6557aa5c85823889502204f5a1f3c9484967d98284c7c4511c9c61345159462c2c070d6b45e0d8fc07cc601ffffffff6c70688f390a33b5b10892e0a889670637543563d1ee0e54c8643f80d57be4fe06000000484730440220627db25375a00b939105a7afd0cacf20877d5dfc4d9205e27ab6ba189bdb3f5402201d5969f6ca779838d62c07f8d9c54ff940fe4eb5efc5847ceb4877ec02e1980801ffffffffbe5ff4358913fb0f357cd4f209eccfad53125dd0ed3c50a59c3811c9057ceb430600000049483045022100f452d8a6c70003c930d82f2540851ca18e83beb10a615bd4cc191b9e9df7d81902202457380fdfa79a8ce047ce7bf714d4f8dc1a2c4c9ab6d2a946b05ec6ad57af6f01ffffffff06f2556fe6339b4cd8fcb89b5d180ea1f83d1ebbf773a4fa97ae5aaa4e67cd60050000004847304402203a3fa35b169d7d1b23c63bf16d934e87154b3acdf43bffdeea9bcd711528c06202200592932c1882f19d97cf83bfc40453c5fe4bd91b0bc38f6068421546ba0b38a501ffffffff84a1ab93a653f5c5b005dafb66f04a0e141861d1d119f6373a0df5568ae3e32d030000004948304502210092d29c1689ff36acb43a6b9838820b4424449287e1eea8a2f591d8f9b9f59a89022063b9e87612a1b7489e4b50d9aed00c9c6373cc7abf041280561850c1b292756d01ffffffffb050ff20ccdbdc700cf3187ebe55d2d9919757638d5e1fa384bc36aaddc29a87000000004847304402200214c129a4182e9ffe71e627315e1dce1b660c49b5004652e7b230a4acc95b9e02204b6f66e0346b587a997b0f8571ca54641ca7995d60aef0a2ebdd353b8367958301ffffffff511bf19814deef29ee88b7a94cc936ae0981319df64605b4ff437746daca7f510900000049483045022100808b3bd26a837ee410e69ceb55b7b29e92833ee449467ca4b2922f5195028f3d022011680ccd601451667ba12ed9443124dc565ab67094aa2cf3d0cc0c67560ce0de01ffffffffb67bdcb7c7f7bc1279cfd085d44635ae7011fd529b1d549327d5ff731ff8fbd607000000484730440220379be20435df02115bedd84f1c5ef0c3b1a09f759e63c437e5879ab808bbc60a022009323b553e6fa48f4f56ea3c581549d7179a6b3d2b46f973d939d5cea6c1613701ffffffff6732d747a48663467d21c4282fb6705f3916421912ec4312ccf3cc6258933e35040000004847304402206f0e939e09a0ccb4d746663e15091aaa5ea64699b8f2faa515c079f41a0f2b4c02204dc5d887f6fc70c6488c644e6adc7e749fd0cbb5195eb986704e486a8a31ec3101ffffffff611904eeb777c1f1c86262fa7f8e3191a2125ee4c8440837e5b8604144dcb526090000004847304402206ec15a69e81569b606b550a7af9530172923c6933a6832608d8fb8f8cf9067ba0220136f0aaa4790e9120da876fa2cfa963b96d2774026c0f803d0924a6cefbf3d0e01fffffffff0300247cd2234bcffd923895b579cf7fbcba5405df5f09c468da835cc416e9005000000484730440220119ee524eae3810da16132e1e9aeb28f23ad81780389808124897f4ebfbacee302205204643fbccbd8befb5d1b71dbcca4a44b6ef0b32fcc894b3fed76ccfc6bd7c601ffffffffa377c825ea5a03dc93c93a41ac06f58042512d5098333574d6de0d8a6d5b99820700000049483045022100ad752b6d0ab189bc1a267008816d8cac4982823dc20a60967a078dc9ed17348e022066c4779c21f706ee3c4aa0f956e0d2a746c2cfb587550c07c5a6a2385c1f3ebf01ffffffff02b0890700000000002321020e46e79a2a8d12b9b5d12c7a91adb4e454edfae43c0a0cb805427d2ac7613fd9ac00000000000000002a6a28071c4524afe8cf8e412b6fdb06e65795839f189205119294d26939c61c37880a084409004b4d440000000000"]}' http://localhost:8383
```

Response:

```
{"error":null,"id":"curltest","result":{"hex":"313031a1ed2dbe12a20706dff48d3dffb0e39d15e3e4ff936d01f091fb3b8556","status":"OK"}}
```

---

**Method: `signrawtransaction`**

```
curl --data-binary '{"jsonrpc": "1.0", "id": "curltest", "method": "signrawtransaction", "params":["0100000002e41ed910166c9276a24e4115d11c80ec7fb8219a12a699277710c11101112ed52000000000ffffffff42b1c03585792d82d4aee6cf2ffaf8116aa7373c27baaf7fa96a8bd228403f0e1900000000ffffffff0210270000000000002321020e46e79a2a8d12b9b5d12c7a91adb4e454edfae43c0a0cb805427d2ac7613fd9ac0000000000000000726a4c6ff2891acab8c11412e051d572812cdd43fe13d6128d7b870c0b28ea51d47ef601c40c0000131def572da30b26652ca29a5ffd3c6993cc02069a0d0fb233c747d65bbb559e545853434c31003e99a1d7cdb33330726310545f428da616a4350523f42f0eec2f23f4ba5e63c90800000000000000",[]]}' http://localhost:8383
```

Response:

```
{"error":null,"id":"curltest","result":{"complete":true,"hex":"010000000dd42b2132cc0f6bea63ad6e94015e5fd988ea0370c519fb04aa3c91afac1cc90a0100000048473044022037abbb3ced70a8cd9c2f5c5dea1f4484140aa189b8911bd76340941462ecd4cd0220646879ec97649d121c6d7bcd1714f5a5cbe050216249eea0d94a7029791a8c8c01ffffffff4f2cb08342da314fac56bb95a1b5bb8f7c7f9505026e7f065a8049a568f6bf0b060000004847304402200c8f0746c945c4b72c2115049be8ccd184971ded8f35ffb6557aa5c85823889502204f5a1f3c9484967d98284c7c4511c9c61345159462c2c070d6b45e0d8fc07cc601ffffffff6c70688f390a33b5b10892e0a889670637543563d1ee0e54c8643f80d57be4fe06000000484730440220627db25375a00b939105a7afd0cacf20877d5dfc4d9205e27ab6ba189bdb3f5402201d5969f6ca779838d62c07f8d9c54ff940fe4eb5efc5847ceb4877ec02e1980801ffffffffbe5ff4358913fb0f357cd4f209eccfad53125dd0ed3c50a59c3811c9057ceb430600000049483045022100f452d8a6c70003c930d82f2540851ca18e83beb10a615bd4cc191b9e9df7d81902202457380fdfa79a8ce047ce7bf714d4f8dc1a2c4c9ab6d2a946b05ec6ad57af6f01ffffffff06f2556fe6339b4cd8fcb89b5d180ea1f83d1ebbf773a4fa97ae5aaa4e67cd60050000004847304402203a3fa35b169d7d1b23c63bf16d934e87154b3acdf43bffdeea9bcd711528c06202200592932c1882f19d97cf83bfc40453c5fe4bd91b0bc38f6068421546ba0b38a501ffffffff84a1ab93a653f5c5b005dafb66f04a0e141861d1d119f6373a0df5568ae3e32d030000004948304502210092d29c1689ff36acb43a6b9838820b4424449287e1eea8a2f591d8f9b9f59a89022063b9e87612a1b7489e4b50d9aed00c9c6373cc7abf041280561850c1b292756d01ffffffffb050ff20ccdbdc700cf3187ebe55d2d9919757638d5e1fa384bc36aaddc29a87000000004847304402200214c129a4182e9ffe71e627315e1dce1b660c49b5004652e7b230a4acc95b9e02204b6f66e0346b587a997b0f8571ca54641ca7995d60aef0a2ebdd353b8367958301ffffffff511bf19814deef29ee88b7a94cc936ae0981319df64605b4ff437746daca7f510900000049483045022100808b3bd26a837ee410e69ceb55b7b29e92833ee449467ca4b2922f5195028f3d022011680ccd601451667ba12ed9443124dc565ab67094aa2cf3d0cc0c67560ce0de01ffffffffb67bdcb7c7f7bc1279cfd085d44635ae7011fd529b1d549327d5ff731ff8fbd607000000484730440220379be20435df02115bedd84f1c5ef0c3b1a09f759e63c437e5879ab808bbc60a022009323b553e6fa48f4f56ea3c581549d7179a6b3d2b46f973d939d5cea6c1613701ffffffff6732d747a48663467d21c4282fb6705f3916421912ec4312ccf3cc6258933e35040000004847304402206f0e939e09a0ccb4d746663e15091aaa5ea64699b8f2faa515c079f41a0f2b4c02204dc5d887f6fc70c6488c644e6adc7e749fd0cbb5195eb986704e486a8a31ec3101ffffffff611904eeb777c1f1c86262fa7f8e3191a2125ee4c8440837e5b8604144dcb526090000004847304402206ec15a69e81569b606b550a7af9530172923c6933a6832608d8fb8f8cf9067ba0220136f0aaa4790e9120da876fa2cfa963b96d2774026c0f803d0924a6cefbf3d0e01fffffffff0300247cd2234bcffd923895b579cf7fbcba5405df5f09c468da835cc416e9005000000484730440220119ee524eae3810da16132e1e9aeb28f23ad81780389808124897f4ebfbacee302205204643fbccbd8befb5d1b71dbcca4a44b6ef0b32fcc894b3fed76ccfc6bd7c601ffffffffa377c825ea5a03dc93c93a41ac06f58042512d5098333574d6de0d8a6d5b99820700000049483045022100ad752b6d0ab189bc1a267008816d8cac4982823dc20a60967a078dc9ed17348e022066c4779c21f706ee3c4aa0f956e0d2a746c2cfb587550c07c5a6a2385c1f3ebf01ffffffff02b0890700000000002321020e46e79a2a8d12b9b5d12c7a91adb4e454edfae43c0a0cb805427d2ac7613fd9ac00000000000000002a6a28071c4524afe8cf8e412b6fdb06e65795839f189205119294d26939c61c37880a084409004b4d440000000000","status":"OK"}}
```
