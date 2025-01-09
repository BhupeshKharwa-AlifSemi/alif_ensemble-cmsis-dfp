# Threadx OS related files
if (REPO_SRC STREQUAL ALIF_GIT)
    set (THREADX_DIR                "${SRC_DIRECTORY}/threadx")
    set (THREADX_COMMON             "${THREADX_DIR}/common")
    set (THREADX_TESTAPP_PATH       "${SRC_DIRECTORY}/bolt_apps/Threadx")
    set (THREADX_TESTAPP_SRC_DIR    "${SRC_DIRECTORY}/bolt_apps/Threadx/**")
    set (THREADX_MODEM_SRC_DIR      "${SRC_DIRECTORY}/bolt_apps/Threadx/MODEM_SS")
    set (THREADX_NETX_TESTAPP_DIR   "${SRC_DIRECTORY}/RTOS_networking/netxduo/ethernet/apps")
    set (THREADX_BAYER2RGB_DIR      "${THREADX_TESTAPP_PATH}/Camera/bayer2rgb")
    set (THREADX_MIPI_IMG_PROC_DIR  "${THREADX_TESTAPP_PATH}/MIPI/image_processing")
    set (THREADX_MIPI_DIR           "${THREADX_TESTAPP_PATH}/MIPI")
    set (THREADX_SPI_TESTAPP_DIR    "${THREADX_TESTAPP_PATH}/SPI")
    set (THREADX_UART_TESTAPP_DIR   "${THREADX_TESTAPP_PATH}/UART")
    set (THREADX_PDM_TESTAPP_DIR    "${THREADX_TESTAPP_PATH}/PDM")
    set (THREADX_ACOMP_TESTAPP_DIR  "${THREADX_TESTAPP_PATH}/Analog_Comparator")
    set (COMMON_INC_PATH            "${SRC_DIRECTORY}/bolt_apps/common/inc")

    # Based on the compiler, collecting the Port source files
    if (COMPILER STREQUAL ARMCLANG)
        set (THREADX_PORTS_DIR      "${THREADX_DIR}/ports/cortex_m55/ac6")
    elseif (COMPILER STREQUAL GCC)
        set (THREADX_PORTS_DIR      "${THREADX_DIR}/ports/cortex_m55/gnu")
    endif ()

elseif (REPO_SRC STREQUAL PACK)
    set (THREADX_DIR                "${AZURERTOS_PACK_DIR}/THREADX")
    set (THREADX_COMMON             "${THREADX_DIR}/common")
    set (THREADX_TESTAPP_SRC_DIR    "${THREADX_DIR}/samples")
    set (THREADX_MODEM_SRC_DIR      "${THREADX_TESTAPP_SRC_DIR}/MODEM_SS")
    set (THREADX_BAYER2RGB_DIR      "${THREADX_TESTAPP_SRC_DIR}")
    set (THREADX_MIPI_IMG_PROC_DIR  "${THREADX_TESTAPP_SRC_DIR}")
    set (THREADX_MIPI_DIR           "${THREADX_TESTAPP_SRC_DIR}")
    set (THREADX_SPI_TESTAPP_DIR    "${THREADX_TESTAPP_SRC_DIR}")
    set (THREADX_UART_TESTAPP_DIR   "${THREADX_TESTAPP_SRC_DIR}")
    set (THREADX_PDM_TESTAPP_DIR    "${THREADX_TESTAPP_SRC_DIR}")
    set (THREADX_ACOMP_TESTAPP_DIR  "${THREADX_TESTAPP_SRC_DIR}")
    set (THREADX_NETX_TESTAPP_DIR   "${AZURERTOS_PACK_DIR}/NETX/sample/*.c")
    set (THREADX_USBX_TESTAPPS      "${AZURERTOS_PACK_DIR}/USBX/samples/*.c")
    set (THREADX_FILEX_TESTAPPS     "${AZURERTOS_PACK_DIR}/FILEX/samples/*.c")
    set (COMMON_INC_PATH            "${THREADX_TESTAPP_SRC_DIR}")

    set (THREADX_PORTS_DIR          "${THREADX_DIR}/ports/cortex_m55/ac6")

elseif (REPO_SRC STREQUAL GITHUB)
    message(FATAL_ERROR         "${Red} Git hub support is not added...\n${ColourReset}")

endif()

# Directories to include from AZURE RTOS
include_directories ("${THREADX_COMMON}/inc;${THREADX_PORTS_DIR}/inc;"
                     "${THREADX_TESTAPP_SRC_DIR}/Include;"
                     "${COMMON_INC_PATH}")

# Source Files from AZURE RTOS
file (GLOB      OS_S_SRC        "${THREADX_PORTS_DIR}/src/*.S"
                                "${THREADX_COMMON}/src/*.c"
                                "${THREADX_PORTS_DIR}/src/*.c")

# Test application source file and dependency files for RTOS Networking
if (netxduo_ret AND filex_ret)
    file(GLOB_RECURSE   RTOS_NW_APP      "${THREADX_NETX_TESTAPP_DIR}")
endif ()

file(GLOB_RECURSE      TEST_APP_SRCS           "${THREADX_TESTAPP_SRC_DIR}/*.c"
                                               "${RTOS_NW_APP}"
                                               "${THREADX_USBX_TESTAPPS}"
                                               "${THREADX_FILEX_TESTAPPS}")
file(GLOB_RECURSE      MDM_TEST_APP_FILES      "${THREADX_MODEM_SRC_DIR}/*.c")
file(GLOB_RECURSE      APP_DEP_FILES           "${THREADX_BAYER2RGB_DIR}/bayer.c"
                                               "${THREADX_BAYER2RGB_DIR}/bayer2rgb.c"
                                               "${THREADX_MIPI_IMG_PROC_DIR}/image_processing.c")

set(NEED_TO_RM_FILES    "${MDM_TEST_APP_FILES};${APP_DEP_FILES}")

foreach (curr_rm_fileName     ${NEED_TO_RM_FILES})
    RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${curr_rm_fileName}"   OFF)
endforeach ()

if (RTSS STREQUAL HP)
    RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${THREADX_SPI_TESTAPP_DIR}/LPSPI_SPI_testapp.c"    ON)
    RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${THREADX_PDM_TESTAPP_DIR}/LPPDM_testApp.c"        ON)
    RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${THREADX_UART_TESTAPP_DIR}/LPUART_testApp.c"      ON)
    RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${THREADX_ACOMP_TESTAPP_DIR}/CMP_testapp.c"        ON)
endif ()

RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${THREADX_MIPI_DIR}/MIPI_Interface_Video_testApp.c"    ON)

set(THREADX_SRC             "${OS_C_SRC};${OS_S_SRC};${APP_DEP_FILES}")

# Creating Library file for OS files
set (OS_LIB_FILE    "THREADX")
add_library (${OS_LIB_FILE} STATIC ${THREADX_SRC})