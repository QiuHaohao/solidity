//
// Created by Qiu Haoze on 13/12/19.
//

#ifndef SOLIDITY_TASKANNOTATION_H
#define SOLIDITY_TASKANNOTATION_H

#include <string>

#include <liblangutil/SourceLocation.h>

namespace dev
{
namespace solidity
{
namespace verifier
{

struct TaskAnnotation {
    std::string m_type;
    langutil::SourceLocation m_line_location;

    TaskAnnotation(std::string _type, int _line_start, int _line_end) : m_type(_type) {
        m_line_location.start = _line_start;
        m_line_location.end = _line_end;
    }
};

}
}
}
#endif //SOLIDITY_TASKANNOTATION_H
