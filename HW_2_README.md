# HW_2

## 說明

1. （輸入）在麵包板上添加按鈕（如DigitalIn）：向上，向下並選擇。
    - 有三個 button (up, down, comfirm)
    - 用來選擇頻率，選好頻率按下 confirm 後會輸出相應的三角波。

2. （顯示）在uLCD上創建選擇顯示，以從您選擇的幾個頻率中進行選擇，例如100Hz，200Hz等。
    - 選擇要產生的波的頻率
3. （生成波形）使用DAC生成具有所選頻率的波形，並將生成的信號通過RC低通濾波器。
    - 做出一個三角波，在S時達到峰值3V。
    S = (1+0+8+0+6+0+0+1+0) mod 10 = 6。
    - 頻率選擇 (R : 3.9k Ohms 5%, C : 47 nF)
        - fc = 1/2piRC = 868.275Hz (截止頻率)
        - 我做了三個頻率 (500Hz, 868Hz, 1000Hz)
    - 產生頻率
4. （測量）使用Picoscope測量生成的波形。
    - picoscope 是 output ，通過 low filter 後用板子讀取(Analog  I/O)
5. （示例）對生成的波形進行採樣，然後將值發送到PC / Python。
6. （分析）分析捕獲的波形：使用Matplotlib在屏幕上顯示頻率響應和波形。
    - 使用 lab4 的 FFT.py code 改寫，主要改變 sample freq。
