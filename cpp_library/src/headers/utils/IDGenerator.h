#pragma once

#include <string>
#include <atomic>


/**
 * @brief The IDGenerator class
 * This class is used to generate unique UUIDs
 */
class IDGenerator {
private:
    IDGenerator();

public:
    /**
     * @brief This method is used to get the instance of the IDGenerator
     * @return
     */
    static IDGenerator& getInstance();

    /**
     * @brief This method is used to generate an UUID
     * @return
     */
    std::string generateID();

};