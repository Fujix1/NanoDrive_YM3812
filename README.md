# OPL2 (YM3812) VGM player

![](https://github.com/Fujix1/NanoDrive_YM3812/workflows/Build/badge.svg)

"Super Nano Stick for YM3812" is a VGM file player works with Longan Nano.

Except for a few parts, all parts are surface mounted to achive small package.

![FZ9QBWraMAY38FR](https://user-images.githubusercontent.com/13434151/184470049-42638414-974e-4dac-9a68-539ba6437c44.jpg)


## Schematics and PCB
![LonganVGM](https://user-images.githubusercontent.com/13434151/184470098-795a471a-8cc7-4e27-9ea4-83d55a54b999.svg)

![51af5ac5dcfd99b2a9d7a3e70d13c27c](https://user-images.githubusercontent.com/13434151/184470134-ca14cdb7-b4aa-41f7-9f35-dafc2144a557.png)

## Parts
- YM3812-F: SOP version of the OPL2 FM sound generator.
- YM3014B-F: SOP version of DAC IC.
- NJM3414A: Operation AMP for the DAC IC.
- PT2557: I2C volume controller, used to eliminate SD card access noise and fadeout.
- AE-Si5351A: I2C 3ch programmable frequency generator module. https://akizukidenshi.com/catalog/g/gK-10679/
- Longan Nano GD32VF103CBT6: Risc-V micro conmupter module.