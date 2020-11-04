cmake_minimum_required(VERSION 3.0)
project(LIBJOVE CXX)

if(QCHEM_SOURCE_DIR)
else(QCHEM_SOURCE_DIR)
        find_package(Armadillo REQUIRED)
        include_directories(${ARMADILLO_INCLUDE_DIRS})
endif(QCHEM_SOURCE_DIR)

find_package(Doxygen 1.8)

option(LIBJOVE_TESTS "Build libjove tests" ON)
add_subdirectory(libjove)

if(LIBJOVE_TESTS)
        add_subdirectory(tests)
endif(LIBJOVE_TESTS)

if(DOXYGEN_FOUND)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in"
        "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" @ONLY)
    add_custom_target(jove_docs
        "${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Doxygen documentation" VERBATIM)
endif(DOXYGEN_FOUND)

