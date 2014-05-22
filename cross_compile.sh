#!/bin/bash

function build_for {
  CC=$1
  CXX=$2
  BUILD_DIR=build-$CC

  mkdir $BUILD_DIR
  pushd $BUILD_DIR
  CC=$CC CXX=$CXX cmake ../..
  make
  popd
}

if [[ -d builds ]]; then
  rm -rf builds
fi

mkdir builds
pushd builds

build_for gcc-4.8 g++-4.8
GCC48=$?

build_for gcc-4.9 g++-4.9
GCC49=$?

build_for clang clang++
CLANG=$?

popd

echo
echo "Result:"
echo -e "gcc-4.8:\t$GCC48"
echo -e "gcc-4.9:\t$GCC49"
echo -e "clang:\t$CLANG"
echo "Done"
exit $(( $GCC48 + $GCC49 + $CLANG ))
