set(SRC_DIGESTERS_COMMON
)

set(HDR_DIGESTERS_COMMON
)

set(SRC_GRID_COMMON
    grid/jove_grid.C
)

set(HDR_GRID_COMMON
    grid/jove_grid.h
)

set(SRC_INTEGRALS_COMMON
)

set(HDR_INTEGRALS_COMMON
)

set(SRC_LOADER_COMMON
    loader/loader_mp2_fromfile.C
)


set(HDR_LOADER_COMMON
    loader/loader_mp2_fromfile.h
)

set(SRC_MP_COMMON
    mp/do_mp2.C
)

set(HDR_MP_COMMON
    mp/do_mp2.h
)


set(SRC_UTILS_COMMON
    utils/3rd_party/gauss_legendre.c
    utils/pprinter.C
)

set(HDR_UTILS_COMMON
    utils/3rd_party/gauss_legendre.h
    utils/ttimer.h
    utils/pprinter.h
)

set(SRC_VAULTS_COMMON
    vaults/vault_mp2.C
)

set(HDR_VAULTS_COMMON
    vaults/vault_mp2.h
)


set(SRC_COMMON
        ${SRC_MP_COMMON}
        ${SRC_DIGESTERS_COMMON}
        ${SRC_GRID_COMMON}
        ${SRC_INTEGRALS_COMMON}
        ${SRC_LOADER_COMMON}
        ${SRC_UTILS_COMMON}
        ${SRC_VAULTS_COMMON}
    jove.C
)

set(HDR_COMMON
        ${HDR_MP_COMMON}
        ${HDR_DIGESTERS_COMMON}
        ${HDR_GRID_COMMON}
        ${HDR_INTEGRALS_COMMON}
        ${HDR_LOADER_COMMON}
        ${HDR_UTILS_COMMON}
        ${HDR_VAULTS_COMMON}
    jove.h
)

set(SRC_QCHEM
    digesters/dig_jove_vmul_cgto_multipole.C
    integrals/jove_vmul.C
    loader/loader_mp2_qchem.C
)

set (HDR_QCHEM
    digesters/dig_jove_vmul_cgto_multipole.h
    integrals/jove_vmul.h
    loader/loader_mp2_qchem.h
)

if(QCHEM_SOURCE_DIR)
    add_library(jove ${SRC_COMMON} ${SRC_QCHEM} ${HDR_COMMON} ${HDR_QCHEM})
    target_include_directories(jove PUBLIC "${LIBJOVE_SOURCE_DIR}")
    target_link_libraries(jove armadillo adcman_qchem libdftn qints grid) 
install(TARGETS jove DESTINATION lib)
else(QCHEM_SOURCE_DIR)
    add_library(jove ${SRC_COMMON} ${HDR_CMMON})
    target_include_directories(jove PUBLIC "${LIBJOVE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/eigen")
    target_compile_definitions(jove PUBLIC EIGEN_DONT_PARALLELIZE)
    target_link_libraries(jove ${ARMADILLO_LIBRARIES} OpenMP::OpenMP_CXX)
    install(TARGETS jove DESTINATION "${CMAKE_SOURCE_DIR}/exe")
endif(QCHEM_SOURCE_DIR)

