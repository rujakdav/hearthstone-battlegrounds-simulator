#pragma once

#include <memory>
class Minion;
class Player;

/**
 * @brief The IFilter class
 * This class is used to represent a filter
 */
class IFilter
{
public:
    /**
     * @brief Is the minion valid
     * @param minion
     * @return true if the minion is valid
     */
    virtual bool isValid(const Minion& minion) const = 0;

    /**
     * @brief Is the player valid
     * @param player
     * @return true if the player is valid
     */
    virtual bool isValid(const Player& player) const = 0;

    /**
     * @brief Clones the filter
     * @return std::unique_ptr<IFilter>
     */
    virtual std::unique_ptr<IFilter> clone() const = 0;
    virtual ~IFilter() = default;
};