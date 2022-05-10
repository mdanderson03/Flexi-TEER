#Flexi-TEER

![](images/logo.png)


Welcome to the Flexi-TEER project. This project is about an adaptable, powerful open-source transepitheal electrical resistance device. 

At this moment, we are looking for new people to contribute to this open source project. Please check the modules that need development page to see what areas you can contribute in. 


* [Assembly Instructions](assembly_instructions.md)
* [General Use.](General_use.md)
* [Tutorials](Tutorials.md)
* [Theory](theory.md)
* [Needed Modules](needed_modules.md)
* [Contribution Guide]()contribution_guide.md)


 The following link is for the [bill of materials]{BOM} page.

## What is TEER

**T**rans**E**pithelial **E**lectrical **R**esistance (TEER) is an electrophysiology technique where resistance across a cell layer is measured as a proxy for ion flow which is related to inter-cellular tight junction formation. 

## Why Do We Need an Open-Source TEER Device?
Currently, the primary commercial product is the [EVOM meter](https://www.wpiinc.com/evom3-epithelial-volt-ohm-teer-meter-3) from World Instrumentation. This device is not cheap, but also not super expensive. The real downside is that it lacks flexibility and connectivity. Examples of these are wireless communication with device via a python based API and reading sequentially through multiple electrodes. 

On the open-source side, no good solution currently exists. Current attempts are listed below:

* [EVOM Add on](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC8000980/)
* [Low Cost TEER](https://chemrxiv.org/engage/chemrxiv/article-details/60c746bdbb8c1aa1073da918)
* [Simple Meter](https://www.jove.com/v/60087/a-simple-approach-to-perform-teer-measurements-using-self-made-volt)

Going through these options depend on the proprietary EVOM meter as a base, are dangerous and inaccurate or are clunky via the use of signal generators and multimeters. None of these are sufficient platforms to build off of. 

## Project Goals

#### Device Goals
1. Robust TEER measurement operation (Fixed Frequency and Frequency Sweep)
* WiFi interface with a Python API

#### Accessory Goals
1. 3D printed cell to hold transwell inserts and keep electrodes in position
* 3D printed platform to hold series of above cells. 


