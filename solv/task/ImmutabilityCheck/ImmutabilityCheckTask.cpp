//
// Created by Qiu Haoze on 24/11/19.
//

#include <string>

#include "ImmutabilityCheckTask.h"
#include "ImmutabilityCheckTaskLocator.h"

using namespace std;
using namespace langutil;

namespace dev
{
namespace solidity
{
namespace verifier
{

const string ImmutabilityCheckTask::taskName = "immutable";

void ImmutabilityCheckTask::execute() {
    return;
}

ITask *ImmutabilityCheckTask::Create(const SourceUnit *_ast, const SourceLocation _line_location) {
    ImmutabilityCheckTaskLocator *_locator = new ImmutabilityCheckTaskLocator(_ast, _line_location);
    const VariableDeclaration *_target = _locator->locate();
    return new ImmutabilityCheckTask(_ast, _target);
}

}
}
}