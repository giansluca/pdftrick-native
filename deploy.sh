git checkout $TRAVIS_BRANCH
git tag v$GIT_TAG_VERSION -a -m "Tagging version v$GIT_TAG_VERSION"
git push origin $TRAVIS_BRANCH --tags 2>&1

if [ $TRAVIS_OS_NAME = 'osx' ]; then
  export SSHPASS=$DEPLOY_PASS
  sshpass -e scp \
  -o stricthostkeychecking=no \
  dist/mac/release/libpdftrick_native_1.7a_64.jnilib \
  $DEPLOY_USER@$DEPLOY_HOST:/home/gians/test-deploy
else
  pscp \
  -pw $DEPLOY_PASS \
  -hostkey $SERVER_FINGERPRINT \
  -P 22 \
  dist/win/release/libpdftrick_native_1.7a_64.dll \
  $DEPLOY_USER@$DEPLOY_HOST:/home/gians/test-deploy
fi

