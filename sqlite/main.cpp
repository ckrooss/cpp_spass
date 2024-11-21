#include <sqlite3.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>

#include <SQLiteCpp/SQLiteCpp.h>

int cb(void* /*none*/, int /*cols*/, char** /*column_text*/, char** /*column_names*/) {
    std::cout << "yay\n";
    return 0;
}

int main_cpp() {
    SQLite::Database db("/tmp/mydb.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    SQLite::Statement creat(db, "CREATE TABLE IF NOT EXISTS users (id int, name varchar(255));");
    creat.exec();

    SQLite::Statement insert(db, "INSERT INTO users VALUES (?, ?);");
    insert.bind(1, 1);
    insert.bind(2, "Hans");
    if(insert.exec() != 1) {
        printf("Failed to insert\n");
        return 1;
    }

    return 0;
}

int main_c() {
    sqlite3* db;
    char* err = nullptr;
    auto retval = sqlite3_open("/tmp/mydb.db", &db);
    if (retval)
        printf("Could not open db!\n");
    retval = sqlite3_exec(db, "CREATE TABLE users (id int, name varchar(255));", cb, nullptr, &err);
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
    try{
    return main_cpp();
    }
    catch(const SQLite::Exception& e) {
        printf("Error in sqlite: %s", e.what());
    }
}
