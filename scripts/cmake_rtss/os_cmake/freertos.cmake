
if (REPO_SRC STREQUAL ALIF_GIT)
    set (FREERTOS_DIR               "${SRC_DIRECTORY}/cmsis_freertos")
    set (FREERTOS_TESTAPP_SRC_DIR   "${SRC_DIRECTORY}/bolt_apps/FreeRTOS")
    set (COMMON_INC_PATH            "${SRC_DIRECTORY}/bolt_apps/common/inc")

elseif (REPO_SRC STREQUAL PACK)
    set (FREERTOS_DIR               "${CMSIS_FREERTOS_PATH}")
    set (FREERTOS_TESTAPP_SRC_DIR   "${ENSEMBLE_PACK_DIR}/Boards/${BOARD_NAME}/Templates/FreeRTOS")
    set (COMMON_INC_PATH            "${ENSEMBLE_PACK_DIR}/Boards/${BOARD_NAME}/Templates/bayer2rgb"
                                    "${ENSEMBLE_PACK_DIR}/Boards/${BOARD_NAME}/Templates/Common/Include")

elseif (REPO_SRC STREQUAL GITHUB)
    message(FATAL_ERROR         "${Red} Git hub support is not added...\n${ColourReset}")

endif()

# FreeRTOS OS related Directories and files
set (FREERTOS_CMSIS_DIR             "${FREERTOS_DIR}/CMSIS/RTOS2/FreeRTOS")
set (FREERTOS_SRC_DIR               "${FREERTOS_DIR}/Source")
set (FREERTOS_PORTABLE_DIR          "${FREERTOS_SRC_DIR}/portable/GCC/ARM_CM55_NTZ/non_secure")
set (FREE_RTOS_CONFIG_CHANGE        ON)

if( CMAKE_SYSTEM_PROCESSOR STREQUAL cortex-m55)
    set(FREERTOS_CONFIG_HEADER_PATH         "${FREERTOS_DIR}/Config/ARMCM")
else()
    message(FATAL_ERROR     "Selected Processor is not supported...\n${ColourReset}")
endif()

##################  Changes needed for Alif testapps ######################
if(${FREE_RTOS_CONFIG_CHANGE})

    set(FREE_RTOS_CONFIG_FILE       "${FREERTOS_CONFIG_HEADER_PATH}/FreeRTOSConfig.h")

    # Change FreeRTOS Config as per Alif's Board Need
    set(CHANGE_LOG      "${HCyan}CHANGING SOME OF THE PARAMETERS AS PER ALIF NEED ... \n${ColourReset}")
    SAVE_ORIG_FILE("${FREE_RTOS_CONFIG_FILE}"    nFileName   configChange)

    CHANGE_SPEC_MACRO_VAL("configTOTAL_HEAP_SIZE"  "size_t"   "4096"    "${FREE_RTOS_CONFIG_FILE}"
                    "#define configTOTAL_HEAP_SIZE                 ((size_t)65536)"   ret)

    if(${ret})
        set(CHANGE_MSG      "${CHANGE_MSG}     HEAP SIZE CHANGED FROM      4096 TO  65536 (configTOTAL_HEAP_SIZE)\n")
    endif()

    CHANGE_SPEC_MACRO_VAL("configMINIMAL_STACK_SIZE "  "uint16_t"   "256"    "${FREE_RTOS_CONFIG_FILE}"
                    "#define configMINIMAL_STACK_SIZE              ((uint16_t)512)"   ret)

    if(${ret})
        set(CHANGE_MSG      "${CHANGE_MSG}     STACK SIZE CHANGED FROM      256 TO    512 (configMINIMAL_STACK_SIZE)\n")
    endif()

    CHANGE_MACRO_VAL("#define configUSE_TIMERS                      0"     "${FREE_RTOS_CONFIG_FILE}"  
        "#define configUSE_TIMERS                      1"  ret  ON)

    if(${ret})
        set(CHANGE_MSG      "${CHANGE_MSG}     TIMERS ENABLE/DISABLE          0 TO      1 (configUSE_TIMERS)\n")
    endif()

    CHECK_DEF ("define configENABLE_MVE                      0" "${FREE_RTOS_CONFIG_FILE}" ret)
    if( NOT ret)
        CHANGE_MACRO_VAL("#define configENABLE_FPU                      1"    "${FREE_RTOS_CONFIG_FILE}"
                "#define configENABLE_FPU                      1\\n#define configENABLE_MVE                      0"
                ret  ON)
    endif()

    if(${ret})
        set(CHANGE_MSG      "${CHANGE_MSG}     MVE ENABLE/DISABLE             0 TO      1 (configENABLE_MVE)\n")
    endif()

    CHANGE_MACRO_VAL("#define configENABLE_TRUSTZONE                1"     "${FREE_RTOS_CONFIG_FILE}"  
            "#define configENABLE_TRUSTZONE                0"   ret  ON)

    if(${ret})
        set(CHANGE_MSG      "${CHANGE_MSG}     TRUSTZONE ENABLE/DISABLE       0 TO      1 (configENABLE_TRUSTZONE)\n")
    endif()

    CHANGE_SPEC_MACRO_VAL("configMINIMAL_SECURE_STACK_SIZE "  "uint32_t"   "1024"    "${FREE_RTOS_CONFIG_FILE}"
                    "#define configMINIMAL_SECURE_STACK_SIZE       ((uint32_t)512)"   ret)

    if(${ret})
        set(CHANGE_MSG      "${CHANGE_MSG}     SECURE_STACK_SIZE           1024 TO    512 (configMINIMAL_SECURE_STACK_SIZE)\n")
    endif()

    CHANGE_MACRO_VAL("#define configRUN_FREERTOS_SECURE_ONLY        0"     "${FREE_RTOS_CONFIG_FILE}"  
            "#define configRUN_FREERTOS_SECURE_ONLY        1"   ret  ON)

    if(${ret})
        set(CHANGE_MSG      "${CHANGE_MSG}     SECURE ENABLE/DISABLE          0 TO      1 (configRUN_FREERTOS_SECURE_ONLY)\n")
    endif()

    CHANGE_MACRO_VAL("#define INCLUDE_vTaskDelayUntil               1"     "${FREE_RTOS_CONFIG_FILE}"  
            "#define INCLUDE_xTaskDelayUntil               1"   ret  ON)

    if(${ret})
        set(CHANGE_MSG      "${CHANGE_MSG}     \"vTaskDelayUntil\" CHANGED TO \"INCLUDE_xTaskDelayUntil\"")
    endif()

    set(CHANGE_MSG_FILENAME         "${FREERTOS_CONFIG_HEADER_PATH}/changes.txt")

    if(${configChange})
        file(WRITE      "${CHANGE_MSG_FILENAME}"    ${CHANGE_MSG})
    else()
        file(READ       "${CHANGE_MSG_FILENAME}"       CHANGE_MSG)
    endif()
endif()
#########################################################################################################

file (GLOB FREERTOS_SRC             "${FREERTOS_SRC_DIR}/*.c")
file (GLOB FREERTOS_PORTABLE_SRC    "${FREERTOS_PORTABLE_DIR}/*.c")
file (GLOB FREERTOS_MEMMANG_SRC     "${FREERTOS_SRC_DIR}/portable/MemMang/heap_4.c")

# Including related header files to the project
set(FREE_RTOS_INC   "${FREERTOS_TESTAPP_SRC_DIR}/Config;        \
                     ${FREERTOS_SRC_DIR}/include;               \
                     ${FREERTOS_PORTABLE_DIR};                  \
                     ${FREERTOS_CONFIG_HEADER_PATH};            \
                     ${FREERTOS_CMSIS_DIR}/Include;             \
                     ${COMMON_INC_PATH}")

include_directories (${FREE_RTOS_INC})

# Collecting all OS related files under one variable name
file (GLOB OS_C_SRC ${FREERTOS_SRC} ${FREERTOS_PORTABLE_SRC} ${FREERTOS_MEMMANG_SRC})

# Collection all Test Applications wrt to Free-RTOS under one variable
file (GLOB_RECURSE  TEST_APP_SRCS   "${FREERTOS_TESTAPP_SRC_DIR}/*.c")

if (RTSS STREQUAL HP)
    RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${FREERTOS_TESTAPP_SRC_DIR}/LPSPI_SPI_app.c"     ON)
    RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${FREERTOS_TESTAPP_SRC_DIR}/LPPDM_testApp.c"     ON)
    RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${FREERTOS_TESTAPP_SRC_DIR}/LPUART_testapp.c"    ON)
    RM_ENTRY(TEST_APP_SRCS      RM_TEST_APPS_LIST   "${FREERTOS_TESTAPP_SRC_DIR}/CMP_testApp.c"       ON)
endif()

# Creating Library file for OS files
set (OS_LIB_FILE    "FREERTOS")
add_library (${OS_LIB_FILE} STATIC ${OS_C_SRC})