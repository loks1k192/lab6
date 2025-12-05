#ifndef BATTLE_H
#define BATTLE_H

#include <utility>

class NPC;
class Dragon;
class Bull;
class Frog;

class BattleVisitor {
public:
    // return pair<attackerDies, defenderDies>
    std::pair<bool, bool> visit(Dragon& a, NPC& b);
    std::pair<bool, bool> visit(Bull& a, NPC& b);
    std::pair<bool, bool> visit(Frog& a, NPC& b);
};

#endif 