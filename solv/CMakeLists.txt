set(
        sources
        CommandLineInterface.cpp CommandLineInterface.h
        solv.cpp
)

add_library(
        libsolv
        task/ITask.h
        task/TaskFactory.cpp
        task/TaskFactory.h
        task/TaskFinder.cpp
        task/TaskFinder.h
        task/TaskLocator.h
        task/TaskAnnotation.h
        task/ImmutabilityCheck/ImmutabilityCheckTask.cpp
        task/ImmutabilityCheck/ImmutabilityCheckTask.h
        task/ImmutabilityCheck/ImmutabilityCheckTaskLocator.h
        task/ImmutabilityCheck/ImmutabilityCheckTaskLocator.cpp
        task/ImmutabilityCheck/ImmutabilityASTTraverser.cpp
        task/ImmutabilityCheck/ImmutabilityASTTraverser.h)
add_executable(solv ${sources})
target_link_libraries(libsolv PRIVATE solidity Boost::boost Boost::program_options)
target_link_libraries(solv PRIVATE solidity libsolv Boost::boost Boost::program_options)

include(GNUInstallDirs)
