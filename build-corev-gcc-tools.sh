#!/bin/bash

# Build script for the CORE-V GCC and GNU tools.

# Copyright (C) 2020 Embecosm Limited
# Contributor Jessica Mills  <jessica_mills@embecosm.com>

# This file is part of the Embecosm GNU toolchain build system for RISC-V.

# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 3 of the License, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.

# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/>.

export ROOT_PREFIX=$(cd ../ && pwd)

export GCC_FOLDER=corev-gcc
export GCC_PREFIX=${ROOT_PREFIX}/${GCC_FOLDER}

export STAGE1_FOLDER=${GCC_FOLDER}-stage1
export STAGE2_FOLDER=${GCC_FOLDER}-stage2

export NEWLIB_FOLDER=riscv-newlib
export NEWLIB_PREFIX=${ROOT_PREFIX}/${NEWLIB_FOLDER}

export BINUTILS_GDB_FOLDER=corev-binutils-gdb
export BINUTILS_GDB_PREFIX=${ROOT_PREFIX}/${BINUTILS_PREFIX}

export BUILD_GCC_FOLDER=build-${GCC_FOLDER}
export BUILD_GCC_PREFIX=${ROOT_PREFIX}/${BUILD_GCC_FOLDER}

export BUILD_BINUTILS_FOLDER=build-${BINUTILS_GDB_FOLDER}
export BUILD_BINUTILS_PREFIX=${ROOT_PREFIX}/${BUILD_BINUTILS_FOLDER}

export INSTALL_FOLDER=toolchain-install
export INSTALL_PREFIX=${ROOT_PREFIX}/${INSTALL_FOLDER}
mkdir -p ${INSTALL_PREFIX}

PARALLEL_JOBS=$(nproc)
DEFAULTARCH=rv32im
DEFAULTABI=ilp32

if [[ $* == *--gcc-stage1* || $* == *--all* ]]; then
    if [[ $* == *--debug* ]]; then
        export BUILD_STAGE1_PREFIX=${BUILD_GCC_PREFIX}-DEBUG/${STAGE1_FOLDER}
    else
        export BUILD_STAGE1_PREFIX=${BUILD_GCC_PREFIX}/${STAGE1_FOLDER}
    fi
    mkdir -p ${GCC_PREFIX}
fi
if [[ $* == *--newlib* || $* == *--all* ]]; then
    if [[ $* == *--debug* ]]; then
        export BUILD_NEWLIB_PREFIX=${BUILD_GCC_PREFIX}-DEBUG/${NEWLIB_FOLDER}
    else
        export BUILD_NEWLIB_PREFIX=${BUILD_GCC_PREFIX}/${NEWLIB_FOLDER}
    fi
    mkdir -p ${GCC_PREFIX}
fi
if [[ $* == *--gcc-stage2* || $* == *--all* ]]; then
    if [[ $* == *--debug* ]]; then
        export BUILD_STAGE2_PREFIX=${BUILD_GCC_PREFIX}-DEBUG/${STAGE2_FOLDER}
    else
        export BUILD_STAGE2_PREFIX=${BUILD_GCC_PREFIX}/${STAGE2_FOLDER}
    fi
    mkdir -p ${GCC_PREFIX}
fi
if [[ $* == *--binutilts-gdb* || $* == *--all* ]]; then
    if [[ $* == *--debug* ]]; then
        export BUILD_BINGDB_PREFIX=${ROOT_PREFIX}/${BUILD_BINUTILS_FOLDER}-DEBUG
    else
        export BUILD_BINGDB_PREFIX=${ROOT_PREFIX}/${BUILD_BINUTILS_FOLDER}
    fi
fi

installs=(
        "riscv32-corev-elf-addr2line"
        "riscv32-corev-elf-nm"
        "riscv32-corev-elf-ar"
        "riscv32-corev-elf-objcopy"
        "riscv32-corev-elf-objdump"
        "riscv32-corev-elf-ranlib"
        "riscv32-corev-elf-c++filt"
        "riscv32-corev-elf-readelf"
        "riscv32-corev-elf-run"
        "riscv32-corev-elf-elfedit"
        "riscv32-corev-elf-gdb"
        "riscv32-corev-elf-size"
        "riscv32-corev-elf-gprof"
        "riscv32-corev-elf-strings"
        "riscv32-corev-elf-ld"
        "riscv32-corev-elf-strip"
        "riscv32-corev-elf-ld.bfd"
        "riscv32-corev-elf-as"
        "riscv32-corev-elf-gcc-ar"
        "riscv32-corev-elf-gcc-nm"
        "riscv32-corev-elf-gcc-ranlib"
        "riscv32-corev-elf-gcov"
        "riscv32-corev-elf-gcov-dump"
        "riscv32-corev-elf-cpp"
        "riscv32-corev-elf-gcov-tool"
        "riscv32-corev-elf-gcc"
        "riscv32-corev-elf-gcc-7.1.1"
        "riscv32-corev-elf-c++"
        "riscv32-corev-elf-g++"

)

if [[ $* == *--help* || $* == *-h* ]]; then
  echo "Usage: build-corev-gcc-tools.sh [--all] [--binutils-gdb] [--gcc-stage1] [--newlib] [--gcc-stage2] [--clean] [--debug] [--help | -h]"
        echo " Builds and installs the PULP tool chain"
        echo " Build directory is the peer directory 'build', install directory is the peer directory 'install'"
        echo " Generates installation summary - this is the only action if no options are specified"
        echo "The options are:"
        echo " --all               Build all components"
        echo " --binutils-gdb      Build binutils and GDB"
        echo " --gcc-stage1        Build GCC stage 1"
        echo " --newlib            Build newlib"
        echo " --gcc-stage2        Build GCC stage 2"
        echo " --clean             Remove build directory"
        echo " --debug             Include debugging CFLAGS"
        echo " --help | -h         Print this help message and exit"
  exit 0
fi


if [[ $* == *--clean* ]]; then
    if [[ -d ${BUILD_STAGE1_PREFIX} ]]; then
        echo Cleaning... ${BUILD_STAGE1_PREFIX}
        rm -rf ${BUILD_STAGE1_PREFIX}
    fi
    if [[ -d ${BUILD_NEWLIB_PREFIX} ]]; then
        echo Cleaning... ${BUILD_NEWLIB_PREFIX}
        rm -rf ${BUILD_NEWLIB_PREFIX}
    fi
    if [[ -d ${BUILD_STAGE2_PREFIX} ]]; then
        echo Cleaning... ${BUILD_STAGE2_PREFIX}
        rm -rf ${BUILD_STAGE2_PREFIX}
    fi
    if [[ -d ${BUILD_BINGDB_PREFIX} ]]; then
        echo Cleaning... ${BUILD_BINGDB_PREFIX}
        rm -rf ${BUILD_BINGDB_PREFIX}
    fi
fi

# Binutils-gdb
if [[ $* == *--binutils-gdb* || $* == *--all* ]]; then
    mkdir -p ${BUILD_BINGDB_PREFIX}
    cd ${BUILD_BINGDB_PREFIX}
    ../${BINUTILS_GDB_FOLDER}/configure        \
        --target=riscv32-corev-elf    \
        --prefix=${INSTALL_PREFIX}       \
        --disable-werror

    #CFLAGS as option for debugging 
    if [[ $* == *--debug* ]]; then
        if ! make CFLAGS="-O0 -ggdb3" -j${PARALLEL_JOBS}; then
            echo "The build has failed during binutils-gdb!" >/dev/stderr
            exit 1
        fi
        if ! make CFLAGS="-O0 -ggdb3" install; then
            echo "The build has failed during binutils-gdb!" >/dev/stderr
            exit 1
        fi
    else
        if ! make -j${PARALLEL_JOBS}; then
            echo "The build has failed during binutils-gdb!" >/dev/stderr
            exit 1
        fi
        if ! make install; then
            echo "The build has failed during binutils-gdb!" >/dev/stderr
            exit 1
        fi
    fi
fi

# GCC (Stage 1)
if [[ $* == *--gcc-stage1*  ||  $* == *--all* ]]; then
    cd ${GCC_PREFIX}
    ./contrib/download_prerequisites
    mkdir -p ${BUILD_STAGE1_PREFIX}
    cd ${BUILD_STAGE1_PREFIX}
    ../../${GCC_FOLDER}/configure                                     \
        --with-system-zlib                                   \
        --target=riscv32-corev-elf                        \
        --prefix=${INSTALL_PREFIX}                           \
        --with-sysroot=${INSTALL_PREFIX}/riscv32-corev-elf \
        --with-newlib                                       \
        --without-headers                                  \
        --disable-shared                                    \
        --enable-languages=c                                \
        --disable-werror                                    \
        --disable-libatomic                                 \
        --disable-libmudflap                                \
        --disable-libssp                                    \
        --disable-quadmath                                  \
        --disable-libgomp                                   \
        --disable-nls                                       \
        --disable-bootstrap                                 \
        --enable-multilib                                   \
        --with-arch=${DEFAULTARCH}                          \
        --with-abi=${DEFAULTABI}
        
    #CFLAGS as option for debugging 
    if [[ $* == *--debug* ]]; then
        if ! make CFLAGS="-O0 -g3" CXXFLAGS="-O0 -g3" -j${PARALLEL_JOBS}; then
            echo "The build has failed during gcc-stage1!" >/dev/stderr
            exit 1
        fi
        if ! make CFLAGS="-O0 -g3" CXXFLAGS="-O0 -g3" install; then
            echo "The build has failed during gcc-stage1!" >/dev/stderr
            exit 1
        fi
    else
        if ! make -j${PARALLEL_JOBS}; then
            echo "The build has failed during gcc-stage1!" >/dev/stderr
            exit 1
        fi
        if ! make install; then
            echo "The build has failed during gcc-stage1!" >/dev/stderr
            exit 1
        fi
    fi
fi

# Newlib - need target tools in PATH from now on
if [[ $* == *--newlib*  ||  $* == *--all* ]]; then
    PATH=${INSTALL_PREFIX}/bin:${PATH}
    mkdir -p ${BUILD_NEWLIB_PREFIX}
    cd ${BUILD_NEWLIB_PREFIX}
    ../../${NEWLIB_FOLDER}/configure            \
        --target=riscv32-corev-elf  \
        --prefix=${INSTALL_PREFIX}     \
        --with-arch=${DEFAULTARCH}    \
        --with-abi=${DEFAULTABI}      \
        --enable-multilib

    #CFLAGS as option for debugging 
    if [[ $* == *--debug* ]]; then
        if ! make CFLAGS="-O0 -ggdb3" -j${PARALLEL_JOBS}; then
            echo "The build has failed during newlib!" >/dev/stderr
            exit 1
        fi
        if ! make CFLAGS="-O0 -ggdb3" install; then
            echo "The build has failed during newlib!" >/dev/stderr
            exit 1
        fi
    else
        if ! make -j${PARALLEL_JOBS}; then
            echo "The build has failed during newlib!" >/dev/stderr
            exit 1
        fi
        if ! make install; then
             echo "The build has failed during newlib!" >/dev/stderr
             exit 1
        fi  
    fi
fi

# GCC (Stage 2)
if [[ $* == *--gcc-stage2*  ||  $* == *--all* ]]; then
    mkdir -p ${BUILD_STAGE2_PREFIX}
    cd ${BUILD_STAGE2_PREFIX}
    ../../${GCC_FOLDER}/configure                                     \
        --with-system-zlib                                   \
        --target=riscv32-corev-elf                        \
        --prefix=${INSTALL_PREFIX}                          \
        --with-sysroot=${INSTALL_PREFIX}/riscv32-corev-elf \
        --with-native-system-header-dir=/include            \
        --with-newlib                                       \
        --disable-shared                                    \
        --enable-languages=c,c++                            \
        --enable-tls                                        \
        --disable-werror                                    \
        --disable-libmudflap                                \
        --disable-libssp                                    \
        --disable-quadmath                                  \
        --disable-libgomp                                   \
        --disable-nls                                       \
        --enable-multilib                                   \
        --with-arch=${DEFAULTARCH}                          \
        --with-abi=${DEFAULTABI}

    #CFLAGS as option for debugging 
    if [[ $* == *--debug* ]]; then
        if ! make CFLAGS="-O0 -g3" CXXFLAGS="-O0 -g3" -j${PARALLEL_JOBS}; then
            echo "The build has failed during gcc-stage2!" >/dev/stderr
            exit 1
        fi
        if ! make CFLAGS="-O0 -g3" CXXFLAGS="-O0 -g3" install; then
            echo "The build has failed during gcc-stage2!" >/dev/stderr
            exit 1
        fi
    else            
        if ! make -j${PARALLEL_JOBS}; then
            echo "The build has failed during gcc-stage2!" >/dev/stderr
            exit 1
        fi
        if ! make install; then
            echo "The build has failed during gcc-stage2!" >/dev/stderr
            exit 1
        fi
    fi
fi

echo ===== Install summary =====
echo ${INSTALL_PREFIX}/bin/
for install in "${installs[@]}"
do
    [ -f ${INSTALL_PREFIX}/bin/${install} ] && echo "${install} ... exists." || echo "${install} ... does not exist."
done
