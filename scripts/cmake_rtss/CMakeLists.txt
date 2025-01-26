# minimum version of cmake = 3.25 for legit reason:
# armclang support doesn't work work in previous releases
cmake_minimum_required(VERSION 3.25.0)

# Setting the Toolchain path
set (TOOLCHAIN_DIRECTORY    "${CMAKE_CURRENT_SOURCE_DIR}/toolchains")

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m"                CACHE INTERNAL "")
  set(ColourBold  "${Esc}[1m"               CACHE INTERNAL "")
  set(Red         "${Esc}[31m"              CACHE INTERNAL "")
  set(Green       "${Esc}[32m"              CACHE INTERNAL "")
  set(Yellow      "${Esc}[33m"              CACHE INTERNAL "")
  set(Blue        "${Esc}[34m"              CACHE INTERNAL "")
  set(Magenta     "${Esc}[35m"              CACHE INTERNAL "")
  set(Cyan        "${Esc}[36m"              CACHE INTERNAL "")
  set(White       "${Esc}[37m"              CACHE INTERNAL "")
  set(HCyan       "${Esc}[38;5;45m"         CACHE INTERNAL "")
endif()

#To Debug Cmake environment
#set(CMAKE_VERBOSE_MAKEFILE      ON)

# Extract Board Revision
string(SUBSTRING    ${REV}      0   1   BOARD_REVISION)

# Extract Device Series
string(SUBSTRING    ${DEVICE}   1   2   DEVICE_SERIES)
string(SUBSTRING    ${DEVICE}   1   1   DEV_FAMILY)

# Look for E1C device
if( ${DEVICE_SERIES} STREQUAL "E1")
    string(SUBSTRING    ${DEVICE}   3   1   D_TMP)
    if( ${D_TMP} STREQUAL "C")
        string(SUBSTRING    ${DEVICE}   1   3   EXT_DEVICE_SERIES)
    endif()
elseif (${DEVICE_SERIES} STREQUAL "E7")
    set(EXT_DEVICE_SERIES   "${DEVICE}")
endif()

# Including Utilities cmake
include (utilities_func.cmake)

#Error Check
ERR_CHECK_MSG(FATAL_ERROR    CMSIS_PACK_PATH        "CMSIS PACK"        Red)
ERR_CHECK_MSG(WARNING        CMSIS_COMPILER_PATH    "CMSIS COMPILER"    Magenta)

# Source directory paths
if (DEFINED CMAKE_REPO_PATH)
    set (SRC_DIRECTORY      "${CMAKE_REPO_PATH}")
else ()
    message (FATAL_ERROR "${Red}GIT REPO PATH NOT DEFINED${ColourReset}")
endif()

set(CMAKE_TOOLCHAIN_FILE    "${TOOLCHAIN_DIRECTORY}/toolchain.cmake")

# Setting Paths for OS selection cmake files
set (OS_CMAKE_DIR           "${CMAKE_CURRENT_SOURCE_DIR}/os_cmake")

# Setting path for Driver cmake files
set (DRIVERS_CMAKE_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/drivers_cmake")

# Setting path for NETXDUO camke files
set (NETXDUO_CMAKE_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/netxduo_cmake")

# Setting path for AzureRTOS USBX cmake file
set (USBX_CMAKE_DIR         "${CMAKE_CURRENT_SOURCE_DIR}/usbx_cmake")

# Setting path for Device related cmake file
set (DEVICE_CMAKE_DIR       "${CMAKE_CURRENT_SOURCE_DIR}/device_cmake")

# Setting path for FileX related cmake file
set (FILEX_CMAKE_DIR        "${CMAKE_CURRENT_SOURCE_DIR}/filex_cmake")

# Setting path for se_host_services related cmake file
set (HOST_SERVICES_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/host_services_cmake")

# Setting Processor Name
set (PROC                   "${CPU}_${RTSS}")

# Based on the source, paths redirection
if (REPO_SRC STREQUAL ALIF_GIT)
    set (DEVICE_PATH            "${SRC_DIRECTORY}/rtss_device")
    set (DRIVERS_CMAKE_FILE     "${DRIVERS_CMAKE_DIR}/bolt_drivers.cmake")
    set (RETARGET_SRC_DIR       "${SRC_DIRECTORY}/bolt_apps")

    #Include common Include path
    include_directories("${SRC_DIRECTORY}/bolt_apps/Common/Include")
    
    # GIT repo branch check
    if (${BOARD_REVISION} STREQUAL "B")
        
        if ( (DEVELOPER STREQUAL "NO") AND (REPO_SRC STREQUAL ALIF_GIT) )
            GET_GIT_PARAMS("${SRC_DIRECTORY}/bolt_apps" "b0_develop" FATAL_ERROR)
            GET_GIT_PARAMS("${SRC_DIRECTORY}/bolt_extsys_driver" "b0_develop" FATAL_ERROR)
        endif()
        
    elseif (${BOARD_REVISION} STREQUAL "A")

        if ( (DEVELOPER STREQUAL "NO") AND (REPO_SRC STREQUAL ALIF_GIT) )
            GET_GIT_PARAMS("${SRC_DIRECTORY}/bolt_apps" "b0_develop" FATAL_ERROR)
            GET_GIT_PARAMS("${SRC_DIRECTORY}/bolt_extsys_driver" "b0_develop" FATAL_ERROR)
        endif()
        
    else()
        message (STATUS "${Yellow}SELECT PROPER BOARD REVISION ${ColourReset}")
    endif()

elseif (REPO_SRC STREQUAL PACK)
    # Board Name
    set (BOARD_NAME             "DevKit-e7")
    set (DEVICE_PATH            "${ENSEMBLE_PACK_DIR}/Device")
    set (DRIVERS_CMAKE_FILE     "${DRIVERS_CMAKE_DIR}/drivers.cmake")
    set (RETARGET_SRC_DIR       "${ENSEMBLE_PACK_DIR}/libs")

    if (OS STREQUAL FREERTOS)
        ERR_CHECK_MSG(FATAL_ERROR    CMSIS_FREERTOS_PATH        "CMSIS FREERTOS"        Red)
    endif()

elseif (REPO_SRC STREQUAL GITHUB)
    message(FATAL_ERROR         "${Red} Git hub support is not added...\n${ColourReset}")

else()
    message(FATAL_ERROR         "${Red} Source Repo is not found...\n${ColourReset}")
    
endif()

#Include Retarget Include path
set(RETARGET_IO_INC     "${CMSIS_COMPILER_PATH}/include;${RETARGET_SRC_DIR}/retarget_io/config")

include_directories("${RETARGET_IO_INC};${CMSIS_PACK_PATH}/CMSIS/RTOS2/Include")
include("${TOOLCHAIN_DIRECTORY}/compiler_config.cmake")

# Library directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY          "${CMAKE_BINARY_DIR}/lib")

message (STATUS "SELECTED COMPILER        --> ${HCyan}${COMPILER}${ColourReset}")
message (STATUS "SELECTED DEVICE          --> ${HCyan}${DEVICE}${ColourReset}")
message (STATUS "SELECTED CORE            --> ${HCyan}${CPU} (${RTSS}, Rev-${BOARD_REVISION})${ColourReset}")

# Including Device related cmake
include (${DEVICE_CMAKE_DIR}/device.cmake)

# Directory paths of OS cmake files
if (OS STREQUAL THREADX)
    message (STATUS "SELECTED OS              --> ${HCyan}THREADX${ColourReset}")

    GET_MACRO_VALUE ("${RTEcomponentFile}"  RTE_AZURE_RTOS_NETXDUO  netxduo_ret)
    GET_MACRO_VALUE ("${RTEcomponentFile}"  RTE_AZURE_RTOS_USBX     usbx_ret)
    GET_MACRO_VALUE ("${RTEcomponentFile}"  RTE_AZURE_RTOS_FILEX    filex_ret)

    # Including cmake for NETXDUO
    if (netxduo_ret)
        include (${NETXDUO_CMAKE_DIR}/netxduo.cmake)
    endif ()

    # Including cmake for USBX repo
    if (usbx_ret)
        include (${USBX_CMAKE_DIR}/usbx.cmake)
    endif ()

    # Including cmake for Threadx OS
    include (${OS_CMAKE_DIR}/threadx.cmake)

    # Including cmake for FileX source
    if (filex_ret)
        include (${FILEX_CMAKE_DIR}/azurertos_filex.cmake)
    endif ()

elseif (OS STREQUAL FREERTOS)
    message (STATUS "SELECTED OS              --> ${HCyan}FREE-RTOS${ColourReset}")
    include (${OS_CMAKE_DIR}/freertos.cmake)

elseif (OS STREQUAL CMSISRTOS)
    set (OS_BIN_DIR     ${CMSIS_RTOS_BIN_DIR})

elseif (OS STREQUAL NONE)
    message (STATUS "SELECTED OS              --> ${HCyan}Bare-Metal${ColourReset}")
    include (${OS_CMAKE_DIR}/baremetal.cmake)

else()
    # OS is not proper
    message (FATAL_ERROR "${Red}PROPER OS IS NOT GIVEN or \"${OS}\" OS IS NOT SUPPORTED ${ColourReset}")
endif ()

message (STATUS "SELECTED BOOT            --> ${HCyan}${BOOT}${ColourReset}")
message (STATUS "SELECTED BOARD           --> ${HCyan}${BOARD}${ColourReset}")
message (STATUS "SELECTED REPO SOURCE     --> ${HCyan}${REPO_SRC}${ColourReset}")

# Pack inclusion based on the configuration
if (DEV_FAMILY STREQUAL "E")
    message (STATUS "SELECTED DEVICE FAMILY   --> ${HCyan}ENSEMBLE ${ColourReset}")
else ()
    message (FATAL_ERROR "${Red}DEFINE PROPER PACK NAME (Please run ./run.sh to see options)${ColourReset}")
endif()

# Including cmake for Drivers
include (${DRIVERS_CMAKE_FILE})

# Including Host Services cmake
include (${HOST_SERVICES_CMAKE_DIR}/se_host_services.cmake)

IS_MACRO_DEF("${RTEcomponentFile}"   RTE_CMSIS_Compiler_STDIN_Custom      stdin_def_cnt)
IS_MACRO_DEF("${RTEcomponentFile}"   RTE_CMSIS_Compiler_STDOUT_Custom     stdout_def_cnt)
IS_MACRO_DEF("${RTEcomponentFile}"   RTE_CMSIS_Compiler_STDERR_Custom     stderr_def_cnt)
IS_MACRO_DEF("${RTEcomponentFile}"   STDIN_ECHO                 stdin_echo_def_cnt)
if( stdin_def_cnt OR (stdout_def_cnt GREATER_EQUAL 2) OR stderr_def_cnt OR stdin_echo_def_cnt)
    set(RETARGET_EN_NO_SEMIHOSTING        ON)
    # Collect all retargeting source files
    file(GLOB_RECURSE   RETARGET_IO_SRCS    "${RETARGET_SRC_DIR}/retarget_io/source/*.c")
    list(APPEND         RETARGET_IO_SRCS    "${RETARGET_IO_SRC}")
endif()

if(${RETARGET_EN_NO_SEMIHOSTING})
    message (STATUS "SELECTED STANDARD I/O    --> ${HCyan}UART${ColourReset}")
else()  
    message (STATUS "SELECTED STANDARD I/O    --> ${HCyan}DEBUGGER CONSOLE${ColourReset}")
endif()

# Creating a Library file for Retarget IO & Common Source Files
if ((RETARGET_IO_SRCS) OR (COMMON_SRCS))
    set(COMMON_LIB     "COMMON")

    if(${RETARGET_EN_NO_SEMIHOSTING})
        list(APPEND     COMMON_SRCS     ${RETARGET_IO_SRCS})
    endif()

    add_library(${COMMON_LIB}   STATIC      ${COMMON_SRCS})
endif()

if(CHANGE_MSG)
    message("\n${HCyan}------------------- Changes (ALIF) --------------------------${ColourReset}")
    message(${CHANGE_MSG})
    message("${HCyan}-------------------------------------------------------------${ColourReset}")
endif()

#Unit Testing
if (DEVELOPER STREQUAL "UT")
    message(FATAL_ERROR     "${Green} UNIT TESTING DONE ${ColourReset}")
endif()

# Mark the language as C so that CMake doesn't try to test the C++
# cross-compiler's ability to compile a simple program because that will fail
project("Alif_RTSS_CMake_Testapps"
        VERSION 2.0.0
        DESCRIPTION "COLLECTION_OF_ALIF_TESTAPPS "
        LANGUAGES C ASM)

# Collecting all the Test application names
list(LENGTH    TEST_APP_SRCS  TOTAL_NUM_OF_APPLICATION)
message("")
message("\n<--- Test Applications to be Built -->")

string (REPLACE     ","     ";"     TEST_APPS           ${TEST_APP} )

if (EN_APP_FLAG)
    list(LENGTH     TEST_APPS   TOTAL_NUM_OF_REQUESTED_APPLICATION)
    list(FIND       TEST_APPS   "ALL"   ALL_APPS_FLAG)

    if( NOT ALL_APPS_FLAG EQUAL -1)
        set(EN_APP_FLAG     0)
        MATH(EXPR TOTAL_NUM_OF_REQUESTED_APPLICATION "${TOTAL_NUM_OF_APPLICATION} - ${TOTAL_NUM_OF_REQUESTED_APPLICATION} + 1")
        set(EXCLUDED_APP_LIST   "${TEST_APPS}")
        set(TEST_APPS           "ALL")
        list(REMOVE_ITEM ${EXCLUDED_APP_LIST} "ALL")
    endif()
    message ("<--- ${TOTAL_NUM_OF_REQUESTED_APPLICATION} application requested to build out of ${TOTAL_NUM_OF_APPLICATION} -->")

else ()
    set(TOTAL_NUM_OF_REQUESTED_APPLICATION ${TOTAL_NUM_OF_APPLICATION})
    message ("<--- All ${TOTAL_NUM_OF_APPLICATION} applications will build -->")

endif()

set(CMAKE_TEMP_FOLDER       "./../.temp")
file(MAKE_DIRECTORY         ${CMAKE_TEMP_FOLDER})
#execute_process(COMMAND     attrib +h   ${CMAKE_TEMP_FOLDER})

set(TMP_FILE                "${CMAKE_TEMP_FOLDER}/.tmp" )
set(TMP_FILE1               "${CMAKE_TEMP_FOLDER}/.tmp1")
file(WRITE      ${TMP_FILE}     ${OUTPUT_DIR})
file(WRITE      ${TMP_FILE1}    "")
file(APPEND     ${TMP_FILE}     "\nRequested: ${TOTAL_NUM_OF_REQUESTED_APPLICATION}, Total: ${TOTAL_NUM_OF_APPLICATION}")
SET(INVALID_TESTAPP_CNT     0)

foreach (testApp ${TEST_APPS})
    set(TEST_FOUND_FLAG "Not Found")
    foreach (testsourcefile ${TEST_APP_SRCS})

        # Collectiong Test app names one by one
        get_filename_component (tempname "${testsourcefile}" NAME)
        string (REPLACE ".c" "" testname ${tempname} )

        # If the Flag is high, build only for the given Test Application
        if (EN_APP_FLAG)

            if (testname STREQUAL testApp)

                message (STATUS "App Name --> ${Yellow}${testname}${ColourReset}")
                set(TEST_FOUND_FLAG "found")
                file(APPEND ${TMP_FILE} "\n${testname}")

                # Calling the build function
                BUILD_PROJECT ()

                break ()

            endif ()

        # Build for all the test Applications
        elseif (NOT EN_APP_FLAG)
            list(FIND       EXCLUDED_APP_LIST   ${testname}   EXCLUDED_APP_LIST_FLAG)

            if (EXCLUDED_APP_LIST_FLAG EQUAL -1)
                message (STATUS "App Name --> ${Yellow}${testname}${ColourReset}")
                file(APPEND ${TMP_FILE} "\n${testname}")

                # Calling the build function
                BUILD_PROJECT ()

            endif()

        endif ()

    endforeach (testsourcefile )

    if ( (TEST_FOUND_FLAG STREQUAL "Not Found") AND (NOT testApp STREQUAL "ALL" ) )
        message (STATUS "App Name --> ${Yellow}${testApp}    => [ :${Red}${TEST_FOUND_FLAG} ]${ColourReset}")
        MATH(EXPR INVALID_TESTAPP_CNT "${INVALID_TESTAPP_CNT}+1")
    endif ()

endforeach (testApp)

message("\n")
message("${HCyan}Disabled App List as follows ${ColourReset}")

foreach(element IN LISTS RM_TEST_APPS_LIST)
    message(STATUS  "${Yellow} ${element} ${ColourReset}")
endforeach()

message("")
file(APPEND ${TMP_FILE} "\n${INVALID_TESTAPP_CNT}")