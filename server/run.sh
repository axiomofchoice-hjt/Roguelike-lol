mkdir -p build
cd build
cmake .. "-DCMAKE_TOOLCHAIN_FILE=/home/ax/repos/vcpkg/scripts/buildsystems/vcpkg.cmake" && \
    make -j Roguelike-Server && \
    ./Roguelike-Server
