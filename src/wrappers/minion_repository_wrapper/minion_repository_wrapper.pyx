# minion_repository_wrapper.pyx

# Include necessary headers
from libcpp.vector cimport vector
from libcpp.string cimport string

# Declare the MinionRepository class
cdef extern from "../../cpp_library/src/headers/repository/MinionRepository.h":
    cdef cppclass MinionRepository:
        MinionRepository() except +
        const vector[string] getTierCardKeys(int tier) const


# Define a Python wrapper for MinionRepository
cdef class PyMinionRepository:
    cdef MinionRepository * thisptr  # Pointer to the C++ instance

    def __cinit__(self):
        self.thisptr = new MinionRepository()

    def __dealloc__(self):
        del self.thisptr

    def getTierCardKeys(self, int tier):
        cdef  vector[string] result = self.thisptr.getTierCardKeys(tier)
        return [item.decode('utf-8') for item in result]
