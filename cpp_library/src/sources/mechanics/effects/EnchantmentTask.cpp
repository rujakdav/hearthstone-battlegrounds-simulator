#include "../../../headers/tasks/EnchantmentTask.h"

EnchantmentTask::EnchantmentTask(const std::vector<Minion *> &targets, Enchantment &enchantment) : targets(targets),
                                                                                                   enchantment(
                                                                                                           enchantment) {}

EnchantmentTask::EnchantmentTask(Minion *&target, Enchantment &enchantment) : enchantment(enchantment) {
    targets.push_back(target);
}

void EnchantmentTask::execute() {
    for (auto target: targets) {
        target->addEnchantment(enchantment.clone());
    }

}
