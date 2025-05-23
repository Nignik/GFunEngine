file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_executable(GFunEngine ${SOURCES} ${HEADERS})

find_package(HECS)
find_package(imgui CONFIG REQUIRED)
find_package(glad REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_package(Vulkan REQUIRED)
find_package(SDL3 CONFIG REQUIRED)

target_link_libraries(GFunEngine PRIVATE HECS::HECS Freetype::Freetype SDL3::SDL3 imgui::imgui glm::glm Vulkan::Vulkan)

add_custom_target(compile_shader
        COMMAND glslc ../shaders/vertex/first_triangle.vert -o ../shaders/vertex/vert.spv
        COMMENT "Compiling shader: first_triangle.vert"
)