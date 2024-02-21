#include "controllers/phases/PhaseController.h"
#include "mechanics/common/tree/TreeNode.h"
#include "utils/Utils.h"
#include "mechanics/effects/IEffect.h"

void PhaseController::traverse(TreeNode *node) {
    visitedNodes++;
    if (node == nullptr || node->isVisited()) {
        std::cout << "nullptr\n";
        return;
    }

    // Process the current node here
    std::visit([this, &node](auto &&data) {
        if constexpr (std::is_same_v<std::decay_t<decltype(data)>, TriggerType>) {
            node->setVisited(true);
            lastNode = node;
        } else if constexpr (std::is_same_v<std::decay_t<decltype(data)>, std::tuple<std::unique_ptr<IEffect>, Minion *, PhaseController *>>) {
            Minion *minion = std::get<1>(data);
            PhaseController *game = std::get<2>(data);


            if (std::get<0>(data) && !node->isVisited()) {
                node->setVisited(true);
                lastNode = node;

                std::get<0>(data)->execute(minion, game);
            }
        } else if constexpr (std::is_same_v<std::decay_t<decltype(data)>, std::tuple<std::unique_ptr<IBattlecry>, RecruitPhaseController *>>) {
            std::unique_ptr<IBattlecry> battlecry = std::move(std::get<0>(data));
            auto recruitPhaseController = std::get<1>(data);


            if (battlecry && !node->isVisited()) {

                node->setVisited(true);
                lastNode = node;

                // Execute the battlecry
                battlecry->execute(recruitPhaseController);
            }
        }
    }, node->data);

    for (TreeNode *child: node->getChildren()) {
        traverse(child);
    }
    delete node;
}


