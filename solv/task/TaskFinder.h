//
// Created by Qiu Haoze on 25/11/19.
//

#ifndef SOLIDITY_TASKFINDER_H
#define SOLIDITY_TASKFINDER_H

#include <regex>
#include <string>
#include <vector>
#include <utility>

#include <liblangutil/SourceLocation.h>
#include <libsolidity/ast/AST.h>
#include <libsolidity/ast/ASTVisitor.h>

#include "TaskFactory.h"
#include "ITask.h"

using namespace langutil;

struct Annotation {
    string m_type;
    SourceLocation m_line_location;
    Annotation(string _type, int _line_start, int _line_end) : m_type(_type) {
        m_line_location.start = _line_start;
        m_line_location.end = _line_end;
    }
};

class TaskFinder:ASTConstVisitor {
public:
    static const regex annotationPattern;
    vector<ITask> findTasks(const SourceUnit * _ast, const string& source);
    vector<Annotation> findAnnotations(const string& source);
    vector<ASTNode> findTargets(const SourceUnit * _ast, vector<Annotation> annotations);
};


#endif //SOLIDITY_TASKFINDER_H
