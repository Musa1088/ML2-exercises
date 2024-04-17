#include "stdexcept"
#include "conjunction.hxx"
#include "dnf.hxx"

inline void test(const bool condition){
    if (!condition) throw std::logic_error("test_failed");
}

void testAccessors(){
    DNF dnf1;

    Conjunction conjunction;

    conjunction.insert(1, true);
    conjunction.insert(2, false);

    Conjunction conjunction2;

    conjunction2.insert(1, false);
    conjunction2.insert(2, true);

    dnf1.insert(conjunction);
    dnf1.insert(conjunction2);
    dnf1.insert(conjunction);

    test(dnf1.length() == 4);
    test(dnf1.depth() == 2);
    test(dnf1.numberOfConjunctions() == 2);
    test(dnf1.conjunctions().find(conjunction) != dnf1.conjunctions().end());
    test(dnf1.conjunctions().find(conjunction2) != dnf1.conjunctions().end());
}

void testContradiction(){
    DNF dnf1;
    DNF dnf2;

    Conjunction conjunction;

    conjunction.insert(1, true);
    conjunction.insert(2, false);

    Conjunction conjunction2;

    conjunction2.insert(1, true);
    conjunction2.insert(2, true);

    Conjunction conjunction3;
    conjunction3.insert(1, false);
    conjunction3.insert(2, true);

    Conjunction conjunction4;
    conjunction4.insert(1, true);
    conjunction4.insert(3, false);

    dnf1.insert(conjunction);
    dnf1.insert(conjunction2);
    dnf2.insert(conjunction3);

    test(dnf1.isProductZero(dnf2));

    DNF dnf3;
    DNF dnf4;

    dnf3.insert(conjunction2);
    dnf3.insert(conjunction3);
    dnf4.insert(conjunction);
    dnf4.insert(conjunction4);

    test(!dnf3.isProductZero(dnf4));
}

int main(){
    testAccessors();
    testContradiction();

    return 0;
}

