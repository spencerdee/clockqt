rm -rf build
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_FLAGS="-lstdc++fs" -DCMAKE_CXX_FLAGS="-std=c++17" -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH="/usr/bin/gcc" -DCMAKE_CXX_COMPILER:FILEPATH="/usr/bin/g++" --no-warn-unused-cli -sc /home/pi/Desktop/Clock/clockqt -B /home/pi/Desktop/Clock/clockqt/build
cmake --build /home/pi/Desktop/Clock/clockqt/build --config Debug --target all
