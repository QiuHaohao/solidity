//
// Created by Qiu Haoze on 13/10/19.
//

#ifndef SOLIDITY_COMMANDLINEINTERFACE_H
#define SOLIDITY_COMMANDLINEINTERFACE_H


//
// Created by Qiu Haoze on 13/10/19.
//

#pragma once

#include <libsolidity/interface/CompilerStack.h>

#include <boost/program_options.hpp>
#include <boost/filesystem/path.hpp>

namespace dev
{
namespace solidity
{
namespace verifier
{
class CommandLineInterface
{
public:
    /// Parse command line arguments and return false if we should not continue
    bool parseArguments(int _argc, char** _argv);

    /// Parse the files and create source code objects
    bool processInput();

    /// Perform actions on the input depending on provided compiler arguments
    /// @returns true on success.
    bool actOnInput();

private:
    void outputResults();

    void handleAst();

    /// Fills @a m_sourceCodes initially and @a m_redirects.
    bool readInputFilesAndConfigureRemappings();

    /// Compiler arguments variable map
    boost::program_options::variables_map m_args;
    /// map of input files to source code strings
    std::map<std::string, std::string> m_sourceCodes;
    /// list of remappings
    std::vector<dev::solidity::CompilerStack::Remapping> m_remappings;
    /// list of allowed directories to read files from
    std::vector<boost::filesystem::path> m_allowedDirectories;
    /// Solidity compiler stack
    std::unique_ptr<dev::solidity::CompilerStack> m_compiler;
    /// EVM version to use
    langutil::EVMVersion m_evmVersion;
    bool m_coloredOutput = true;
};

}
}
}


#endif //SOLIDITY_COMMANDLINEINTERFACE_H
