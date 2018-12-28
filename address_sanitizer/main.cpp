#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>

using namespace std;
using Data = vector<string>;

//Return map[key] if it exists in the map, otherwise return the default value
const string& get_default(const map<string, string>& map, const string& key, const string& dflt) {
    auto pos = map.find(key);
    return (pos != map.end() ? pos->second : dflt);
}

// give me a vector, nicely protected by using shared_ptr
shared_ptr<Data> get_data() {
    auto data = make_shared<Data>();
    data->push_back("4");
    return data;
}

int main() {
    map<string, string> m;
    pair<string, string> p1("key1", "value1");
    pair<string, string> p2("key2", "value2");
    m.insert(p1);
    m.insert(p2);

    auto& v1 = get_default(m, "key2", "default_value_2");
    cout << "key2 is: " << v1 << endl;

    auto& v2 = get_default(m, "key3", "default_value_3");
    cout << "key3 is: " << v2 << endl;

    auto& d = *get_data();
    cout << "Data is: " << d[0] << endl;
}
