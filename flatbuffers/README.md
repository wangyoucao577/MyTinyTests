# FlatBuffers
[Google FlatBuffers](https://google.github.io/flatbuffers) 尝试.    

## 实验环境
- `Debian GNU/Linux 9 (stretch)`
- `gcc (Debian 6.3.0-18+deb9u1) 6.3.0 20170516`
- `cmake version 3.7.2`
- https://github.com/google/flatbuffers/commit/4363c1d2cb898768073128bb92db9d4c63b43300

## Test  
```bash
$ cd ${YOUR_WORKSPACE}  # your workspace path
$ git clone https://github.com/google/flatbuffers
$ 
$ # build flatbuffers, especially `flatc`
$ cd flatbuffers
$ cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
$ cmake --build . -- -j
$ ./flattests
ALL TESTS PASSED
$ ./flatc -h 
# helper of flatc
$ 
$ # cd this folder
$ cd cpp
$ 
$ # generate cpp header 
$ ${YOUR_WORKSPACE}/flatbuffers/flatc --cpp ../monster.fbs
$ 
$ # build
$ mkdir -p build 
$ cd build 
$ cmake .. -DFLATBUFFERS_SRC_DIR=${YOUR_WORKSPACE}/flatbuffers/
$ cmake --build . -- -j
$ 
$ # create/read
$ ./build_monster
monster has been written to file "monster.bin", buffer size: 188 bytes
$ ./read_monster
Reading 188 characters...
all characters read successfully.
hp: 300
mana: 150
name: Orc
$ 
$ # binary to/from json
$ ${YOUR_WORKSPACE}/flatbuffers/flatc --json --strict-json --raw-binary ../../monster.fbs -- ./monster.bin
$ cat monster.json
$ ${YOUR_WORKSPACE}/flatbuffers/flatc -b ../../monster.fbs monster.json
$ ll monster.bin
$ 
```

## 参考
- https://google.github.io/flatbuffers
- https://github.com/google/flatbuffers

