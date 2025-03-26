# MACRO to add all directories in result
# argv[0] - result variable, argv[1] - add relative paths, set "" if you don't want it
# argv[2] - path to folder with folders
macro (SUBDIRLIST firstdir curdir)
    file(GLOB ENDF6_SRC_TOP RELATIVE ${curdir} ${curdir}/*)
    file(GLOB ENDF6_SRC_SUBS RELATIVE ${curdir}/ ${curdir}/**/**)

    set(children ${ENDF6_SRC_TOP} ${ENDF6_SRC_SUBS})

    set(dirlist "${firstdir}")

    foreach (child ${children})
        if (IS_DIRECTORY ${curdir}/${child})
            list (APPEND dirlist ${curdir}/${child})
        endif ()
    endforeach ()

    set(result ${dirlist})

    foreach (subdir ${result})
        include_directories(${subdir})
    endforeach ()
endmacro ()

# Checking for Macro Definition in given header file
macro (CHECK_DEF    check_def   header_file     return_val)
    file (READ "${header_file}" header)
    string (REGEX MATCH "${check_def}" MACRODEF "${header}")    # The string should be exactly as present in the file, including the spaces/tabs
    if (MACRODEF)
        set (${return_val}              1)
    else ()
        set (${return_val}              0)
    endif (MACRODEF)
endmacro ()

# Get Macro value, (Note: It works only for real number of Macros)
macro (GET_MACRO_VALUE      header      macro_name      macro_val   varMsg)

    FOREACH(arg ${header})
        string(REGEX MATCHALL "^[ \t]*#(define|DEFINE)[ \t]+${macro_name}[ \t]+[0-9]+[ \t]*.*" foundDefines "${arg}")

        if (foundDefines)
            string(REGEX MATCH "[ \t]+[0-9]+" tmp "${foundDefines}")
            string(REGEX MATCH "[0-9]+" tmp "${tmp}")

            if(${tmp})
                set(${macro_val}    ON      CACHE   BOOL    ${varMsg})
                add_definitions(-D${macro_name})
            else()
                set(${macro_val}    OFF     CACHE   BOOL    ${varMsg})
            endif()

        endif (foundDefines)
    endforeach()

endmacro ()

# Get Macro value, (Note: It works only for real number of Macros)
macro (GET_MACRO_VAL    headerFileName      macro_name      macro_val)

    file (STRINGS ${headerFileName}  file_content)
    FOREACH(arg ${file_content})
        string(REGEX MATCHALL "^[ \t]*#(define|DEFINE)[ \t]+${macro_name}[ \t]+[0-9]+[ \t]*.*" foundDefines "${arg}")

        if (foundDefines)
            string(REGEX MATCH "[ \t]+[0-9]+" tmp "${foundDefines}")
            string(REGEX MATCH "[0-9]+" tmp "${tmp}")

            set(${macro_val}     ${tmp})
        endif (foundDefines)
    endforeach()

endmacro ()

# Change Macro value
macro (CHANGE_MACRO_VAL     check_def   header_file     change_val    return_val    exactStr)
    set (${return_val}              0)
    file (READ      "${header_file}"     header_content)

    if(${exactStr})
        set(matchCriteria       "${check_def}")
    else()
        set(matchCriteria    "[ |\\t]*#(define|DEFINE)+[ |\\t]+${check_def}[ |\\t]+")
    endif()

    # The string should be exactly as present in the file, including the spaces/tabs
    string(REGEX MATCH     ${matchCriteria}     macrodef    "${header_content}")

    # Check if the match was successful
    if(macrodef)
        if(${exactStr})
            string (REPLACE "${macrodef}" "${change_val}" changed_header_content "${header_content}")
        else()
            string (REPLACE "${macrodef}" "${macrodef}${change_val}" changed_header_content "${header_content}")
        endif()

        if(NOT "${changed_header_content}" STREQUAL "${check_def}")
            file(WRITE      "${header_file}"        "${changed_header_content}")
            set (${return_val}              1)
        endif()
    endif()

endmacro ()

# Change Macro value (special which contain ())
macro (CHANGE_SPEC_MACRO_VAL    prm1  prm2  prm3  fileNameWithPath    change_val    return_val)
    set(${return_val}              0)

    file(READ      "${fileNameWithPath}"     file_content)
    set(matchCriteria    "[ |\\t]*#(define|DEFINE)+[ |\\t]+${prm1}[ |\\t]+\\(\\(${prm2}\\)${prm3}\\)")

    # The string should be exactly as present in the file, including the spaces/tabs
    string(REGEX MATCHALL  ${matchCriteria}  macrodef    "${file_content}")

    # Check if the match was successful
    if(macrodef)
        string (REPLACE "${macrodef}" "${change_val}" changed_header_content "${file_content}")
        if(NOT "${changed_header_content}" STREQUAL "${check_def}")
            file(WRITE      "${fileNameWithPath}"        "${changed_header_content}")
            set (${return_val}              1)
        endif()
    endif()

endmacro ()

# Backup_file_creation
macro (SAVE_ORIG_FILE   fileNameWithPath    newFileNameWithPath     return_val)
    set(${return_val}              0)
    file(READ  ${fileNameWithPath}   file_content)

    get_filename_component(filePath     "${fileNameWithPath}"   DIRECTORY)
    get_filename_component(fileName     "${fileNameWithPath}"   NAME)

    # FileName
    string(REPLACE      "."     "_"     newFileName    "${fileName}")
    set(${newFileNameWithPath}      "${filePath}/${newFileName}.bak")

    if( NOT EXISTS ${${newFileNameWithPath}})
        file(WRITE  ${${newFileNameWithPath}}   "${file_content}")
        set(${return_val}              1)
    endif()

endmacro ()

# Know Macro define or not
macro (IS_MACRO_DEF     header     macro_name  macro_def_cnt)
    set(tmp    0)
    FOREACH(arg ${header})
        string(REGEX MATCHALL   "^[ \t]*#(define|DEFINE)[ \t]*([^a-zA-Z0-9_]|^)${macro_name}([^a-zA-Z0-9_]|$)[ \t]*"  foundDefines    "${arg}")

        if (foundDefines)
            MATH(EXPR tmp     "${tmp}+1")
        endif (foundDefines)
    endforeach()
    set(${macro_def_cnt} ${tmp})

endmacro ()

# Macro definition to Compile w.r.t OS types
macro (BUILD_PROJECT)

    set(EXECUTABLE ${testname})

    # Adding executable file name
    add_executable (${EXECUTABLE} ${testsourcefile}  ${addonsourcefiles})

    if (OS STREQUAL FREERTOS)

        # Linking all the library files to the test application
        target_link_libraries(${EXECUTABLE} PRIVATE ${COMMON_LIB} ${PACK_LIB} ${SE_HOST_SERVICES_LIB} ${DRIVER_LIB} ${DEVICE_LIB} ${OS_LIB_FILE})

    elseif (OS STREQUAL THREADX)

        # Linking all the library files to the test application
        target_link_libraries (${EXECUTABLE} PRIVATE ${COMMON_LIB} ${FILEX_LIB} ${PACK_LIB} ${NETXDUO_LIB} ${USBX_LIB} ${SE_HOST_SERVICES_LIB} ${DRIVER_LIB} ${DEVICE_LIB} ${OS_LIB_FILE})

    elseif (OS STREQUAL NONE)

        # Linking all the library files to the test application
        target_link_libraries(${EXECUTABLE} PRIVATE ${COMMON_LIB}  ${SE_HOST_SERVICES_LIB} ${DRIVER_LIB} ${DEVICE_LIB})

    endif ()

    # Improve clean target
    set_target_properties(${EXECUTABLE} PROPERTIES ADDITIONAL_CLEAN_FILES
        "${OUTPUT_DIR}/${EXECUTABLE}.bin;${OUTPUT_DIR}/${EXECUTABLE}.hex;${OUTPUT_DIR}/${EXECUTABLE}.map")

    if (COMPILER STREQUAL GCC)

        target_link_options(${EXECUTABLE} PRIVATE  -Wl,-Map=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE}.map)
        target_link_libraries(${EXECUTABLE} PRIVATE m)
        set_target_properties(${EXECUTABLE} PROPERTIES OUTPUT_NAME ${EXECUTABLE}.elf)

        add_custom_command(TARGET  ${EXECUTABLE}
           POST_BUILD
           COMMAND echo "${EXECUTABLE}" >> "${TMP_FILE1}"
            && echo  "${Cyan} ${EXECUTABLE}.elf  BUILD SUCCESSFUL *******************************${ColourReset}"
            && arm-none-eabi-objcopy -O binary     ${OUTPUT_DIR}/${EXECUTABLE}.elf  ${OUTPUT_DIR}/${EXECUTABLE}.bin
            && echo  "${Green}Generated Bin files for ${Yellow}${EXECUTABLE}   ${ColourReset}"
           COMMAND  arm-none-eabi-objcopy -O ihex       ${OUTPUT_DIR}/${EXECUTABLE}.elf  ${OUTPUT_DIR}/${EXECUTABLE}.hex
            &&  echo  "${Green}Generated Hex files for ${Yellow}${EXECUTABLE}   ${ColourReset}"
        )

    elseif (COMPILER STREQUAL ARMCLANG)

        add_custom_command(TARGET  ${EXECUTABLE}
           POST_BUILD
           COMMAND  echo "${EXECUTABLE}" >> "${TMP_FILE1}"
           && echo  "${Cyan} ${EXECUTABLE}.elf  BUILD SUCCESSFUL *******************************${ColourReset}"
           && fromelf -v --bin --output=${OUTPUT_DIR}/${EXECUTABLE}.bin  ${OUTPUT_DIR}/${EXECUTABLE}.elf
           && echo  "${Green}Generated Bin files for ${Yellow}${EXECUTABLE}.elf   ${ColourReset}"
           COMMAND  fromelf -v --i32 --output=${OUTPUT_DIR}/${EXECUTABLE}.hex  ${OUTPUT_DIR}/${EXECUTABLE}.elf
           && echo  "${Green}Generated Hex files for ${Yellow}${EXECUTABLE}.elf   ${ColourReset}"
        )

    elseif (COMPILER STREQUAL CLANG)

        target_link_options(${EXECUTABLE} PRIVATE   -Wl,-Map=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE}.map)
        set_target_properties(${EXECUTABLE}     PROPERTIES      OUTPUT_NAME     ${EXECUTABLE}.elf)

        add_custom_command(TARGET  ${EXECUTABLE}
           POST_BUILD
           COMMAND  echo "${EXECUTABLE}" >> "${TMP_FILE1}"
           && echo  "${Cyan} ${EXECUTABLE}.elf  BUILD SUCCESSFUL *******************************${ColourReset}"
           && llvm-objcopy --output-target binary  ${OUTPUT_DIR}/${EXECUTABLE}.elf  ${OUTPUT_DIR}/${EXECUTABLE}.bin
           && echo  "${Green}Generated Bin files for ${Yellow}${EXECUTABLE}.elf   ${ColourReset}"
           COMMAND  llvm-objcopy --output-target ihex  ${OUTPUT_DIR}/${EXECUTABLE}.elf  ${OUTPUT_DIR}/${EXECUTABLE}.hex
         )

    endif ()

    IF (EXISTS "${SE_TOOLS_IMAGE_DIR}")
        add_custom_command(TARGET  ${EXECUTABLE}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${OUTPUT_DIR}/${EXECUTABLE}.bin" "${SE_TOOLS_IMAGE_DIR}/${EXECUTABLE}_${CPU}_${RTSS}.bin"  &&
            echo "${Cyan}Copied binary ${EXECUTABLE}_${CPU}_${RTSS}.bin ${ColourReset} to ${Green} ${SE_TOOLS_IMAGE_DIR} ${ColourReset}"
        )
    endif ()

    #To Support Package Preset
    install(TARGETS ${EXECUTABLE} DESTINATION bin)

    # Set global property (all targets are impacted)
    #set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
    #set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK    "${CMAKE_COMMAND} -E time")

    # Set property for my_target only
    #set_property(TARGET ${EXECUTABLE} PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

    # get_target_property(INCLUDE_DIRS ${EXECUTABLE} INCLUDE_DIRECTORIES)
    # message(STATUS "Include Directories for my_target: ${INCLUDE_DIRS}")

    #get_target_property(LIBS ${EXECUTABLE} LINK_LIBRARIES)
    #message(DEBUG       "\n${EXECUTABLE} Linked Libraries: ${LIBS}\n")

endmacro (BUILD_PROJECT)

# Get Git Parameters
macro (GET_GIT_PARAMS repoPath branchName messageType )

    string(REGEX REPLACE "[ \t]+$" "" my_repo_withpath ${repoPath})
    execute_process(
        COMMAND git -C ${my_repo_withpath} rev-parse --abbrev-ref HEAD
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

   execute_process(
        COMMAND git -C ${my_repo_withpath} rev-parse --short HEAD
        OUTPUT_VARIABLE GIT_SHA_ID
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    string(LENGTH ${my_repo_withpath} repoPath_length)
    math(EXPR repoPath_length "${repoPath_length} - 1")
    string(SUBSTRING ${my_repo_withpath} ${repoPath_length} 1 repoPath_last_char)

    if( repoPath_last_char STREQUAL "/")
        string(SUBSTRING ${my_repo_withpath} 0 ${repoPath_length} my_repo_withpath)
    endif()

    string(FIND ${my_repo_withpath} "/" last_slash REVERSE)
    math(EXPR last_slash "+ ${last_slash} + 1")
    string(SUBSTRING ${my_repo_withpath} ${last_slash} -1 repoName)

    if (${branchName} STREQUAL ${GIT_BRANCH})
        message(VERBOSE "Branch (${repoName}) Check : ${Cyan} PASS ${ColourReset}")
    else ()
        if (${branchName} STREQUAL ${GIT_SHA_ID})
            message(VERBOSE "Branch (${repoName}) Check : ${Cyan} PASS ${ColourReset}")
        else()
            message(${messageType} "Branch (${repoName}) Check : ${Red} FAIL \n(checkout proper branch as per A/B series device)${ColourReset}")
        endif()
    endif ()

endmacro ()

# Define a macro to move an item from one list to another
macro(RM_ENTRY      src_list dst_list       elementName_to_remove       update_dst_flag)
    get_filename_component(F_NAME   ${elementName_to_remove}    NAME_WE)
    list(REMOVE_ITEM    ${src_list}     ${elementName_to_remove})
    if(${update_dst_flag})
        list(APPEND         ${dst_list}     ${F_NAME})
    endif()
endmacro()

# Custom Error Check Function
macro(ERR_CHECK_MSG     msg_type    var_to_check   msg_key  msg_color)
    if(NOT ${var_to_check})
        message(${msg_type}     "${${msg_color}}${msg_key} IS NOT ASSIGNED TO ANY VALUE...${ColourReset}")
    elseif (NOT EXISTS ${${var_to_check}})
        message(${msg_type}     "⛔${${msg_color}}GIVEN ${msg_key} PATH IS NOT AVAILABLE...${ColourReset}")
    endif()
endmacro()

# Convert Preset Cache/Enviroment into cmake variable Function
macro(CONVERT_PRESET_VAR_TO_CMAKE_VAR     presetVar    cmakeVar   presetVarType)
    if(DEFINED ${presetVarType}{${presetVar}})
        set(${cmakeVar}         $${presetVarType}{${presetVar}})
    else()
        message(STATUS        "${Yellow}⚠️[WARNING] ${presetVar} is not defined in preset ${ColourReset}")
    endif()
endmacro()

# Add files in variable conditionally and prepare statistics
macro(COND_FILE_ADD     fileNameWithPath    cond    testApp   typeOfFile)
    #message(STATUS        "${Yellow}⚠️[WARNING] ${fileNameWithPath} is not defined in preset ${${cond}} ${ColourReset}")

    if(EXISTS ${fileNameWithPath})
        if( ${typeOfFile} STREQUAL "test-apps")
            list(APPEND     ALL_TEST_APPS_SRC_LIST      "${fileNameWithPath}")
        elseif(${typeOfFile} STREQUAL "dependency")
            list(APPEND     TEST_APPS_DEPENDENCY_SRC_LIST      "${fileNameWithPath}")
        else()
            message(STATUS      "${Yellow}⚠️[WARNING] File type is not given for given file ${fileNameWithPath}" )
        endif()

        if(${cond})
            list(APPEND     ${testApp}      "${fileNameWithPath}")
        else()
            #message(STATUS        "${Yellow}⚠️[WARNING] ${cond} No proper flags are enabled for file ${fileNameWithPath} ${ColourReset}")
        endif()
    else()
        message(STATUS        "${Yellow}⚠️[WARNING] ${fileNameWithPath} doesn't exit ${ColourReset}")
    endif()

endmacro()

function(get_rte_macros)
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_MHU         ENABLE_MHU          "Enable/disable MHU Driver.")

    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_LL_PINCONF  ENABLE_PIN_CONF     "Enable/disable PinPAD and PinMux Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_USART       ENABLE_USART        "Enable/disable USART Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_IO          ENABLE_IO           "Enable/disable IO Driver.")

    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_ADC                        ENABLE_ADC       "Enable/disable ADC Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_CANFD                      ENABLE_CANFD     "Enable/disable CANFD commands.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_CDC200                     ENABLE_CDC200    "Enable/disable CDC200 Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_MIPI_DSI_ILI9806E_PANEL    ENABLE_MIPI_DSI_ILI9806E_PANEL   "Enable/disable MIPI DSI ILI9806E_PANEL Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_CDC_ILI6122_PANEL          ENABLE_CDC_ILI6122E_PANEL        "Enable/disable CDC ILI6122_PANEL Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_MIPI_DSI_ILI9488_PANEL     ENABLE_MIPI_DSI_ILI9488E_PANEL   "Enable/disable MIPI DSI ILI9488E_PANEL Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_CMP         ENABLE_CMP          "Enable/disable Comparator Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_CRC         ENABLE_CRC          "Enable/disable CRC Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_DAC         ENABLE_DAC          "Enable/disable DAC Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_SD          ENABLE_SD           "Enable/disable SD Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_OSPI        ENABLE_OSPI         "Enable/disable OSPI Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_ISSI_FLASH  ENABLE_ISSI_FLASH   "Enable/disable ISSI FLASH Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_GT911       ENABLE_GT911        "Enable/disable GT911 Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_HWSEM       ENABLE_HWSEM        "Enable/disable Hardware Semaphores Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_SAI         ENABLE_I2S          "Enable/disable I2S Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_I3C         ENABLE_I3C          "Enable/disable I3C Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_ICM42670P   ENABLE_ICM42670P    "Enable/disable ICM42670P Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_LPI2C       ENABLE_LPI2C        "Enable/disable LPI2C Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_PDM         ENABLE_PDM          "Enable/disable PDM Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_SPI         ENABLE_SPI          "Enable/disable SPI Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_LPTIMER     ENABLE_LPTIMER      "Enable/disable LPTIMER Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_MRAM        ENABLE_MRAM         "Enable/disable MRAM Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_RTC         ENABLE_RTC          "Enable/disable RTC Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_UTIMER      ENABLE_UTIMER       "Enable/disable UTIMER Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_WDT         ENABLE_WDT          "Enable/disable WDT Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_WIFI        ENABLE_WIFI         "Enable/disable WIFI Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_DMA         ENABLE_DMA          "Enable/disable DMA Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_I2C         ENABLE_I2C          "Enable/disable I2C Driver.")

    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_CAMERA                      ENABLE_CAMERA           "Enable/disable Camera Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_CAMERA_SENSOR_MT9M114       ENABLE_MT9M114_CAMERA   "Enable/disable Camera MT9M114 Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_CAMERA_SENSOR_ARX3A0        ENABLE_ARX3A0_CAMERA    "Enable/disable Camera ARX3A0 Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_MIPI_CSI2                   ENABLE_MIPI_CSI2        "Enable/disable MIPI CSI2 Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_MIPI_DSI                    ENABLE_MIPI_DSI         "Enable/disable MIPI DSI Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_CPI                         ENABLE_CPI              "Enable/disable CPI Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_Drivers_GPIO                        ENABLE_GPIO             "Enable/disable GPIO Driver.")

    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_CMSIS_Compiler_STDIN            ENABLE_STDIN    "Enable/disable retarget STDIN  Driver.")
    GET_MACRO_VALUE("${RTEcomponentFile}"   RTE_CMSIS_Compiler_STDOUT           ENABLE_STDOUT   "Enable/disable retarget STDOUT Driver.")

endfunction()

macro(RESOLVE_TESTAPP_DEPENDANCY testAppNameWithPath macro_name)

    set(${macro_name}    OFF  PARENT_SCOPE)

    if(EXISTS ${testAppNameWithPath})
        get_filename_component(TEST_APP_FILENAME "${testAppNameWithPath}" NAME_WE)
        # Find position of "SUBSTRING"
        string(FIND     "${TEST_APP}"   ${TEST_APP_FILENAME}  POSITION)
        string(FIND     "${TEST_APP}"   "ALL"           ALL_STR_POSITION)

        if (( "${TEST_APP}" STREQUAL "ALL") OR ( "${TEST_APP}" STREQUAL "${TEST_APP_FILENAME}") OR ( (NOT (POSITION GREATER -1)) AND (ALL_STR_POSITION GREATER -1)))
            set(${macro_name}    ON      PARENT_SCOPE)
        endif()
    endif()
endmacro()

function(resolve_dependancy)
    if(NOT ${ENABLE_UTIMER})
        RESOLVE_TESTAPP_DEPENDANCY(${BARE_METAL_APP_DIR}/ADC_Ext_Trigger_Baremetal.c    ENABLE_UTIMER)
    endif()
endfunction()


function(eval_flags final_res operation)

    set(res             ON)

    if("${operation}" STREQUAL "OR")
        set(res         OFF)
    endif()

    foreach(flag IN LISTS ARGN)
        if(NOT DEFINED ${flag})
            message(STATUS         "${Yellow}⚠️ [WARNING]  Flag ${flag} is not defined. Assuming OFF ${ColourReset}")
            set(${flag}         OFF)
        endif()

        if("${operation}"   STREQUAL    "AND"   AND     NOT ${flag})
            set(res             OFF)
            break()
        elseif("${operation}"   STREQUAL    "OR"    AND     ${flag})
            set(res             ON)
            break()
        endif()
    endforeach()

    set(${final_res}        ${res}          PARENT_SCOPE)

endfunction()
