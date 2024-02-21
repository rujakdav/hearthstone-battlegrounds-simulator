# game_manager_wrapper.pyx

# Include necessary headers
from libcpp.string cimport string
from libcpp.vector cimport vector
from libcpp cimport bool


# Declare the GameManager class
cdef extern from "../../cpp_library/src/headers/GameManager.h":
    cdef cppclass GameManager:
        GameManager() except +

        string addPlayer(const string cardKey)

        void movePlayerToDead(const string playerId)

        void startRecruitPhase(const string cardKey)
        void startGame()

        void executeSingleCombat(const string playerId1, const vector[string] minionIds1,
                                 const string playerId2, const vector[string] minionIds2, bool isPrint);



cdef class PyGameManager:
    cdef GameManager * thisptr  # Pointer to the C++ instance

    def __cinit__(self):
        self.thisptr = new GameManager()

    def __dealloc__(self):
        del self.thisptr

    def addPlayer(self, str card_key):
        cdef bytes card_key_bytes = card_key.encode('utf-8')
        return self.thisptr.addPlayer(card_key_bytes)

    def startRecruitPhase(self, card_key):
        if not isinstance(card_key, bytes):
            card_key = card_key.encode('utf-8')
        self.thisptr.startRecruitPhase(card_key)

    def startGame(self):
        self.thisptr.startGame()

    def movePlayerToDead(self, playerId):
        self.thisptr.movePlayerToDead(playerId.encode('utf-8'))

    def executeSingleCombat(self, playerId1, list minionIds1, playerId2, list minionIds2, bool isPrint=True):
        cdef string playerId1_bytes = playerId1.encode('utf-8')
        cdef string playerId2_bytes = playerId2.encode('utf-8')

        cdef vector[string] minionIds1_vector
        for minionId in minionIds1:
            minionIds1_vector.push_back(minionId.encode('utf-8'))

        cdef vector[string] minionIds2_vector
        for minionId in minionIds2:
            minionIds2_vector.push_back(minionId.encode('utf-8'))

        self.thisptr.executeSingleCombat(playerId1_bytes, minionIds1_vector,
                                         playerId2_bytes, minionIds2_vector, isPrint)
