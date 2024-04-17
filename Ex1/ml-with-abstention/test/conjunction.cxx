#include "stdexcept"
#include "conjunction.hxx"

inline void test(const bool condition){
    if (!condition) throw std::logic_error("test_failed");
}

void testConjunctionAccessors(){
    Conjunction conjunction;

    conjunction.insert(1, true);
    conjunction.insert(2, false);

    test(conjunction.negated().find(1) != conjunction.negated().end());
    test(conjunction.nonNegated().find(2) != conjunction.nonNegated().end());

    test(conjunction.size() == 2);

    conjunction.insert(2, false);
    test(conjunction.size() == 2);

}

void testEquality(){
    Conjunction conjunction1;

    conjunction1.insert(1, true);
    conjunction1.insert(2, false);

    Conjunction conjunction2;

    conjunction2.insert(1, true);
    conjunction2.insert(2, false);

    Conjunction conjunction3;

    conjunction3.insert(1, true);
    conjunction3.insert(2, true);

    test(conjunction1 == conjunction2);
    test(conjunction1 != conjunction3);


}

void testContradiction(){
    Conjunction conjunction1;

    conjunction1.insert(1, true);
    conjunction1.insert(2, false);

    Conjunction conjunction2;

    conjunction2.insert(3, true);
    conjunction2.insert(4, false);

    Conjunction conjunction3;

    conjunction3.insert(1, true);
    conjunction3.insert(2, true);

    test(!conjunction1.isProductZero(conjunction2));

    test(conjunction1.isProductZero(conjunction3));
}

int main(){
    testConjunctionAccessors();
    testEquality();
    testContradiction();

    return 0;
}

