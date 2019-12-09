//
// Created by Qiu Haoze on 25/11/19.
//

#ifndef SOLIDITY_TASKFINDER_H
#define SOLIDITY_TASKFINDER_H

#include <regex>
#include <string>
#include <vector>
#include <utility>

#include <libsolidity/ast/AST.h>
#include <libsolidity/ast/ASTVisitor.h>

#include "TaskFactory.h"
#include "ITask.h"

struct Annotation {
    string type;
    int position;
    Annotation(string _type, int _position) : type(_type), position(_position) {}
};

class TaskFinder:ASTConstVisitor {
public:
    static const regex annotationPattern;
    vector<ITask> findTasks(const ASTPointer<SourceUnit> _ast, const string& source);
    vector<Annotation> findAnnotations(const string& source);
    vector<ASTNode> findTargets(const ASTPointer<SourceUnit> _ast, vector<Annotation> annotations);
};


#endif //SOLIDITY_TASKFINDER_H
