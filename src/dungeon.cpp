#include "dungeon.h"
#include "npc.h"
#include "factory.h"
#include "observer.h"
#include "battle.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <algorithm>

DungeonEditor::DungeonEditor() {
    printerObs_ = std::make_unique<DeathPrinter>();
    loggerObs_ = std::make_unique<DeathLogger>("log.txt");
    deathSubject_.subscribe(printerObs_.get());
    deathSubject_.subscribe(loggerObs_.get());
}
DungeonEditor::~DungeonEditor() = default;

bool DungeonEditor::nameExists(const std::string& name) const {
    for (auto& p : npcs_) if (p->name() == name) return true;
    return false;
}

bool DungeonEditor::addNPC(std::unique_ptr<NPC> npc, std::string& err) {
    if (!npc) { err = "Null NPC"; return false; }
    if (npc->pos().x < 0 || npc->pos().x > 500 || npc->pos().y < 0 || npc->pos().y > 500) {
        err = "Coordinates must be in 0..500";
        return false;
    }
    if (nameExists(npc->name())) {
        err = "Name '" + npc->name() + "' already exists";
        return false;
    }
    npcs_.push_back(std::move(npc));
    return true;
}

void DungeonEditor::listNPCs() const {
    if (npcs_.empty()) {
        std::cout << "No NPCs.\n";
        return;
    }
    std::cout << "NPCs (" << npcs_.size() << "):\n";
    for (auto& p : npcs_) {
        std::cout << p->type() << " " << p->name() << " (" << p->pos().x << ", " << p->pos().y << ")\n";
    }
}

bool DungeonEditor::saveToFile(const std::string& filename) const {
    std::ofstream fout(filename);
    if (!fout) return false;
    for (auto& p : npcs_) {
        fout << p->type() << " " << p->name() << " " << p->pos().x << " " << p->pos().y << "\n";
    }
    return true;
}

bool DungeonEditor::loadFromFile(const std::string& filename) {
    std::vector<std::string> errors;
    auto loaded = NPCFactory::loadFromFile(filename, errors);

    for (auto& e : errors) std::cout << "Load error: " << e << "\n";

    if (loaded.empty()) {
        std::cout << "No valid NPCs in file. Current state is saved.\n";
        return false;
    }

    std::vector<std::string> seenNames;
    std::vector<std::unique_ptr<NPC>> newlist;
    for (auto& npc_ptr : loaded) {
        if (!npc_ptr) continue;
        if (std::find(seenNames.begin(), seenNames.end(), npc_ptr->name()) != seenNames.end()) {
            std::cout << "Duplicate name in file: " << npc_ptr->name() << " — skipped\n";
            continue;
        }
        seenNames.push_back(npc_ptr->name());
        newlist.push_back(std::move(npc_ptr));
    }

    npcs_ = std::move(newlist);

    std::cout << "Loading completed. Total NPC: " << npcs_.size() << "\n";
    return true;
}

double distance(const NPC& a, const NPC& b) {
    auto pa = a.pos(), pb = b.pos();
    double dx = pa.x - pb.x, dy = pa.y - pb.y;
    return std::sqrt(dx * dx + dy * dy);
}

size_t DungeonEditor::battleMode(double radius) {
    BattleVisitor visitor;
    bool anyFight = true;
    while (anyFight) {
        anyFight = false;
        if (npcs_.size() < 2) break;
        size_t n = npcs_.size();
        std::vector<bool> alive(n, true);
        for (size_t i = 0; i < n; ++i) {
            if (!alive[i]) continue;
            for (size_t j = i + 1; j < n; ++j) {
                if (!alive[j]) continue;
                double d = distance(*npcs_[i], *npcs_[j]);
                if (d <= radius) {
                    anyFight = true;
                    auto res = npcs_[i]->accept(visitor, *npcs_[j]);
                    bool attackerDies = res.first;
                    bool defenderDies = res.second;
                    if (attackerDies && !defenderDies) {
                        deathSubject_.notify(npcs_[j]->name(), npcs_[i]->name(),
                            npcs_[j]->type() + " defeated " + npcs_[i]->type());
                        alive[i] = false;
                    }
                    else if (!attackerDies && defenderDies) {
                        deathSubject_.notify(npcs_[i]->name(), npcs_[j]->name(),
                            npcs_[i]->type() + " defeated " + npcs_[j]->type());
                        alive[j] = false;
                    }
                    else if (attackerDies && defenderDies) {
                        deathSubject_.notify("", npcs_[i]->name(), std::string("mutual destruction with ") + npcs_[j]->name());
                        deathSubject_.notify("", npcs_[j]->name(), std::string("mutual destruction with ") + npcs_[i]->name());
                        alive[i] = false;
                        alive[j] = false;
                    }
                    else {
                        
                    }
                }
            }
        }
        std::vector<std::unique_ptr<NPC>> newlist;
        for (size_t i = 0; i < n; ++i) if (alive[i]) newlist.push_back(std::move(npcs_[i]));
        npcs_ = std::move(newlist);
    }
    return npcs_.size();
}

size_t DungeonEditor::npcCount() const { return npcs_.size(); }