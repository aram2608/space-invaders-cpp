export VCPKG_ROOT=~/dev/tools/vcpkg
cmake -B bin -S src -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build bin