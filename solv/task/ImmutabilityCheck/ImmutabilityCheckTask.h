//
// Created by Qiu Haoze on 24/11/19.
//


#ifndef SOLIDITY_IMMUTABILITYCHECKTASK_H
#define SOLIDITY_IMMUTABILITYCHECKTASK_H

#include <set>

#include <liblangutil/SourceLocation.h>
#include <libsolidity/ast/AST.h>
#include <solv/task/ITask.h>

#include "solv/task/TaskFactory.h"

namespace dev
{
namespace solidity
{
namespace verifier
{

class ImmutabilityCheckTask : ITask {
public:
    static const std::string taskName;

    ImmutabilityCheckTask(const SourceUnit& _ast, const ASTNode *_target) : ITask(_ast, _target) {}

    void execute() override;

    static ITask *Create(const SourceUnit& _ast, const langutil::SourceLocation& _line_location);

private:
    std::map<size_t, FunctionDefinition const *> idMap;
};

}
}
}
#endif //SOLIDITY_IMMUTABILITYCHECKTASK_H
