//
// Created by Qiu Haoze on 24/11/19.
//

#include "ITask.h"
#include "TaskFactory.h"

#ifndef SOLIDITY_IMMUTABILITYCHECKTASK_H
#define SOLIDITY_IMMUTABILITYCHECKTASK_H


class ImmutabilityCheckTask: ITask {
public:
    static const string taskName;
    ImmutabilityCheckTask(const ASTPointer<SourceUnit> _ast, const ASTPointer<ASTNode> _target):ITask(_ast, _target){}
    void execute();
    static ITask* Create(const ASTPointer<SourceUnit> _ast, const ASTPointer<ASTNode> _target) {
        return new ImmutabilityCheckTask(_ast, _target);
    }
};


#endif //SOLIDITY_IMMUTABILITYCHECKTASK_H
