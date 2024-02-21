import random

from generated.game_manager_wrapper import  PyGameManager
from generated.minion_repository_wrapper import PyMinionRepository
from generated.player_repository_wrapper import PyPlayerRepository


def recruit_phase_worker(game_manager, card_key):
    game_manager.startRecruitPhase(card_key)


def main():
    game_manager = PyGameManager()
    minion_repository = PyMinionRepository()
    player_repository = PyPlayerRepository()

    player_card_keys = player_repository.getPlayerCardKeys()
    player_random_keys = random.sample(player_card_keys, 2)
    player1CardKey = player_random_keys[0]
    player2VCardKey = player_random_keys[1]

    playerId=game_manager.addPlayer(player1CardKey)
    game_manager.startRecruitPhase(playerId)

    minion_card_keys = minion_repository.getTierCardKeys(1)
    player1Minions = []
    player2Minions = []

    for i in range(1, 7):
        player1Minions.append(random.choice(minion_card_keys))
        player2Minions.append(random.choice(minion_card_keys))

    print(player1Minions)
    print(player2Minions)


    #game_manager.executeSingleCombat(player1CardKey, player1Minions, player2VCardKey, player2Minions)


if __name__ == "__main__":
    main()
