# CMake Configurations

This document contains all the CMake files necessary for including header directories and source files required to compile and generate binaries.

## Directory Structure

- **device_cmake**  
  - Contains the CMake file with details related to devices, including **RTSS_HP/RTSS_HE** and **M55_HP/M55_HE**.

- **drivers_cmake**  
  - Includes the CMake file that specifies the source files and header files for all supporting drivers.

- **netxduo_cmake**  
  - Includes the CMake file which details the source and header files for the network module.

- **os_cmake**  
  - Contains CMake files with specifics on OS-related source and header files, including details about test applications for each supported operating system.

- **toolchains**  
  - Contains the CMake file with details about the compiler toolchain.

- **usbx_cmake**  
  - Includes the CMake file detailing the source and header files for the USBX driver.

## Source Files 

- **CMakeLists.txt**  
  - The primary CMake file that manages the integration of all the aforementioned CMake files based on the project's configuration and requirements. It also includes source files for test applications within the build process.

- **utilities_func.cmake**  
  - A CMake script file containing helper functions and macro definitions vital for the build process.

- **rtss_compiler_config.cmake**  
  - This script is used to configure default compiler arguments for the RTSS environment.
