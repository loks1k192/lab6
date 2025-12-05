#include <gtest/gtest.h>
#include "../src/dungeon.h"
#include "../src/factory.h"
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

TEST(DungeonBasic, AddAndCount) {
    DungeonEditor d;
    std::string err;
    auto n1 = NPCFactory::create("dragon", "Dr1", 10, 10);
    EXPECT_TRUE(d.addNPC(std::move(n1), err));
    auto n2 = NPCFactory::create("bull", "Bl1", 12, 12);
    EXPECT_TRUE(d.addNPC(std::move(n2), err));
    EXPECT_EQ(d.npcCount(), 2u);
}

TEST(DungeonLoad, LoadFromFile) {
    std::string fname = "temp_npcs.txt";
    std::ofstream fout(fname);
    fout << "dragon Bobby 100 100\n";
    fout << "bull Bully 120 105\n";
    fout << "frog Froggy 200 200\n";
    fout.close();

    DungeonEditor d;
    bool ok = d.loadFromFile(fname);
    EXPECT_TRUE(ok);
    EXPECT_EQ(d.npcCount(), 3u);

    std::filesystem::remove(fname);
}

TEST(DungeonBattle, DragonEatsBullAndBullTramplesFrog) {
    DungeonEditor d;
    std::string err;
    d.addNPC(NPCFactory::create("dragon", "Draggy", 0, 0), err);
    d.addNPC(NPCFactory::create("bull", "Bully", 1, 1), err);   
    d.addNPC(NPCFactory::create("bull", "Bully2", 100, 100), err);
    d.addNPC(NPCFactory::create("frog", "Klava", 101, 101), err); 

    size_t remaining = d.battleMode(5.0);
    EXPECT_EQ(remaining, 2u);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}