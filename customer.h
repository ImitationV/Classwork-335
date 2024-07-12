#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <cstdlib>

struct Customer {
    std::string name;
    int service_time;
    int priority_level;

    Customer(const std::string& name) : name(name) {
        SetPriorityLevel();
    }

    void SetPriorityLevel() {
        priority_level = rand() % 101; // Random priority between 0 and 100
    }

    void SetServiceTime() {
        service_time = rand() % 61; // Random service time between 0 and 60
    }

    bool operator<(const Customer& other) const {
        return priority_level < other.priority_level;
    }

    bool operator>(const Customer& other) const {
        return priority_level > other.priority_level;
    }
};

#endif // CUSTOMER_H
