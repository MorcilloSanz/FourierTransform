# FourierTransform

the [Fourier transform](https://en.wikipedia.org/wiki/Fourier_transform) is an integral transform that converts a function into a form that describes the frequencies present in the original function. The output of the transform is a complex-valued function of frequency. The term Fourier transform refers to both this complex-valued function and the mathematical operation. When a distinction needs to be made the Fourier transform is sometimes called the frequency domain representation of the original function. The Fourier transform is analogous to decomposing the sound of a musical chord into the intensities of its constituent pitches.

## Definition
The Fourier Transform (FT) is an analysis process, decomposing a complex-valued function $f(x)$ into its constituent frequencies.The inverse process is synthesis, which recreates $f(x)$ from its transform.

$$\widehat {f}(\xi )=\int _{-\infty }^{\infty }f(x)\ e^{-i2\pi \xi x}\,dx$$

Thus, the inverse of the Fourier transform is given by:

$$f(x)=\int _{-\infty }^{\infty }{\widehat {f}}(\xi )\ e^{i2\pi \xi x}\,d\xi ,\quad \forall \ x\in \mathbb {R}$$

## Discrete Fourier Transform (DFT)
As we are dealing with discrete data, the Discrete Fourier Transform (DFT) transforms a sequence of $N$ complex numbers:

${\displaystyle \left\{\mathbf {x} _{n}\right\}:=x_{0},x_{1},\ldots ,x_{N-1}}$

${\displaystyle \left\{\mathbf {X} _{k}\right\}:=X_{0},X_{1},\ldots ,X_{N-1},}$

$$X_{k}=\sum _{n=0}^{N-1}x_{n}\cdot e^{-i2\pi {\tfrac {k}{N}}n}$$

The inverse of the Discrete Fourier Transform is given by:

$$x_{n}={\frac {1}{N}}\sum _{k=0}^{N-1}X_{k}\cdot e^{i2\pi {\tfrac {k}{N}}n}$$

## Fast Fourier Transform (FFT)

It is an algorithm that efficiently computes the discrete Fourier transform (DFT) of a sequence, or its inverse. The standard DFT has a time complexity of $O(N^2)$, where $N$ is the number of data points, while FFT reduces this to $O(N \log N)$, making it much faster for practical applications.

### The radix-2 DIT case

A radix-2 decimation-in-time (DIT) FFT is the simplest and most common form of the Cooley–Tukey algorithm, although highly optimized Cooley–Tukey implementations typically use other forms of the algorithm as described below. Radix-2 DIT divides a DFT of size $N$ into two interleaved DFTs (hence the name "radix-2") of size $N/2$ with each recursive stage.

Radix-2 DIT first computes the DFTs of the even-indexed inputs ${\displaystyle (x_{2m}=x_{0},x_{2},\ldots ,x_{N-2})}$ and of the odd-indexed inputs ${\displaystyle (x_{2m+1}=x_{1},x_{3},\ldots ,x_{N-1})}$ and then combines those two results to produce the DFT of the whole sequence. This idea can then be performed recursively to reduce the overall runtime to $O(N \log N)$. This simplified form assumes that $N$ is a power of two.

$${\displaystyle {\begin{matrix}X_{k}=\underbrace {\sum \limits _{m=0}^{N/2-1}x_{2m}e^{-{\frac {2\pi i}{N/2}}mk}} _{\mathrm {DFT\;of\;even-indexed\;part\;of\;} x_{n}}{}+e^{-{\frac {2\pi i}{N}}k}\underbrace {\sum \limits _{m=0}^{N/2-1}x_{2m+1}e^{-{\frac {2\pi i}{N/2}}mk}} _{\mathrm {DFT\;of\;odd-indexed\;part\;of\;} x_{n}}=E_{k}+e^{-{\frac {2\pi i}{N}}k}O_{k}\qquad {\text{ for }}k=0,\dots ,{\frac {N}{2}}-1.\end{matrix}}}$$

## References
[Fourier Transform](https://en.wikipedia.org/wiki/Fourier_transform)

[Discrete Fourier Transform](https://en.wikipedia.org/wiki/Discrete_Fourier_transform)

[Fast Fourier Transform](https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm)

[Cooley–Tukey FFT algorithm](https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm)