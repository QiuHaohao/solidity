//
// Created by Qiu Haoze on 24/11/19.
//


#ifndef SOLIDITY_FIXEDAFTERINITCHECKTASK_H
#define SOLIDITY_FIXEDAFTERINITCHECKTASK_H

#include <set>

#include <liblangutil/SourceLocation.h>
#include <libsolidity/ast/AST.h>

#include "solv/task/ITask.h"
#include "solv/task/TaskFactory.h"
#include "./FixedAfterInitReportItem.h"

namespace dev
{
namespace solidity
{
namespace verifier
{

class FixedAfterInitCheckTask : ITask {
public:
    static const std::string taskName;

    FixedAfterInitCheckTask(const SourceUnit& _ast, const ASTNode *_target) : ITask(_ast, _target) {}

    std::vector<IReportItem*> execute() override;

    static ITask *Create(const SourceUnit& _ast, const langutil::SourceLocation _line_location);

private:
    std::map<size_t, FunctionDefinition const *> idMap;
};

}
}
}
#endif //SOLIDITY_FIXEDAFTERINITCHECKTASK_H
