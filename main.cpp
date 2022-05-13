#include <iostream>
#include "irodsClientApiTest.h"
//#include <openssl/md5.h>

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

    print_all_resource_names(conn);
    read_and_write(conn, "/tempZone/home/rods/a.txt", "../test/testIO.txt");
    iterating_over_collections(conn);
    return 0;
}
