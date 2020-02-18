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
        task/FixedAfterInitCheck/FixedAfterInitCheckTask.cpp
        task/FixedAfterInitCheck/FixedAfterInitCheckTask.h
        task/FixedAfterInitCheck/FixedAfterInitCheckTaskLocator.h
        task/FixedAfterInitCheck/FixedAfterInitCheckTaskLocator.cpp
        task/FixedAfterInitCheck/FixedAfterInitASTTraverser.cpp
        task/FixedAfterInitCheck/FixedAfterInitASTTraverser.h)
add_executable(solv ${sources})
target_link_libraries(libsolv PRIVATE solidity Boost::boost Boost::program_options)
target_link_libraries(solv PRIVATE solidity libsolv Boost::boost Boost::program_options)

include(GNUInstallDirs)
