#!/bin/bash

# Configure: CMSIS Version
export CMSIS_VERSION=5.9.0

# Configure: CMSIS Compiler Version
export CMSIS_COMPILER_VERSION=1.0.0

# Configure: CMSIS FreeRTOS Version
export CMSIS_FREERTOS_VERSION=10.5.1

# Configure: compiler (ARMCLANG | GCC | CLANG)
export COMPILER=ARMCLANG

# Configure: ARM License Type
export ARM_PRODUCT_DEF="/mnt/c/Program Files/Arm/Development Studio 2022.0/sw/mappings/gold.elmap"

# Configure: Complete Compiler Path
export COMPILER_BIN_PATH="$HOME/ArmCompilerforEmbedded6.18/bin/"

export CMSIS_PACK_PATH="/mnt/e/armds2021_ws/cmsis_root_pack/ARM/CMSIS/5.9.0"

export CMSIS_COMPILER_PATH="/mnt/e/armds2021_ws/cmsis_root_pack/ARM/CMSIS-Compiler/1.0.0"

export CMSIS_FREERTOS_PATH="/mnt/e/armds2021_ws/cmsis_root_pack/ARM/CMSIS-FreeRTOS/10.5.1"

export ARMLMD_LICENSE_FILE="$HOME/.arm/ds/licenses/"

# Configure: Operating System (default) [ THREADX | FREERTOS | CMSISRTOS | NONE ]
export OS=NONE

# Configure: Boot Type (default) [ MRAM | TCM ]
export BOOT=TCM

export DEVICE="AE722F80F55D5XX"
export ENSEMBLE_PACK_DIR="$HOME/rtss_repos/ensemble-cmsis-dfp_DEV"



#**************************************************************************************************
#                                           NO EDIT
#**************************************************************************************************

alif_dev_list()  {
    echo ""
    echo "|---------------------------------------------------------------------------|"
    echo "|     E1 Series    |     E3 Series    |     E5 Series    |     E7 Series    |"
    echo "|---------------------------------------------------------------------------|"
    echo "| AE101F1061517LH  | AE302F80F55D5AE  | AE512F80F55D5AS  | AE722F80F55D5AS  |"
    echo "| AE101F4071542LH  | AE302F80F5582AE  | AE512F80F5582AS  | AE722F80F55D5LS  |"
    echo "|                  | AE302F80F55D5LE  | AE512F80F55D5LS  | AE722F80F55D5XX  |"
    echo "|                  | AE302F80F5582LE  | AE512F80F5582LS  |                  |"
    echo "|                  | AE302F80C1557LE  | AE512F80F55D5XX  |                  |"
    echo "|                  | AE302F40C1537LE  | AE512F80F5582XX  |                  |"
    echo "|                  | AE302F80F55D5XX  |                  |                  |"
    echo "|                  | AE302F80F5582XX  |                  |                  |"
    echo "|                  |                  |                  |                  |"
    echo "|---------------------------------------------------------------------------|"
    echo "|---------------------------------------------------------------------------|"
    echo "|     E1C Series   |     B1C Series   |     XX Series    |     XX Series    |"
    echo "|---------------------------------------------------------------------------|"
    echo "| AE1C1F4051920PH  |                  |                  |                  |"
    echo "| AE1C1F4051920HH  |                  |                  |                  |"
    echo "| AE1C1F40319205H  |                  |                  |                  |"
    echo "| AE1C1F1041010XX  |                  |                  |                  |"
    echo "| AE1C1F1040505XX  |                  |                  |                  |"
    echo "|                  |                  |                  |                  |"
    echo "|                  |                  |                  |                  |"
    echo "|---------------------------------------------------------------------------|"
    echo ""
}

echo ""
read -p "Current Device $DEVICE ; Do you want to change device? <y/N> " prompt
echo ""

if [[ $prompt == "y" || $prompt == "Y" || $prompt == "yes" || $prompt == "Yes" || $prompt == "YES" ]] ; then
    echo " ALIF DEVICES : "
    alif_dev_list
    TMP_DEV=$DEVICE
    read -p "Select Desired Device Part Number (from above list) : " DEVICE
    if [ -z "$DEVICE" ] ; then
        DEVICE=$TMP_DEV
    fi
    echo ""
fi

echo -e "\nSELECTED DEVICE : $DEVICE \n"

os_specific_str()  {

    if [[ "$OSTYPE" = "linux-gnu"* ]] ; then
        if uname -r | grep -q "microsoft-standard-WSL*"; then
            local  str1=$(wslpath "$(wslvar USERPROFILE)")
            local  str2="$str1/AppData/Roaming/"
            str1="$str1/AppData/Local/Arm/Packs"
        else
            local  str1="$HOME/.cache/arm/packs"
            local  str2="$HOME/."
        fi
    elif [[ "$OSTYPE" = "darwin"* ]]; then
        echo "Not Supported !!! $OSTYPE"
        exit 1
    elif [[ "$OSTYPE" = "cygwin" ]]; then
        echo "Not Supported !!! $OSTYPE"
        exit 1
    elif [[ "$OSTYPE" = "msys" ]]; then
        local  str1="$HOME/AppData/Local/Arm/Packs"
        local  str2="$HOME/AppData/Roaming/"
    elif [[ "$OSTYPE" = "win32" ]]; then
        local  str1="%USERPROFILE%\AppData\Local\Arm\Packs"
        local  str2="%USERPROFILE%\AppData\Roaming\\"
    elif [[ "$OSTYPE" = "freebsd"* ]]; then
        echo "Not Supported !!! $OSTYPE"
        exit 1
    else
        echo "UNKNOWN OS !!!"
        exit 1
    fi

   eval "$1=$str1"
   eval "$2=$str2"
}

#os_specific_str     ALIF_PACK_BASE      ARM_LICENSE_BASE_PATH

if [ -z "$CMSIS_PACK_PATH" ]; then
    export CMSIS_PACK_PATH="$ALIF_PACK_BASE/ARM/CMSIS/$CMSIS_VERSION"
fi

if [ -z $CMSIS_COMPILER_PATH ]; then
    export CMSIS_COMPILER_PATH="$ALIF_PACK_BASE/ARM/CMSIS-Compiler/$CMSIS_COMPILER_VERSION"
fi

if [ -z $CMSIS_FREERTOS_PATH ]; then
    export CMSIS_FREERTOS_PATH="$ALIF_PACK_BASE/ARM/CMSIS-FreeRTOS/$CMSIS_FREERTOS_VERSION"
fi

if [ -z $ARMLMD_LICENSE_FILE ]; then
    export ARMLMD_LICENSE_FILE="${ARM_LICENSE_BASE_PATH}arm/ds/licenses"
fi

if [ ! -d $CMSIS_PACK_PATH ]; then
  echo " \"CMSIS_PACK_PATH\" does not exist...."
fi

if [ ! -d $CMSIS_COMPILER_PATH ]; then
  echo " \"CMSIS_COMPILER_PATH\" does not exist...."
fi

if [ ! -d $CMSIS_FREERTOS_PATH ]; then
  echo " \"CMSIS_FREERTOS_PATH\" does not exist...."
fi

if [ ! -d $ARMLMD_LICENSE_FILE ]; then
  echo " \"ARMLMD_LICENSE_FILE\" does not exist...."
fi

if [ ! -d $COMPILER_BIN_PATH ]; then
  echo " \"COMPILER_BIN_PATH\" compiler does not exist...."
fi

# Paths of Directories for the build of cmake_rtss and cmake_gnss
export CMAKE_REPO_PATH=$PWD/source
export CMAKE_RTSS_BUILD_DIR=$PWD/build_rtss

# Setting the Compiler bin to PATH environment variable
export PATH=$COMPILER_BIN_PATH:$PATH

# Export this path in the bashrc file so that the binary images will be copied
# to the SE tools images folder 
#export SE_TOOLS = ""
