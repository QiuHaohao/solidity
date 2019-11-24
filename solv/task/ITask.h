//
// Created by Qiu Haoze on 24/11/19.
//

#include <libsolidity/ast/AST.h>

#ifndef SOLIDITY_ITASK_H
#define SOLIDITY_ITASK_H

using namespace std;
using namespace dev::solidity;

class ITask {
public:
    ITask(SourceUnit const& _ast, ASTNode const& _target): m_ast(_ast), m_target(_target) {};
    static string taskName;
    virtual void execute() = 0;

private:
    SourceUnit const&  m_ast;
    ASTNode const& m_target;
};


#endif //SOLIDITY_ITASK_H
