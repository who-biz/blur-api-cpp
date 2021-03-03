# Find header and source files
FILE(GLOB blurapi_header types.h exceptions.h blur_api.h)
FILE(GLOB blurapi_source blur_api.cpp)

# Set target libraries
ADD_LIBRARY(blurapi SHARED ${blurapi_source})
ADD_LIBRARY(blurapi_static STATIC ${blurapi_source})

# Set output name of static library
SET_TARGET_PROPERTIES(blurapi_static PROPERTIES OUTPUT_NAME blurapi)

# Link the library with json-rpc-cpp libs
if(CMAKE_BUILD_TYPE STREQUAL Debug)
TARGET_LINK_LIBRARIES(blurapi
			backward
                        jsonrpccommon
                        jsonrpcclient)

TARGET_LINK_LIBRARIES(blurapi_static
			backward
                        jsonrpccommon
                        jsonrpcclient)
else()
TARGET_LINK_LIBRARIES(blurapi
                        jsonrpccommon
                        jsonrpcclient)

TARGET_LINK_LIBRARIES(blurapi_static
                        jsonrpccommon
                        jsonrpcclient)
endif()
# Set version settings
SET(VERSION_STRING ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})
SET_TARGET_PROPERTIES(blurapi blurapi_static PROPERTIES
    VERSION "${VERSION_STRING}"
    SOVERSION "${SO_VERSION}")

# Install to appropriate destinations
INSTALL(FILES ${blurapi_header} DESTINATION include/blurapi)

INSTALL(TARGETS blurapi blurapi_static
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib)
