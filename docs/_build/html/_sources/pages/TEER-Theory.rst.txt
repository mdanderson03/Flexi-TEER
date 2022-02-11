TEER Theory
===========
![](https://github.com/mdanderson03/Felxi-TEER/blob/11124297eae28fc72f78af3b5448df1af65e0caa/passive%20diffusion.png)

The typical use of TEER is with transwells. In these, monolayers of cells are formed and ions can passively diffuse through the gaps between cells. 

![](https://github.com/mdanderson03/Felxi-TEER/blob/11124297eae28fc72f78af3b5448df1af65e0caa/passive%20diffusion2.png)

Lets start forming a model on this. So if a gap has a tight junction formed, it blocks the ion from going through it. If it lacks a tight junction, then the ion can go on through. Lets translate that into a simple electrical circuit model.

![](https://github.com/mdanderson03/Felxi-TEER/blob/11124297eae28fc72f78af3b5448df1af65e0caa/passive%20diffusion3.png)

So we replace tight junctions with open circuits and given gaps restrict the rate that charged particles can pass through the monolayer, lets say they are  resistors. So **tight junctions = open circuit** and **gaps = resistors**

**Ohm's Law**

$$V = I*R$$ (1)
**Parallel Resistance Equivalency**

$$R_{eq} = \dfrac{1}{(\sum{\dfrac{1}{R_g}})}$$(2) 
$$R_{1} \approx R_{2} \approx R_{3} \approx ... \approx R_{G}$$(3)
Sub [3] into [2]
$$R_{eq} = \dfrac{1}{(\dfrac{1}{R_G}*N_{G})}=\dfrac{R_{G}}{N_{G}}$$(4)
$$N_{CJ}=N_{TJ}+N_{G} \to N_{G} = N_{CJ}-N_{TJ}$$(5)
Sub (3) into (4) and taylor expand 
$$R_{eq}=\dfrac{R_{G}}{N_{CJ}*(1-\dfrac{ N_{TJ}} {N_{CJ}})} \to \dfrac{R_{eq}*N_{CJ}}{R_{G}}
= \dfrac{1}{(1-\dfrac{N_{TJ}}{N_{CJ}})} \approx 1+ \dfrac{N_{TJ}}{N_{CJ}}$$(6)
Thus
$$R_{eq} \propto N_{TJ}$$(7)


