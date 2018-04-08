cmake_minimum_required(VERSION 3.5)
project(UniversalCard)

set(CMAKE_BUILD_TYPE Release)
if("${DEGUG}" STREQUAL "ON")
    set(CMAKE_BUILD_TYPE Debug)
endif()

find_package(Doxygen REQUIRED dot)
if(DOXYGEN_FOUND)
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/doc)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_target(doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif()


file(GLOB SOURCE_FILES lib/*.cpp lib/*.h)

if("${WITH_TEST}" STREQUAL "ON")
    file(GLOB TEST_SOURCES test/*.h test/*.cpp ${SOURCE_FILES})
    add_executable(UnitTest ${TEST_SOURCES})
    target_include_directories(UnitTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(UnitTest gtest)
    target_link_libraries(UnitTest pthread)
    add_test(UnitTest UnitTest)
endif()