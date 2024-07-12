// Assignment 3 - Priority Queue
// Fahim Naytik
// CSCI 335


#include <iostream>
#include <vector>
#include <algorithm>
#include "max_heap.h"
#include "customer.h"

int main() {
    MaxHeap<Customer> maxHeap;
    std::vector<Customer> history;

    // Create random customers and insert them into the MaxHeap
    for (int i = 0; i < 10; ++i) {
        Customer customer("Customer" + std::to_string(i + 1));
        maxHeap.Insert(customer);
    }

    // Remove customers from the MaxHeap, update service time, and store in history
    while (!maxHeap.IsEmpty()) {
        Customer customer = maxHeap.DeleteMax();
        customer.SetServiceTime();
        history.push_back(customer);
    }

    // Sort history based on service time in ascending order
    std::sort(history.begin(), history.end(), [](const Customer& a, const Customer& b) {
        return a.service_time < b.service_time;
    });

    // Print sorted history
    for (const auto& customer : history) {
        std::cout << "Name: " << customer.name << ", Priority Level: " << customer.priority_level 
                  << ", Service Time: " << customer.service_time << std::endl;
    }

    return 0;
}
