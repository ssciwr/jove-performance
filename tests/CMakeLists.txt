
set(SRC_MP
    mp/do_mp2_test.C
)

set(HDR_MP
    mp/do_mp2_test.h
)
set(SRC
    ${SRC_MP}
    libjove_tests.C
)

set(HDR
    ${HDR_MP}
)

set(TARGETS
    libjove_tests
)

add_library(jove_tests ${SRC} ${HDR})
add_executable(libjove_tests ${SRC} ${HDR})

foreach(TARGET ${TARGETS})
        target_link_libraries(${TARGET} jove_tests jove ${ARMADILLO_LIBRARIES})
endforeach(TARGET)
install(TARGETS libjove_tests DESTINATION "${CMAKE_SOURCE_DIR}/exe")


