//
// Created by Qiu Haoze on 19/2/20.
//

#ifndef SOLIDITY_FIXEDAFTERINITASTTRAVERSER_H
#define SOLIDITY_FIXEDAFTERINITASTTRAVERSER_H

#include <libsolidity/ast/AST.h>
#include <libsolidity/ast/ASTVisitor.h>

namespace dev::solidity::verifier {
class FixedAfterInitASTTraverser : public ASTConstVisitor {
public:
    FixedAfterInitASTTraverser(const SourceUnit* _ast, const ASTNode *_target) : m_ast(_ast), m_target(_target) {}

    [[nodiscard]] const SourceUnit *getAst() const {
        return m_ast;
    }

    [[nodiscard]] const ASTNode *getTarget() const {
        return m_target;
    }

    [[nodiscard]] const std::multimap<size_t, size_t> &getCalledBy() const;

    [[nodiscard]] const std::set<size_t> &getAssigners() const;

    bool visit(FunctionDefinition const &_node) override;

    bool visit(Assignment const &_node) override;

    bool visit(FunctionCall const &_node) override;

private:
    const SourceUnit *m_ast;
    const ASTNode *m_target;

    FunctionDefinition const *currentFunc{};
    std::multimap<size_t, size_t> calledBy;
    std::set<size_t> assigners;
};

}
#endif //SOLIDITY_FIXEDAFTERINITASTTRAVERSER_H
