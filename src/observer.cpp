#include "observer.h"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <iomanip>

void DeathSubject::subscribe(DeathObserver* obs) {
    observers_.push_back(obs);
}
void DeathSubject::unsubscribe(DeathObserver* obs) {
    observers_.erase(std::remove(observers_.begin(), observers_.end(), obs), observers_.end());
}
void DeathSubject::notify(const std::string& killerName, const std::string& victimName, const std::string& reason) {
    for (auto o : observers_) o->onDeath(killerName, victimName, reason);
}

void DeathPrinter::onDeath(const std::string& killerName, const std::string& victimName, const std::string& reason) {
    if (killerName.empty())
        std::cout << "[DEATH] " << victimName << " died: " << reason << "\n";
    else
        std::cout << "[DEATH] " << killerName << " killed " << victimName << ": " << reason << "\n";
}

DeathLogger::DeathLogger(const std::string& filename) {
    fout_.open(filename, std::ios::app);
    if (!fout_) {
        std::cerr << "Cannot open log file: " << filename << "\n";
    }
}
DeathLogger::~DeathLogger() {
    if (fout_) fout_.close();
}
void DeathLogger::onDeath(const std::string& killerName, const std::string& victimName, const std::string& reason) {
    if (!fout_) return;
    if (killerName.empty())
        fout_ << victimName << " died: " << reason << "\n";
    else
        fout_ << killerName << " killed " << victimName << ": " << reason << "\n";
}