if [ $TRAVIS_OS_NAME = 'osx' ]; then
  make -f mac-Makefile release
else
  make -f .\win-Makefile release
fi

echo "Build Done"