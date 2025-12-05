#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include <string>
#include <vector>

class NPC;

class NPCFactory {
public:
    static std::unique_ptr<NPC> create(const std::string& type, const std::string& name, double x, double y);
    static std::vector<std::unique_ptr<NPC>> loadFromFile(const std::string& filename, std::vector<std::string>& errors);
};

#endif