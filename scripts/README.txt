This folder contains below sub-directories which are needed to build Test applications:-
====================================================================================================

1. cmake_rtss       --> This directory contains all the cmake files related to toolchain and
projects source files with respect to Cortex-M55.

2. Include_RTE_Components --> This directory contains "RTE_Components.h" header file specifically
for RTSS_HP, RTSS_HE devices.

Prerequisites for Windows host machines:-
=========================================

    1. CMake should be installed and should be aware about its bin path.
    2. MingW64 should be installed, which provides the application named "GitBash".
    3. Git should be installed.
    4. GitBash application should be used as Terminal console while using this CMake Framework.

Below are the steps to initialize the cmake environment and compile the test applications:-
===========================================================================================

Note:-
======
	1. The "setup_user_env.sh" script assigns the script contents as the environment variables,
    which configures compiler license and sets compiler related paths.

	2. In "setup_user_env.sh" script, make sure to give the complete paths for variables.

    Example :-
            export CMSIS_VERSION=5.9.0

	5. Run the command --> source setup_user_env.sh
	6. The setup_user_env.sh script assignes the script contents as the environment variable, which
    will be used by the cmake for the build process.

Note:-
======
1. CMake Make requires complete path for all the arguments while running the scripts. So make sure
to provide complete paths in the scripts.
2. Keep in mind not to give an extra slash (/) at the end of the path variables. If given, cmake
will not be able to handle it properly.
3. The syntax provided for the File system in the Linux Terminal and in Windows GitBash Terminal
are different. Please use the examples in the shell scripts as a reference before modifications.

Below are the steps to configure and build:-
============================================

1. Run the command --> ./run.sh RTSS=[HP or HE] OS=[THREADX or FREERTOS or CMSISRTOS or NONE] BOOT=[MRAM or TCM] TEST_APP=[UART4_Baremetal or ALL] CLEAN=[NO or YES or FORCE] 

    Example command for RTSS build -->
    #./build.sh RTSS=HE OS=NONE BOOT=TCM REPO_SRC=PACK BOARD=DEVKIT_E7 TEST_APP=dma_testmemcpy CLEAN=NO CPU=M55 REV=1

2. The script assignes the git repo's source directory and build directory's path to cmake file.

3. After that, it enables the macro definitions such as Device name, Package name, Operating System
and boot file selection.
    RTSS        --> HE or HP
    DEVICE      --> AE722F80F55D5XX
    OS          --> THREADX, FREERTOS, CMSISRTOS AND NONE (BareMetal)
    BOOT        --> MRAM or TCM
    CLEAN       --> NO or YES or FORCE
    REPO_SRC    --> ALIF_GIT or PACK
    BOARD       --> DEVKIT_E7

4. Once these definitions and assignments are done, cmake command will be called with respective
arguments passed properly.

5. On successful cmake run, a Makefile will be generated in the build directory path.

6. This newly generated Makefile will be run from the build directory, which will compile all the
source files and generate binaries/executables for respective test applications.

7. This run.sh script has support to generate binaries for all the test applications and also to
generate binary for a specific test application. We have to pass the app name via TEST_APP variable
or 'ALL' to generate for all test applications.

8. RTOS networking test app names for Threadx are :- 'UART4_Baremetal' and 'demo_netx'.

9. Optional Arguments which can be passed based on requirement are :-
    CLEAN               --> NO or YES OR FORCE
    COMPILER_USER_ARG   --> "-std=c99 -O0 -g -Wall -fshort-enums -fshort-wchar"
    ASM_USER_ARG        --> "-g3 -Wall -masm=auto"
    DEVELOPER           --> YES it will not check branch related combination
    JOB                 --> Make command option to run multiple thread for compilation

    Note:- The compiler arguments should be passed within the double quotes.
    ======

10. Thse 3 Arguments can be neglected when no modifications are required, then default
configurations will be considered.

11. CLEAN argument is used to clear all the object files, library files and dependency files which
were generated in the previous build.

12. COMPILER_USER_ARG and ASM_USER_ARG are the arguments which can be used when the user wants to
pass different compiler arguments other than default values. The user should make sure to pass all
the required compiler arguments, because the default arguments from the config file will not be
considered when these two arguments are used.
