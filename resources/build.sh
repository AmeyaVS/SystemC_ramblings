#!/bin/bash

# This script will download the SystemC library from Accelera website and configure the build and build it for you.
echo "======================================================"
echo "Downloading the SystemC library from accellera website"
echo "======================================================"
wget -c http://www.accellera.org/images/downloads/standards/systemc/systemc-2.3.1.tgz

echo "======================================================"
echo "Extracting the SystemC source code"
echo "======================================================"
tar xf systemc-2.3.1.tgz

pd=$PWD

cd systemc-2.3.1

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
SYSTEMC=$HOME/systemcInstall
mkdir -p $HOME/systemcInstall

# Configure the SystemC library
echo "============================================================================"
echo "Configuring the SystemC library"
echo "SystemC library will be installed in $SYSTEMC"
echo "============================================================================"
../configure --prefix=$HOME/systemcInstall

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
make check

# Do the Installation
echo "======================================================"
echo "SystemC Installation"
echo "======================================================"
make install

cd $pd

echo "====================================================================================================================================================="
echo "Please Add the contents of this SystemC.config to the end of your .bashrc file located in your $HOME folder"
echo "====================================================================================================================================================="

echo "export SYSTEMC=$SYSTEMC" > SystemC.config
echo "export SYSTEMC_HOME=\$SYSTEMC" >> SystemC.config
MACHINE_TYPE=`uname -m`
if [ ${MACHINE_TYPE} = "x86_64" ]; then
	echo "export TARGET_ARCH=linux64" >> SystemC.config
else
	echo "export TARGET_ARCH=linux" >> SystemC.config
fi

#if [ ${LD_LIBRARY_PATH} == "" ]; then
#	echo "export LD_LIBRARY_PATH=\$SYSTEMC/lib-\$TARGET_ARCH" >> SystemC.config
#else
#	echo "export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:\$SYSTEMC/lib-\$TARGET_ARCH" >> SystemC.config
#fi

echo "export LD_LIBRARY_PATH=${LD_LIBRARY_PATH:+$LD_LIBRARY_PATH:}\$SYSTEMC/lib-\$TARGET_ARCH" >> SystemC.config

echo "======================================================"
echo "Build and Installation finished"
echo "======================================================"
