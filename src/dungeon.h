#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <memory>
#include <string>

#include "npc.h"
#include "factory.h"
#include "observer.h"

class NPC;
class DeathSubject;

class DungeonEditor {
    std::vector<std::unique_ptr<NPC>> npcs_;
    DeathSubject deathSubject_;
    std::unique_ptr<class DeathPrinter> printerObs_;
    std::unique_ptr<class DeathLogger> loggerObs_;
public:
    DungeonEditor();
    ~DungeonEditor();

    bool nameExists(const std::string& name) const;
    bool addNPC(std::unique_ptr<NPC> npc, std::string& err);
    void listNPCs() const;
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    size_t battleMode(double radius);
    size_t npcCount() const;
};

double distance(const NPC& a, const NPC& b);

#endif 