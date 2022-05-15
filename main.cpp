#include <iostream>
#include "irodsClientApiTest.h"

int main() {
    rodsEnv env;
    if(getRodsEnv(&env) < 0) {
        std::cerr << "environment file not found." << std::endl;
        return 2;
    }

    const int connect_pool_size = 4;
    const int refresh_time_in_secs = 600;

    // IRODS_CONNECTION_POOL
    irods::connection_pool pool {connect_pool_size, env.rodsHost, env.rodsPort, env.rodsUserName, env.rodsZone, refresh_time_in_secs};

    auto conn = pool.get_connection();

    load_client_api_plugins();

    print_all_resource_names(conn);
    const std::string path = "../test/testIO.txt";
    //ad_and_write(conn, "/tempZone/home/rods/test/testIO.txt", "../test/testIO.txt");
    iterating_over_collections(conn);
    upload_add_metadata(env, conn, path);
    get_checksum(conn, "/tempZone/home/rods/unit_testing_sandbox/testIO.txt");
    return 0;
}
