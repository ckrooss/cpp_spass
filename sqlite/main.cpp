#include <SQLiteCpp/SQLiteCpp.h>


namespace {
    int main_cpp() {
        SQLite::Database db("/tmp/mydb.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        db.exec("DROP TABLE IF EXISTS users;");
        db.exec("CREATE TABLE users (id int UNIQUE PRIMARY KEY, name TEXT, age REAL) STRICT;");
        db.exec(R"(INSERT INTO users VALUES (1, "Hans", 31);)");
        db.exec(R"(INSERT INTO users VALUES (2, "Peter", "32");)");
        db.exec(R"(INSERT INTO users VALUES (3, "Karl", "21.21");)");
        db.exec(R"(INSERT INTO users VALUES (3, "Karl", "21.21");)");
        return 0;
    }
}

int main() {
    try {
        return main_cpp();
    } catch (const SQLite::Exception &e) {
        printf("Error in sqlite: %s", e.what());
    }
}
