#pragma once
#include <string>

class Characters;

class Item
{
protected:
    std::string Name;
public:
    Item(const std::string& name) : Name(name) {}
    virtual ~Item() {}
    virtual std::string GetName() const { return Name; }
    virtual void Use(Characters& target) = 0;
};
