#ifndef ML_WITH_ABSTENTION_MNIST_UTILS_HXX
#define ML_WITH_ABSTENTION_MNIST_UTILS_HXX

#include "set"
#include "vector"
#include "mnist_loader.hxx"

inline
std::vector<std::vector<unsigned char>> getTruthPointsFromMNISTLabel(
        mnist_loader const & loader,
        int const label,
        size_t num = 0
        ){

    std::vector<std::vector<unsigned char>> truthPoints;

    for (int n = 0; n < loader.size(); ++n){
        std::vector<double> image_ = loader.images(n);
        int label_ = loader.labels(n);

        if (label_ == label){
            std::vector<unsigned char> truthPoint(image_.size());

            for (size_t index = 0; index < image_.size(); ++index){
                truthPoint[index] = static_cast<unsigned char>(image_[index] != 0.0);
            }

            truthPoints.push_back(truthPoint);

            if ((num != 0) && (truthPoints.size() == num)){
                break;
            }
        }
    }

    return truthPoints;
}


#endif //ML_WITH_ABSTENTION_MNIST_UTILS_HXX
