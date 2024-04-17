#ifndef ML_WITH_ABSTENTION_ALGORITHMS_H
#define ML_WITH_ABSTENTION_ALGORITHMS_H

#include "dnf.hxx"
#include "vector"
#include "log.hxx"

inline
DNF buildCDNF(std::vector<std::vector<unsigned char>> const &truthPoints) {
    DNF dnf;
    for (auto const &truthPoint: truthPoints) {
        Conjunction conjunction;

        for (size_t i = 0; i < truthPoint.size(); ++i) {
            conjunction.insert(i, !truthPoint[i]);
        }

        dnf.insert(conjunction);
    }

    return dnf;
}

inline
bool
canVariableBeRemoved(Conjunction const & conjunction, size_t variable, Conjunction const & cnj){
    for (auto v1: conjunction.negated()){
        for (auto v2: cnj.nonNegated()){
            if ((v1 == v2) && (v1 != variable)){
                return true;
            }
        }
    }

    for (auto v1 : conjunction.nonNegated()){
        for (auto v2 : cnj.negated()){
            if ((v1 == v2) && (v1 != variable)){
                return true;
            }
        }
    }
    return false;
}

inline
bool
canVariableBeRemoved(Conjunction const & conjunction, size_t variable, DNF const & otherDNF){
    for (auto const &cnj: otherDNF.conjunctions()) {
        if (!canVariableBeRemoved(conjunction, variable, cnj))
            return false;
    }

    return true;
}

inline
bool
localRemoveVariableFromDNF (DNF & dnf, DNF const & otherDNF, size_t maxEliminatedVariablesPerIteration){
    size_t eliminated = 0;

    for (auto it = dnf.conjunctions().begin(); it != dnf.conjunctions().end(); ){
        Conjunction tmpConjunction = *it;

        for (auto v : it->variables()){
            if (canVariableBeRemoved(tmpConjunction, v, otherDNF)){
                tmpConjunction.remove(v);

                eliminated++;

                if (eliminated == maxEliminatedVariablesPerIteration){
                    dnf.remove(*it);
                    dnf.insert(tmpConjunction);

                    return true;
                }
            }
        }

        if (tmpConjunction.size() < it->size()){
            auto current = it++;
            dnf.remove(*current);
            dnf.insert(tmpConjunction);
        } else {
            it++;
        }
    }

    return false;
}

inline
void
localSearchRemoveVariables(DNF & dnf1, DNF & dnf2, size_t maxEliminatedVariablesPerIteration, Log const & log){

    bool firstDone = false;
    bool secondDone = false;

    log.log(dnf1.length(), dnf2.length());

    while (!firstDone && !secondDone){
        firstDone = !localRemoveVariableFromDNF(dnf1, dnf2, maxEliminatedVariablesPerIteration);
        log.log(dnf1.length(), dnf2.length());
        secondDone = !localRemoveVariableFromDNF(dnf2, dnf1, maxEliminatedVariablesPerIteration);
        log.log(dnf1.length(), dnf2.length());
    }
}



#endif //ML_WITH_ABSTENTION_ALGORITHMS_H
