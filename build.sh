set -xe

clang --target=wasm32 --no-standard-libraries -Wl,--export-table -Wl,--no-entry -Wl,--allow-undefined -Wl,--export=main -o web/main.wasm src/main.c -DPLATFORM_WEB
gcc -o ./linux/main.out ./linux/raylib_wrapper.c src/main.c -lraylib
