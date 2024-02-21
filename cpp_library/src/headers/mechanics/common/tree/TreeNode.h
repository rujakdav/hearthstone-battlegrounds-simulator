#pragma once

#include <vector>
#include <variant>
#include <memory>
#include "enums/mechanics/common/triggerType.h"
#include "controllers/phases/PhaseController.h"

/**
 * @brief The TreeNode class
 * This class is used to store the tree of effects
 */
class TreeNode {
public:
    std::variant<TriggerType,
            std::tuple<std::unique_ptr<IEffect>, Minion *, PhaseController *>,
            std::tuple<std::unique_ptr<IBattlecry>, RecruitPhaseController *>> data; /**< The data stored in the node */


    TreeNode(TriggerType trigger);

    TreeNode(std::unique_ptr<IEffect> effect, Minion *minion, PhaseController *game);

    TreeNode(std::unique_ptr<IBattlecry> battlecry, RecruitPhaseController *recruitPhaseController);

    /**
     * @brief addChild
     * Adds a child to the node
     * @param treeNode The child to add
     */
    void addChild(TreeNode *treeNode);

private:
    bool visited = false; /**< Whether the node has been visited or not */
    std::vector<TreeNode *> children; /**< The children of the node */
public:
    const std::vector<TreeNode *> &getChildren() const;

    bool isVisited() const;

    void setVisited(bool visit);
};
