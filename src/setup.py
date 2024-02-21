from setuptools import setup, Extension
from Cython.Build import cythonize
import subprocess
import os

# Set environment variables for MSVC compiler
os.environ["CC"] = "cl"
os.environ["CXX"] = "cl"

subprocess.run(["cmake", "-G", "Visual Studio 17 2022", "-B", "build", "cpp_library"])
subprocess.run(["cmake", "--build", "build", "--config", "Release"])

extension_modules = [
    Extension(
        "game_manager_wrapper",
        sources=["src/wrappers/game_manager_wrapper/game_manager_wrapper.pyx"],
        libraries=["battlegrounds_simulator"],
        library_dirs=["build/Release"],  # Adjust the library directory
        language="c++",
        extra_compile_args=["/std:c++17"]
    ),
    Extension(
        "minion_repository_wrapper",
        sources=["src/wrappers/minion_repository_wrapper/minion_repository_wrapper.pyx"],
        libraries=["battlegrounds_simulator"],
        library_dirs=["build/Release"],  # Adjust the library directory
        language="c++",
        extra_compile_args=["/std:c++17"]
    ),
    Extension(
        "player_repository_wrapper",
        sources=["src/wrappers/player_repository_wrapper/player_repository_wrapper.pyx"],
        libraries=["battlegrounds_simulator"],
        library_dirs=["build/Release"],  # Adjust the library directory
        language="c++",
        extra_compile_args=["/std:c++17"]
    )
]

setup(
    ext_modules=cythonize(extension_modules),
    options={
        "build": {
            "build_lib": "src/generated"
        }
    }
)
