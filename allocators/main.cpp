#include "allocator.h"

using value_type = unsigned int;
using array_vector_t = std::vector<value_type, ArrayAllocator<value_type>>;

int main() {
    ArrayAllocator<value_type> allocator(20);
    array_vector_t v{allocator};
    v.reserve(3);
    v.push_back(0xaaaaaaaa);
    v.push_back(0xbbbbbbbb);
    v.push_back(0xcccccccc);
    v.push_back(0xdddddddd);
    v.push_back(0xeeeeeeee);
    v.push_back(0xffffffff);
    v.clear();
    v.shrink_to_fit();
    v.push_back(0x11111111);
}
