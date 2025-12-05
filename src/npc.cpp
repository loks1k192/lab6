#include "npc.h"
#include "battle.h"
#include <ostream>

NPC::NPC(const std::string& name, double x, double y) : name_(name), pos_{ x,y } {}
NPC::~NPC() = default;
std::string NPC::name() const { return name_; }
Point NPC::pos() const { return pos_; }
void NPC::print(std::ostream& os) const {
    os << type() << " " << name_ << " (" << pos_.x << ", " << pos_.y << ")";
}

Dragon::Dragon(const std::string& name, double x, double y) : NPC(name, x, y) {}
std::string Dragon::type() const { return "dragon"; }
std::pair<bool, bool> Dragon::accept(BattleVisitor& visitor, NPC& other) { return visitor.visit(*this, other); }

Bull::Bull(const std::string& name, double x, double y) : NPC(name, x, y) {}
std::string Bull::type() const { return "bull"; }
std::pair<bool, bool> Bull::accept(BattleVisitor& visitor, NPC& other) { return visitor.visit(*this, other); }

Frog::Frog(const std::string& name, double x, double y) : NPC(name, x, y) {}
std::string Frog::type() const { return "frog"; }
std::pair<bool, bool> Frog::accept(BattleVisitor& visitor, NPC& other) { return visitor.visit(*this, other); }