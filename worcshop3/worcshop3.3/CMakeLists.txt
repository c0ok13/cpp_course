add_executable(worcshop3.3 main.cpp)

target_include_directories(worcshop3.3 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(worcshop3.3 PUBLIC cxx_std_17)
target_compile_definitions(worcshop3.3 PRIVATE SFML_STATIC)

target_link_libraries(worcshop3.3 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})