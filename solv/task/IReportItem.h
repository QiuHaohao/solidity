//
// Created by Qiu Haoze on 20/2/20.
//

#ifndef SOLIDITY_IREPORTITEM_H
#define SOLIDITY_IREPORTITEM_H
namespace dev
{
namespace solidity
{
namespace verifier
{

class IReportItem {
public:
    virtual void report() { return; };
};
}
}
}
#endif //SOLIDITY_IREPORTITEM_H
