# protobuf
[Google Protocol Buffers](https://developers.google.com/protocol-buffers/)尝试.    

## 实验环境
- `macOS Mojave, Version 10.14.4 (18E226)`
- `Apple LLVM version 10.0.1 (clang-1001.0.46.4)`
- `cmake version 3.13.3`

### Installation
Refer to [Protocol Buffers Compiler C++ Installation Instructions](https://github.com/protocolbuffers/protobuf/blob/master/src/README.md) for more details.    
```bash
$ brew install autoconf automake libtool
$ 
$ git clone https://github.com/protocolbuffers/protobuf.git
$ cd protobuf
$ git submodule update --init --recursive
$ ./autogen.sh
$ ./configure
$ make
$ make check
$ sudo make install
$
$ cd ~
$ protoc --version
libprotoc 3.7.1
```

## 实验

### 生成protobuf的接口代码
```bash
# generate codes for proto2
$ cd proto2
$ protoc --cpp_out=. addressbook.proto 
$ protoc --python_out=. addressbook.proto 
$ 
# generate codes for proto3
$ cd proto3
$ protoc --cpp_out=. addressbook.proto
$ protoc --python_out=. addressbook.proto
```

### C++ Sample Code
```bash
# generate executable binaries
$ cd proto2  # or `cd proto3`
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$
# test 
$ ./write_main addressbook1
# ...
$ ./read_main addressbook1
# ...
```

## References
- [protobuf repo on Github](https://github.com/protocolbuffers/protobuf)
- [Google Protocol Buffers](https://developers.google.com/protocol-buffers/)
- [Protocol Buffers Compiler C++ Installation Instructions](https://github.com/protocolbuffers/protobuf/blob/master/src/README.md)
- [Protocol Buffers Developer Guide Overview](https://developers.google.com/protocol-buffers/docs/overview)
- [Language Guide (proto3)](https://developers.google.com/protocol-buffers/docs/proto3)
- [Language Guide (proto2)](https://developers.google.com/protocol-buffers/docs/proto)
- [Protocol Buffers Basic: C++](https://developers.google.com/protocol-buffers/docs/cpptutorial)
- [Protocol Buffer Basics: Python](https://developers.google.com/protocol-buffers/docs/pythontutorial)
- [Protocol Buffer Basics: Go](https://developers.google.com/protocol-buffers/docs/gotutorial)
- [Protocol Buffers Encoding](https://developers.google.com/protocol-buffers/docs/encoding)
- [OSM PBF Format](https://wiki.openstreetmap.org/wiki/PBF_Format)

