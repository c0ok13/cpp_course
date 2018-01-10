add_executable(10 main.cpp)

target_include_directories(10 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(10 PUBLIC cxx_std_17)
target_compile_definitions(10 PRIVATE SFML_STATIC)

target_link_libraries(10 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})