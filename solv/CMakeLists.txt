set(
        sources
        CommandLineInterface.cpp CommandLineInterface.h
        solv.cpp
)

add_executable(solv ${sources})
target_link_libraries(solv PRIVATE solidity Boost::boost Boost::program_options)

include(GNUInstallDirs)
