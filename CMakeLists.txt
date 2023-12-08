


cmake_minimum_required(VERSION 3.21)
project(Plutonium)


set (CMAKE_CXX_STANDARD 20)


include_directories(lib/include/Core)
include_directories(lib/include/Core/Mesh)
include_directories(lib/include/Renderer)
include_directories(lib/include/Scene)
include_directories(lib/include/Utility)
include_directories(lib-3rd-party/stb_image)


add_library(PlutoniumCore SHARED

    lib/src/Core/Mesh/HalfEdgeMesh.cpp
    lib/src/Core/Mesh/IndexedTriangleMesh.cpp
    lib/src/Core/Mesh/TriangleFanMesh.cpp
    lib/src/Core/Mesh/TriangleStripMesh.cpp

    lib/src/Core/Color.cpp
    lib/src/Core/Matrix4.cpp
    lib/src/Core/PixelBuffer.cpp
    lib/src/Core/Ray.cpp
    lib/src/Core/Transform.cpp
    lib/src/Core/Vector3.cpp
    lib/src/Core/Vector4.cpp

    lib/src/Renderer/Renderer.cpp

    lib/src/Scene/Materials/Lambert.cpp
    lib/src/Scene/Materials/Metal.cpp
    lib/src/Scene/Materials/Dielectric.cpp

    lib/src/Scene/Shapes/BVHNode.cpp
    lib/src/Scene/Shapes/MeshRef.cpp
    lib/src/Scene/Shapes/Rectangle.cpp
    lib/src/Scene/Shapes/ShapeGroup.cpp
    lib/src/Scene/Shapes/ShapeInstance.cpp
    lib/src/Scene/Shapes/Sphere.cpp
    lib/src/Scene/Shapes/Triangle.cpp

    lib/src/Scene/BoundingBox.cpp
    lib/src/Scene/Camera.cpp
    lib/src/Scene/Scene.cpp

    lib/src/Utility/Utility.cpp
)


add_executable(Plutonium
    app/main.cpp)

    
target_link_libraries(Plutonium
    PlutoniumCore)
