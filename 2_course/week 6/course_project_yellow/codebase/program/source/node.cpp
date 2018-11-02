#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) : cmp_(cmp), date_(date) {
}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
    return GetCompression(cmp_, date, GetDate());
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& value) : cmp_(cmp), value_(value) {
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
    return GetCompression(cmp_, event, GetEvent());
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logical_operation,
                                           const shared_ptr<Node>& left,
                                           const shared_ptr<Node>& right) : logical_operation_(logical_operation), 
                                                                            left_(left),
                                                                            right_(right) {}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    switch (logical_operation_) {
    case LogicalOperation::And:
        return left_->Evaluate(date, event) && right_->Evaluate(date, event);       
    case LogicalOperation::Or:
        return left_->Evaluate(date, event) || right_->Evaluate(date, event);
    }
    return true;
}

template <typename LHS, typename RHS>
bool GetCompression(const Comparison& cmp, const LHS& lhs, const RHS& rhs) {
    switch (cmp) {
    case Comparison::Equal:
        return lhs == rhs;
    case Comparison::Greater:
        return lhs > rhs;
    case Comparison::GreaterOrEqual:
        return lhs >= rhs;
    case Comparison::Less:
        return lhs < rhs;
    case Comparison::LessOrEqual:
        return lhs <= rhs;
    case Comparison::NotEqual:
        return lhs != rhs;
    }
}