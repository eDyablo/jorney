#!/bin/sh
startDir=`pwd`
scriptDir=`dirname $0`
cd $scriptDir/jamplus
git submodule init
git submodule update
./bootstrap-macosx32.sh
result=$?
cd $startDir
exit $result