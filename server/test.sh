mkdir -p build
mkdir -p .report/test
cd build
cmake .. \
    "-DCMAKE_TOOLCHAIN_FILE=/home/ax/repos/vcpkg/scripts/buildsystems/vcpkg.cmake" && \
    make geo-test -j && \
    cd geo/test && \
    ctest && \
    cd /home/ax/repos/Roguelike-Server && \
    lcov -d . -t test -o .report/test/test.info -b build -c --no-external && \
    genhtml -o .report/test .report/test/test.info
