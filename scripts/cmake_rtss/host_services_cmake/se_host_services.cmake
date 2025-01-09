if (REPO_SRC STREQUAL ALIF_GIT)
    #SE service common files
    include_directories ("${SRC_DIRECTORY}/bolt_apps/libs/se_services/port/include")
    include_directories ("${SRC_DIRECTORY}/bolt_apps/libs/se_services/include")
    file(GLOB SE_SERVICES_SRC  "${SRC_DIRECTORY}/bolt_apps/libs/se_services/*.c" "${SRC_DIRECTORY}/bolt_apps/libs/se_services/port/*.c")
    list(APPEND COMMON_SRCS "${SE_SERVICES_SRC}")

    # Setting path for se_host_services repo
    set (SE_HOST_SERVICES_DIR       "${SRC_DIRECTORY}/se_host_service")

    # Collecting driver files
    set (HOST_SERVICES_DRIVERS_DIR  "${SE_HOST_SERVICES_DIR}/drivers")
    file (GLOB HOST_DRIVERS_SRC "${HOST_SERVICES_DRIVERS_DIR}/src/*.c")
    include_directories (${HOST_SERVICES_DRIVERS_DIR}/include)

    include_directories (${SE_HOST_SERVICES_DIR}/include)
    file (GLOB SE_SERVICE_LIB_SRC  "${SE_HOST_SERVICES_DIR}/services_lib/*.c")

    # Removing Linux files from services_lib source file list
    get_filename_component (rm_app "${SE_HOST_SERVICES_DIR}/services_lib/services_host_handler_linux.c" ABSOLUTE)
    list (REMOVE_ITEM SE_SERVICE_LIB_SRC "${rm_app}")

elseif (REPO_SRC STREQUAL PACK)
    set(SE_HOST_SERVICES_DIR            "${ENSEMBLE_PACK_DIR}/se_services")
    set(SE_SERVICE_LIB_INC              "${SE_HOST_SERVICES_DIR}/include;${SE_HOST_SERVICES_DIR}/port/include")
    include_directories (${SE_SERVICE_LIB_INC})
    file (GLOB_RECURSE  SE_SERVICE_LIB_SRC  "${SE_HOST_SERVICES_DIR}/source/*.c" "${SE_HOST_SERVICES_DIR}/port/*.c")

    # Removing Linux files from source file list
    get_filename_component (rm_app "${SE_HOST_SERVICES_DIR}/source/services_host_handler_linux.c" ABSOLUTE)
    list (REMOVE_ITEM SE_SERVICE_LIB_SRC "${rm_app}")

elseif (REPO_SRC STREQUAL GITHUB)
    message(FATAL_ERROR         "${Red} Git hub support is not added...\n${ColourReset}")

endif()

# Creating a Library file for HOST SERVICES
set (SE_HOST_SERVICES_LIB     "SE_HOST_SERVICE")
add_library (${SE_HOST_SERVICES_LIB} STATIC ${SE_SERVICE_LIB_SRC} ${HOST_DRIVERS_SRC})