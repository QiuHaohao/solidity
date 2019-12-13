//
// Created by Qiu Haoze on 12/12/19.
//
#ifndef SOLIDITY_TASKLOCATOR_H
#define SOLIDITY_TASKLOCATOR_H

#include <liblangutil/SourceLocation.h>
#include <libsolidity/ast/AST.h>
#include <libsolidity/ast/ASTVisitor.h>

namespace dev
{
namespace solidity
{
namespace verifier {

class TaskLocator : public ASTConstVisitor {

public:
    TaskLocator(
            const SourceUnit *_ast, langutil::SourceLocation const &_line_location
    ) : m_ast(_ast), m_line_location(_line_location) {};

    virtual const ASTNode *locate() = 0;

    const SourceUnit *ast() const {
        return m_ast;
    }

    langutil::SourceLocation const &lineLocation() const { return m_line_location; }

private:
    const SourceUnit *m_ast;
    langutil::SourceLocation m_line_location;
};

}
}
}

#endif //SOLIDITY_TASKLOCATOR_H
