#include <iostream>
#include <dlfcn.h>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cout << "Usage: " << argv[0] << " modules..." << endl;
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        void* shared_lib = dlopen(argv[i], RTLD_LAZY);
        void (*module)() = reinterpret_cast<void (*)()>(dlsym(shared_lib, "module"));
        if (module) {
            module();
            dlclose(shared_lib);
        } else {
            cout << "Error loading " << argv[i] << endl;
        }
    }
    return 0;
}
