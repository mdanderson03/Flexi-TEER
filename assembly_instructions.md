[10uF SMD Capacitor]:(Parts.yaml#capacitor603)
[35pF SMD Capacitor]:(Parts.yaml#capacitor603)
[0.1uF SMD Capacitor]:(Parts.yaml#capacitor603)
[2k SMD Resistor]:(Parts.yaml#resistor603)
[50 SMD Resistor]:(Parts.yaml#resistor603)
[300 SMD Resistor]:(Parts.yaml#resistor603)
[1k SMD Resistor]:(Parts.yaml#resistor603)}
[SPDT Switch]:(Parts.yaml#MAX4644EUA+T)
[ICL7660 Chargepump]:(Parts.yaml#ICL7660SCPAZ)
[Arduino Nano]:(Parts.yaml#Arduino)
[OP295 OP Amp]:(Parts.yaml#OP295GPZ)
[INA592 Diff Amp]:(Parts.yaml#INA592IDGKR)
[ADS1115 Breakout]:(Parts.yaml#ADS1115)
[REF200 Current Source]:(Parts.yaml#REF200AU2K5)
[ad9833 Function Generator]:(Parts.yaml#AD9833)
[LM358 OP Amp]:(Parts.yaml#LM358)
[Curved Soldering Iron Tip]:(Parts.yaml#Soldering_Iron_Tip)
[Straight Soldering Iron Tip]:(Parts.yaml#Soldering_Iron_Tip)
[16x1 Female Pin Header]:(Parts.yaml#Female_pin_header)
[7x1 Female Pin Header]:(Parts.yaml#Female_pin_header)
[10x1 Female Pin Header]:(parts.yaml#Female_pin_header)

# Assembly Instructions

{{BOM}}

## Step 1: Order PCB

Download the [Gerber File](files/Gerber_PCB_Flexi-TEER.zip) for the PCB. Go to [EasyEDA PCB ordering](https://docs.easyeda.com/en/PCB/Order-PCB/index.html ) website and follow instructions to order PCB from the gerber file. 

## Step 2: Solder Surface Mount Components (SMD)
Solder components onto circuit board in the order below. A strategy that has worked well is to use a soldering iron with fine 0.5mm solder. First place some solder onto each pad for the component, then place component with tweezers and press into place with tweezers and gently touch each lead from the component with the soldering iron until the solder melts around it. 

>i **Note**
>i a [Curved Soldering Iron Tip]{Qty: 1} will help solder SMD components to board.

1. [10uF SMD Capacitor]{Qty: 2}
* [35pF SMD Capacitor]{Qty: 2}
* [0.1uF SMD Capacitor]{Qty: 2}
* [2k SMD Resistor]{Qty: 2}
* [50 SMD Resistor]{Qty: 1}
* [300 SMD Resistor]{Qty: 3}
* [1k SMD Resistor]{Qty: 1}
* [SPDT Switch]{Qty: 6}
* [INA592 Diff Amp]{Qty: 1}
* [REF200 Current Source]{Qty: 1}
* [LM358 OP Amp]{Qty: 1}

## Step 3: Solder Through Hole Components

>i **Note**
>i a [Straight Soldering Iron Tip]{Qty: 1} will help solder through hole components to board.

1. 2x [16x1 Female Pin Header]{Qty: 2}, one for each side of Arduino Nano IOT
2. 1x [7x1 Female Pin Header]{Qty: 1} in ad9833 socket
3. 1x [10x1 Female Pin Header]{Qty: 1} in ADS1115 socket

## Step 4: Solder Male Pin Headers
If ordered any breakout boards (ADS1115, AD9833, Arduino, etc.), solder male pin headers to each board.

## Step 5: Attach Breakout Boards
Attach each breakout board and Arduino into respective sockets.

## Step 6: Flash Arduino Sketch
Currently no sketch is available. 






