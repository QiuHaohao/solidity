//
// Created by Qiu Haoze on 20/2/20.
//

#ifndef SOLIDITY_FIXEDAFTERINITREPORTITEM_H
#define SOLIDITY_FIXEDAFTERINITREPORTITEM_H

#include "solv/task/IReportItem.h"



namespace dev
{
namespace solidity
{
namespace verifier
{
class FixedAfterInitReportItem : public IReportItem {
public:
    FixedAfterInitReportItem(std::string _caller, std::string _assigner, std::string _variable)
        :caller(_caller), assigner(_assigner), variable(_variable) {};
    void report();

    std::string getCaller() {
        return caller;
    }
    std::string getAssigner() {
        return assigner;
    }
    std::string getVariable() {
        return variable;
    }

private:
    std::string caller;
    std::string assigner;
    std::string variable;
};
}
}
}
#endif //SOLIDITY_FIXEDAFTERINITREPORTITEM_H
