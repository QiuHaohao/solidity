//
// Created by Qiu Haoze on 24/11/19.
//
#include <queue>
#include <string>

#include "ImmutabilityCheckTask.h"
#include "ImmutabilityCheckTaskLocator.h"
#include "ImmutabilityASTTraverser.h"

using namespace std;
using namespace langutil;

namespace dev::solidity::verifier
{

const string ImmutabilityCheckTask::taskName = "immutable";

void ImmutabilityCheckTask::execute() {
    // init idMap
    vector<FunctionDefinition const*> functions = dynamic_cast<ContractDefinition*>(getAst()->nodes()[1].get())->definedFunctions();
    for (auto & function : functions) {
        idMap.insert(pair<size_t, FunctionDefinition const*>(function->id(), function));
    }
    // run visitor on ast
    const SourceUnit* ast = getAst();
    auto* astTraverser = new ImmutabilityASTTraverser(getAst(), getTarget());
    ast->accept(*astTraverser);
    const map<size_t, vector<size_t>> calledBy = astTraverser->getCalledBy();
    const set<size_t> assigners = astTraverser->getAssigners();
    for (auto assigner : assigners) {
        queue<size_t> q;
        set<size_t> reached;

        q.push(assigner);
        reached.insert(assigner);
        while (!q.empty()) {
            size_t cur = q.front();
            reached.insert(cur);
            for (auto callee : calledBy.at(cur)) {
                if (reached.find(callee) != reached.end()) {
                    q.push(callee);
                    reached.insert(callee);
                }
            }
            q.pop();
        }

        for (auto id : reached) {
            auto f = functions[id];
            if (f->isPublic()) {
                cerr << "Function "<<functions[assigner]->name()
                    <<", which contains an assignment to the immutable variable "
                    << dynamic_cast<const VariableDeclaration*>(getTarget())->name()
                    <<", can be called Through a public function "<<f->name()<<".";
            }
        }
    }
}

ITask* ImmutabilityCheckTask::Create(const SourceUnit& _ast, const SourceLocation _line_location) {
    auto *_locator = new ImmutabilityCheckTaskLocator(_ast, _line_location);
    const VariableDeclaration *_target = _locator->locate();
    return new ImmutabilityCheckTask(_ast, _target);
}
}