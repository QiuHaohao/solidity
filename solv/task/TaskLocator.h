//
// Created by Qiu Haoze on 12/12/19.
//
#include<libsolidity/ast/AST.h>
#include<libsolidity/ast/ASTVisitor.h>
#include<solv/task/TaskFinder.h>

#ifndef SOLIDITY_TASKLOCATOR_H
#define SOLIDITY_TASKLOCATOR_H

class TaskLocator: public ASTConstVisitor {
public:
    TaskLocator(
        const SourceUnit * _ast, SourceLocation const& _line_location
    ): m_ast(_ast), m_line_location(_line_location) {};

    virtual const ASTNode * locate() = 0;

    const SourceUnit * ast() const {
        return m_ast;
    }

    SourceLocation const& lineLocation() const { return m_line_location; }
private:
    const SourceUnit * m_ast;
    SourceLocation m_line_location;
};

#endif //SOLIDITY_TASKLOCATOR_H
