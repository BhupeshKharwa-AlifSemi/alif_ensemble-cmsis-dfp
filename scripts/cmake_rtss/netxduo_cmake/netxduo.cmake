# Setting path for NETXDUO repo
set (NETXDUO_DIR        "${SRC_DIRECTORY}/netxduo")

# Setting paths and source files for NETX
set (NETXDUO_COMMON_DIR "${NETXDUO_DIR}/common")
file (GLOB NETXDUO_COMMON_SRC "${NETXDUO_COMMON_DIR}/src/*.c")
include_directories (${NETXDUO_COMMON_DIR}/inc)

set (NETXDUO_PORTS_DIR  "${NETXDUO_DIR}/ports/cortex_m55/ac6/inc")
include_directories (${NETXDUO_PORTS_DIR})

# Setting path for Addon directory
set (NETXDUO_ADDONS_DIR "${NETXDUO_DIR}/addons")
file (GLOB NETXDUO_ADDON_WEB    "${NETXDUO_ADDONS_DIR}/web/*.c")
file (GLOB NETXDUO_ADDON_DHCP   "${NETXDUO_ADDONS_DIR}/dhcp/*.c")
include_directories (${NETXDUO_ADDONS_DIR}/web)
include_directories (${NETXDUO_ADDONS_DIR}/dhcp)
file (GLOB NETXDUO_ADDON_FILES ${NETXDUO_ADDON_WEB} ${NETXDUO_ADDON_DHCP})

# Collecting all netx related source files under one variable
file (GLOB NETXDUO_SRC ${NETXDUO_COMMON_SRC} ${NETXDUO_ADDON_FILES})

# Creating a Library file for NETXDUO_SRC
set (NETXDUO_LIB     "NETXDUO")
add_library (${NETXDUO_LIB} STATIC ${NETXDUO_SRC})
