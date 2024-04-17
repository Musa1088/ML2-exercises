#include <iostream>
#include <mnist_loader.hxx>
#include "mnist_utils.hxx"
#include "dnf.hxx"
#include "algorithms.hxx"
#include "log.hxx"
#include "filesystem"

std::string GetCurrentTimeForFileName()
{
    auto time = std::time(nullptr);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%F_%T"); // ISO 8601 without timezone information.
    auto s = ss.str();
    std::replace(s.begin(), s.end(), ':', '-');
    return s;
}


void evaluateDNFs(
        DNF const & dnf1,
        DNF const & dnf2,
        std::vector<std::vector<unsigned char>> const & firstDigitTest,
        std::vector<std::vector<unsigned char>> const & secondDigitTest
){
    if (dnf1.isProductZero(dnf2)){
        std::cout << "Resulting DNFs are contradicting" << std::endl;
    } else  {
        std::cout << "Resulting DNFs are not contradicting!" << std::endl;
    }

    // evaluate
    double fivesCorrect = 0;
    double ninesCorrect = 0;

    for (auto const & testTruthPoint : firstDigitTest){
        if (dnf1.evaluate(testTruthPoint)){
            fivesCorrect += 1;
        }
    }

    for (auto const & testTruthPoint : secondDigitTest){
        if (dnf2.evaluate(testTruthPoint)){
            ninesCorrect += 1;
        }
    }

    std::cout << "Test 5-Accuracy: " << fivesCorrect / static_cast<double>(firstDigitTest.size()) << std::endl;
    std::cout << "Test 9-Accuracy: " << ninesCorrect / static_cast<double>(secondDigitTest.size()) << std::endl;
}

int main() {
    size_t localSearchMaxEliminatedVariablesPerIteration = 10000;
    size_t numElementsPerDigit = 50;
    std::filesystem::path filePath = "../results/" + GetCurrentTimeForFileName() + ".txt";

    int digits[] = {5, 9};

    mnist_loader train("../data/train-images.idx3-ubyte",
                       "../data/train-labels.idx1-ubyte");
    mnist_loader test("../data/t10k-images.idx3-ubyte",
                       "../data/t10k-labels.idx1-ubyte");

    auto firstDigitTrain = getTruthPointsFromMNISTLabel(train, digits[0], numElementsPerDigit);
    auto secondDigitTrain = getTruthPointsFromMNISTLabel(train, digits[1], numElementsPerDigit);

    auto firstDigitTest = getTruthPointsFromMNISTLabel(test, digits[0]);
    auto secondDigitTest = getTruthPointsFromMNISTLabel(test, digits[1]);

    DNF dnf1 = buildCDNF(firstDigitTrain);
    DNF dnf2 = buildCDNF(secondDigitTrain);

    // UNCOMMENT if you want to log to file
    std::ofstream file(filePath);
    Log log(file);

    // UNCOMMENT if you want to log to console
//    Log log;

    localSearchRemoveVariables(dnf1, dnf2, localSearchMaxEliminatedVariablesPerIteration, log);

    evaluateDNFs(dnf1, dnf2, firstDigitTest, secondDigitTest);
    evaluateDNFs(dnf1, dnf2, firstDigitTrain, secondDigitTrain);
}
