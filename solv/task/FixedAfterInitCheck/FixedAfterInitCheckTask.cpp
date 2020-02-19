//
// Created by Qiu Haoze on 24/11/19.
//
#include <queue>
#include <string>

#include "FixedAfterInitCheckTask.h"
#include "FixedAfterInitCheckTaskLocator.h"
#include "FixedAfterInitASTTraverser.h"

using namespace std;
using namespace langutil;

namespace dev::solidity::verifier
{

const string FixedAfterInitCheckTask::taskName = "fixed-after-init";

vector<IReportItem*> FixedAfterInitCheckTask::execute() {
    // init idMap
    vector<FunctionDefinition const*> functions = dynamic_cast<ContractDefinition*>(getAst()->nodes()[1].get())->definedFunctions();
    for (auto & function : functions) {
        idMap.insert(pair<size_t, FunctionDefinition const*>(function->id(), function));
    }
    // run visitor on ast
    const SourceUnit* ast = getAst();
    auto* astTraverser = new FixedAfterInitASTTraverser(getAst(), getTarget());
    ast->accept(*astTraverser);
    const map<size_t, vector<size_t>> calledBy = astTraverser->getCalledBy();
    const set<size_t> assigners = astTraverser->getAssigners();

    vector<IReportItem*> report;
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
                report.push_back(
                    new FixedAfterInitReportItem(
                        f->name(),
                        functions[assigner]->name(),
                        dynamic_cast<const VariableDeclaration*>(getTarget())->name()
                    )
                );
            }
        }
    }
    return report;
}

ITask* FixedAfterInitCheckTask::Create(const SourceUnit& _ast, const SourceLocation _line_location) {
    auto *_locator = new FixedAfterInitCheckTaskLocator(_ast, _line_location);
    const VariableDeclaration *_target = _locator->locate();
    return new FixedAfterInitCheckTask(_ast, _target);
}
}