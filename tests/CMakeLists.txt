file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true ./DocTest/**.h ./DocTest/**.cpp ./DocTest/*.h ./Doctest/*.cpp)

add_executable(tests_run ${SOURCES})
target_link_libraries(tests_run SimpleGameEngineLib)