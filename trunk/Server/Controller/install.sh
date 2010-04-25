#!/bin/sh

echo "Building MLBServer..."
make

if [ $? -ne 0 ]
then
    echo "Build failed... Try getting a newer version from http://magiclegoblimps.googlecode.com/downloads/list"
    exit 1
fi

echo "Installing libraries to /usr/local/lib"
arch = `uname -r |grep 64`
if [ "$arch." = "64." ]
then
    cp -f lib/*64.so /usr/local/lib/
    if [ $? -ne 0 ]
    then
        echo "Library install failed.  Are you root?"
	exit 1
    fi
else
    cp -f lib/*32.so /usr/local/lib/
    if [ $? -ne 0 ]
    then
        echo "Library install failed.  Are you root?"
	exit 1
    fi
fi

echo "Installing MLBServer binary to /usr/local/bin"
cp -f build/ServerController /usr/local/bin/MLBServer
if [ $? -ne 0 ]
then
    echo "Install failed. Are you root?"
    exit 1
fi


echo "Done!"
exit 0
