# Bare-Metal related files and directories
if (REPO_SRC STREQUAL ALIF_GIT)
    set (BARE_METAL_APP_DIR         "${SRC_DIRECTORY}/bolt_apps/Baremetal")
    set (COMMON_INC_PATH            "${SRC_DIRECTORY}/bolt_apps/common/inc"
                                    "${BARE_METAL_APP_DIR}/FatFS"
                                    "${BARE_METAL_APP_DIR}/Include")
    set (OSPI_XIP                   "${BARE_METAL_APP_DIR}/ospi_xip")

elseif (REPO_SRC STREQUAL PACK)
    set (BARE_METAL_APP_DIR         "${ENSEMBLE_PACK_DIR}/Boards/${BOARD_NAME}/Templates/Baremetal")
    set (COMMON_INC_PATH            "${ENSEMBLE_PACK_DIR}/Boards/${BOARD_NAME}/Templates/bayer2rgb"
                                    "${ENSEMBLE_PACK_DIR}/Boards/${BOARD_NAME}/Templates/Common/Include"
                                    "${BARE_METAL_APP_DIR}/FatFS")
    set (OSPI_XIP                   "${ENSEMBLE_PACK_DIR}/ospi_xip")

elseif (REPO_SRC STREQUAL GITHUB)
    message(FATAL_ERROR             "${Red} Git hub support is not added...\n${ColourReset}")

endif()

include_directories ("${BARE_METAL_APP_DIR}/Include;${COMMON_INC_PATH};${OSPI_XIP}")

# Collection all Test Applications wrt to Free-RTOS under one variable
file (GLOB TEST_APP_SRCS    "${BARE_METAL_APP_DIR}/*.c")

file(GLOB_RECURSE      APP_DEP_FILES        "${BARE_METAL_APP_DIR}/FatFS/*.c"
                                            "${BARE_METAL_APP_DIR}/DPHY_Loopback_test.c")

# Removing LGVL files from test app source file list
RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${BARE_METAL_APP_DIR}/LVGL_baremetal.c"    ON)
RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${BARE_METAL_APP_DIR}/lv_port_disp.c"      ON)

if (RTSS STREQUAL HP)
    RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${BARE_METAL_APP_DIR}/LPSPI_SPI_baremetal.c"   ON)
    RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${BARE_METAL_APP_DIR}/LPPDM_baremetal.c"       ON)
    RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${BARE_METAL_APP_DIR}/LPUART_Baremetal.c"      ON)
    RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${BARE_METAL_APP_DIR}/LPI2C_Baremetal.c"       ON)
endif ()

# Creating Library file for OS files
set (OS_LIB_FILE    "BAREMETAL")
add_library (${OS_LIB_FILE} STATIC ${APP_DEP_FILES})