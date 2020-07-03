#include <string>
#include <vector>

#include <json/json.h>

    /* === General types (adapted from bitcoin-api-cpp) === */
    struct getinfo_t{
      std::string status;
      uint64_t height;
      uint64_t target_height;
      uint64_t difficulty;
      uint64_t target;
      uint64_t tx_count;
      uint64_t notarization_count;
      std::string notarizedhash;
      std::string notarizedtxid;
      int32_t notarized;
      int32_t prevMoMheight;
      int32_t notarized_MoMdepth;
      std::string notarized_MoM;
      uint64_t tx_pool_size;
      uint64_t alt_blocks_count;
      uint64_t outgoing_connections_count;
      uint64_t incoming_connections_count;
      uint64_t rpc_connections_count;
      uint64_t white_peerlist_size;
      uint64_t grey_peerlist_size;
      bool mainnet;
      bool testnet;
      bool stagenet;
      std::string top_block_hash;
      uint64_t cumulative_difficulty;
      uint64_t block_size_limit;
      uint64_t block_size_median;
      uint64_t start_time;
      uint64_t free_space;
      bool offline;
      bool untrusted;
      std::string bootstrap_daemon_address;
      uint64_t height_without_bootstrap;
      bool was_bootstrap_ever_used;
      std::string version;
    };
