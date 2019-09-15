#!/bin/sh

# TODO These aren't used because resources2.cfg sets the path
# mkdir data
# cp -r Ogre/ogre/Samples/Media/Hlms/Common data/Common
# cp -r Ogre/ogre/Samples/Media/Hlms/Pbs data/Pbs
# cp -r Ogre/ogre/Samples/Media/Hlms/Unlit data/Unlit
# cp -r Ogre/ogre/Samples/Media/2.0/scripts/materials/Common data/CommonMaterials

# Copy source files
cp -r Ogre/ogre/Samples/2.0/Tutorials/Tutorial06_Multithreading/*.cpp src/
cp -r Ogre/ogre/Samples/2.0/Tutorials/Tutorial06_Multithreading/*.h src/

# Copy config files
cp Ogre/ogre/build/Release/bin/plugins.cfg .
cp Ogre/ogre/build/Release/bin/resources2.cfg .
