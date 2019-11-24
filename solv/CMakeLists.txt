set(
        sources
        CommandLineInterface.cpp CommandLineInterface.h
        solv.cpp
        task/ITask.h task/ImmutabilityCheckTask.cpp task/ImmutabilityCheckTask.h task/TaskFactory.cpp task/TaskFactory.h task/TaskFinder.cpp task/TaskFinder.h)

add_executable(solv ${sources})
target_link_libraries(solv PRIVATE solidity Boost::boost Boost::program_options)

include(GNUInstallDirs)
