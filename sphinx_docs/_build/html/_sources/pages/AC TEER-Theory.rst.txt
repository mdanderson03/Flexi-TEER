AC TEER Theory
==============

The DC analysis section is interesting, but not practical. The charge build up on membranes is a health hazard to the cells and it still depends on measuring within a time window. Too fast and charge has not sufficiently built
up on the cells membrane to force all of the current through the tight junctions. Too slow and and the current can become too low to accurately measure. 

To address these concerns and to extract more components, we turn to AC analysis.

.. image:: C:\Users/mike/Documents/GitHub/Felxi-TEER/images/teer_theory/4_electrode.png
    :width: 800

We are still using the 4 electrode circuit, but we just use AC current instead of DC.

.. math:: Z = Z_{1}+Z_{2}
    :label: eq.1

.. math:: Z_{1}=R_{med}+ \dfrac{-j}{\omega*C_{e}}
    :label: eq.2

Where -j is imaginary i (standard syntax for electronics as i is typically a current value) and omega is angular freq. 

.. math:: Z_{2}= \dfrac{1}{\dfrac{1}{R_{TJ}}+j*\omega*C_{cells}}=\dfrac{R_{TJ}}{1+j*\omega*C_{cells}*R_{TJ}}
    :label: eq.3

Multiple (3) by the complex conjugate of its demonator

.. math:: Z_{2}= \dfrac{R_{TJ}*(1-j*\omega*C_{cells}*R_{TJ})}{1+\omega^2*C_{cells}^2*R_{TJ}^2}= [\dfrac{1}{1+\omega^2*C_{cells}^2*R_{TJ}^2}]*(R_{TJ}-j*\omega*C_{cells}*R_{TJ}^2)
    :label: eq.4

Separate terms that are real and imaginary

.. math:: Z = [\dfrac{1}{1+\omega^2*C_{cells}^2*R_{TJ}^2}]*[(R_{TJ}+R_{med}+\omega^2*C_{cells}^2*R_{TJ}^2)+ j*[(-\omega^2*C_{e}*C_{cells}*R_{TJ}^2-1-\omega^2*C_{cells}^2*R_{TJ}^2)*\dfrac{1}{\omega*C_{e}}]]
    :label: eq.5

Lets make some new variables to make it easier to read

.. math:: \alpha = \dfrac{1}{1+\omega^2*C_{cells}^2*R_{TJ}^2}, \quad \beta = \dfrac{1}{\omega*C_{e}}
    :label: eq.6

Sub (6) into (5)

.. math:: Z = \alpha*[(R_{TJ}+R_{med}+\omega^2*C_{cells}^2*R_{TJ}^2) +j*\beta*[-\omega^2*C_{e}*C_{cells}*R_{TJ}^2-\omega^2*C_{cells}^2*R_{TJ}^2-1]]
    :label: eq.7

Lets reduce this further

.. math:: R_{base}= R_{TJ}+R_{med}+\omega^2*C_{cells}^2*R_{TJ}^2, \quad and \quad X_{base} =-(\omega^2*C_{e}*C_{cells}*R_{TJ}^2+\omega^2*C_{cells}^2*R_{TJ}^2+1)
    :label: eq.8

.. math:: Z = \alpha*[R_{base} -j*\beta*X_{base}]
    :label: eq.9

Next to find the total ressitance we must find the complex magnitude to solve for it. 

.. math:: |Z| = \sqrt[2]{z*z^{\star}}= \alpha*\sqrt[2]{R_{base}^2+\beta^2*X_{base}}
    :label: eq.10

Lets look at some cases. The first will be high frequency.

.. math:: if \quad w \gg 1, \beta*X_{base} \approx \dfrac{\omega^2}{\omega*C_{e}} (C_{e}*C_{cells}*R_{TJ}^2+C_{cells}^2*R_{TJ}^2) \propto \omega
    :label: eq.11

.. math:: R_{base} \approx \omega^2*C_{cells}^2*R_{TJ}^2*R_{media} \propto \omega^2 
    :label: eq.12

R_base contributes to a higher degree than X_base and thus

.. math:: Z \approx \alpha*\omega^2*C_{cells}^2*R_{TJ}^2 \approx \dfrac{\omega^2*C_{cells}^2*R_{TJ}^2*R_{media}}{\omega^2*C_{cells}^2*R_{TJ}^2}=R_{media}
    :label: eq.13

Now lets turn to the opposite end of the spectrum and find the solution at small omegas

.. math:: at \quad \omega \ll 1, \quad  X_{base} \approx 1 , \quad R_{base} \approx R_{TJ} +R_{media}

and

.. math:: \alpha \approx 1, \quad \beta = \dfrac{1}{\omega*C_{e}}

thus

.. math:: Z \approx \sqrt[2]{(R_{TJ} +R_{media})^2 + \dfrac{1}{\omega*C_{e}}^2} \approx \dfrac{1}{\omega*C_{e}}
    :label: eq.14

In summary

.. math:: if \quad \color{blue}{\omega \gg 1, \quad Z \approx R_{media}} \color{black} \quad and \quad at \quad \color{red}{\omega \ll 1, \quad Z \approx \dfrac{1}{\omega*C_{e}}}

This allows us to perform something called impedence spectroscopy. At low freq we can determine the electrode capacitance and at high freq we can determine the resistance in the media. Subbinng those terms in and doing
a regression to the full solution allows us to determine the cell capacitance and tight junctional resistance. Notice too in this method that nothing was time depended and thus no integrals to perform over hard to determine variables.
Below is a sample spectra of impedences from the full solution.

.. image:: C:\Users/mike/Documents/GitHub/Felxi-TEER/images/teer_theory/spectrum.png
    :width: 800





