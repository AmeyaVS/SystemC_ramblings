#!/bin/bash

SRC_DIR=systemc-2.3.3
ZIP_FILE=$SRC_DIR.tar.gz
DOWNLOAD_URL=https://www.accellera.org/images/downloads/standards/systemc/$ZIP_FILE

BUILD_TYPE=Release

function stepTry {
  "$@"
  local step_status=$?
  if [ $step_status -ne 0 ]; then
    echo "Error: $1" >&2
    exit $step_status
  fi
  return $step_status
}

# This script will download the SystemC library from Accelera website and configure the build and build it for you.
if [ -f "$ZIP_FILE" ]; then
    echo "======================================================"
    echo "Downloaded file exists"
    echo "======================================================"
else
    echo "======================================================"
    echo "Downloading the SystemC library from accellera website"
    echo "======================================================"
    stepTry wget -c "$DOWNLOAD_URL"
fi

if [ -d "$SRC_DIR" ]; then
    echo "======================================================"
    echo " Source Directory Exists."
    echo "======================================================"
else
    echo "======================================================"
    echo "Extracting the SystemC source code"
    echo "======================================================"
    stepTry tar xf $ZIP_FILE
fi

pd=$PWD

stepTry cd $SRC_DIR

echo "======================================================"
echo "Creating build directory"
echo "======================================================"
if [ -d "build" ]; then
	echo "!!!Directory Already Exists!!!"
else
	stepTry mkdir build
fi

stepTry cd build

# Create Installation Directory
SYSTEMC=$HOME/apps/$SRC_DIR
stepTry mkdir -p $SYSTEMC

# Configure the SystemC library
echo "============================================================================"
echo "Configuring the SystemC library"
echo "SystemC library will be installed in $SYSTEMC: $BUILD_TYPE"
echo "============================================================================"
#if [ "$BUILD_TYPE" == "Debug" ]; then
#    CONFIG_PARMETER="--enable-debug --disable-optimize"
#elif [ "$BUILD_TYPE" == "RelWithDebInfo" ]; then
#    CONFIG_PARAMETER="--enable-debug"
#else
#    CONFIG_PARAMTER=""
#fi
stepTry cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE     \
              -DCMAKE_INSTALL_PREFIX=$SYSTEMC    \
              -DCMAKE_CXX_STANDARD=17            \
              -DCMAKE_CXX_EXTENSIONS=OFF         \
              -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
              -DBUILD_SOURCE_DOCUMENTATION=ON    \
              -DENABLE_PHASE_CALLBACKS=ON        \
              ..
#../configure --prefix=$SYSTEMC $CONFIG_PARAMETER

# Find the Number of CPUS to utilize all the cores to build the SystemC llibrary
CPUS=`nproc`
echo "======================================================"
echo "Using $CPUS Threads to build SystemC"
echo "======================================================"

# Build the SystemC library
echo "======================================================"
echo "Building the SystemC library"
echo "======================================================"
#stepTry make clean
stepTry make -j $CPUS

# Check the build SystemC library
echo "==========================================================="
echo "Checking the Built library by building examples application"
echo "==========================================================="
stepTry make check -j $CPUS

# Do the Installation
echo "======================================================"
echo "SystemC Installation"
echo "======================================================"
stepTry make install

cd $pd

#echo "====================================================================================================================================================="
#echo "Please Add the contents of this SystemC.config to the end of your .bashrc file located in your $HOME folder"
#echo "====================================================================================================================================================="

#echo "export SYSTEMC=$SYSTEMC" > SystemC.config
#echo "export SYSTEMC_HOME=\$SYSTEMC" >> SystemC.config
#MACHINE_TYPE=`uname -m`
#if [ ${MACHINE_TYPE} = "x86_64" ]; then
#	echo "export TARGET_ARCH=linux64" >> SystemC.config
#else
#	echo "export TARGET_ARCH=linux" >> SystemC.config
#fi

##if [ ${LD_LIBRARY_PATH} == "" ]; then
##	echo "export LD_LIBRARY_PATH=\$SYSTEMC/lib-\$TARGET_ARCH" >> SystemC.config
##else
##	echo "export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:\$SYSTEMC/lib-\$TARGET_ARCH" >> SystemC.config
##fi

#echo "export LD_LIBRARY_PATH=${LD_LIBRARY_PATH:+$LD_LIBRARY_PATH:}\$SYSTEMC/lib-\$TARGET_ARCH" >> SystemC.config

echo "======================================================"
echo "Build and Installation finished"
echo "======================================================"
