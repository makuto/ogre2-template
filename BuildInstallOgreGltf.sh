#!/bin/sh

# "Install" Ogre where we expect
cd Ogre/ogre/build/Release
# export DESTDIR="OgreInstall_Release" && ninja -j4 install
export DESTDIR="$HOME/Ogre/LocalInstall" && ninja -j4 install

cd ../../../../
mkdir build_ogre_gltf
cd build_ogre_gltf
# cmake ../Ogre_glTF -DOGRE_SOURCE="Ogre/ogre/build/Release/OgreInstall_Release/usr/local" -DOGRE_BUILD="Ogre/ogre/build/Release/OgreInstall_Release/usr/local"

# Working with
# In build/Release:
# export DESTDIR="$HOME/Software/LocalInstall" && ninja -j4 install
cmake ../Ogre_glTF -DOGRE_SOURCE="$HOME/Ogre/LocalInstall/usr/local" -DOGRE_BUILD="$HOME/Ogre/LocalInstall/usr/local"

make
