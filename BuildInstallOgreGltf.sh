#!/bin/sh

# "Install" Ogre where we expect
# This is redundant with my CloneBuildOgre.sh
cd Ogre/ogre/build/Release
export DESTDIR="$HOME/Ogre/LocalInstall" && ninja -j4 install

# Build Ogre_glTF
cd ../../../../
mkdir build_ogre_gltf
cd build_ogre_gltf
cmake ../Ogre_glTF -DOGRE_SOURCE="$HOME/Ogre/LocalInstall/usr/local" -DOGRE_BUILD="$HOME/Ogre/LocalInstall/usr/local"
make

# Copy Ogre resources for glTF samples
cp -r $HOME/Ogre/LocalInstall/usr/local/share/OGRE/Media/Hlms .
cp -r $HOME/Ogre/LocalInstall/usr/local/lib/OGRE/* .
cp $HOME/Ogre/LocalInstall/usr/local/share/OGRE/plugins.cfg .
cp $HOME/Ogre/LocalInstall/usr/local/share/OGRE/resources2.cfg .
# Replace the /usr dir in configs with local install
sed -i "s+=/usr+=$HOME/Ogre/LocalInstall/usr+g" plugins.cfg resources2.cfg
# :( damn relative paths (Ogre_glTF hard codes it)
mkdir ../Media
cp -r ../Ogre_glTF/Media/* ../Media/

# To run sample:
# cd build_ogre_gltf
# ./LoadMesh

# Install Ogre_glTF
# TODO
