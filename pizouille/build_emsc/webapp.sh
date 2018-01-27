#emscripten should be installed
#EMSCRIPTEN value is set by the emscripten
#installation script :
#source ~/emsdk-portable/emsdk_env.sh
cmake -DCMAKE_TOOLCHAIN_FILE="$EMSCRIPTEN/cmake/Modules/Platform/emscripten.cmake" -G"Unix Makefiles" ..
python ../../oxygine-framework/tools/others/embed_folder_js.py -s ../res
mv data.js ..
