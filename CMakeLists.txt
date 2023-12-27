cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(game)

include_directories(headers include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_INCLUDE_DIR include)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
#find_package(PNG REQUIRED)
find_package(SFML 2 COMPONENTS audio window graphics system REQUIRED)

file(GLOB SRC "basicAnimation/*.cpp" "basicAnimation/*.h")
add_executable(game ${SRC}
        basicAnimation/CollisionableObject.h
        basicAnimation/CollisionObject.cpp
        basicAnimation/MovingObject.cpp
        basicAnimation/MovingObject.h
        basicAnimation/Car.h
        basicAnimation/Car.cpp
        basicAnimation/parkingLot.h
        basicAnimation/ParkingLot.cpp)
target_include_directories(game PRIVATE ${SFML_INCLUDE_DIR} ${JPEG_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS})
target_compile_features(game PUBLIC cxx_std_17)
target_compile_definitions(game PRIVATE SFML_STATIC)
target_link_libraries(game ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${JPEG_LIBRARIES} ${FREETYPE_LIBRARIES})