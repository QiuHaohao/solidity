//
// Created by Qiu Haoze on 20/2/20.
//
#include <iostream>
#include "FixedAfterInitReportItem.h"

using namespace std;
namespace dev
{
namespace solidity
{
namespace verifier
{

void FixedAfterInitReportItem::report() {
    cerr << "Function \"" << getAssigner()
         << "\", which contains an assignment to the fixed-after-init variable \""
         << getVariable()
         << "\", can be invoked through a public function \""
         << getCaller() << "\"." << endl;
}
}
}
}