This directory contains all the cmake files which includes the header directories and source files
required to compile and generate binaries.

1. device_cmake     --> This contains cmake file which has the details related to
Devices(RTSS_HP/RTSS_HE, M55_HP/M55_HE).

2. drivers_cmake    --> This contains cmake file which has the details of source files and header
files of all the supporting drivers.

3. netxduo_cmake    --> This contains cmake file which has the details of source files and header
files with respect to network module.

4. os_cmake         --> This contains cmake files which has the details of OS related source files
and header files to include with respect to different Operating Systems. Also it has details of
Test applications w.r.t each OS.

5. toolchains       --> This contains cmake file which has the compiler toolchain related details.

6. usbx_cmake       --> This contains cmake file which has the details of source files and header
files of driver USBX.

7. CMakeLists.txt   --> This is the main cmake file, which links all the above cmake files based on
the configuration and requirement. This also has Test application source files related inclusions
for the build.

8. utilities_func.cmake --> This cmake file has helper functions and macro definitions required for
the build.

9. rtss_compiler_config.cmake --> This script can be used to configure default compiler arguments.
