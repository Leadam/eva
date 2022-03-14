project(ImageTest)

include_directories(../../src)

file(GLOB SORUCE *.cpp)

add_executable(${PROJECT_NAME} ${SORUCE})

target_link_libraries(${PROJECT_NAME}
        GTest::gtest
        GTest::gtest_main
        )

