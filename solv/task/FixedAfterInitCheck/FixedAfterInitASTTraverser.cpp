//
// Created by Qiu Haoze on 19/2/20.
//

#include "FixedAfterInitASTTraverser.h"
using namespace std;
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
        calledBy.insert({originalDecl->id(), currentFunc->id()});
    }
    return true;
}

const std::multimap<size_t, size_t> &FixedAfterInitASTTraverser::getCalledBy() const {
    return calledBy;
}

const std::set<size_t> &FixedAfterInitASTTraverser::getAssigners() const {
    return assigners;
}
}