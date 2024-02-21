cmake_minimum_required(VERSION 3.16)
project(battlegrounds_simulator)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Catch2 as an external project
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.2 # or a later release
)
FetchContent_MakeAvailable(Catch2)



set(SOURCES
        src/sources/entities/Minion.cpp src/headers/entities/Minion.h src/headers/enums/card/rarity.h src/headers/enums/card/rarity.h src/headers/enums/minion/minionType.h src/headers/enums/minion/versions.h src/sources/entities/Player.cpp src/headers/entities/Player.h src/headers/controllers/phases/PhaseController.h src/sources/utils/Utils.cpp src/headers/utils/Utils.h src/headers/enums/card/zone.h src/headers/enums/card/zone.h src/sources/components/IDestructible.cpp src/headers/components/IDestructible.h src/headers/components/IDestructible.h src/sources/components/IArmored.cpp src/headers/components/IArmored.h src/sources/components/ICombative.cpp src/headers/components/ICombative.h src/sources/components/ICard.cpp src/headers/components/ICard.h src/headers/tasks/DamageTask.h src/headers/tasks/DamageTask.h src/headers/tasks/DamageTask.h src/headers/mechanics/common/data/DamageEffectData.h src/headers/mechanics/common/data/DamageEffectData.h src/sources/tasks/DamageTask.cpp src/sources/tasks/DamageTask.cpp src/headers/tasks/DamageTask.h src/sources/mechanics/common/data/DamageTaskData.cpp src/sources/mechanics/common/data/DamageTaskData.cpp src/sources/tasks/AttackTask.cpp src/sources/tasks/AttackTask.cpp src/sources/tasks/AttackTask.cpp src/headers/tasks/AttackTask.h src/sources/tasks/AttackTask.cpp src/sources/tasks/DamageTask.cpp src/headers/enums/mechanics/common/triggerType.h src/headers/enums/mechanics/common/triggerSource.h src/sources/mechanics/effects/DamageEffect.cpp src/headers/mechanics/effects/DamageEffect.h src/headers/mechanics/effects/DamageEffect.h src/headers/enums/mechanics/effects/EffectTargets.h src/sources/mechanics/common/TargetsBuilder.cpp src/headers/mechanics/common/TargetsBuilder.h src/headers/mechanics/common/TargetsBuilder.h src/headers/tasks/ITask.h src/headers/tasks/ITask.h src/headers/tasks/ITask.h src/headers/mechanics/effects/IEffect.h src/headers/mechanics/common/criterias/targets/EffectTargetCriteria.h src/sources/mechanics/common/criterias/targets/TargetCriteria.cpp src/headers/mechanics/common/criterias/targets/EffectTargetCriteria.h src/sources/mechanics/common/criterias/targets/RandomTargets.cpp src/headers/mechanics/common/criterias/targets/RandomTargets.h src/sources/tasks/HealTask.cpp src/headers/tasks/HealTask.h src/sources/mechanics/effects/HealEffect.cpp src/headers/mechanics/effects/HealEffect.h src/headers/mechanics/effects/HealEffect.h src/sources/mechanics/common/data/HealTaskData.cpp src/headers/mechanics/common/data/HealEffectData.h src/headers/messaging/observer/PlayerObserver.h src/headers/messaging/observer/MinionSubject.h src/headers/messaging/observer/GameObserver.h src/headers/messaging/observer/GameObserver.h
        src/sources/messaging/NotificationCenter.cpp
        src/headers/messaging/ActionsCenter.h
        src/sources/mechanics/enchantments/Enchantment.cpp
        src/headers/mechanics/enchantments/Enchantment.h
        src/sources/mechanics/effects/EnchantmentEffect.cpp
        src/headers/mechanics/effects/EnchantmentEffect.h
        src/sources/mechanics/common/data/EnchantmentTaskData.cpp
        src/headers/mechanics/common/data/EnchantmentEffectData.h
        src/sources/mechanics/common/data/SummonTaskData.cpp
        src/headers/mechanics/common/data/SummonEffectData.h
        src/sources/mechanics/effects/SummonEffect.cpp
        src/headers/mechanics/effects/SummonEffect.h
        src/sources/tasks/SummonTask.cpp
        src/headers/tasks/SummonTask.h
        src/sources/mechanics/auras/Aura.cpp
        src/headers/mechanics/auras/Aura.h
        src/headers/mechanics/common/criterias/filters/IFilter.h
        src/sources/mechanics/common/criterias/filters/MinionFilter.cpp
        src/headers/mechanics/common/criterias/filters/MinionFilter.h
        src/sources/mechanics/common/criterias/filters/PlayerFilter.cpp
        src/headers/mechanics/common/criterias/filters/PlayerFilter.h
        src/sources/mechanics/common/criterias/filters/MixedFilter.cpp
        src/headers/mechanics/common/criterias/filters/MixedFilter.h
        src/sources/mechanics/common/criterias/source/SourceCriteria.cpp
        src/headers/mechanics/common/criterias/source/SourceCriteria.h
        src/sources/builders/MinionBuilder.cpp
        src/headers/builders/MinionBuilder.h
        src/sources/mechanics/common/tree/TreeNode.cpp
        src/headers/mechanics/common/tree/TreeNode.h
        src/sources/utils/IDGenerator.cpp
        src/headers/utils/IDGenerator.h
        src/sources/GameManager.cpp
        src/headers/GameManager.h
        src/headers/controllers/phases/PhaseController.h
        src/sources/controllers/phases/CombatPhaseController.cpp
        src/sources/controllers/phases/PhaseController.cpp
        src/sources/controllers/phases/RecruitPhaseController.cpp
        src/headers/controllers/phases/RecruitPhaseController.h
        src/sources/repository/MinionPool.cpp
        src/headers/repository/MinionPool.h
        src/sources/controllers/input/UserInputController.cpp
        src/headers/controllers/input/UserInputController.h
        src/sources/views/RecruitPhaseView.cpp
        src/headers/views/RecruitPhaseView.h
        src/sources/mechanics/battlecries/IBattlecry.cpp
        src/headers/mechanics/battlecries/IBattlecry.h
        src/sources/mechanics/battlecries/EnchantmentBattlecry.cpp
        src/headers/mechanics/battlecries/EnchantmentBattlecry.h
        src/sources/mechanics/common/criterias/targets/BattlecryTargetCriteterias.cpp
        src/headers/mechanics/common/criterias/targets/BattlecryTargetCriterias.h
        src/headers/enums/mechanics/battlecries/battlecryTargets.h
        src/sources/mechanics/common/Damage.cpp
        src/headers/mechanics/common/Damage.h
        src/sources/mechanics/common/IOwned.cpp
        src/headers/mechanics/common/IOwned.h
        src/sources/mechanics/effects/IEffect.cpp
        src/sources/builders/PlayerBuilder.cpp
        src/headers/builders/PlayerBuilder.h
        src/headers/config/OptionKeys.h
        src/sources/mechanics/effects/EnchantmentTask.cpp
        src/headers/tasks/EnchantmentTask.h
        src/sources/views/CombatPhaseView.cpp
        src/headers/views/CombatPhaseView.h
        src/headers/views/CombatPhaseView.h
        src/sources/mechanics/battlecries/DecreaseLeveLUpCostBattlecry.cpp
        src/headers/mechanics/battlecries/DecreaseLeveLUpCostBattlecry.h
        src/headers/enums/view/printMode.h
        src/sources/repository/MinionRepository.cpp
        src/headers/repository/MinionRepository.h
        src/sources/repository/PlayerRepository.cpp
        src/headers/repository/PlayerRepository.h
)
# Create the library for battlegrounds_simulator
add_library(battlegrounds_simulator STATIC ${SOURCES})

# Set the library output directory
set_target_properties(battlegrounds_simulator PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Add include directories for the library
target_include_directories(battlegrounds_simulator PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/headers
        # Add any other include directories as needed
)





add_executable(unitTests Testing/mechanics/common/DamageTest.cpp Testing/entities/MinionTest.cpp
        Testing/entities/PlayerTest.cpp Testing/messaging/ActionsCentreTest.cpp
        Testing/tasks/DamageTaskTest.cpp
        Testing/mechanics/auras/AuraTest.cpp
        Testing/utils/UtilsTest.cpp
        Testing/controllers/CombatPhaseControllerTest.cpp
        Testing/tasks/AttackTaskTest.cpp
        Testing/tasks/AttackTaskTest.cpp
        Testing/tasks/HealTask.cpp
        Testing/repository/MinionPoolTest.cpp)

# Link the tests executable with Catch2 and battlegrounds_simulator


target_link_libraries(unitTests PRIVATE Catch2::Catch2WithMain battlegrounds_simulator)

target_include_directories(unitTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/headers
        # Add any other include directories as neede
)