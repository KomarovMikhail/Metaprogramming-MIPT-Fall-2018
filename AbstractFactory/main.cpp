/*
 * Simple example implementation of Abstract Factory
 */

#include <iostream>
#include <vector>

class Unit {
protected:
    int health;
    int attack;
    int speed;

public:
    Unit(int h, int a, int s): health(h), attack(a), speed(s) {};
    virtual ~Unit() {};
    virtual void getInfo() = 0;
};

class Archer: public Unit {
public:
    Archer(int h, int a, int s): Unit(h, a, s) {};
    void getInfo() {
        std::cout << "This is archer:\n|speed: " << this->speed << "\n|health: " << this->health
                  << "\n|attack: " << this->attack << std::endl;
    }
};

class Swordsman: public Unit {
public:
    Swordsman(int h, int a, int s): Unit(h, a, s) {};
    void getInfo() {
        std::cout << "This is swordsman:\n|speed: " << this->speed << "\n|health: " << this->health
                  << "\n|attack: " << this->attack << std::endl;
    }
};

class Horseman: public Unit {
public:
    Horseman(int h, int a, int s): Unit(h, a, s) {};
    void getInfo() {
        std::cout << "This is horseman:\n|speed: " << this->speed << "\n|health: " << this->health
                  << "\n|attack: " << this->attack << std::endl;
    }
};


class AbstractFactory {
public:
    virtual Archer* createArcher() = 0;
    virtual Swordsman* createSwordsman() = 0;
    virtual Horseman* createHorseman() = 0;
    virtual ~AbstractFactory() {};
};

class FactoryEasyLevel: public AbstractFactory{
public:
    Archer* createArcher() {
        return new Archer(100, 50, 70);
    }
    Swordsman* createSwordsman() {
        return new Swordsman(100, 100, 50);
    }
    Horseman* createHorseman() {
        return new Horseman(100, 100, 100);
    }
};

class FactoryNormalLevel: public AbstractFactory{
public:
    Archer* createArcher() {
        return new Archer(110, 60, 80);
    }
    Swordsman* createSwordsman() {
        return new Swordsman(110, 110, 60);
    }
    Horseman* createHorseman() {
        return new Horseman(110, 110, 110);
    }
};

class FactoryHardLevel: public AbstractFactory{
public:
    Archer* createArcher() {
        return new Archer(120, 70, 90);
    }
    Swordsman* createSwordsman() {
        return new Swordsman(120, 120, 70);
    }
    Horseman* createHorseman() {
        return new Horseman(120, 120, 120);
    }
};

int main() {
    std::vector<Unit*> army;
    FactoryHardLevel * factory = new FactoryHardLevel;
    army.push_back(factory->createArcher());
    army.push_back(factory->createSwordsman());
    army.push_back(factory->createHorseman());
    for (auto item = army.begin(); item != army.end(); item++) {
        (*item)->getInfo();
    }
    return 0;
}
