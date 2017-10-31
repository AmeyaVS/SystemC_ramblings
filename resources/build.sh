#!/bin/bash

FILE_PREFIX="systemc"
FILE_VERSION="2.3.2"

DIRECTORY_NAME="$FILE_PREFIX-$FILE_VERSION"

# This script will download the SystemC library from Accelera website and configure the build and build it for you.
echo "======================================================"
echo "Downloading the SystemC library from accellera website"
echo "======================================================"
wget -c http://accellera.org/images/downloads/standards/systemc/$DIRECTORY_NAME.tar.gz

echo "======================================================"
echo "Extracting the SystemC source code"
echo "======================================================"
tar xf $DIRECTORY_NAME.tar.gz

pd=$PWD

cd $DIRECTORY_NAME

echo "======================================================"
echo "Creating build directory"
echo "======================================================"
if [ -d "objdir" ]; then
	echo "!!!Directory Already Exists!!!"
else
	mkdir objdir
fi

cd objdir

# Create Installation Directory
SYSTEMC_HOME=$HOME/apps/$DIRECTORY_NAME
mkdir -p $HOME/apps/$DIRECTORY_NAME

# Configure the SystemC library
echo "============================================================================"
echo "Configuring the SystemC library"
echo "SystemC library will be installed in $SYSTEMC_HOME"
echo "============================================================================"
#../configure --prefix=$SYSTEMC_HOME --enable-debug
# Using CMake for much better integration and portability accross system with
# different OS's.
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo    \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON   \
      -DCMAKE_INSTALL_PREFIX=$SYSTEMC_HOME \
      -DCMAKE_CXX_STANDARD=11              \
      ..

# Find the Number of CPUS to utilize all the cores to build the SystemC llibrary
CPUS=`nproc`
echo "======================================================"
echo "Using $CPUS Threads to build SystemC"
echo "======================================================"

# Build the SystemC library
echo "======================================================"
echo "Building the SystemC library"
echo "======================================================"
make -j $CPUS

# Check the build SystemC library
echo "==========================================================="
echo "Checking the Built library by building examples application"
echo "==========================================================="
make check -j $CPUS

# Do the Installation
echo "======================================================"
echo "SystemC Installation"
echo "======================================================"
make install

cd $pd

echo "====================================================================================================================================================="
echo "Please Add the contents of this SystemC.config to the end of your .bashrc file located in your $HOME folder"
echo "====================================================================================================================================================="

echo "export SYSTEMC_HOME=$SYSTEMC_HOME" > SystemC.config
MACHINE_TYPE=`uname -m`
if [ ${MACHINE_TYPE} = "x86_64" ]; then
	echo "export LD_LIBRARY_PATH=${LD_LIBRARY_PATH:+$LD_LIBRARY_PATH:}\$SYSTEMC_HOME/lib-linux64:\$SYSTEMC_HOME/lib" >> SystemC.config
else
	echo "export LD_LIBRARY_PATH=${LD_LIBRARY_PATH:+$LD_LIBRARY_PATH:}\$SYSTEMC_HOME/lib-linux:\$SYSTEMC_HOME/lib" >> SystemC.config
fi

echo "======================================================"
echo "Build and Installation finished"
echo "======================================================"
