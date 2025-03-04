# Basic Input check Starts -------------------------------
if (DEV_FAMILY STREQUAL "E")
    set (RTE_COMP_DIR   "${CMAKE_SOURCE_DIR}/Include_RTE_Comp/ensemble")
else ()
    message (FATAL_ERROR "${Red}\n Unknown Device Family \n${ColourReset}")
endif ()

if(EXISTS "${RTE_COMP_DIR}/RTE_Components.h")
    file (GLOB RTE_COMPONENTS_FILE  "${RTE_COMP_DIR}/RTE_Components.h")
    file (STRINGS ${RTE_COMPONENTS_FILE}  RTEcomponentFile)
else ()
    message (FATAL_ERROR "${Red}\n RTE_Components.h is missing \n${ColourReset}")
endif ()

if (NOT( (BOOT STREQUAL TCM) OR (BOOT STREQUAL MRAM)))
    message(FATAL_ERROR  "${Red}\n BOOT MODE IS NOT GIVEN OR \"${BOOT}\" BOOT IS INVALID BOOT MODE ... !!!\n${ColourReset}")
endif ()

if ((${DEVICE_SERIES} STREQUAL "E1" ) AND (${RTSS} STREQUAL HP))
    message(FATAL_ERROR  "${Red}\n ${DEVICE_SERIES}-SERIES (DEVICE : ${DEVICE}) DOESN'T HAVE ${RTSS} SUB-SYSTEM \n"
         " (Please run \"setup_user_env.sh\" to see device options) ... !!!\n${ColourReset}")
endif ()

# Linker File Details
if (COMPILER STREQUAL ARMCLANG)
    set(COMPILER_LINKER_SPEC_NAME      "ac6")
    set(COMPILER_LINKER_FILE_EXT       "sct")

elseif ( (COMPILER STREQUAL GCC) OR (COMPILER STREQUAL CLANG) )
    set(COMPILER_LINKER_SPEC_NAME      "gnu")
    set(COMPILER_LINKER_FILE_EXT       "ld.src")

else ()
    message(FATAL_ERROR  "${Red}INVALID COMPILER ... !!!${ColourReset}")

endif ()
# Basic Input check Ends ---------------------------------

string(TOLOWER          ${RTSS}             rtss)
string(TOLOWER          ${BOOT}             boot)
set(RTSS_SPECIFIC_DIR   "rtss_${rtss}")

set (DEVICE_CORE_PATH                       "${DEVICE_PATH}/core/${RTSS_SPECIFIC_DIR}")

# Binary Directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY          ${CMAKE_BINARY_DIR}/exec)

# Setting paths for Device directories
set (DEVICE_SKU_DIR             "${DEVICE_PATH}/soc/${DEVICE_PART_NUMBER}")
set (DEVICE_COMMON_SRC          "${DEVICE_PATH}/core/common/source")
set (DEVICE_COMMON_INC          "${DEVICE_PATH}/core/common/include")
set (DEVICE_CORE_CONFIG_DIR     "${DEVICE_CORE_PATH}/config")
set (DEVICE_SYSTEM_INC          "${DEVICE_PATH}/system/include")
set (DEVICE_SYSTEM_SRC          "${DEVICE_PATH}/system/source")
set (DEVICE_SKU_CONFIG          "${DEVICE_SKU_DIR}/config")
set (DEVICE_SKU_INC             "${DEVICE_SKU_DIR}/include/${rtss}")
set (SCRIPT_DIR                 "${DEVICE_CORE_PATH}/linker")
set (OUTPUT_DIR                 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} CACHE INTERNAL "")
set (DEVICE_INC                 "${DEVICE_COMMON_INC};${DEVICE_CORE_CONFIG_DIR};${DEVICE_SYSTEM_INC};"
                                "${DEVICE_SKU_DIR}/include/;${DEVICE_SKU_CONFIG};${DEVICE_SKU_INC}")
set (LINKER_FILENAME            "linker_${COMPILER_LINKER_SPEC_NAME}_${boot}.${COMPILER_LINKER_FILE_EXT}")
set (LINKER_SCRIPT_FILE         "${SCRIPT_DIR}/${LINKER_FILENAME}")
set (CMAKE_LINKER_SCRIPT        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${LINKER_FILENAME})
set (LINKER_INC_PATH            "-I${DEVICE_SKU_CONFIG}")
set (LINKER_CMD                 "#! armclang -E --target=arm-arm-none-eabi -mcpu=cortex-m55 -xc")

# Assigning RTE components header file to a variable
include_directories (${RTE_COMP_DIR})
include_directories (${DEVICE_INC})

# Collecting Source files
file (GLOB DEVICE_SRC           "${DEVICE_COMMON_SRC}/*.c" "${DEVICE_SYSTEM_SRC}/*.c")

file(READ       ${LINKER_SCRIPT_FILE}       LINKER_CONTENT)
string(REPLACE  "${LINKER_CMD}"     "${LINKER_CMD}  ${LINKER_INC_PATH}"     MODIFIED_LINKER_CONTENT     "${LINKER_CONTENT}")
file(WRITE      ${CMAKE_LINKER_SCRIPT}      "${MODIFIED_LINKER_CONTENT}")

set (DEVICE_LIB     "DEVICE")
add_library (${DEVICE_LIB} STATIC ${DEVICE_SRC})
