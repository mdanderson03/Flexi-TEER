
# AC Theory

The DC analysis section is interesting, but not practical. The charge build up on membranes is a health hazard to the cells and it still depends on measuring within a time window. Too fast and charge has not sufficiently built
up on the cells membrane to force all of the current through the tight junctions. Too slow and and the current can become too low to accurately measure. 

To address these concerns and to extract more components, we turn to AC analysis.


![](images/4_electrode001.png)


We are still using the 4 electrode circuit, but we just use AC current instead of DC.

```math
\tag{1} Z = Z_{1}+Z_{2}
```

```math
\tag{2} Z_{1}=R_{med}+ \dfrac{-j}{\omega*C_{e}}
```

Where -j is imaginary i (standard syntax for electronics as i is typically a current value) and omega is angular freq. 

```math 
\tag{3} Z_{2}= \dfrac{1}{\dfrac{1}{R_{TJ}}+j*\omega*C_{cells}}=\dfrac{R_{TJ}}{1+j*\omega*C_{cells}*R_{TJ}}
```

Multiple (3) by the complex conjugate of its denominator

```math
Z_{2}= \dfrac{R_{TJ}*(1-j*\omega*C_{cells}*R_{TJ})}{1+\omega^2*C_{cells}^2*R_{TJ}^2}= [\dfrac{1}{1+\omega^2*C_{cells}^2*R_{TJ}^2}]*(R_{TJ}-j*\omega*C_{cells}*R_{TJ}^2)
```

Separate terms that are real and imaginary

```math
Z = [\dfrac{1}{1+\omega^2*C_{cells}^2*R_{TJ}^2}]*[(R_{TJ}+R_{med}+\omega^2*C_{cells}^2*R_{TJ}^2)+ j*[(-\omega^2*C_{e}*C_{cells}*R_{TJ}^2-1-\omega^2*C_{cells}^2*R_{TJ}^2)*\dfrac{1}{\omega*C_{e}}]]
```

Lets make some new variables to make it easier to read

```math
\tag{6} \alpha = \dfrac{1}{1+\omega^2*C_{cells}^2*R_{TJ}^2}, \quad \beta = \dfrac{1}{\omega*C_{e}}
```

Sub (6) into (5)

```math
Z = \alpha*[(R_{TJ}+R_{med}+\omega^2*C_{cells}^2*R_{TJ}^2) +j*\beta*[-\omega^2*C_{e}*C_{cells}*R_{TJ}^2-\omega^2*C_{cells}^2*R_{TJ}^2-1]]
```

Lets reduce this further

```math
R_{base}= R_{TJ}+R_{med}+\omega^2*C_{cells}^2*R_{TJ}^2, \quad and \quad X_{base} =-(\omega^2*C_{e}*C_{cells}*R_{TJ}^2+\omega^2*C_{cells}^2*R_{TJ}^2+1)
```

```math
\tag{7} Z = \alpha*[R_{base} -j*\beta*X_{base}]
```

Next to find the total resitance we must find the complex magnitude to solve for it. 

```math
\tag{8} \mid Z \mid = \sqrt[2]*{z*z^{\star}}= \alpha*\sqrt[2]*{R_{base}^2+\beta^2*X_{base}}
```

Lets look at some cases. The first will be high frequency.

```math
\tag{9} if \quad w \gg 1, \beta*X_{base} \approx \dfrac{\omega^2}{\omega*C_{e}} (C_{e}*C_{cells}*R_{TJ}^2+C_{cells}^2*R_{TJ}^2) \propto \omega
```

```math
\tag{10} R_{base} \approx \omega^2*C_{cells}^2*R_{TJ}^2*R_{media} \propto \omega^2 
```

R_base contributes to a higher degree than X_base and thus

```math
\tag{11} Z \approx \alpha*\omega^2*C_{cells}^2*R_{TJ}^2 \approx \dfrac{\omega^2*C_{cells}^2*R_{TJ}^2*R_{media}}{\omega^2*C_{cells}^2*R_{TJ}^2}=R_{media}
```

Now lets turn to the opposite end of the spectrum and find the solution at small omegas

```math
\tag{12} at \quad \omega \ll 1, \quad  X_{base} \approx 1 , \quad R_{base} \approx R_{TJ} +R_{media}
```

and

```math
\tag{13} \alpha \approx 1, \quad \beta = \dfrac{1}{\omega*C_{e}}
```

thus

```math
\tag{14} Z \approx \sqrt[2]*{(R_{TJ} +R_{media})^2 + \dfrac{1}*{\omega*C_{e}}^2} \approx \dfrac{1}{\omega*C_{e}}
```

In summary

```math
\tag{15} if \quad \color{blue}{\omega \gg 1, \quad Z \approx R_{media}} \color{black} \quad and \quad at \quad \color{red}{\omega \ll 1, \quad Z \approx \dfrac{1}{\omega*C_{e}}}
```

This allows us to perform something called impedence spectroscopy. At low freq we can determine the electrode capacitance and at high freq we can determine the resistance in the media. Subbinng those terms in and doing
a regression to the full solution allows us to determine the cell capacitance and tight junctional resistance. Notice too in this method that nothing was time depended and thus no integrals to perform over hard to determine variables.
Below is a sample spectra of impedences from the full solution.


![](images/spectrum.png)














