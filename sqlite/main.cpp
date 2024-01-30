#include <sqlite3.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>

int cb(void* /*none*/, int /*cols*/, char** /*column_text*/, char** /*column_names*/) {
    std::cout << "yay\n";
    return 0;
}

int _main() {
    sqlite3* db;
    char* err = nullptr;
    auto retval = sqlite3_open("/tmp/mydb.db", &db);
    if (retval)
        printf("Could not open db!\n");
    //retval = sqlite3_exec(db, "CREATE TABLE users (id int, name varchar(255));", cb, nullptr, &err);c
    retval = sqlite3_exec(db, "INSERT INTO users ());", cb, nullptr, &err);
    if (retval)
        printf("Could not create table: %s\n", err);
    retval = sqlite3_close(db);
    if (retval)
        printf("Could not close db!\n");
    usleep(500000);
    return 0;
}

int main() {
    FILE* fd;
    const char* new_err{"OH HAI"};
    if (nullptr == (fd = fopen("/asd", "r"))) {
        printf("%s\n", strerror(errno));
        printf("%s\n", strerror(errno));
        memcpy(strerror(errno), new_err, 7);
        printf("%s\n", strerror(errno));
        printf("%s\n", strerror(errno));
        exit(1);
    }
    return 0;
}
