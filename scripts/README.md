# Test Applications Build Setup

This folder contains the following sub-directories needed to build test applications:

1. **cmake_rtss**  
   Contains all the CMake files related to the toolchain and project source files for Cortex-M55.

2. **Include_RTE_Components**  
   Contains the `RTE_Components.h` header file specifically for RTSS_HP and RTSS_HE devices.

## Prerequisites for Windows Host Machines

- Install CMake and ensure its bin path is set.
- Install MingW64, which provides the "GitBash" application.
- Install Git.
- Use GitBash as the terminal console while using this CMake framework.

## Initializing the CMake Environment and Compiling Test Applications

### Note

- The `setup_user_env.sh` script sets environment variables, configuring the compiler license and paths.
- Ensure complete paths are provided in the `setup_user_env.sh` script.

    **Example**:  
    ```bash
    export CMSIS_VERSION=5.9.0
    ```

- Run the command:
    ```bash
    source setup_user_env.sh
    ```
- The `setup_user_env.sh` script assigns the script contents as environment variables, which will be used by CMake for the build process.

### Important Notes

- CMake requires complete paths for all arguments. Ensure complete paths are provided in the scripts.
- Avoid adding an extra slash (/) at the end of path variables, as CMake may not handle it properly.
- The file system syntax differs between Linux Terminal and Windows GitBash Terminal. Refer to the examples in the shell scripts before making modifications.

## Steps to Configure and Build

1. Run the command:
    ```bash
    ./run.sh RTSS=[HP or HE] OS=[THREADX or FREERTOS or CMSISRTOS or NONE] BOOT=[MRAM or TCM] TEST_APP=[UART4_Baremetal or ALL] CLEAN=[NO or YES or FORCE]
    ```

    **Example command for RTSS build**:  
    ```bash
    ./build.sh RTSS=HE OS=NONE BOOT=TCM REPO_SRC=PACK BOARD=DEVKIT_E7 TEST_APP=dma_testmemcpy CLEAN=NO CPU=M55 REV=1
    ```

2. The script assigns the Git repo's source directory and build directory paths to the CMake file.

3. It enables macro definitions such as Device name, Package name, Operating System, and boot file selection:
    - **RTSS**: HE or HP
    - **DEVICE**: AE722F80F55D5XX
    - **OS**: THREADX, FREERTOS, CMSISRTOS, or NONE (BareMetal)
    - **BOOT**: MRAM or TCM
    - **CLEAN**: NO, YES, or FORCE
    - **REPO_SRC**: ALIF_GIT or PACK
    - **BOARD**: DEVKIT_E7

4. Once these definitions and assignments are done, the CMake command will be called with the respective arguments.

5. On successful CMake run, a Makefile will be generated in the build directory.

6. Run the newly generated Makefile from the build directory to compile all source files and generate binaries/executables for the respective test applications.

7. The `run.sh` script supports generating binaries for all test applications or a specific test application by passing the app name via the `TEST_APP` variable or 'ALL' to generate for all test applications.

8. RTOS networking test app names for ThreadX are: 'UART4_Baremetal' and 'demo_netx'.

### Optional Arguments

- **CLEAN**: NO, YES, or FORCE
- **COMPILER_USER_ARG**: "-std=c99 -O0 -g -Wall -fshort-enums -fshort-wchar"
- **ASM_USER_ARG**: "-g3 -Wall -masm=auto"
- **DEVELOPER**: YES (will not check branch-related combination)
- **JOB**: Make command option to run multiple threads for compilation

    **Note**: Compiler arguments should be passed within double quotes.

### Additional Information

- The `CLEAN` argument clears all object files, library files, and dependency files generated in the previous build.
- `COMPILER_USER_ARG` and `ASM_USER_ARG` allow passing different compiler arguments other than default values. Ensure all required compiler arguments are passed, as default arguments from the config file will not be considered when these two arguments are used.