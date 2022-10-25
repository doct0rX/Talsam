* Talsam

LED Pins are; [4, 5, 8
               3, 6, 9,
               2, 7, 10]


I2C device found at address 0x27!

used article for implementing the LCD I2C screen: https://create.arduino.cc/projecthub/akshayjoseph666/interface-i2c-16x2-lcd-with-arduino-uno-just-4-wires-273b24 
> the used library: https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library 

=======
Pseudocode:
  i. Start or push the button
     ii. LEDs keep blinking for 3 seconds randomly
    iii. Selects 3 random numbers from the grid box (axis: x, y, diagonal)
     iv. LEDs go out.
      v. Displays the 3 numbers on the screen on the 1st row. (500ms)
            between them the + sign and the total sum after =
            i.e., x + y + z = n
     vi. LEDs lights on again with the right coordination represnting the selected numbers
    vii. Loop:
            1. Start counting from 1 ~ n (n the total sum number)
            2. displaying "يا عليم" on and off (500ms) with each number count (on the bottom row)
            3. n++
            4. if n reaches the sum and waits 1000ms
                5. writes on LCD "تمت" on the bottom row
                6. waits 1000ms
                7. all goes off
                6. break
