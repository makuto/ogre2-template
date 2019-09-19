#!/bin/bash

OGRE_BRANCH_NAME="v2-1"

mkdir Ogre
cd Ogre
if test ! -f ogredeps; then
	mkdir ogredeps
	echo "--- Cloning Ogredeps ---"
	hg clone https://bitbucket.org/cabalistic/ogredeps ogredeps
else
	echo "--- Ogredeps repo detected. Cloning skipped ---"
fi
cd ogredeps
mkdir build
cd build
echo "--- Building Ogredeps ---"
cmake  -G Ninja ..
ninja
ninja install

cd ../../
if test ! -f ogre; then
	mkdir ogre
	echo "--- Cloning Ogre v2-1 ---"
	hg clone https://bitbucket.org/sinbad/ogre -r ${OGRE_BRANCH_NAME} ogre
fi
cd ogre
if test ! -f Dependencies; then
	ln -s ../ogredeps/build/ogredeps Dependencies
fi
mkdir -p build/Debug
mkdir -p build/Release
cd build/Debug
echo "--- Building Ogre (Debug) ---"
cmake -D OGRE_USE_BOOST=0 -D OGRE_CONFIG_THREAD_PROVIDER=0 -D OGRE_CONFIG_THREADS=0 -D OGRE_BUILD_COMPONENT_SCENE_FORMAT=1 -D OGRE_BUILD_SAMPLES2=1 -D OGRE_BUILD_TESTS=1 -D CMAKE_BUILD_TYPE="Debug"  -G Ninja ../..
ninja
cd ../Release
echo "--- Building Ogre (Release) ---"
cmake -D OGRE_USE_BOOST=0 -D OGRE_CONFIG_THREAD_PROVIDER=0 -D OGRE_CONFIG_THREADS=0 -D OGRE_BUILD_COMPONENT_SCENE_FORMAT=1 -D OGRE_BUILD_SAMPLES2=1 -D OGRE_BUILD_TESTS=1 -D CMAKE_BUILD_TYPE="Release"  -G Ninja ../..
ninja

echo "Done!"

# Macoy's additions
# Install ogre locally to build Gltf
cd Ogre/ogre/build/Release
# export DESTDIR="OgreInstall_Release" && ninja -j4 install
export DESTDIR="$HOME/Ogre/LocalInstall" && ninja -j4 install
