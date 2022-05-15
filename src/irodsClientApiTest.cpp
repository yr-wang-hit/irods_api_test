//
// Created by wangyuren on 2022/5/8.
//
#include "irodsClientApiTest.h"
#include <irods/filesystem.hpp>
#include <metadata.hpp>
#include <fstream>
#include <boost/filesystem.hpp>


std::string concat_path(const std::string& path, const std::string& irods_path_base) {
    auto filename = boost::filesystem::path(path).filename().string();
    return irods_path_base + "/" + filename;
}

void print_all_resource_names(rcComm_t& _conn) {
    for(auto&& row : irods::query<rcComm_t>{&_conn, "select RESC_NAME"}) {
        std::cout << row[0] << std::endl;
    }
}

void iterating_over_collections(rcComm_t& _conn) {
    namespace fs = irods::experimental::filesystem;
    for(auto&& e : fs::client::recursive_collection_iterator{_conn, "/tempZone/home/rods"}) {
        //if (e.is_data_object())
        std::cout << e << " size is : " << e.data_size() << std::endl;
    }
}

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

int upload_add_metadata(rodsEnv& env, rcComm_t& _conn, const std::string& path) {
    // iput a file and then add metadata to it.
    namespace fs = irods::experimental::filesystem;
    namespace ixm = irods::experimental::metadata;
    const auto sandbox = fs::path{env.rodsHome} / "unit_testing_sandbox";
    if(!fs::client::exists(_conn, sandbox)) {
        if(!fs::client::create_collection(_conn, sandbox)){
            std::cerr << "create collection failed. exit" << std::endl;
            return 3;
        }
    }
    std::string result_path = concat_path(path, sandbox.string());
    int result = read_and_write(_conn, result_path, path);
    assert(result == 0);
    auto md = ixm::avu{"a", "v", "u"};
    ixm::set(_conn, md, irods::experimental::entity::entity_type::data_object, fs::path(result_path));
    std::cout << "successfully write data object and tag metadata." << std::endl;
    return 0;
}



