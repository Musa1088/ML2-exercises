#ifndef ML_WITH_ABSTENTION_CONJUNCTION_H
#define ML_WITH_ABSTENTION_CONJUNCTION_H

#include <algorithm>
#include "set"

class Conjunction{
public:
    Conjunction();

    size_t size() const;

    constexpr bool operator==(const Conjunction & other) const;
    constexpr bool operator!=(const Conjunction & other) const;
    constexpr bool operator<(const Conjunction & other) const;

    template<class RandomAccessIterator>
    bool evaluate(RandomAccessIterator const & point) const;

    void insert(size_t const, bool const);

    void remove(size_t);

    bool isProductZero(const Conjunction & other) const;

    const std::set<size_t > & nonNegated() const;
    const std::set<size_t > & negated() const;
    const std::set<size_t > & variables() const;

private:
    std::set<size_t> nonNegated_;
    std::set<size_t> negated_;
    std::set<size_t> variables_;

};

Conjunction::Conjunction() :
    nonNegated_(),
    negated_(),
    variables_(){

    }

inline
size_t
Conjunction::size() const {
    return variables_.size();
}

constexpr bool Conjunction::operator==(const Conjunction &other) const {
    return (negated_ == other.negated_) && (nonNegated_ == other.nonNegated_);
}

constexpr bool Conjunction::operator<(const Conjunction &other) const {
    return (nonNegated_ < other.nonNegated_)
        || ((nonNegated_ == other.nonNegated_) && (negated_ < other.negated_));
}

void Conjunction::insert(const size_t variable, const bool negated) {
    if (negated){
        negated_.insert(variable);
    } else {
        nonNegated_.insert(variable);
    }

    variables_.insert(variable);
}

constexpr bool Conjunction::operator!=(const Conjunction &other) const {
    return !(*this == other);
}

inline
std::set<size_t> const &
Conjunction::nonNegated() const {
    return nonNegated_;
}

inline
std::set<size_t> const &
Conjunction::negated() const {
    return negated_;
}

bool Conjunction::isProductZero(const Conjunction &other) const {
    if (variables_.empty() || other.variables_.empty()){
        return true;
    }

    for (auto v1: negated_){
        for (auto v2: other.nonNegated_){
            if (v1 == v2){
                return true;
            }
        }
    }

    for (auto v1: nonNegated_){
        for (auto v2: other.negated_){
            if (v1 == v2){
                return true;
            }
        }
    }

    return false;
}

void Conjunction::remove(size_t variable) {
    negated_.erase(variable);
    nonNegated_.erase(variable);
    variables_.erase(variable);
}

inline
std::set<size_t> const &
Conjunction::variables() const {
    return variables_;
}


template<class RandomAccessIterator>
inline
bool
Conjunction::evaluate(RandomAccessIterator const &point) const {
    for (auto nonNegated : nonNegated_){
        if (point[nonNegated] == 0){
            return false;
        }
    }

    for (auto negated: negated_){
        if(point[negated] == 1){
            return false;
        }
    }

    return true;
}




#endif //ML_WITH_ABSTENTION_CONJUNCTION_H
