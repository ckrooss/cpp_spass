#include "lib.hpp"

using namespace std;

shared_ptr<Data> get_data() {
    auto data = make_shared<Data>();
    data->push_back("4");
    return data;
}
