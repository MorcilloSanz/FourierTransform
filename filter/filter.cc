#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib> 

#include "../src/FourierTransform.h"

using namespace std::complex_literals;

template <typename T>
std::complex<T> f(T t) {
    T noise = rand() % 100;
    return t + 100 * cos(t / 20) + noise;
}

template <typename T>
std::vector<std::complex<T>> generateSignal(float t0, float t1, unsigned int samples) {

    std::vector<std::complex<T>> signal;
    float deltaTime = (t1 - t0) / samples;

    std::ofstream signalFile("signal.txt");

    for(float t = t0; t < t1; t += deltaTime) {

        std::complex<T> n = f(t);

        signal.push_back(n);
        signalFile << n.real() << " ";
    }

    signalFile.close();

    return signal;
}

int main() {

    // Original signal 
    unsigned int samples = 1024;
    float t0 = 0.0f, t1 = 1000;
    
    std::vector<std::complex<double>> signal = generateSignal<double>(t0, t1, samples);

    // Apply filter
    double lowFrequencyThreshold = 0.02;
    double highFrequencyThreshold = 1.0;

    std::vector<std::complex<double>> fourierTransform = ft::FFT(signal);
    std::vector<std::complex<double>> filteredFourierTransform(fourierTransform.size());

    float sampleRate = samples / (t1 - t0);
    std::vector<double> frequencies = ft::FFT_FREQ<double>(samples, sampleRate);

    std::ofstream domainsFile("dom.txt");
    domainsFile << t0 << " " << t1 << " " << frequencies[0] << " " << frequencies[frequencies.size() - 1] << " " << samples;
    domainsFile.close();

    std::ofstream fourierTransformRealFile("ftr.txt");
    std::ofstream fourierTransformImagFile("fti.txt");

    for(int k = 0; k < samples; k ++) {

        if(fabs(frequencies[k]) <= lowFrequencyThreshold || fabs(frequencies[k]) > highFrequencyThreshold)
            filteredFourierTransform[k] = fourierTransform[k];
        else 
            filteredFourierTransform[k] = 0;

        fourierTransformRealFile << fourierTransform[k].real() << " ";
        fourierTransformImagFile << fourierTransform[k].imag() << " ";
    }

    fourierTransformRealFile.close();
    fourierTransformImagFile.close();
    
    // Final signal
    std::vector<std::complex<double>> filteredSignal = ft::IFFT(filteredFourierTransform);

    std::ofstream filteredSignalFile("filtered_signal.txt");

    for(int k = 0; k < samples; k ++)
        filteredSignalFile << filteredSignal[k].real() << " ";
        
    filteredSignalFile.close();

    return 0;
}