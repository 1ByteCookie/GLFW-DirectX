import os
import shutil
import sys

# This script will be invoked by Visual Studio's post build events which can be found in the project settings
# The command line arguments will be passed by Visual Studio macros


SolutionDir = sys.argv[1]
OutputDir = sys.argv[2]
GlfwDependency = "Dependencies/GLFW/lib/glfw3.dll"


os.chdir("../")
print("PYTHON CWD: " + os.getcwd())


shutil.copy(GlfwDependency, OutputDir)


print("PYTHON BUILD SCRIPT INVOKED")