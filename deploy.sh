if [ $TRAVIS_OS_NAME = 'osx' ]; then
  export SSHPASS=$DEPLOY_PASS
  sshpass -e scp ./dist/mac/release/libpdftrick_native_1.7a_64.jnilib $DEPLOY_USER@$DEPLOY_HOST:/home/gians/test-deploy
else
  pscp -pw $DEPLOY_PASS ./dist/win/release/libpdftrick_native_1.7a_64.dll $DEPLOY_USER@$DEPLOY_HOST:/home/gians/test-deploy
fi

