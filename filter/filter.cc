#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib> 

#include "FourierTransform.h"

using namespace std::complex_literals;


int main() {

    // Original signal 
    std::vector<std::complex<double>> signal;
    std::ofstream signalFile("signal.txt");

    float dt = 0.1;
    for(float t = 0; t < 128; t += dt) {

        float noise = rand() % 10;
        std::complex<double> n = t + 20 * cos(t / 2) + noise + 0i;
        signal.push_back(n);

        signalFile << n.real() << " ";
    }

    signalFile.close();

    // Filter
    unsigned int samples = 512; // power of 2
    double sampleRate = static_cast<double>(samples) / signal.size();
    double lowFrequencyThreshold = 0.01;
    double highFrequencyThreshold = 0.39;

    std::ofstream sampledsignalFile("sampled_signal.txt");

    std::vector<std::complex<double>> sampledsignal(samples);
    for(int k = 0; k < samples; k ++) {
        sampledsignal[k] = signal[k * static_cast<int>(signal.size() / samples)];
        sampledsignalFile << sampledsignal[k].real() << " ";
    }

    sampledsignalFile.close();

    std::vector<std::complex<double>> fourierTransform = ft::FFT(sampledsignal);
    std::vector<std::complex<double>> filteredFourierTransform(fourierTransform.size());

    std::vector<double> frequencies = ft::FFT_FREQ(samples, sampleRate);
    for(int k = 0; k < samples; k ++) {

        if(fabs(frequencies[k]) <= lowFrequencyThreshold || fabs(frequencies[k]) > highFrequencyThreshold)
            filteredFourierTransform[k] = fourierTransform[k];
        else 
            filteredFourierTransform[k] = 0;
    }
    
    // Final signal
    std::vector<std::complex<double>> filteredSignal = ft::IFFT(filteredFourierTransform);

    std::ofstream filteredSignalFile("filtered_signal.txt");
    for(int k = 0; k < samples; k ++) {

        if(k < samples - 1)
            filteredSignalFile << filteredSignal[k].real() << " ";
        else
            filteredSignalFile << filteredSignal[k].real();
    }
        
    filteredSignalFile.close();

    return 0;
}