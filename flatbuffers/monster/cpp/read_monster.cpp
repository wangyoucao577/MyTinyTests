
#include "monster_generated.h"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {

    std::string file_name = "monster.bin";
    std::ifstream is(file_name, std::ifstream::in | std::ifstream::binary);
    if (!is) {
        std::cerr << "load file " << file_name << " failed!" << std::endl;
        return -1;
    }

    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);

    char * buffer = new char [length];

    std::cout << "Reading " << length << " characters... " << std::endl;
    // read data as a block:
    is.read (buffer,length);

    if (is){
        std::cout << "all characters read successfully." << std::endl;
    }else{
        std::cout << "error: only " << is.gcount() << " could be read" << std::endl;
    }
    is.close();

    // ...buffer contains the entire file...

    uint8_t *buffer_pointer = (uint8_t *)buffer; /* the data you just read */
    // Get a pointer to the root object inside the buffer.
    auto monster = MyGame::Sample::GetMonster(buffer_pointer);

    std::cout << "hp: " << monster->hp() << std::endl;
    std::cout << "mana: " << monster->mana() << std::endl;
    std::cout << "name: " << monster->name()->str() << std::endl;


    delete[] buffer;
    return 0;
}