//
// Created by Qiu Haoze on 24/11/19.
//

#include <libsolidity/ast/AST.h>

#ifndef SOLIDITY_ITASK_H
#define SOLIDITY_ITASK_H

using namespace std;
using namespace dev::solidity;

class ITask {
public:
    ITask(const ASTPointer<SourceUnit> _ast, const ASTPointer<ASTNode> _target): m_ast(_ast), m_target(_target) {};
    static const string taskName;
    virtual void execute() { return; };
    static ITask* Create(const ASTPointer<SourceUnit> _ast, const ASTPointer<ASTNode> _target);
    [[nodiscard]] const ASTPointer<SourceUnit> getMAst() const {
        return m_ast;
    }

    [[nodiscard]] const ASTPointer<ASTNode> getMTarget() const {
        return m_target;
    }
private:
    const ASTPointer<SourceUnit>  m_ast;
    const ASTPointer<ASTNode> m_target;
};


#endif //SOLIDITY_ITASK_H
