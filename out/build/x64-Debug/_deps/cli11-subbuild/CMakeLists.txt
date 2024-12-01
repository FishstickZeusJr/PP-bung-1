# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.26.0-msvc3)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(cli11-populate NONE)


# Pass through things we've already detected in the main project to avoid
# paying the cost of redetecting them again in ExternalProject_Add()
set(GIT_EXECUTABLE [==[GIT_EXECUTABLE-NOTFOUND]==])
set(GIT_VERSION_STRING [==[]==])
set_property(GLOBAL PROPERTY _CMAKE_FindGit_GIT_EXECUTABLE_VERSION
  [==[GIT_EXECUTABLE-NOTFOUND;]==]
)


include(ExternalProject)
ExternalProject_Add(cli11-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/CLIUtils/CLI11.git" "GIT_TAG" "815553211b644b2a64b5dc671c602233c49c065f"
                    SOURCE_DIR          "C:/Users/sebas/OneDrive/Desktop/Word/PP praktische Übung 1/out/build/x64-Debug/_deps/cli11-src"
                    BINARY_DIR          "C:/Users/sebas/OneDrive/Desktop/Word/PP praktische Übung 1/out/build/x64-Debug/_deps/cli11-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
                    USES_TERMINAL_PATCH     YES
)


