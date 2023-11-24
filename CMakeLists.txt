


cmake_minimum_required(VERSION 3.21)
project(Plutonium)


set (CMAKE_CXX_STANDARD 20)


include_directories(lib/include)
include_directories(lib-3rd-party/stb_image)


add_library(PlutoniumCore SHARED
    lib/src/Color.cpp
    lib/src/PixelBuffer.cpp
    lib/src/Vector3.cpp
)


add_executable(Plutonium
    app/main.cpp)

    
target_link_libraries(Plutonium
    PlutoniumCore)
