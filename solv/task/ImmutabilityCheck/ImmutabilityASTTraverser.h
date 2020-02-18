//
// Created by Qiu Haoze on 19/2/20.
//

#ifndef SOLIDITY_IMMUTABILITYASTTRAVERSER_H
#define SOLIDITY_IMMUTABILITYASTTRAVERSER_H

#include <libsolidity/ast/AST.h>
#include <libsolidity/ast/ASTVisitor.h>

namespace dev::solidity::verifier {
class ImmutabilityASTTraverser : public ASTConstVisitor {
public:
    ImmutabilityASTTraverser(const SourceUnit* _ast, const ASTNode *_target) : m_ast(_ast),m_target(_target) {}

    [[nodiscard]] const SourceUnit *getAst() const {
        return m_ast;
    }

    [[nodiscard]] const ASTNode *getTarget() const {
        return m_target;
    }

    [[nodiscard]] const std::map<size_t, std::vector<size_t>> &getCalledBy() const;

    [[nodiscard]] const std::set<size_t> &getAssigners() const;

    bool visit(FunctionDefinition const &_node) override;

    bool visit(Assignment const &_node) override;

    bool visit(FunctionCall const &_node) override;

private:
    const SourceUnit *m_ast;
    const ASTNode *m_target;

    FunctionDefinition const *currentFunc{};
    std::map<size_t, std::vector<size_t>> calledBy;
public:


private:
    std::set<size_t> assigners;
};

}
#endif //SOLIDITY_IMMUTABILITYASTTRAVERSER_H
