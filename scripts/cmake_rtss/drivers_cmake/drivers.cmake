# Setting path variables for Alif CMSIS directory
set (ALIF_CMSIS_DIR         "${ENSEMBLE_PACK_DIR}/Alif_CMSIS")
set (ALIF_CMSIS_SRC_DIR     "${ALIF_CMSIS_DIR}/Source")
set (DRIVERS_INC            "${ALIF_CMSIS_SRC_DIR};${ALIF_CMSIS_DIR}/Include;\
                             ${ALIF_CMSIS_DIR}/Include/config;\
                             ${ENSEMBLE_PACK_DIR}/components/Include")

include_directories (${DRIVERS_INC})

file (GLOB_RECURSE  ALIF_CMSIS_SRC  "${ALIF_CMSIS_SRC_DIR}/*.c"     "${ENSEMBLE_PACK_DIR}/components/Source/*.c")

# Setting variables for Drivers
set (DRIVERS_DIR        "${ENSEMBLE_PACK_DIR}/drivers")
file (GLOB DRIVER_SRC   "${DRIVERS_DIR}/source/*.c")
include_directories (${DRIVERS_DIR}/include)

# Setting variables for OSPI drivers
set (OSPI_XIP_DIR       "${ENSEMBLE_PACK_DIR}/ospi_xip")
set (OSPI_APP_DIR       "${OSPI_XIP_DIR}/app")
set (OSPI_SRC_DIR       "${OSPI_XIP_DIR}/source")

set (OSPI_INC
    ${OSPI_SRC_DIR}/issi_flash ${OSPI_SRC_DIR}/ospi
    ${OSPI_XIP_DIR}/include    ${OSPI_XIP_DIR}/config)
include_directories (${OSPI_INC})

file (GLOB ISSI_FLASH_SRC   "${OSPI_SRC_DIR}/issi_flash/*.c")
file (GLOB OSPI_SRC         "${OSPI_SRC_DIR}/ospi/*.c")
file (GLOB ISSI_FLASH_APP   "${OSPI_APP_DIR}/*.c")

if (NOT (OS STREQUAL CMSISRTOS))
    get_filename_component (tmp "${ALIF_CMSIS_SRC_DIR}/driver_mac.c" ABSOLUTE)
    list (REMOVE_ITEM ALIF_CMSIS_SRC "${tmp}")
endif()

# Collecting all the Driver source files in one variable
file (GLOB DRIVER_SRC_FILES ${ALIF_CMSIS_SRC} ${DRIVER_SRC} ${ISSI_FLASH_SRC} ${OSPI_SRC})

# Creating a Library file for Driver Source Files
set (DRIVER_LIB     "DRIVERS")
add_library (${DRIVER_LIB} STATIC ${DRIVER_SRC_FILES})