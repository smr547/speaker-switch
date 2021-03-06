EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Voice controlled speaker selection switch"
Date "2021-06-01"
Rev "1.0"
Comp "Ring Instruments "
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Steven Ring"
$EndDescr
$Comp
L Transistor_Array:ULN2003 U?
U 1 1 60B5925B
P 5350 1250
F 0 "U?" H 5350 1917 50  0000 C CNN
F 1 "ULN2003" H 5350 1826 50  0000 C CNN
F 2 "" H 5400 700 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2003a.pdf" H 5450 1050 50  0001 C CNN
	1    5350 1250
	1    0    0    -1  
$EndComp
$Comp
L MCU_Module:Arduino_UNO_R3 A?
U 1 1 60B5EBBD
P 9400 1850
F 0 "A?" H 9400 1950 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 9950 2900 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 9550 800 50  0001 L CNN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 9200 2900 50  0001 C CNN
	1    9400 1850
	1    0    0    -1  
$EndComp
Text GLabel 8900 1450 0    50   Input ~ 0
D2
Text GLabel 4950 1050 0    50   Input ~ 0
D2
Text GLabel 8900 1550 0    50   Input ~ 0
D3
Text GLabel 4950 1150 0    50   Input ~ 0
D3
Text GLabel 8900 1650 0    50   Input ~ 0
D4
Text GLabel 4950 1250 0    50   Input ~ 0
D4
Text GLabel 8900 1750 0    50   Input ~ 0
D5
Text GLabel 4950 1350 0    50   Input ~ 0
D5
Text GLabel 8900 1850 0    50   Input ~ 0
D6
Text GLabel 4950 1450 0    50   Input ~ 0
D6
Text GLabel 8900 1950 0    50   Input ~ 0
D7
Text GLabel 4950 1550 0    50   Input ~ 0
D7
Text GLabel 8900 2050 0    50   Input ~ 0
D8
Text GLabel 4950 1650 0    50   Input ~ 0
D8
$Comp
L Relay:G6SU-2 K?
U 1 1 60B66A47
P 3700 4150
F 0 "K?" V 2933 4150 50  0000 C CNN
F 1 "G6SU-2" V 3024 4150 50  0000 C CNN
F 2 "" H 4350 4100 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g6s.pdf" H 3500 4150 50  0001 C CNN
	1    3700 4150
	0    1    1    0   
$EndComp
$Comp
L Relay:G6SU-2 K?
U 1 1 60B740BD
P 3700 5700
F 0 "K?" V 2933 5700 50  0000 C CNN
F 1 "G6SU-2" V 3024 5700 50  0000 C CNN
F 2 "" H 4350 5650 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g6s.pdf" H 3500 5700 50  0001 C CNN
	1    3700 5700
	0    1    1    0   
$EndComp
Text GLabel 3400 5300 0    50   Input ~ 0
patio
Text GLabel 5750 1150 2    50   Input ~ 0
dining
Text GLabel 5750 1250 2    50   Input ~ 0
kitchen
Text GLabel 5750 1350 2    50   Input ~ 0
lounge
Text GLabel 4000 3750 2    50   Input ~ 0
12V
Text GLabel 4000 5300 2    50   Input ~ 0
12V
Text GLabel 5750 1050 2    50   Input ~ 0
patio
Text GLabel 3400 3750 0    50   Input ~ 0
patio
$Comp
L Connector:Screw_Terminal_01x02 J?
U 1 1 60B8539C
P 1600 2200
F 0 "J?" H 1518 1875 50  0000 C CNN
F 1 "Left input" H 1518 1966 50  0000 C CNN
F 2 "" H 1600 2200 50  0001 C CNN
F 3 "~" H 1600 2200 50  0001 C CNN
	1    1600 2200
	-1   0    0    1   
$EndComp
Text GLabel 1800 2100 2    50   Input ~ 0
Left_pos
Text GLabel 1800 2200 2    50   Input ~ 0
Left_neg
$Comp
L Connector:Screw_Terminal_01x02 J?
U 1 1 60B89959
P 1600 2750
F 0 "J?" H 1518 2425 50  0000 C CNN
F 1 "Right input" H 1518 2516 50  0000 C CNN
F 2 "" H 1600 2750 50  0001 C CNN
F 3 "~" H 1600 2750 50  0001 C CNN
	1    1600 2750
	-1   0    0    1   
$EndComp
Text GLabel 1800 2650 2    50   Input ~ 0
Right_pos
Text GLabel 1800 2750 2    50   Input ~ 0
Right_neg
NoConn ~ 4000 4050
NoConn ~ 4000 4450
NoConn ~ 4000 5600
NoConn ~ 4000 6000
NoConn ~ 2050 2650
Text GLabel 3400 5700 0    50   Input ~ 0
Right_pos
Text GLabel 3400 6100 0    50   Input ~ 0
Right_neg
Text GLabel 4000 5800 2    50   Input ~ 0
patio_spk_R_pos
Text GLabel 4000 6200 2    50   Input ~ 0
patio_spk_R_neg
Text GLabel 3400 4150 0    50   Input ~ 0
Left_pos
Text GLabel 3400 4550 0    50   Input ~ 0
Left_neg
Text GLabel 4000 4250 2    50   Input ~ 0
patio_spk_L_pos
Text GLabel 4000 4650 2    50   Input ~ 0
patio_spk_L_neg
$Comp
L Connector:Screw_Terminal_01x16 J?
U 1 1 60B9118D
P 1550 5050
F 0 "J?" H 1468 4025 50  0000 C CNN
F 1 "Screw_Terminal_01x16" H 1468 4116 50  0000 C CNN
F 2 "" H 1550 5050 50  0001 C CNN
F 3 "~" H 1550 5050 50  0001 C CNN
	1    1550 5050
	-1   0    0    1   
$EndComp
Text GLabel 1750 5750 2    50   Input ~ 0
patio_spk_R_neg
Text GLabel 1750 5650 2    50   Input ~ 0
patio_spk_R_pos
Text GLabel 1750 5550 2    50   Input ~ 0
patio_spk_L_neg
Text GLabel 1750 5450 2    50   Input ~ 0
patio_spk_L_pos
$Comp
L Relay:G6SU-2 K?
U 1 1 60BB8412
P 5600 4150
F 0 "K?" V 4833 4150 50  0000 C CNN
F 1 "G6SU-2" V 4924 4150 50  0000 C CNN
F 2 "" H 6250 4100 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g6s.pdf" H 5400 4150 50  0001 C CNN
	1    5600 4150
	0    1    1    0   
$EndComp
$Comp
L Relay:G6SU-2 K?
U 1 1 60BB841C
P 5600 5700
F 0 "K?" V 4833 5700 50  0000 C CNN
F 1 "G6SU-2" V 4924 5700 50  0000 C CNN
F 2 "" H 6250 5650 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g6s.pdf" H 5400 5700 50  0001 C CNN
	1    5600 5700
	0    1    1    0   
$EndComp
Text GLabel 5300 5300 0    50   Input ~ 0
dining
Text GLabel 5900 3750 2    50   Input ~ 0
12V
Text GLabel 5900 5300 2    50   Input ~ 0
12V
Text GLabel 5300 3750 0    50   Input ~ 0
dining
NoConn ~ 5900 4050
NoConn ~ 5900 4450
NoConn ~ 5900 5600
NoConn ~ 5900 6000
Text GLabel 5300 5700 0    50   Input ~ 0
Right_pos
Text GLabel 5300 6100 0    50   Input ~ 0
Right_neg
Text GLabel 5900 5800 2    50   Input ~ 0
dining_spk_R_pos
Text GLabel 5900 6200 2    50   Input ~ 0
dining_spk_R_neg
Text GLabel 5300 4150 0    50   Input ~ 0
Left_pos
Text GLabel 5300 4550 0    50   Input ~ 0
Left_neg
Text GLabel 5900 4250 2    50   Input ~ 0
dining_spk_L_pos
Text GLabel 5900 4650 2    50   Input ~ 0
dining_spk_L_neg
Text GLabel 1750 5350 2    50   Input ~ 0
dining_spk_R_neg
Text GLabel 1750 5250 2    50   Input ~ 0
dining_spk_R_pos
Text GLabel 1750 5150 2    50   Input ~ 0
dining_spk_L_neg
Text GLabel 1750 5050 2    50   Input ~ 0
dining_spk_L_pos
$Comp
L Relay:G6SU-2 K?
U 1 1 60BBDCCE
P 7450 4150
F 0 "K?" V 6683 4150 50  0000 C CNN
F 1 "G6SU-2" V 6774 4150 50  0000 C CNN
F 2 "" H 8100 4100 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g6s.pdf" H 7250 4150 50  0001 C CNN
	1    7450 4150
	0    1    1    0   
$EndComp
$Comp
L Relay:G6SU-2 K?
U 1 1 60BBDCD8
P 7450 5700
F 0 "K?" V 6683 5700 50  0000 C CNN
F 1 "G6SU-2" V 6774 5700 50  0000 C CNN
F 2 "" H 8100 5650 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g6s.pdf" H 7250 5700 50  0001 C CNN
	1    7450 5700
	0    1    1    0   
$EndComp
Text GLabel 7150 5300 0    50   Input ~ 0
kitchen
Text GLabel 7750 3750 2    50   Input ~ 0
12V
Text GLabel 7750 5300 2    50   Input ~ 0
12V
Text GLabel 7150 3750 0    50   Input ~ 0
kitchen
NoConn ~ 7750 4050
NoConn ~ 7750 4450
NoConn ~ 7750 5600
NoConn ~ 7750 6000
Text GLabel 7150 5700 0    50   Input ~ 0
Right_pos
Text GLabel 7150 6100 0    50   Input ~ 0
Right_neg
Text GLabel 7750 5800 2    50   Input ~ 0
kitchen_spk_R_pos
Text GLabel 7750 6200 2    50   Input ~ 0
kitchen_spk_R_neg
Text GLabel 7150 4150 0    50   Input ~ 0
Left_pos
Text GLabel 7150 4550 0    50   Input ~ 0
Left_neg
Text GLabel 7750 4250 2    50   Input ~ 0
kitchen_spk_L_pos
Text GLabel 7750 4650 2    50   Input ~ 0
kitchen_spk_L_neg
Text GLabel 1750 4950 2    50   Input ~ 0
kitchen_spk_R_neg
Text GLabel 1750 4850 2    50   Input ~ 0
kitchen_spk_R_pos
Text GLabel 1750 4750 2    50   Input ~ 0
kitchen_spk_L_neg
Text GLabel 1750 4650 2    50   Input ~ 0
kitchen_spk_L_pos
$Comp
L Relay:G6SU-2 K?
U 1 1 60BEA46E
P 9600 4150
F 0 "K?" V 8833 4150 50  0000 C CNN
F 1 "G6SU-2" V 8924 4150 50  0000 C CNN
F 2 "" H 10250 4100 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g6s.pdf" H 9400 4150 50  0001 C CNN
	1    9600 4150
	0    1    1    0   
$EndComp
$Comp
L Relay:G6SU-2 K?
U 1 1 60BEA478
P 9600 5700
F 0 "K?" V 8833 5700 50  0000 C CNN
F 1 "G6SU-2" V 8924 5700 50  0000 C CNN
F 2 "" H 10250 5650 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g6s.pdf" H 9400 5700 50  0001 C CNN
	1    9600 5700
	0    1    1    0   
$EndComp
Text GLabel 9300 5300 0    50   Input ~ 0
lounge
Text GLabel 9900 3750 2    50   Input ~ 0
12V
Text GLabel 9900 5300 2    50   Input ~ 0
12V
Text GLabel 9300 3750 0    50   Input ~ 0
lounge
NoConn ~ 9900 4050
NoConn ~ 9900 4450
NoConn ~ 9900 5600
NoConn ~ 9900 6000
Text GLabel 9300 5700 0    50   Input ~ 0
Right_pos
Text GLabel 9300 6100 0    50   Input ~ 0
Right_neg
Text GLabel 9900 5800 2    50   Input ~ 0
lounge_spk_R_pos
Text GLabel 9900 6200 2    50   Input ~ 0
lounge_spk_R_neg
Text GLabel 9300 4150 0    50   Input ~ 0
Left_pos
Text GLabel 9300 4550 0    50   Input ~ 0
Left_neg
Text GLabel 9900 4250 2    50   Input ~ 0
lounge_spk_L_pos
Text GLabel 9900 4650 2    50   Input ~ 0
lounge_spk_L_neg
Text GLabel 1750 4550 2    50   Input ~ 0
lounge_spk_R_neg
Text GLabel 1750 4450 2    50   Input ~ 0
lounge_spk_R_pos
Text GLabel 1750 4350 2    50   Input ~ 0
lounge_spk_L_neg
Text GLabel 1750 4250 2    50   Input ~ 0
lounge_spk_L_pos
Wire Notes Line
	1300 1700 2450 1700
Wire Notes Line
	2450 1700 2450 3300
Wire Notes Line
	2450 3300 1300 3300
Wire Notes Line
	1300 3300 1300 1700
Text Notes 1450 3200 0    50   ~ 10
From SONOS
$Comp
L Regulator_Switching:R-78C9.0-1.0 U?
U 1 1 60BF2D15
P 5800 2500
F 0 "U?" H 5800 2742 50  0000 C CNN
F 1 "R-78C9.0-1.0" H 5800 2651 50  0000 C CNN
F 2 "Converter_DCDC:Converter_DCDC_RECOM_R-78E-0.5_THT" H 5850 2250 50  0001 L CIN
F 3 "https://www.recom-power.com/pdf/Innoline/R-78Cxx-1.0.pdf" H 5800 2500 50  0001 C CNN
	1    5800 2500
	1    0    0    -1  
$EndComp
$Comp
L Converter_ACDC:IRM-10-12 PS?
U 1 1 60C01527
P 1950 1050
F 0 "PS?" H 1950 1417 50  0000 C CNN
F 1 "IRM-10-12" H 1950 1326 50  0000 C CNN
F 2 "Converter_ACDC:Converter_ACDC_MeanWell_IRM-10-xx_THT" H 1950 700 50  0001 C CNN
F 3 "https://www.meanwell.com/Upload/PDF/IRM-10/IRM-10-SPEC.PDF" H 1950 650 50  0001 C CNN
	1    1950 1050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J?
U 1 1 60C0F7B3
P 1350 1050
F 0 "J?" H 1268 725 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 1268 816 50  0000 C CNN
F 2 "" H 1350 1050 50  0001 C CNN
F 3 "~" H 1350 1050 50  0001 C CNN
	1    1350 1050
	-1   0    0    1   
$EndComp
Wire Wire Line
	1550 1050 1550 1150
$Comp
L power:GND #PWR?
U 1 1 60C16E79
P 2350 1150
F 0 "#PWR?" H 2350 900 50  0001 C CNN
F 1 "GND" H 2355 977 50  0000 C CNN
F 2 "" H 2350 1150 50  0001 C CNN
F 3 "" H 2350 1150 50  0001 C CNN
	1    2350 1150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60C1DEA5
P 5800 2800
F 0 "#PWR?" H 5800 2550 50  0001 C CNN
F 1 "GND" H 5805 2627 50  0000 C CNN
F 2 "" H 5800 2800 50  0001 C CNN
F 3 "" H 5800 2800 50  0001 C CNN
	1    5800 2800
	1    0    0    -1  
$EndComp
Text GLabel 6400 2500 2    50   Input ~ 10
9V
Text GLabel 9300 850  1    50   Input ~ 10
9V
$Comp
L power:GND #PWR?
U 1 1 60C1EFF3
P 9750 2950
F 0 "#PWR?" H 9750 2700 50  0001 C CNN
F 1 "GND" H 9755 2777 50  0000 C CNN
F 2 "" H 9750 2950 50  0001 C CNN
F 3 "" H 9750 2950 50  0001 C CNN
	1    9750 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 2950 9400 2950
Wire Wire Line
	9500 2950 9750 2950
Wire Wire Line
	9400 2950 9500 2950
Connection ~ 9400 2950
Connection ~ 9500 2950
Text GLabel 5750 850  2    50   Input ~ 10
9V
$Comp
L power:GND #PWR?
U 1 1 60C216A0
P 5350 1850
F 0 "#PWR?" H 5350 1600 50  0001 C CNN
F 1 "GND" H 5355 1677 50  0000 C CNN
F 2 "" H 5350 1850 50  0001 C CNN
F 3 "" H 5350 1850 50  0001 C CNN
	1    5350 1850
	1    0    0    -1  
$EndComp
NoConn ~ 5750 1450
NoConn ~ 5750 1550
NoConn ~ 5750 1650
NoConn ~ 5650 2850
Wire Wire Line
	6400 2500 6100 2500
Text GLabel 2350 950  2    50   Input ~ 0
12V
Text GLabel 4550 2500 0    50   Input ~ 0
12V
Wire Wire Line
	5100 2500 5300 2500
$Comp
L Device:L_Small L?
U 1 1 60C299EC
P 5000 2500
F 0 "L?" V 4819 2500 50  0000 C CNN
F 1 "10 uH" V 4910 2500 50  0000 C CNN
F 2 "" H 5000 2500 50  0001 C CNN
F 3 "~" H 5000 2500 50  0001 C CNN
	1    5000 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	4550 2500 4750 2500
$Comp
L Device:CP C?
U 1 1 60C30435
P 4750 2650
F 0 "C?" H 4868 2696 50  0000 L CNN
F 1 "10 uF" H 4868 2605 50  0000 L CNN
F 2 "" H 4788 2500 50  0001 C CNN
F 3 "~" H 4750 2650 50  0001 C CNN
	1    4750 2650
	1    0    0    -1  
$EndComp
Connection ~ 4750 2500
Wire Wire Line
	4750 2500 4900 2500
$Comp
L power:GND #PWR?
U 1 1 60C31E35
P 4750 2800
F 0 "#PWR?" H 4750 2550 50  0001 C CNN
F 1 "GND" H 4755 2627 50  0000 C CNN
F 2 "" H 4750 2800 50  0001 C CNN
F 3 "" H 4750 2800 50  0001 C CNN
	1    4750 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C?
U 1 1 60C3281A
P 5300 2650
F 0 "C?" H 5418 2696 50  0000 L CNN
F 1 "10 uF" H 5418 2605 50  0000 L CNN
F 2 "" H 5338 2500 50  0001 C CNN
F 3 "~" H 5300 2650 50  0001 C CNN
	1    5300 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60C32824
P 5300 2800
F 0 "#PWR?" H 5300 2550 50  0001 C CNN
F 1 "GND" H 5305 2627 50  0000 C CNN
F 2 "" H 5300 2800 50  0001 C CNN
F 3 "" H 5300 2800 50  0001 C CNN
	1    5300 2800
	1    0    0    -1  
$EndComp
Connection ~ 5300 2500
Wire Wire Line
	5300 2500 5500 2500
$Comp
L Connector:RJ45 J?
U 1 1 60C341F2
P 4200 1400
F 0 "J?" H 4257 2067 50  0000 C CNN
F 1 "RJ45" H 4257 1976 50  0000 C CNN
F 2 "" V 4200 1425 50  0001 C CNN
F 3 "~" V 4200 1425 50  0001 C CNN
	1    4200 1400
	1    0    0    -1  
$EndComp
Text Notes 6550 850  0    50   ~ 10
Arduino Ethernet Shield\n+ Prototype area
$Comp
L Connector:Screw_Terminal_01x02 J?
U 1 1 60C386AC
P 8450 900
F 0 "J?" H 8368 575 50  0000 C CNN
F 1 "ST" H 8368 666 50  0000 C CNN
F 2 "" H 8450 900 50  0001 C CNN
F 3 "~" H 8450 900 50  0001 C CNN
	1    8450 900 
	-1   0    0    1   
$EndComp
Text GLabel 8650 800  2    50   Input ~ 10
9V
$Comp
L power:GND #PWR?
U 1 1 60C3CCD9
P 8650 900
F 0 "#PWR?" H 8650 650 50  0001 C CNN
F 1 "GND" H 8655 727 50  0000 C CNN
F 2 "" H 8650 900 50  0001 C CNN
F 3 "" H 8650 900 50  0001 C CNN
	1    8650 900 
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J?
U 1 1 60C41C1D
P 3000 950
F 0 "J?" H 3080 942 50  0000 L CNN
F 1 "ST" H 3080 851 50  0000 L CNN
F 2 "" H 3000 950 50  0001 C CNN
F 3 "~" H 3000 950 50  0001 C CNN
	1    3000 950 
	1    0    0    -1  
$EndComp
Text GLabel 2800 950  0    50   Input ~ 0
12V
$Comp
L power:GND #PWR?
U 1 1 60C4E37C
P 2800 1100
F 0 "#PWR?" H 2800 850 50  0001 C CNN
F 1 "GND" H 2805 927 50  0000 C CNN
F 2 "" H 2800 1100 50  0001 C CNN
F 3 "" H 2800 1100 50  0001 C CNN
	1    2800 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 1050 2800 1100
$Comp
L Connector:Screw_Terminal_01x02 J?
U 1 1 60C507C3
P 3850 2600
F 0 "J?" H 3768 2275 50  0000 C CNN
F 1 "ST" H 3768 2366 50  0000 C CNN
F 2 "" H 3850 2600 50  0001 C CNN
F 3 "~" H 3850 2600 50  0001 C CNN
	1    3850 2600
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60C514CB
P 4050 2650
F 0 "#PWR?" H 4050 2400 50  0001 C CNN
F 1 "GND" H 4055 2477 50  0000 C CNN
F 2 "" H 4050 2650 50  0001 C CNN
F 3 "" H 4050 2650 50  0001 C CNN
	1    4050 2650
	1    0    0    -1  
$EndComp
Text GLabel 4050 2500 2    50   Input ~ 0
12V
$Comp
L Connector:Screw_Terminal_01x02 J?
U 1 1 60C52174
P 7000 2500
F 0 "J?" H 7080 2492 50  0000 L CNN
F 1 "ST" H 7080 2401 50  0000 L CNN
F 2 "" H 7000 2500 50  0001 C CNN
F 3 "~" H 7000 2500 50  0001 C CNN
	1    7000 2500
	1    0    0    -1  
$EndComp
Text GLabel 6800 2500 0    50   Input ~ 10
9V
$Comp
L power:GND #PWR?
U 1 1 60C5356E
P 6800 2600
F 0 "#PWR?" H 6800 2350 50  0001 C CNN
F 1 "GND" H 6805 2427 50  0000 C CNN
F 2 "" H 6800 2600 50  0001 C CNN
F 3 "" H 6800 2600 50  0001 C CNN
	1    6800 2600
	1    0    0    -1  
$EndComp
Wire Notes Line
	8200 500  10300 500 
Wire Notes Line
	10300 500  10300 3200
Wire Notes Line
	10300 3200 8200 3200
Wire Notes Line
	8200 3200 8200 500 
Text Notes 8350 3150 0    50   ~ 10
Arduino R3
Wire Notes Line
	3650 550  3650 3100
Wire Notes Line
	3650 3100 7600 3100
Wire Notes Line
	7600 3100 7600 550 
Wire Notes Line
	7600 550  3650 550 
Wire Notes Line
	850  550  3300 550 
Wire Notes Line
	3300 550  3300 3250
Wire Notes Line
	3300 3250 10900 3250
Wire Notes Line
	10900 3250 10900 6400
Wire Notes Line
	10900 6400 850  6400
Wire Notes Line
	850  6400 850  550 
Text Notes 1100 6250 0    50   ~ 10
DIN mounting rail
$EndSCHEMATC
