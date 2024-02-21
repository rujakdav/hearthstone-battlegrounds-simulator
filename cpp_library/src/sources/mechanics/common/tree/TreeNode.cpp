#include "mechanics/common/tree/TreeNode.h"

TreeNode::TreeNode(TriggerType trigger) : data(trigger) {}


void TreeNode::addChild(TreeNode *treeNode) {
    children.push_back(treeNode);
}

TreeNode::TreeNode(std::unique_ptr<IEffect> effect, Minion *minion, PhaseController *game) {
    data = std::tuple<std::unique_ptr<IEffect>, Minion *, PhaseController *>(effect->clone(), minion, game);
}

TreeNode::TreeNode(std::unique_ptr<IBattlecry> battlecry, RecruitPhaseController *recruitPhaseController) {
    data = std::tuple<std::unique_ptr<IBattlecry>, RecruitPhaseController *>(std::move(battlecry),
                                                                             recruitPhaseController);
}

bool TreeNode::isVisited() const {
    return visited;
}

void TreeNode::setVisited(bool visit) {
    TreeNode::visited = visit;
}

const std::vector<TreeNode *> &TreeNode::getChildren() const {
    return children;
}
