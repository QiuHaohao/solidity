//
// Created by Qiu Haoze on 24/11/19.
//

#include "ITask.h"
#include "TaskFactory.h"

#ifndef SOLIDITY_IMMUTABILITYCHECKTASK_H
#define SOLIDITY_IMMUTABILITYCHECKTASK_H


class ImmutabilityCheckTask: ITask {
public:
    static string taskName = "immutable";
    ImmutabilityCheckTask(SourceUnit const& _ast, ASTNode const& _target);
    void execute() {}
    static ImmutabilityCheckTask* Create(SourceUnit const& _ast, ASTNode const& _target) {
        return new ImmutabilityCheckTask(_ast, _target);
    }
};


#endif //SOLIDITY_IMMUTABILITYCHECKTASK_H
