# OPL2 (YM3812) VGM player

![](https://github.com/Fujix1/NanoDrive_YM3812/workflows/Build/badge.svg)

NanoStick YM3812 はRISC-V マイコン「LonganNano」を使った小型のFM 音源VGM プレーヤーです。microSD カードに保存した.vgm フォーマットファイルを読み込み、逐次データFM 音源チップにを送信して再生します。可変周波数生成器の採用により、幅広い動作周波数に対応します。またI2C 制御のデジタルボリュームを使うことで、チップリセット時、曲切り替え時のノイズ抑制、指定ループ数経過後のフェードアウト機能などを実現しています。OPL1とOPL2用の vgm を再生できます。

[マニュアルはこちら](https://github.com/Fujix1/NanoDrive_YM3812/blob/main/NanoStickYM3812.pdf)

"Nano Stick YM3812" is a VGM file player works with Longan Nano.

Except for a few parts, all parts are surface mounted to achive small package.

![FZ9QBWraMAY38FR](https://user-images.githubusercontent.com/13434151/184470049-42638414-974e-4dac-9a68-539ba6437c44.jpg)

## コンパイル済み firmware / Precompiled firmware

[firmware.zip](https://github.com/user-attachments/files/19357146/firmware.zip)


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
