#!/bin/sh

VERSION="0.2.0"

echo -n "Running aclocal ... "
aclocal && echo "OK" || echo "FAILED"
echo -n "Running autoconf ... "
autoconf && echo "OK" || echo "FAILED"
echo -n "Running automake ... "
automake -a -c && echo "OK" || echo "FAILED"
