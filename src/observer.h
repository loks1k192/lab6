#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <vector>
#include <fstream>
#include <memory>

class DeathObserver {
public:
    virtual ~DeathObserver() {}
    virtual void onDeath(const std::string& killerName, const std::string& victimName, const std::string& reason) = 0;
};

class DeathSubject {
    std::vector<DeathObserver*> observers_;
public:
    void subscribe(DeathObserver* obs);
    void unsubscribe(DeathObserver* obs);
    void notify(const std::string& killerName, const std::string& victimName, const std::string& reason);
};

class DeathPrinter : public DeathObserver {
public:
    void onDeath(const std::string& killerName, const std::string& victimName, const std::string& reason) override;
};

class DeathLogger : public DeathObserver {
    std::ofstream fout_;
public:
    explicit DeathLogger(const std::string& filename = "log.txt");
    ~DeathLogger();
    void onDeath(const std::string& killerName, const std::string& victimName, const std::string& reason) override;
};

#endif 