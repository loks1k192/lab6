#include "factory.h"
#include "npc.h"
#include <fstream>
#include <sstream>
#include <algorithm>

std::unique_ptr<NPC> NPCFactory::create(const std::string& type, const std::string& name, double x, double y) {
    std::string lc = type;
    std::transform(lc.begin(), lc.end(), lc.begin(), ::tolower);
    if (lc == "dragon") return std::make_unique<Dragon>(name, x, y);
    if (lc == "bull")    return std::make_unique<Bull>(name, x, y);
    if (lc == "frog")   return std::make_unique<Frog>(name, x, y);
    return nullptr;
}

std::vector<std::unique_ptr<NPC>> NPCFactory::loadFromFile(const std::string& filename, std::vector<std::string>& errors) {
    std::vector<std::unique_ptr<NPC>> res;
    std::ifstream fin(filename);
    if (!fin) {
        errors.push_back("Cannot open file: " + filename);
        return res;
    }
    std::string line;
    int lineno = 0;
    while (std::getline(fin, line)) {
        lineno++;
        auto trim = [](std::string s)->std::string {
            size_t a = s.find_first_not_of(" \t\r\n");
            if (a == std::string::npos) return "";
            size_t b = s.find_last_not_of(" \t\r\n");
            return s.substr(a, b - a + 1);
            };
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;
        std::istringstream iss(line);
        std::string type, name;
        double x, y;
        if (!(iss >> type >> name >> x >> y)) {
            errors.push_back("Bad format at line " + std::to_string(lineno) + ": " + line);
            continue;
        }
        if (x < 0 || x > 500 || y < 0 || y > 500) {
            errors.push_back("Coords out of range at line " + std::to_string(lineno));
            continue;
        }
        auto npc = create(type, name, x, y);
        if (!npc) {
            errors.push_back("Unknown type '" + type + "' at line " + std::to_string(lineno));
            continue;
        }
        res.push_back(std::move(npc));
    }
    return res;
}