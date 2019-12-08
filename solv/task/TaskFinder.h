//
// Created by Qiu Haoze on 25/11/19.
//

#ifndef SOLIDITY_TASKFINDER_H
#define SOLIDITY_TASKFINDER_H

#include <string>
#include <vector>
#include <utility>

#include <libsolidity/ast/AST.h>
#include <libsolidity/ast/ASTVisitor.h>

#include "TaskFactory.h"
#include "ITask.h"

class TaskFinder:ASTConstVisitor {
public:
    vector<ITask> findTasks(const ASTPointer<SourceUnit> _ast, const string& source);
private:
    typedef vector<pair<string, int>> Annotations;
    Annotations findAnnotations(const string& source);
    vector<ASTNode> findTargets(const ASTPointer<SourceUnit> _ast, Annotations annotations);
};


#endif //SOLIDITY_TASKFINDER_H
