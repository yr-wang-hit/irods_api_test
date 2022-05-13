//
// Created by wangyuren on 2022/5/10.
//

#ifndef DATAHUB_IRODSCLIENTAPITEST_H
#define DATAHUB_IRODSCLIENTAPITEST_H

#include <rodsClient.h>
#include <irods/irods_query.hpp>
#include <irods/connection_pool.hpp>
#include <irods/dstream.hpp>
#include <irods/transport/default_transport.hpp>


#include <iostream>
void print_all_resource_names(rcComm_t& _conn);
void iterating_over_collections(rcComm_t& _conn);
int read_and_write(rcComm_t& _conn, const std::string& irods_path, const std::string& path);

#endif //DATAHUB_IRODSCLIENTAPITEST_H
