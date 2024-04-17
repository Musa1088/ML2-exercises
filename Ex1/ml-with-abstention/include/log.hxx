#pragma once
#ifndef ML_WITH_ABSTENTION_LOG_H
#define ML_WITH_ABSTENTION_LOG_H

#include "chrono"
#include "iostream"

class Log{

public:
    Log(std::ostream & = std::cout);

    void log(size_t, size_t) const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock > currentStart_;
    std::ostream & out_;
};

inline
Log::Log(std::ostream & out) :
    out_(out)
    {
    out_ << "Elapsed\tDNF1\tDNF2" << std::endl;
    currentStart_ = std::chrono::high_resolution_clock::now();
}


inline
void
Log::log(size_t dnfSize1, size_t dnfSize2) const {
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - currentStart_).count();

    out_ <<  duration << "\t" << dnfSize1 << "\t" << dnfSize2 << std::endl;
}


#endif //ML_WITH_ABSTENTION_LOG_H
