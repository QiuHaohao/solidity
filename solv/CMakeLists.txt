set(
        sources
        CommandLineInterface.cpp CommandLineInterface.h
        solv.cpp
)

add_library(
        libsolv
        task/ITask.h
        task/ImmutabilityCheckTask.cpp
        task/ImmutabilityCheckTask.h
        task/TaskFactory.cpp
        task/TaskFactory.h
        task/TaskFinder.cpp
        task/TaskFinder.h
        task/TaskLocator.h
        task/ImmutabilityCheckTaskLocator.h
        task/ImmutabilityCheckTaskLocator.cpp
)
add_executable(solv ${sources})
target_link_libraries(libsolv PRIVATE solidity Boost::boost Boost::program_options)
target_link_libraries(solv PRIVATE solidity libsolv Boost::boost Boost::program_options)

include(GNUInstallDirs)
