#!/bin/bash
# Number of Arguments passed
ARGUMENTS_PASSED=$#

#Initialize Variable
cmake_build_error=0

NC='\033[0m' # No Color
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
BROWN='\033[0;37m'
HIGH_CYAN='\033[38;5;45m'

supported_compiler=("GCC" "ARMCLANG" "CLANG")

curr_dir=$PWD
run_start_time=$SECONDS
echo -e "\n\n==================================================================================================="

curr_temp="$curr_dir/.temp"
rtss_cfg_file=$curr_temp/.rtss_cfg

# Checking for Number of Arguments passed
for arg in "$@"
do
    case "$arg" in (-help|-HELP|--h|--H|-h|-H|help|HELP)
        # Insert help message here
        echo -e "${CYAN}<--- CMAKE RTSS BUILD DISPLAYING HELP INFORMATION --->${NC}\n"
        echo -e "${GREEN}script usage --> \n"
        echo -e "Usage: ./run.sh [options]\n"
        echo -e "For Example : "
        echo -e "              ./run.sh RTSS=HP OS=NONE DEVICE=AE722F80F55D5AS TEST_APP=ALL \n ${NC}"

        echo -e "${YELLOW}Optional Arguments [options] --> \n"
        echo -e "     RTSS=[ HP or HE ]"
        echo -e "     OS=[ NONE or THREADX or FREERTOS or CMSISRTOS ]"
        echo -e "     BOOT=[ TCM or MRAM ]"
        echo -e "     TEST_APP=[ UART4_Baremetal or ALL ]"
        echo -e "     CLEAN=[ NO or YES or FORCE OR CACHE ]"
        echo -e "     DEVICE=[ AE722F80F55D5AS or AE722F80F55D5LS ... ] Run setup_user_env.sh script to see device list"
        echo -e "     REPO_SRC=[ ALIF_GIT or PACK or GITHUB ]"
        echo -e "     JOB=NUMBER_OF_PARALLEL_THREADS"
        echo -e "     DEVELOPER=[ NO or YES ]"
        echo -e "     BOARD=[ DEVKIT_E7 or APPKIT ]"
        echo -e "     REV=[ A0 or B0 or B1 or B2 or B3 or B4 ]"
        echo -e "     COMPILER_USER_ARG=\"-std=c99 -O0 -g -Wall -fshort-enums -fshort-wchar\""
        echo -e "     ASM_USER_ARG=\"-g3 -Wall -masm=auto\""
        echo -e "${NC}"
        exit 1
        ;;
    esac
done

# Checking for Number of Arguments passed
if [ $ARGUMENTS_PASSED -eq 0 ] ; then
    echo -e "${HIGH_CYAN}<--- BUILD WITH DEFAULT/PREVIOUS-BUILD SETTINGS --->\n\n${NC}"
fi

if [ -e $rtss_cfg_file ] ; then
    is_rtss_cfg_file_present=1
else
    mkdir $curr_temp
    touch $rtss_cfg_file
    chmod 666 $rtss_cfg_file
    if [ $? -ne 0 ]; then
        echo -e "\n\n${RED} Not able to generate rtss cfg file, Run in root mode ${NC}\n"
        exit 1
    fi
    is_rtss_cfg_file_present=1
fi

# Assigning Arguments to their respective variables
for ARGUMENT in "$@"
do
    KEY=$(echo $ARGUMENT | cut -f1 -d=)
    KEY_LENGTH=${#KEY}
    VALUE="${ARGUMENT:$KEY_LENGTH+1}"

    export "$KEY"="$VALUE"

    # Check if the rtss file contains the substring
    if grep -q "export \"$KEY\"=\"" "$rtss_cfg_file"; then
        # If a match is found, replace the line containing the substring
        sed -i "s/.*export \"$KEY\"=.*/export \"$KEY\"=\"$VALUE\"/" "$rtss_cfg_file"

    else
        # If no match is found, append the new string to the file
        echo "export \"$KEY\"=\"$VALUE\"" >> "$rtss_cfg_file"

        if [ $? -ne 0 ]; then
            echo -e "\n\n${RED} RTSS cfg not able to update, Run in root mode ${NC}\n"
            exit 1
        fi
    fi

done

# Cleaning the cache from previous builds
if [ "$CLEAN" = "CACHE" ] ; then
    echo  -e  "${RED}\n"
    rm -vf "$rtss_cfg_file"
    echo  -e  "${NC}\n"
    is_rtss_cfg_file_present=0
fi

if [ $is_rtss_cfg_file_present = 1 ] ; then
    source "$rtss_cfg_file"
fi

# Current Working Directory
CMAKE_SHELL_SCRIPT_PATH=$curr_dir

# Path for CMakeLists.txt file for rtss projects
CMAKE_LIST_PATH=$curr_dir/cmake_rtss      # $HOME/path/cmake_rtss

# Checking if Test app name is given
if [[ "$TEST_APP" = "ALL" ]]
  then
    APP_FLAG=0
else
    APP_FLAG=1                      # If Test App name is given, then make the flag high
fi

if [ -z $DEVELOPER ] ; then
   DEVELOPER="NO"
fi

if [ -n "$DEVICE" ] ; then
    valid_Device=$(grep -iw $DEVICE setup_user_env.sh | wc -l)
else
    echo -e "${RED} DEVICE IS NOT SET ; either set environment properly using"
    echo -e " (setup_user_env.sh) or pass DEVICE name as argument of (run.sh) ${NC}\n"
    exit 1
fi

if [ $valid_Device = "0" ] ; then
    echo -e "${CYAN}\n [ WARNING ] :: ${RED}\"$DEVICE\"${CYAN} DEVICE IS NOT AVAILABLE IN DEVICE LIST ...${NC}\n\n"
fi

src_as_pack=0
src_as_alif_git=0

if [ -e $curr_temp/.pack ] ; then
    src_as_pack=1
fi

if [ -e $curr_temp/.alif_git ] ; then
    src_as_alif_git=1
fi

if [ $src_as_pack = 1 ] && [ $src_as_alif_git = 1 ] ; then
    echo -e "${CYAN}Since PACK and Git both info is available, Tool will"
    echo -e "proceed with default/selected repo source : $REPO_SRC ...${NC}\n"
fi

if [ -e $curr_temp/.local_path ] ; then
    OS_STR=$(head -n 1 $curr_temp/.local_path)
else
    echo -e "${CYAN} Environment is not set properly...${NC}\n"
fi

if [ "$REPO_SRC" = "ALIF_GIT" ] ; then
    curr_temp_file=$curr_temp/.alif_git
    if [ -e $curr_temp_file ] ; then
        CMAKE_REPO_PATH=$(sed -n '1p' $curr_temp_file)

        if [[ $CMAKE_REPO_PATH != "/mnt/"* ]]; then
            CMAKE_REPO_PATH="${OS_STR}${CMAKE_REPO_PATH}"
        fi

        if ! [ -d $CMAKE_REPO_PATH ] ; then
            echo -e  "${RED} Source Code Repo is not available...${NC}\n"
            exit 1
        fi

        dir_count=$(find $CMAKE_REPO_PATH -maxdepth 1 -type d | wc -l)
        if [ $dir_count -gt 0 ] ; then
            dir_count=$((dir_count-1))
        fi

        line=$(sed -n '2p' $curr_temp_file)

        if [ "$dir_count" != "$line" ] ; then
            echo  -e  "${CYAN} [WARNING] : Directory count doesn't match with cloned repo count, Please check it may create some failure ...${NC}\n"
        fi
    else
        echo  -e  "${CYAN}  [WARNING] : Directory Info is not available ...${NC}\n"
    fi

elif [ "$REPO_SRC" = "PACK" ] ; then
    echo -e "${YELLOW}[INFO]:IN PACK BUILDING INDIVIDUAL DRIVER CAN NOT BE DISABLED \n${NC}"
else
    echo -e  "${RED}  [WARNING] : Repo Source is invalid ...${NC}\n"
    exit 1
fi

# Creating Build directory based on Compiler
if [ "${OS}" = "NONE" ] ; then
    CMAKE_RTSS_BUILD_DIR=${CMAKE_RTSS_BUILD_DIR}/${REPO_SRC}/${COMPILER}/${DEVICE}/${BOARD}/BAREMETAL/${RTSS}/${CPU}/${BOOT}
else
    CMAKE_RTSS_BUILD_DIR=${CMAKE_RTSS_BUILD_DIR}/${REPO_SRC}/${COMPILER}/${DEVICE}/${BOARD}/${OS}/${RTSS}/${CPU}/${BOOT}
fi

# Cleaning the directories from previous build
if [ "$CLEAN" = "FORCE" ]
  then
    echo  -e  "${RED} Deleting Build folder \"$CMAKE_RTSS_BUILD_DIR\"...${NC}\n"
    rm -rf $CMAKE_RTSS_BUILD_DIR
fi

# Checking the Host Machine's OS type
echo -e "-- HOST_OSTYPE              --> ${YELLOW}${OSTYPE}${NC}"

if ! [[ ${supported_compiler[@]} =~ $COMPILER ]]
  then
    echo -e "\n\n${RED}Build Environment is not set ...!!! "
    echo -e "User  has to edit [\"setup_user_env.sh\"] as per local setup"
    echo -e "After editing Run [\"source setup_user_env.sh\"]\n\n${NC}"
    exit 1
fi

# CMake command Arguments for RTSS
CMAKE_RTSS_CMD_ARG="-S ${CMAKE_LIST_PATH} -B ${CMAKE_RTSS_BUILD_DIR} -DCMAKE_REPO_PATH=${CMAKE_REPO_PATH}        \
                    -DCMSIS_PACK_PATH=${CMSIS_PACK_PATH} -DRTSS=${RTSS} -DDEVICE=${DEVICE} -DCPU=${CPU}          \
                    -DOS=${OS} -DREV=${REV} -DBOOT=${BOOT} -DEN_APP_FLAG=${APP_FLAG} -DTEST_APP=${TEST_APP}      \
                    -DCOMPILER_USER_ARG="${COMPILER_USER_ARG}" -DASM_USER_ARGS="${ASM_USER_ARGS}"                \
                    -DCOMPILER=${COMPILER} -DCMSIS_COMPILER_PATH=${CMSIS_COMPILER_PATH} -DDEVELOPER=${DEVELOPER} \
                    -DBOARD=${BOARD} -DREPO_SRC=${REPO_SRC} -DCMAKE_EXPORT_COMPILE_COMMANDS=1"

if [ "$REPO_SRC" = "PACK" ]
  then
    echo $ENSEMBLE_PACK_DIR
    CMAKE_RTSS_CMD_ARG="${CMAKE_RTSS_CMD_ARG} -DENSEMBLE_PACK_DIR=${ENSEMBLE_PACK_DIR}  \
                        -DCMSIS_FREERTOS_PATH=${CMSIS_FREERTOS_PATH}                    \
                        -DAZURERTOS_PACK_DIR=${AZURERTOS_PACK_DIR}                      \
                        -DFREERTOS_COMPONENT_DIR={FREERTOS_COMPONENT_DIR}"
fi

# CMake command to run CMakeLists.txt file to configure and generate Makefile for the project
# If the Host is Linux Machine
if [ "$OSTYPE" = "linux-gnu" ]
  then
  echo ${CMAKE_RTSS_CMD_ARG}
    cmake -E time cmake ${CMAKE_RTSS_CMD_ARG} || { exit 1; }
# If the Host is Git Bash on Windows Machine
elif [ "$OSTYPE" = "msys" ]
  then
    cmake -E time cmake -G "Unix Makefiles" ${CMAKE_RTSS_CMD_ARG} || { exit 1; }
fi

# going to the directory where the Makefile is generated
cd ${CMAKE_RTSS_BUILD_DIR}

# Cleaning the directories from previous build
if [ "$CLEAN" = "YES" ]
  then
    make clean
fi

# Running the makefile which is genereated by Cmake
echo -e "\n\n"
build_start_time=$SECONDS
if [ $JOB ] ; then
    make -k -j $JOB
else
    make -k -j 16
fi

cmake_build_error=$?

elapsed_time_for_build=$(( SECONDS - build_start_time ))

echo -e "\n"
for i in $(seq 1 60);
do
    printf  $'\U2728'
done

if [ -e $curr_temp/.tmp ]
then
    line1=$(sed -n '1p' $curr_temp/.tmp)
    line2=$(sed -n '2p' $curr_temp/.tmp)
    available_elf_files=$(find $line1 -maxdepth 1 -type f -name '*.elf' | wc -l)
    requested_application_cnt=$(echo $line2 | cut -d "," -f 1 | cut -d " " -f 2)
    invalid_application_cnt=`tail -1 "$curr_temp/.tmp"`

    echo -e "\n"
    generated_elf_files_cnt=0
    old_elf_files_cnt=0

    # First 2 line is already read in previous lines
    for i in `seq 1 $((requested_application_cnt - invalid_application_cnt))`
    do
        k=$((i+2))         # Skipping first two line
        line=$(sed -n "${k}p" $curr_temp/.tmp)

        eval "grep -sqF \"${line}\" \"$curr_temp/.tmp1\""
        if [ $? -eq 0 ] ; then
            execGeneratedFlag=1
        else
            execGeneratedFlag=0 # do something else if the string is not found
        fi

        elf_file=$line.elf
        if [ -e "$line1/$elf_file" ] ; then
            if [ ${execGeneratedFlag} -eq 1 ]; then
                echo -e $'\U2705'" ${GREEN}-- Generate App Name          --> $elf_file ${NC}"
                generated_elf_files_cnt=$((generated_elf_files_cnt+1))
            else
                echo -e $'\U2757'" ${YELLOW}-- Couldn't Generate App Name --> $elf_file ${BLUE}(last successful build elf exist) ${NC}"
                old_elf_files_cnt=$((old_elf_files_cnt+1))
            fi

        else
            echo -e '\U26D4'" ${RED}-- Couldn't Generate App Name --> $elf_file ${NC}"
        fi
    done

    failed_elf_cnt=$((requested_application_cnt - invalid_application_cnt - generated_elf_files_cnt - old_elf_files_cnt))
    echo -e ""
    for i in $(seq 1 60);
    do
        printf  $'\U2728'
    done
    echo -e "\n\n\n ${HIGH_CYAN}-- Application Build Statistics  [ ${GREEN}Generated: $generated_elf_files_cnt, ${RED}Failed: $failed_elf_cnt, Invalid: $invalid_application_cnt, ${YELLOW}$line2 ] ${NC}"
    rm   $curr_temp/.tmp
    rm   $curr_temp/.tmp1
fi

echo -e "\n"
eval "echo ========================== Build Time Taken :: $(date -ud "@$elapsed_time_for_build" +'$((%s/3600/24)) days %H hr %M min %S sec') =========================="
echo -e "\n\n"
total_run_elapsed_time=$(( SECONDS - run_start_time ))
eval "echo  Total Elapsed Time: $(date -ud "@$total_run_elapsed_time" +'$((%s/3600/24)) days %H hr %M min %S sec')"
echo -e "\n"

# Returning to the Shell Script directory
cd ${CMAKE_SHELL_SCRIPT_PATH}
exit $((cmake_build_error + invalid_application_cnt))
