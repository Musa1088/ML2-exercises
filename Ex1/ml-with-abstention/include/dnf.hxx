#ifndef ML_WITH_ABSTENTION_DNF_H
#define ML_WITH_ABSTENTION_DNF_H

#include "set"
#include "conjunction.hxx"

class DNF{
public:
    DNF();

    size_t length() const;
    size_t depth() const;
    size_t numberOfConjunctions() const;
    template<class RandomAccessIterator>
    bool evaluate(RandomAccessIterator const & point) const;
    void insert(Conjunction const &);

    void remove(Conjunction const &);


    std::set<Conjunction> const & conjunctions() const;

    bool isProductZero(DNF const & ) const;

private:
    std::set<Conjunction> conjunctions_;
};

DNF::DNF():
    conjunctions_(){
}


inline
size_t
DNF::length() const {
    size_t length = 0;
    for (const auto& conj: conjunctions_){
        length += conj.size();
    }
    return length;
}

inline
size_t
DNF::depth() const {
    size_t depth = 0;
    for (const auto& conj: conjunctions_){
        depth = std::max(depth, conj.size());
    }
    return depth;
}

size_t DNF::numberOfConjunctions() const {
    return conjunctions_.size();
}

void DNF::insert(const Conjunction & conjunction) {
    if (conjunction.size() != 0){
        conjunctions_.insert(conjunction);
    }
}

void DNF::remove(const Conjunction & conjunction) {
    conjunctions_.erase(conjunction);
}

std::set<Conjunction> const & DNF::conjunctions() const {
    return conjunctions_;
}

bool DNF::isProductZero(const DNF & other) const {
    for (auto const & cnj1: conjunctions_){
        for (auto const & cnj2 : other.conjunctions_){
            if (!cnj1.isProductZero(cnj2)){
                return false;
            }
        }
    }
    return true;
}

template<class RandomAccessIterator>
bool DNF::evaluate(const RandomAccessIterator &point) const {
    for (const auto& conjunction: conjunctions_){
        if (conjunction.evaluate(point)){
            return true;
        }
    }
    return false;
}


#endif //ML_WITH_ABSTENTION_DNF_H
