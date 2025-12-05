#include "battle.h"
#include "npc.h"
#include <string>

std::pair<bool, bool> BattleVisitor::visit(Dragon& a, NPC& b) {
    std::string t = b.type();
    if (t == "bull") return { false, true };   
    if (t == "dragon") return { true, true };  
    if (t == "frog") return { false, false };  
    return { false,false };
}

std::pair<bool, bool> BattleVisitor::visit(Bull& a, NPC& b) {
    std::string t = b.type();
    if (t == "frog") return { false, true };   
    if (t == "bull") return { true, true };    
    if (t == "dragon") return { true, false }; 
    return { false,false };
}

std::pair<bool, bool> BattleVisitor::visit(Frog& a, NPC& b) {
    std::string t = b.type();
    if (t == "frog") return { true, true };    
    return { false,false };                    
}