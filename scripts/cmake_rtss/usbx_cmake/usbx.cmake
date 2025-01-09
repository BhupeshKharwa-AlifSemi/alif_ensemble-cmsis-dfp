# Setting path for USBX repo
if (REPO_SRC STREQUAL ALIF_GIT)
    set (USBX_DIR                   "${SRC_DIRECTORY}/AzureRTOS_usbx")
    set (USBX_COMMON_DIR            "${USBX_DIR}/common")
    set (USBX_CORE_DIR              "${USBX_COMMON_DIR}/core")
    set (USBX_PORTS_M55             "${USBX_DIR}/ports/cortex_m55")
    set (USBX_DEV_CLASS             "${USBX_COMMON_DIR}/usbx_device_classes")
    set (USBX_PORTS_M55_INC         "${USBX_DIR}/ports/cortex_m55/gnu/inc")

elseif (REPO_SRC STREQUAL PACK)
    set (USBX_DIR                   "${AZURERTOS_PACK_DIR}/USBX")
    set (USBX_CORE_DIR              "${USBX_DIR}/core")
    set (USBX_PORTS_M55             "${USBX_DIR}/ports/cortex_m55")
    set (USBX_DEV_CLASS             "${USBX_DIR}/usbx_device_classes")
    set (DEV_CLASS_DRIVER_DIR       "${USBX_DIR}/device_class_driver")
    set (USBX_PORTS_M55_INC "${USBX_DIR}/ports/cortex_m55/ac6/inc")
    file(GLOB       DEV_CLASS_DRIVER_SRC   "${DEV_CLASS_DRIVER_DIR}/*.c")

    include_directories(${DEV_CLASS_DRIVER_DIR})

elseif (REPO_SRC STREQUAL GITHUB)
    message(FATAL_ERROR     "${Red} Git hub support is not added...\n${ColourReset}")

endif()

include_directories ( "${USBX_CORE_DIR}/inc;${USBX_PORTS_M55_INC};"
                      "${USBX_DEV_CLASS}/inc;${USBX_DEV_CLASS};")

file(GLOB       USBX_CORE_SRC   "${USBX_CORE_DIR}/src/*.c")
file(GLOB       USBX_DEV_SRC    "${USBX_DEV_CLASS}/src/*.c"     ${DEV_CLASS_DRIVER_SRC})
list(FILTER     USBX_DEV_SRC    EXCLUDE REGEX     ".*_cdc_ecm_*")
list(FILTER     USBX_DEV_SRC    EXCLUDE REGEX     ".*_rndis_*")
file(GLOB       USBX_SRC        ${USBX_CORE_SRC}    ${USBX_DEV_SRC})

# Creating a Library file for USBX_SRC
set (USBX_LIB     "USBX")
add_library (${USBX_LIB}    STATIC      ${USBX_SRC})