
#pragma once

/**
 * @brief The ITask class
 * This class is used to represent a tasks
 */
class ITask {
public:
    /**
     * @brief This method is used to execute the tasks
     */
    virtual void execute() = 0;
};