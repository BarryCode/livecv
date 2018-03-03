
#//TODO Check if LIVECV_DEV_PATH, LIVECV_BIN_PATH have been set and exist

BUILD_PATH  = $$shadowed($$PROJECT_ROOT)
DEPLOY_PATH = $$LIVECV_BIN_PATH

macx:PLUGIN_DEPLOY_PATH = $$DEPLOY_PATH/PlugIns
else:PLUGIN_DEPLOY_PATH = $$DEPLOY_PATH/plugins

macx:LIBRARY_DEPLOY_PATH = $$DEPLOY_PATH/Frameworks/live.framework
else:LIBRARY_DEPLOY_PATH = $$DEPLOY_PATH

macx:QMAKE_SONAME_PREFIX = @rpath

include($$PWD/functions.pri)
