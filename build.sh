export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
export LDFLAGS="-L/opt/homebrew/opt/llvm/lib"
export CMAKE_PREFIX_PATH="/opt/homebrew/opt/llvm"
export CPPFLAGS="-I/opt/homebrew/opt/llvm/include"
CC=clang CXX=clang++ cmake -S . -B build -GNinja 
cmake --build build --parallel