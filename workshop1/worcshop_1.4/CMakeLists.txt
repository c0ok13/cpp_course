add_executable(worcshop_1.4 main.cpp)

target_include_directories(worcshop_1.4 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(worcshop_1.4 PUBLIC cxx_std_17)
target_compile_definitions(worcshop_1.4 PRIVATE SFML_STATIC)

target_link_libraries(worcshop_1.4 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})