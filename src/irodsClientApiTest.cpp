//
// Created by wangyuren on 2022/5/8.
//
#include "irodsClientApiTest.h"
#include <irods/filesystem.hpp>
#include <fstream>


void print_all_resource_names(rcComm_t& _conn) {
    for(auto&& row : irods::query<rcComm_t>{&_conn, "select RESC_NAME"}) {
        std::cout << row[0] << std::endl;
    }
}

void iterating_over_collections(rcComm_t& _conn) {
    namespace fs = irods::experimental::filesystem;
    for(auto&& e : fs::client::collection_iterator{_conn, "/tempZone/home/rods"}) {
        //if (e.is_data_object())
        std::cout << e << " size is : " << e.data_size() << std::endl;
    }
}

// TODO: The odstream cannot be established and the client API test failed.
int read_and_write(rcComm_t& _conn, const std::string& irods_path, const std::string& path) {
    namespace io = irods::experimental::io;
    io::client::default_transport xport{_conn};
    io::odstream out {xport, irods_path};
    if(!out) {
        std::cerr << "irods streaming cannot be established, exit" << std::endl;
        return 2;
    }
    std::ostringstream buf;
    std::ifstream input(path.c_str());
    buf << input.rdbuf();
    std::string content = buf.str();
    out.write(content.c_str(), content.size());
    return 0;
}

/*
int read_from_irods(rcComm_t _conn, const std::string& irods_path) {
    namespace io = irods::experimental::io;
    io::client::default_transport xport{_conn};


}
 */



