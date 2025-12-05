#include <iostream>
#include "dungeon.h"
#include "factory.h"

int main() {
    DungeonEditor editor;
    std::cout << "=== Balagur Fate 3 ===\n";
    std::cout << "Types: dragon, bull, frog\n";

    while (true) {
        std::cout << "\nMenu:\n1) Add NPC\n2) List NPCs\n3) Save to file\n4) Load from file\n5) Battle mode\n0) Exit\nChoose: ";
        int opt;
        if (!(std::cin >> opt)) break;
        if (opt == 0) break;
        if (opt == 1) {
            std::string type, name;
            double x, y;
            std::cout << "Type: "; std::cin >> type;
            std::cout << "Name: "; std::cin >> name;
            std::cout << "x y: "; std::cin >> x >> y;
            auto npc = NPCFactory::create(type, name, x, y);
            std::string err;
            if (!editor.addNPC(std::move(npc), err)) std::cout << "Error: " << err << "\n";
            else std::cout << "Added.\n";
        }
        else if (opt == 2) {
            editor.listNPCs();
        }
        else if (opt == 3) {
            std::string fname; std::cout << "Filename: "; std::cin >> fname;
            if (editor.saveToFile(fname)) std::cout << "Saved.\n"; else std::cout << "Save failed.\n";
        }
        else if (opt == 4) {
            std::string fname; std::cout << "Filename: "; std::cin >> fname;
            editor.loadFromFile(fname);
        }
        else if (opt == 5) {
            double r; std::cout << "Radius: "; std::cin >> r;
            size_t left = editor.battleMode(r);
            std::cout << "Battle finished. Remaining NPCs: " << left << "\n";
        }
        else {
            std::cout << "Unknown option\n";
        }
    }
    std::cout << "Exit.\n";
    return 0;
}