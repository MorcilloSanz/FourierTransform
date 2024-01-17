# FourierTransform

the [Fourier transform (FT)](https://en.wikipedia.org/wiki/Fourier_transform) is an integral transform that converts a function into a form that describes the frequencies present in the original function. The output of the transform is a complex-valued function of frequency. The term Fourier transform refers to both this complex-valued function and the mathematical operation. When a distinction needs to be made the Fourier transform is sometimes called the frequency domain representation of the original function. The Fourier transform is analogous to decomposing the sound of a musical chord into the intensities of its constituent pitches.

## Definition
The [Fourier transform (FT)](https://en.wikipedia.org/wiki/Fourier_transform) is an analysis process, decomposing a complex-valued function $f(x)$ into its constituent frequencies.The inverse process is synthesis, which recreates $f(x)$ from its transform. The Fourier Transform is defined as:

```math
$$\widehat {f}(\xi )=\int _{-\infty }^{\infty }f(x)\ e^{-i2\pi \xi x}\,dx$$
```

In the case of having discrete data, like a sequence of complex numbers $\left\{{x} _{n}\right\}:=x_{0},x_{1},\ldots ,x_{N-1}$, we need the [Discrete Fourier Transform (DFT)](https://en.wikipedia.org/wiki/Discrete_Fourier_transform) to compute a new sequence of complex numbers $\left\{{X} _{k}\right\}:=X_{0},X_{1},\ldots ,X_{N-1}$

```math
$$X_{k}=\sum _{n=0}^{N-1}x_{n}\cdot e^{-i2\pi {\frac {k}{N}}n}$$
```

Note that the standard DFT has a time complexity of $O(N)$ where $N$ is the number of data points, whereas [Fast Fourier Transform (FFT)](https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm) reduces this to $O(N \log N)$, making it much faster for practical applications.

## Usage

```cpp
#include <iostream>

#include "FourierTransform.h"

using namespace std::complex_literals;

int main() {

	std::vector<std::complex<double>> sequence = {
		1.0 + 2i, 2.5 - 2.5i, 3.2 + 5i, 4.8 + 0.5i
	};

	std::cout << "\nDiscrete Fourier transform:" << std::endl;
	std::vector<std::complex<double>> transformedSequence = ft::DFT(sequence);

	for(auto& z : transformedSequence) 
		std::cout << z << std::endl;

	std::cout << "\nInverse Fourier transform: " << std::endl;
	std::vector<std::complex<double>> invTransformedSequence = ft::invDFT(transformedSequence);

	for(auto& z : invTransformedSequence) 
		std::cout << z << std::endl;

	return 0;
}
```