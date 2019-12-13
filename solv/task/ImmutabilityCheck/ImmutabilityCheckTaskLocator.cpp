//
// Created by Qiu Haoze on 12/12/19.
//

#include "ImmutabilityCheckTaskLocator.h"

using namespace langutil;

namespace dev
{
namespace solidity
{
namespace verifier
{

const VariableDeclaration *ImmutabilityCheckTaskLocator::locate() {
    if (!m_located) {
        const SourceUnit *sourceUnit = TaskLocator::ast();
        sourceUnit->accept(*this);
        m_located = true;
    }
    return m_target;
}

bool ImmutabilityCheckTaskLocator::visit(VariableDeclaration const &_node) {
    SourceLocation nodeLocation = _node.location();
    SourceLocation annotationLocation = TaskLocator::lineLocation();
    if (annotationLocation.start <= nodeLocation.start
        && nodeLocation.end <= annotationLocation.end) {
        m_target = &_node;
        return false;
    }
    return true;
}

}
}
}