# player_repository_wrapper.pyx

# Include necessary headers
from libcpp.vector cimport vector
from libcpp.string cimport string

# Declare the PlayerRepository class
cdef extern from "../../cpp_library/src/headers/repository/PlayerRepository.h":
    cdef cppclass PlayerRepository:
        PlayerRepository() except +
        const vector[string] getPlayerCardKeys() const

# Define a Python wrapper for PlayerRepository
cdef class PyPlayerRepository:
    cdef PlayerRepository * thisptr  # Pointer to the C++ instance

    def __cinit__(self):
        self.thisptr = new PlayerRepository()

    def __dealloc__(self):
        del self.thisptr

    def getPlayerCardKeys(self):
        cdef  vector[string] result = self.thisptr.getPlayerCardKeys()
        return [item.decode('utf-8') for item in result]
