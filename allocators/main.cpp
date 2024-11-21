#include "allocator.h"

using test_t = int;
using array_vector_t = std::vector<test_t, ArrayAllocator<std::vector<test_t>::value_type>>;

template <class T, class U>
bool operator==(const ArrayAllocator<T>&, const ArrayAllocator<U>&) {
    return false;
}

int main() {
    array_vector_t v;
    v.reserve(3);
    v.push_back(4);
    v.push_back(4);
    v.push_back(4);
    v.push_back(4);
    v.push_back(4);
    v.push_back(4);
    v.clear();
    v.shrink_to_fit();
    v.push_back(4);
}
