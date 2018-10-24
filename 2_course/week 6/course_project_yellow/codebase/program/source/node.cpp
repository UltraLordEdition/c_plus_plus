#include "node.h"

bool EmptyNode::Evaluate(const Date&, const string& event) const {

    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) : cmp_(cmp), date_(date) {
}

bool DateComparisonNode::Evaluate(const Date&, const string& event) const {
    return true;
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& value) : cmp_(cmp), value_(value) {
}

bool EventComparisonNode::Evaluate(const Date&, const string& event) const {
    return true;
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logical_operation,
                                           const shared_ptr<Node>& left,
                                           const shared_ptr<Node>& ParseExpression) : logical_operation_(logical_operation), 
                                                                                      left_(left),
                                                                                      ParseExpression_(ParseExpression) {}

bool LogicalOperationNode::Evaluate(const Date&, const string& event) const {
    return true;
}