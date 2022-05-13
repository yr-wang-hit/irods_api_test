cmake_minimum_required(VERSION 3.10)
project(irods_api_test VERSION 1.0.0 LANGUAGES CXX)

find_package(IRODS 4.2.11 EXACT REQUIRED)
find_package(nlohmann_json REQUIRED)

set(CMAKE_CXX_COMPILER ${IRODS_EXTERNALS_FULLPATH_CLANG}/bin/clang++)
set(CMAKE_CXX_STANDARD ${IRODS_CXX_STANDARD})
set(CMAKE_MODULE_LINKER_FLAGS_INIT "-Wl,--enable-new-dtags -Wl,--as-needed -Wl,-z,defs")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "-Wl,--enable-new-dtags -Wl,--as-needed -Wl,-z,defs")
set(CMAKE_MODULE_LINKER_FLAGS_RELEASE_INIT "-Wl,--gc-sections -Wl,-z,combreloc")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE_INIT "-Wl,--gc-sections -Wl,-z,combreloc")

set(IRODS_EXTERNALS_FULLPATH_BOOST /opt/irods-externals/boost1.67.0-0)
set(IRODS_EXTERNALS_FULLPATH_FMT /opt/irods-externals/fmt6.1.2-1)

include(${IRODS_TARGETS_PATH})
include(GNUInstallDirs)
include(UseLibCXX)

add_executable(irods_api_test main.cpp src/irodsClientApiTest.cpp include/irodsClientApiTest.h) #setup the target.
include_directories(include)
target_include_directories(irods_api_test PRIVATE ${IRODS_INCLUDE_DIRS} ${IRODS_EXTERNALS_FULLPATH_BOOST}/include ${IRODS_EXTERNALS_FULLPATH_FMT}/include)

target_link_libraries(irods_api_test PRIVATE
        irods_common irods_client
        ${IRODS_EXTERNALS_FULLPATH_BOOST}/lib/libboost_filesystem.so
        ${IRODS_EXTERNALS_FULLPATH_BOOST}/lib/libboost_program_options.so
        ${IRODS_EXTERNALS_FULLPATH_BOOST}/lib/libboost_system.so
        ${IRODS_EXTERNALS_FULLPATH_FMT}/lib/libfmt.so
        nlohmann_json::nlohmann_json)
