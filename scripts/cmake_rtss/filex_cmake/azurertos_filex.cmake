# Setting path for Filex repo
if (REPO_SRC STREQUAL ALIF_GIT)
    set (FILEX_DIR          "${SRC_DIRECTORY}/AzureRTOS_FileX")
    set (FILEX_COMMON_DIR   "${FILEX_DIR}/common")
    set (FILEX_PORTS_DIR    "${FILEX_DIR}/ports/cortex_m55/ac6/inc")

elseif (REPO_SRC STREQUAL PACK)
    set (FILEX_DIR          "${AZURERTOS_PACK_DIR}/FILEX")
    set (FILEX_COMMON_DIR   "${FILEX_DIR}")
    set (FILEX_PORTS_DIR    "${FILEX_DIR}/ports/cortex_m55/ac6/inc")

elseif (REPO_SRC STREQUAL GITHUB)
    message(FATAL_ERROR         "${Red} Git hub support is not added...\n${ColourReset}")

endif()

include_directories ("${FILEX_COMMON_DIR}/inc;${FILEX_PORTS_DIR};"
                     "${FILEX_COMMON_DIR}/driver;"
                     "${FILEX_COMMON_DIR}/driver/inc")

# Setting paths and source files for FILEX
file (GLOB  FILEX_COMMON_SRC    "${FILEX_COMMON_DIR}/src/*.c"
                                "${FILEX_COMMON_DIR}/driver/src/*.c")

# Collecting all netx related source files under one variable
file (GLOB FILEX_SRC    ${FILEX_COMMON_SRC})

# Creating a Library file for FILEX_SRC
set (FILEX_LIB     "FILEX")
add_library (${FILEX_LIB}   STATIC      ${FILEX_SRC})