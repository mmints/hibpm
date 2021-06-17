/** Declare Parser Demonstration
 *
 * This program is a simple demo of the parsing process from a Declare-file
 * to a Declare data structure. In future this data structure is used as data
 * input for different solvers.
 */

#include <iostream>
#include "Declare/Declare.hh"

int main() {

    hibpm::Event event {"EVENT_0"};
    hibpm::Event event1 {"EVENT_1"};
    hibpm::Event event2 {"EVENT_2"};


    hibpm::Rule rule {hibpm::INIT, std::vector<hibpm::Event>{event}};
    hibpm::Rule rule1 {hibpm::END, std::vector<hibpm::Event>{event1}};

    hibpm::Rule rule2 {hibpm::RESPONDED_EXISTENCE, std::vector<hibpm::Event>{event1, event2}};

    hibpm::Declare declare;

    declare.addRule(rule);
    declare.addRule(rule1);
    declare.addRule(rule);
    declare.addRule(rule2);
    declare.addRule(rule2);

    std::cout << "All Events: " << std::endl;
    for (const auto& e : declare.getEvents()) {
        std::cout << e.name << std::endl;
    }

    std::cout << "\n --- \n" << std::endl;

    std::cout << "All Rules: " << std::endl;
    for (const auto& e : declare.getRules()) {
        std::cout << e.type << std::endl;
    }

    return 0;
}