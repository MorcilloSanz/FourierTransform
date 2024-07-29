/*
    MIT License

    Copyright (c) 2024 Alberto Morcillo Sanz

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <complex>

#ifndef M_PI
#define M_PI   3.14159265358979323846264338327950288
#endif

namespace ft
{

using namespace std::complex_literals;

/**
 * @brief Discrete Fourier Transform.
 * 
 * @param sequence sequence of complex numbers (x1, x2, ..., xn).
 * 
 * @return returns the new sequence (X1, X2, ..., Xk).
*/
template <typename T>
std::vector<std::complex<T>> DFT(const std::vector<std::complex<T>>& sequence) {

    std::vector<std::complex<T>> output;
    for(size_t k = 0; k < sequence.size(); k ++) {
    
        std::complex<T> Xk = 0;
        for(size_t n = 0; n < sequence.size(); n ++) {
            Xk += sequence[n] * std::exp(-1i * 2.0 * M_PI * static_cast<T>(k) 
                * static_cast<T>(n) / static_cast<T>(sequence.size()));
        }

        output.push_back(Xk);   
    }

    return output;
}

/**
 * @brief Inverse Discrete Fourier Transform.
 * 
 * @param sequence sequence of complex numbers (X1, X2, ..., Xk).
 * 
 * @return returns the new sequence (x1, x2, ..., xk).
*/
template <typename T>
std::vector<std::complex<T>> IDFT(const std::vector<std::complex<T>>& sequence) {

    std::vector<std::complex<T>> output;
    for(size_t n = 0; n < sequence.size(); n ++) {
    
        std::complex<T> xn = 0;
        for(size_t k = 0; k < sequence.size(); k ++) {
            xn += sequence[k] * std::exp(1i * 2.0 * M_PI * static_cast<T>(k) 
                * static_cast<T>(n) / static_cast<T>(sequence.size()));
        }
        xn /= static_cast<T>(sequence.size());

        output.push_back(xn);
    }

    return output;
}

/**
 * @brief Radix-2 DIT Fast Fourier Transform.
 * 
 * @pre N must be a power of 2.
 * 
 * @param sequence sequence of complex numbers (x1, x2, ..., xn).
 * @param k k index.
 * 
 * @return returns the Xk element.
*/
template <typename T>
std::complex<T> DITFFT(const std::vector<std::complex<T>>& sequence, unsigned int k) {

    if(sequence.size() == 1) return sequence[0];

    std::vector<std::complex<T>> even, odd;
    for(int i = 0; i < sequence.size(); i ++) {

        if(i % 2 == 0) even.push_back(sequence[i]);
        else odd.push_back(sequence[i]);
    }

    std::complex<T> Wk = std::exp(-1i * 2.0 * M_PI * static_cast<T>(k) / static_cast<T>(sequence.size()));
    std::complex<T> Ek = DITFFT(even, k);
    std::complex<T> Ok = DITFFT(odd, k);

    std::complex<T> Xk = Ek + Wk * Ok;

    return Xk;
}

/**
 * @brief Radix-2 DIT Fast Fourier Transform.
 * 
 * @pre N must be a power of 2.
 * 
 * @param sequence sequence of complex numbers (x1, x2, ..., xn).
 * 
 * @return returns the new sequence (X1, X2, ..., Xk).
*/
template <typename T>
std::vector<std::complex<T>> FFT(const std::vector<std::complex<T>>& sequence) {

   std::vector<std::complex<T>> output;

    for(int k = 0; k < sequence.size(); k ++) {
        std::complex<T> Xk = DITFFT(sequence, k);
        output.push_back(Xk);
    }

   return output;
}

/**
 * @brief Radix-2 DIT Inverse Fast Fourier Transform.
 * 
 * @pre N must be a power of 2.
 * 
 * @param sequence sequence of complex numbers (x1, x2, ..., xn).
 * 
 * @return returns the new sequence (X1, X2, ..., Xk).
*/
template <typename T>
std::vector<std::complex<T>> IFFT(const std::vector<std::complex<T>>& sequence) {

    std::vector<std::complex<T>> conjugates;
    for(auto& z : sequence)
        conjugates.push_back(std::conj(z));

    std::vector<std::complex<T>> output = FFT(conjugates);
    for(auto& z : output)
        z = std::conj(z) / static_cast<T>(output.size());
    
    return output;
}

/**
 * @brief Computes the frequencies of the frequency domain.
 * 
 * @param samples the number of samples.
 * @param samplingRate the sampling rate.
 * 
 * @return returns the frequencies.
*/
template <typename T>
std::vector<T> FFT_FREQ(unsigned int samples, T samplingRate) {

    std::vector<T> freq;

    for(int k = 0; k < samples; k ++)
        freq.push_back(k * samplingRate / samples);

    return freq;
}

/**
 * @brief Normalizes a sequence
 * 
 * @param sequence the sequence.
 * 
 * @return returns the normalized sequence.
*/
template <typename T>
std::vector<std::complex<T>> normalize(const std::vector<std::complex<T>>& sequence) {

    if (sequence.empty()) return {};

    T norm = 0;
    for (const auto& val : sequence)
        norm += std::norm(val);
    norm = std::sqrt(norm);

    if (norm == 0) return sequence;

    std::vector<std::complex<T>> normalizedSequence;
    normalizedSequence.reserve(sequence.size());

    for (const auto& val : sequence)
        normalizedSequence.push_back(val / norm);

    return normalizedSequence;
}

}