
#include "monster_generated.h"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {

    // Create a `FlatBufferBuilder`, which will be used to create our
    // monsters' FlatBuffers.
    flatbuffers::FlatBufferBuilder builder(1024);

    auto weapon_one_name = builder.CreateString("Sword");
    short weapon_one_damage = 3;
    auto weapon_two_name = builder.CreateString("Axe");
    short weapon_two_damage = 5;

    // Use the `CreateWeapon` shortcut to create Weapons with all the fields set.
    auto sword = MyGame::Sample::CreateWeapon(builder, weapon_one_name, weapon_one_damage);
    auto axe = MyGame::Sample::CreateWeapon(builder, weapon_two_name, weapon_two_damage);

    // Place the weapons into a `std::vector`, then convert that into a FlatBuffer `vector`.
    std::vector<flatbuffers::Offset<MyGame::Sample::Weapon>> weapons_vector;
    weapons_vector.push_back(sword);
    weapons_vector.push_back(axe);
    auto weapons = builder.CreateVector(weapons_vector);

    // Serialize a name for our monster, called "Orc".
    auto name = builder.CreateString("Orc");

    // Create a `vector` representing the inventory of the Orc. Each number
    // could correspond to an item that can be claimed after he is slain.
    unsigned char treasure[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto inventory = builder.CreateVector(treasure, 10);

    MyGame::Sample::Vec3 points[] = { MyGame::Sample::Vec3(1.0f, 2.0f, 3.0f), MyGame::Sample::Vec3(4.0f, 5.0f, 6.0f) };
    auto path = builder.CreateVectorOfStructs(points, 2);

    // Create the position struct
    auto position = MyGame::Sample::Vec3(1.0f, 2.0f, 3.0f);
    // Set his hit points to 300 and his mana to 150.
    int hp = 300;
    int mana = 150;

    // Finally, create the monster using the `CreateMonster` helper function
    // to set all fields.
    auto orc = MyGame::Sample::CreateMonster(builder, &position, mana, hp, name, inventory,
                            MyGame::Sample::Color_Red, weapons, MyGame::Sample::Equipment_Weapon, axe.Union(),
                            path);
    

    // Finally, or create monster via builder
    // auto monster_builder = MyGame::Sample::MonsterBuilder(builder);
    // monster_builder.add_color(MyGame::Sample::Color_Red);
    // monster_builder.add_equipped(axe.Union());
    // monster_builder.add_equipped_type(MyGame::Sample::Equipment_Weapon);
    // monster_builder.add_path(path);
    // monster_builder.add_pos(&position);
    // monster_builder.add_mana(mana);
    // monster_builder.add_hp(hp);
    // monster_builder.add_inventory(inventory);
    // auto orc = monster_builder.Finish();

    // Call `Finish()` to instruct the builder that this monster is complete.
    // Note: Regardless of how you created the `orc`, you still need to call
    // `Finish()` on the `FlatBufferBuilder`.
    builder.Finish(orc); // You could also call `FinishMonsterBuffer(builder, orc);`.

    // This must be called after `Finish()`.
    uint8_t *buf = builder.GetBufferPointer();
    int size = builder.GetSize(); // Returns the size of the buffer that `GetBufferPointer()` points to.

    std::string file_name = "monster.bin";
    std::ofstream output(file_name, std::ofstream::out | std::ofstream::binary);
    output.write((const char*)buf, size);
    output.close();

    std::cout << "monster has been written to file \"" << file_name << "\", buffer size: " << size << " bytes" << std::endl;
    return 0;
}