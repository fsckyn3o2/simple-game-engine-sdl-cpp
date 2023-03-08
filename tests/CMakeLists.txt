file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true ./DocTes/*.h ./DocTest/*.cpp)
set(SOURCES ${SOURCES})

add_executable(tests_run ${SOURCES})
target_link_libraries(tests_run SimpleGameEngineLib)