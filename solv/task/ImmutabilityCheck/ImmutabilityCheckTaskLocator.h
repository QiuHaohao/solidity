//
// Created by Qiu Haoze on 12/12/19.
//
#include <solv/task/TaskLocator.h>

#ifndef SOLIDITY_IMMUTABILITYCHECKTASKLOCATOR_H
#define SOLIDITY_IMMUTABILITYCHECKTASKLOCATOR_H


class ImmutabilityCheckTaskLocator: TaskLocator {
public:
    ImmutabilityCheckTaskLocator(
        const SourceUnit * _ast, SourceLocation const& _line_location
    ): TaskLocator(_ast, _line_location) {};
    const VariableDeclaration * locate() override;
    bool visit(VariableDeclaration const& _node) override;
private:
    const VariableDeclaration * m_target;
    bool m_located = false;
};


#endif //SOLIDITY_IMMUTABILITYCHECKTASKLOCATOR_H
