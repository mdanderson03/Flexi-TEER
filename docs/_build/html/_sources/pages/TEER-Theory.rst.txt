TEER Theory
===========

.. image:: C:\Users/mike/Documents/GitHub/Felxi-TEER/images/teer_theory/passive_diffusion.png
  :width: 800

The typical use of TEER is with transwells. In these, monolayers of cells are formed and ions can passively diffuse through the gaps between cells. 

.. image:: C:\Users/mike/Documents/GitHub/Felxi-TEER/images/teer_theory/passive_diffusion2.png
  :width: 800

Lets start forming a model on this. So if a gap has a tight junction formed, it blocks the ion from going through it. If it lacks a tight junction, then the ion can go on through. Lets translate that into a simple electrical circuit model.

.. image:: C:\Users/mike/Documents/GitHub/Felxi-TEER/images/teer_theory/passive_diffusion3.png
  :width: 800


So we replace tight junctions and cells with open circuits and given gaps restrict the rate that charged particles can pass through the monolayer, lets say they are  resistors. So **tight junctions and cells = open circuit** and **gaps = resistors**


**Ohm's Law**

.. math:: V = I*R 
    :label: ohm
**Parallel Resistance Equivalency**

.. math:: R_{eq} = \dfrac{1}{(\sum{\dfrac{1}{R_g}})}
    :label: par_res

All gap resistances are approximately equal

.. math:: R_{1} \approx R_{2} \approx R_{3} \approx ... \approx R_{G}
    :label: 3

Sub [3] into [2]

.. math:: R_{eq} = \dfrac{1}{(\dfrac{1}{R_G}*N_{G})}=\dfrac{R_{G}}{N_{G}}
    :label: 4

.. math:: N_{CJ}=N_{TJ}+N_{G} \to N_{G} = N_{CJ}-N_{TJ}
    :label: 5

Sub (3) into (4) and taylor expand 

.. math:: R_{eq}=\dfrac{R_{G}}{N_{CJ}*(1-\dfrac{ N_{TJ}} {N_{CJ}})} \to \dfrac{R_{eq}*N_{CJ}}{R_{G}} = \dfrac{1}{(1-\dfrac{N_{TJ}}{N_{CJ}})} \approx 1+ \dfrac{N_{TJ}}{N_{CJ}}
    :label: 6

Thus

.. math:: R_{eq} \propto N_{TJ}
    :label: 7


In the previous model we considered cell bodies themselves as open circuits, but is that accurate? Check out the image below to see that they are more accurately capacitors!


.. image:: C:\Users/mike/Documents/GitHub/Felxi-TEER/images/teer_theory/membrane_cap.png
  :width: 800

Now lets add the cell capacitance and resistance due to the media into the model circuit


.. image:: C:\Users/mike/Documents/GitHub/Felxi-TEER/images/teer_theory/cap_res_equiv.png
  :width: 800

We need Kirchoff Loop and Node Equations to solve this one:

.. math:: \color{blue}{V_{in}-R_{media}*I -R_{TJ}*I_{TJ}=0}
    :label: kirch1

.. math:: \color{red}{V_{in}-R_{media}*I-V_{cells}=V_{in}-R_{media}*I-\dfrac{Q}{C_{cells}}=0}
    :label: kirch2

.. math:: \color{yellow}{I=I_{TJ}+I_{cells}}
    :label: kirch3

The node and loops look like this (color coordinated)

.. image:: C:\Users/mike/Documents/GitHub/Felxi-TEER/images/teer_theory/kirchoff.png
  :width: 800

Set (8) equal to (9)

.. math:: \dfrac{Q}{C_{cells}}=R_{TJ}*I_{TJ}\to \color{red}{I_{TJ}=\dfrac{Q}{R_{TJ}*C_{cells}}}
    :label: eq.11

 