# Basic Input check Starts -------------------------------
if (DEV_FAMILY STREQUAL "E")
    set (RTE_COMP_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/../Include_RTE_Comp/ensemble")
else ()
    message (FATAL_ERROR "${Red}\n SELECT PROPER DEVICE FAMILY (Please run ./run.sh to see options) \n${ColourReset}")
endif ()

if (NOT( (BOOT STREQUAL TCM) OR (BOOT STREQUAL MRAM)))
    message(FATAL_ERROR  "${Red}\n BOOT MODE IS NOT GIVEN OR \"${BOOT}\" BOOT IS INVALID BOOT MODE ... !!!\n${ColourReset}")
endif ()

if ((${DEVICE_SERIES} STREQUAL "E1" ) AND (${RTSS} STREQUAL HP))
    message(FATAL_ERROR  "${Red}\n ${DEVICE_SERIES}-SERIES (DEVICE : ${DEVICE}) DOESN'T HAVE ${RTSS} SUB-SYSTEM \n"
         " (Please run \"setup_user_env.sh\" to see device options) ... !!!\n${ColourReset}")
endif ()

# Basic Input check Ends -------------------------------

# Assigning RTE components header file to a variable
include_directories (${RTE_COMP_DIR})
file (GLOB RTE_COMPONENTS_FILE  "${RTE_COMP_DIR}/RTE_Components.h")
file (STRINGS ${RTE_COMPONENTS_FILE}  RTEcomponentFile)

set (DEVICE_CORE_PATH           "${DEVICE_PATH}/core/${PROC}")
set (SCRIPT_NAME                "${PROC}")

if (${EXT_DEVICE_SERIES} STREQUAL "E1C" )
    set (DEVICE_CORE_PATH       "${DEVICE_CORE_PATH}_${EXT_DEVICE_SERIES}")
endif()

if(BOOT STREQUAL TCM)
    set (SCRIPT_NAME            "${PROC}_TCM")
endif()

# Binary Directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY          ${CMAKE_BINARY_DIR}/exec)

# Path for RTEDevice.h
set (DEVICE_ROOT     "${DEVICE_PATH}/${DEVICE_SERIES}/${EXT_DEVICE_SERIES}")

if (NOT (EXISTS "${DEVICE_ROOT}"))
    message(FATAL_ERROR  "${Red}\n LINKER SCRIPT for ${DEVICE} ( ${DEVICE_ROOT} ) DOESN'T EXIST \n"
         " (Please run \"setup_user_env.sh\" to see device options) ... !!!\n${ColourReset}")
endif()

# Setting paths for Device directories
set (DEVICE_COMMON_SRC_DIR      "${DEVICE_PATH}/common/source")
set (DEVICE_COMMON_SRC          "${DEVICE_PATH}/core/common/source")
set (DEVICE_COMMON_INC          "${DEVICE_PATH}/common/include")
set (DEVICE_COMMON_CFG          "${DEVICE_PATH}/common/config")
set (DEVICE_CORE_SRC_DIR        "${DEVICE_CORE_PATH}/source")
set (DEVICE_CORE_CONFIG_DIR     "${DEVICE_CORE_PATH}/config")
set (DEVICE_CORE_INC_DIR        "${DEVICE_CORE_PATH}/include")
set (OUTPUT_DIR                 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} CACHE INTERNAL "")
if (PROC STREQUAL M55_HP)
    set (SUBSYSTEM_SRC_DIR        "${DEVICE_PATH}/core/rtss_hp/e7/AE722F80F55D5/source")
else ()
    set (SUBSYSTEM_SRC_DIR        "${DEVICE_PATH}/core/rtss_he/e7/AE722F80F55D5/source")
endif ()
set (SOC_SRC_DIR                "${DEVICE_PATH}/soc/e7/AE722F80F55D5/source")
# Collecting Source files
file (GLOB DEVICE_SRC   "${DEVICE_COMMON_SRC}/*.c" "${DEVICE_COMMON_SRC_DIR}/*.c" "${DEVICE_CORE_SRC_DIR}/*.c"
                        "${SUBSYSTEM_SRC_DIR}/*.c" "${SOC_SRC_DIR}/*.c")
include_directories (${DEVICE_ROOT})
include_directories (${DEVICE_COMMON_INC})
include_directories (${DEVICE_CORE_CONFIG_DIR})
include_directories ("${DEVICE_PATH}/soc/e7/AE722F80F55D5/include")
include_directories ("${DEVICE_PATH}/core/common/config/")
include_directories ("${DEVICE_PATH}/core/common/include/")
if (PROC STREQUAL M55_HP)
    include_directories ("${DEVICE_PATH}/core/rtss_hp/e7/AE722F80F55D5/include")
    include_directories ("${DEVICE_PATH}/core/rtss_hp/include/m55")
    include_directories ("${DEVICE_PATH}/core/rtss_hp/config")
else ()
    include_directories ("${DEVICE_PATH}/core/rtss_he/e7/AE722F80F55D5/include")
    include_directories ("${DEVICE_PATH}/core/rtss_he/include/m55")
    include_directories ("${DEVICE_PATH}/core/rtss_he/config")
endif ()
include_directories (${DEVICE_CORE_INC_DIR})
include_directories (${DEVICE_COMMON_CFG})

# Linker File Details
if (COMPILER STREQUAL ARMCLANG)
    set (SCRIPT_DIR                 "${DEVICE_ROOT}/linker_script/ARM")
    set (LINKER_SCRIPT_FILE         ${SCRIPT_DIR}/${SCRIPT_NAME}.sct)
    set (CMAKE_LINKER_SCRIPT        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${SCRIPT_NAME}.sct)

elseif ( (COMPILER STREQUAL GCC) OR (COMPILER STREQUAL CLANG) )
    set (SCRIPT_DIR                     "${DEVICE_ROOT}/linker_script/GCC")
    #string(TOLOWER      ${COMPILER}     COMP)
    set (LINKER_SCRIPT_FILE             ${SCRIPT_DIR}/gcc_${SCRIPT_NAME}.ld)
    set (CMAKE_LINKER_SCRIPT            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/gcc_${SCRIPT_NAME}.ld)

else ()
    message(FATAL_ERROR  "${Red}INVALID COMPILER ... !!!${ColourReset}")

endif ()

set (LINKER_INC_PATH       "-I${DEVICE_CORE_INC_DIR} -I${DEVICE_COMMON_INC} -I${DEVICE_COMMON_CFG}")
set (LINKER_CMD            "#! armclang -E --target=arm-arm-none-eabi -mcpu=cortex-m55 -xc")
file(READ       ${LINKER_SCRIPT_FILE}       LINKER_CONTENT)
string(REPLACE  "${LINKER_CMD}"     "${LINKER_CMD}  ${LINKER_INC_PATH}"     MODIFIED_LINKER_CONTENT     "${LINKER_CONTENT}")
file(WRITE      ${CMAKE_LINKER_SCRIPT}      "${MODIFIED_LINKER_CONTENT}")

set (DEVICE_LIB     "DEVICE")
add_library (${DEVICE_LIB} STATIC ${DEVICE_SRC})
