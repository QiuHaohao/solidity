//
// Created by Qiu Haoze on 19/2/20.
//

#include "FixedAfterInitASTTraverser.h"
namespace dev::solidity::verifier {

bool FixedAfterInitASTTraverser::visit(FunctionDefinition const &_node) {
    this->currentFunc = &_node;
    return true;
}

bool FixedAfterInitASTTraverser::visit(Assignment const &_node) {
    Expression const &leftHandSideExpr = _node.leftHandSide();
    // if left-hand side is an identifier
    if (auto const *identifier = &dynamic_cast<Identifier const &>(leftHandSideExpr)) {
        Declaration const *originalDecl = identifier->annotation().referencedDeclaration;
        // if the variable assigned to is the target
        if (originalDecl->id() == getTarget()->id()) {
            assigners.insert(this->currentFunc->id());
        }
    }
    return true;
}

bool FixedAfterInitASTTraverser::visit(FunctionCall const &_node) {
    Expression const &idFuncCalled = _node.expression();
    // if the expression is an identifier
    if (auto const *identifier = &dynamic_cast<Identifier const &>(idFuncCalled)) {
        Declaration const *originalDecl = identifier->annotation().referencedDeclaration;
        calledBy.at(originalDecl->id()).push_back(currentFunc->id());
    }
    return true;
}

const std::map<size_t, std::vector<size_t>> &FixedAfterInitASTTraverser::getCalledBy() const {
    return calledBy;
}

const std::set<size_t> &FixedAfterInitASTTraverser::getAssigners() const {
    return assigners;
}
}