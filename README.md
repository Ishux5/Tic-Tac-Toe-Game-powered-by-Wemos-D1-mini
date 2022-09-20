[![CC BY-NC-SA 4.0][cc-by-nc-sa-shield]][cc-by-nc-sa]
# Tic-Tac-Toe-powered-by-D1-mini

![Tic-Tac-Toe making of](https://github.com/Ishux5/Tic-Tac-Toe-powered-by-D1-mini/blob/main/Images/Konstruktion_2022-Sep-20_01-05-23AM-000_CustomizedView2792266026_png.png)]

## Idea

The Idea started when I was working on a birthday present for a friend. It was a 7 Segment Clock powered by an ESP32. The core part was to build something powered by a microcontroller by using a PCB and a Bettery Pack. I then setteled on building a Tic-Tac-Toe because I thought it was relatively simple. The code would be simple, the PCB-layout would be simple and it would be easy to manufacture a couple of them.

## Journey

After setteling on the idea I started working on the form. It shouldn't be to big and I wanted it to have a maximum size of 10 cm x 10 cm. After finishing the first 3D Model in Autodesk Fusion 360 I continued with creating the circuit which I never done before. I screen recorded my work and decided to create a little Video about how I made the PCB, Code and the casing. PCB and Code are older Versions and non functional!
[![Tic-Tac-Toe making of](https://res.cloudinary.com/marcomontalbano/image/upload/v1663260394/video_to_markdown/images/youtube--2Q2LxaJ6QfE-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://youtu.be/2Q2LxaJ6QfE "Tic-Tac-Toe making of")
<br>
The first ordered sample worked but had a huge flaw as I connected the LEDs to the wrong Pins on the micro Controller. Pin 8 and 1 weren't functioning as internal Pullup pins. The second and current version is still flawed because of to small holes for the Power Switch. I have not reordered any PCBs with the right hole sizes.

## Finished Product

After all I am very Happy how it turned out. It is functioning as I wanted it, looks decend and the learning experience on the journey to the finished product was fun too. It has become more elaborate and costly than expected

## Parts

| Item # | Component                                           | Quantity |
| :----- | :-------------------------------------------------- | :------- |
| 1      | [Cherry MX Blue switches, MX1A-E1NA][switchlink]    | 9        |
| 2      | [AZDelivery Battery Shield for D1 Mini][shieldlink] | 1        |
| 3      | AZDelivery D1 Mini NodeMcu ESP8266-12F              | 1        |
| 4      | [LiPo 1200mAh 3,7V Batterie][lipolink]              | 1        |
| 5      | [SK6812 MINI-E RGB][ledlink]                        | 11       |
| 6      | [SALECOM SS 13ASP][powerswtichlink]                 | 1        |
| 7      | [Short-Stroke switch 5mm][shortstrokelink]          | 1        |
| 8      | [Micro USB to DIP breakout Board][usbbreakoutlink]  | 1        |
| 9      | JST – Connecter Female 90°                          | 1        |
| 10     | [JST – Connector wire][jstwirelink]                 | 1        |
| 11     | 10k Ohm Resistor                                    | 1        |
| 12     | 100k Ohm Resistor                                   | 1        |
| 13     | [Micro USB Power Cable 20 cm][usbwirelink]          | 1        |
| 14     | [M4 Threaded Inserts][insertslink]                  | 4        |
| 15     | M4 Cylindrical Screws                               | 4        |
| 16     | [Tic-Tac-Toe PCB][pcblink]                          | 1        |

[switchlink]: https://de.aliexpress.com/item/1005003772714638.html?spm=a2g0o.order_detail.0.0.799c6368iBbwmS&gatewayAdapt=glo2deu
[shieldlink]: https://www.amazon.de/-/en/dp/B07XB75NTD/ref=twister_B07ZRK81LT?_encoding=UTF8&psc=1
[lipolink]: https://www.ebay.de/itm/282581166241
[ledlink]: https://de.aliexpress.com/item/1005002865070175.html?spm=a2g0o.order_list.0.0.21ef5c5fAsRIgP&gatewayAdapt=glo2deu
[powerswitchlink]: https://www.reichelt.de/schiebeschalter-1x-um-stehend-print-rm-4-7-ss-13asp-p112182.html?&nbc=1
[shortstrokelink]: https://www.reichelt.de/kurzhubtaster-6x6mm-hoehe-7-0mm-12v-vertikal-taster-9303-p44583.html?&nbc=1
[usbbreakoutlink]: https://www.amazon.de/gp/product/B07W13X3TD/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1
[jstwirelink]: https://www.reichelt.de/jst-stiftleiste-90-1x2-polig-ph-jst-ph2p-st90-p185056.html?&nbc=1
[usbwirelink]: https://www.reichelt.de/micro-usb-b-stecker-auf-freie-enden-sw-20-cm-usb-b-awg22-20-p292508.html?&nbc=1
[insertslink]: https://www.amazon.de/gp/product/B09CL4M6JB/ref=ppx_yo_dt_b_asin_title_o01_s02?ie=UTF8&psc=1
[pcblink]: https://www.pcbway.com/project/shareproject/Tic_Tac_Toe_5d14ccaf.html

## Assembly

1. Solder LEDs to the PCB (ground marked with while dot)
2. Solder Button 2 (opposite to D1 mini at LED2) to the PCB
3. Install the Software on the D1 mini
4. Solder D1 mini to the PCB
5. Solder the Power Switch, Resistors, JST – Connector and short-stroke switch to the PCB
6. Solder JST – Connector wire to the Battery shield
7. Solder Micro USB cable to the Micro USB breakout board
8. Insert the Button on the PCB through the larger hole in the 3D – Printed top part of the Casing
9. Insert rest of the Buttons in the Holes of the 3D – Printed top part of the Casing
10. Solder Buttons to the PCB
11. Connect the Battey and Micro USB Cable to the Battery Shield
12. Install M4 Threaded Inserts
13. Route Cables in the 3D – Printed bottom part of the Casing
14. Connect the JST – Male header with the JST – Female header on the PCB

## License

This work is licensed under a
[Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License][cc-by-nc-sa].

[![CC BY-NC-SA 4.0][cc-by-nc-sa-image]][cc-by-nc-sa]

[cc-by-nc-sa]: http://creativecommons.org/licenses/by-nc-sa/4.0/
[cc-by-nc-sa-image]: https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png
[cc-by-nc-sa-shield]: https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg
