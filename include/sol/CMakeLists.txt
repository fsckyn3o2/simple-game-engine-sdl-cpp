
message("INCLUDE / SOL : ")
message("   - SOL BINARY : ${PROJECT_BINARY_DIR}")
message("   - SOL SOURCE CODE : ${CMAKE_CURRENT_SOURCE_DIR}\n")

add_library(sol ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(sol PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(sol INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(sol PROPERTIES IMPORTED_LOCATION ${PROJECT_BINARY_DIR}/include/libsol.so)