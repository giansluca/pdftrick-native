if [ $TRAVIS_OS_NAME = 'osx' ]; then
  export SSHPASS=$DEPLOY_PASS
  sshpass -e scp \
  -o stricthostkeychecking=no \
  dist/mac/release/pdftrick-native.* \
  $DEPLOY_USER@$DEPLOY_HOST:/home/gians/test-deploy
else
  pscp \
  -pw $DEPLOY_PASS \
  -hostkey $SERVER_FINGERPRINT \
  -P 22 \
  dist/win/release/pdftrick-native.* \
  $DEPLOY_USER@$DEPLOY_HOST:/home/gians/test-deploy
fi

