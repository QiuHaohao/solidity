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

#include "ITask.h"
#include "TaskAnnotation.h"


namespace dev
{
namespace solidity
{
namespace verifier
{

class TaskFinder : ASTConstVisitor {
public:
    static const std::regex annotationPattern;

    std::vector<TaskAnnotation> findAnnotations(const std::string &source);
};

}
}
}
#endif //SOLIDITY_TASKFINDER_H
