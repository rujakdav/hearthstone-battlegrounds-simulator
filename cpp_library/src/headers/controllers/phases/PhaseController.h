#pragma once
#include "entities/Player.h"
#include "repository/MinionPool.h"


class TreeNode;

class ActionsCenter;

/**
 * @brief The PhaseController class
 * This class is used to control the phases
 */
class PhaseController {
public:

    /**
    * @brief Returns the friendly player of the given minion
    * @param minion
    * @return Player*
    */
    virtual Player *getFriendlyPlayer(Minion *minion) = 0;

    /**
     * @brief Returns the enemy player of the given minion
     * @param minion
     * @return Player*
     */
    virtual Player *getEnemyPlayer(Minion *minion) = 0;


    virtual void init() = 0;

    /**
     * @brief Traverses the action tree
     * @param node
     */
    void traverse(TreeNode *node);

    ~PhaseController() = default;

protected:
    std::unique_ptr<ActionsCenter> actionsCenter; /**< The actions center */
    int totalNodes = 0; /**< The total number of nodes of action tree*/
    int visitedNodes = 0; /**< The number of visited nodes action tree*/
    int maxNodes = 250; /**< The maximum number of nodes of action tree*/
    TreeNode *root = nullptr; /**< The root of the action tree*/
    TreeNode *lastNode = nullptr; /**< The last node of the action tree*/
};


