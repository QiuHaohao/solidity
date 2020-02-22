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
    ASTPointer<ASTNode> contractNodeSmartPtr = getAst()->nodes()[1];
    ASTNode* contractNodePtr = contractNodeSmartPtr.get();
    auto contractDefs = dynamic_cast<ContractDefinition*>(contractNodePtr);
    vector<FunctionDefinition const*> functions = contractDefs->definedFunctions();

    for (auto & function : functions) {
        idMap[function->id()] = function;
    }
    // run visitor on ast
    const SourceUnit* ast = getAst();
    auto* astTraverser = new FixedAfterInitASTTraverser(getAst(), getTarget());
    ast->accept(*astTraverser);
    const multimap<size_t, size_t> calledBy = astTraverser->getCalledBy();
    const set<size_t> assigners = astTraverser->getAssigners();
    vector<IReportItem*> report;
    for (auto assigner : assigners) {
        queue<size_t> q;
        set<size_t> reached;

        q.push(assigner);
        reached.insert(assigner);
        while (!q.empty()) {
            size_t cur = q.front();
            auto range = calledBy.equal_range(cur);
            for (auto i = range.first; i != range.second; ++i) {
                if (reached.find(i->second) != reached.end()) {
                    q.push(i->second);
                    reached.insert(i->second);
                }
            }
            q.pop();
        }

        for (auto id : reached) {
            auto f = idMap[id];
            if (f->isPublic()) {
                report.push_back(
                    new FixedAfterInitReportItem(
                        f->name(),
                        idMap[assigner]->name(),
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