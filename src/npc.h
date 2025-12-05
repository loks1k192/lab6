#ifndef NPC_H
#define NPC_H

#include <string>
#include <utility>

struct Point { double x, y; };

class BattleVisitor;
class NPC {
protected:
    std::string name_;
    Point pos_;
public:
    NPC(const std::string& name, double x, double y);
    virtual ~NPC();
    std::string name() const;
    Point pos() const;
    virtual std::string type() const = 0;
    virtual std::pair<bool, bool> accept(BattleVisitor& visitor, NPC& other) = 0;
    virtual void print(std::ostream& os) const;
};

class Dragon : public NPC {
public:
    Dragon(const std::string& name, double x, double y);
    std::string type() const override;
    std::pair<bool, bool> accept(BattleVisitor& visitor, NPC& other) override;
};

class Bull : public NPC {
public:
    Bull(const std::string& name, double x, double y);
    std::string type() const override;
    std::pair<bool, bool> accept(BattleVisitor& visitor, NPC& other) override;
};

class Frog : public NPC {
public:
    Frog(const std::string& name, double x, double y);
    std::string type() const override;
    std::pair<bool, bool> accept(BattleVisitor& visitor, NPC& other) override;
};

#endif 