#include <iostream>

#include "FourierTransform.h"

using namespace std::complex_literals;

std::vector<std::complex<double>> sequence = {
    1.0 + 2i, 2.5 - 2.5i, 3.2 + 5i, 4.8 + 0.5i
};

void DFT_test() {

    std::cout << "Sequence of complex numbers" << std::endl;
    for(auto& z : sequence) std::cout << z << std::endl;

    std::vector<std::complex<double>> transformedSequence = ft::DFT(sequence);

    std::cout << "\nDiscrete Fourier transform:" << std::endl;
    for(auto& z : transformedSequence) std::cout << z << std::endl;
    
    std::vector<std::complex<double>> invTransformedSequence = ft::IDFT(transformedSequence);
    
    std::cout << "\nInverse Discrete Fourier transform: " << std::endl;
    for(auto& z : invTransformedSequence) std::cout << z << std::endl;
}

void FFT_test() {

    std::cout << "Sequence of complex numbers" << std::endl;
    for(auto& z : sequence) std::cout << z << std::endl;

    std::vector<std::complex<double>> transformedSequence = ft::FFT(sequence);

    std::cout << "\nFast Fourier transform:" << std::endl;
    for(auto& z : transformedSequence) std::cout << z << std::endl;

    std::vector<std::complex<double>> invTransformedSequence = ft::IFFT(transformedSequence);
    
    std::cout << "\nInverse Fast Fourier transform: " << std::endl;
    for(auto& z : invTransformedSequence) std::cout << z << std::endl;
}

int main() {

    std::cout << "\n-------DISCRETE FOURIER TRANSFORM-------\n" << std::endl;
    DFT_test();

    std::cout << "\n---------FAST FOURIER TRANSFORM---------\n" << std::endl;
    FFT_test();

    return 0;
}