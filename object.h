
#pragma once

#include <string>
using namespace std;

class Object {
private:
    string name;

public:
    Object(string n) : name(n) {}

    string get_name();
};

// Object declarations
extern Object chair;
extern Object knocker;