# 4006_Robot
17.03.23
       Robot Setup

1)First Mobile app unzip and open Android Studio after run
2)Pico code loading .ino or py code
3)If you are not going to use the board, follow the schematic path!

ESP SETUP
1) first esp board load code after change webview link 

Commands: 
      F : Robot Forward
      R : Robot Right
      L : Robot Left
      B : Robot Back
      S : Robot Stop
      D : Box Open
      d : Box Close
      U : Leg Up
      u : Leg Down
   Warn : If the box is used, the robot motors stop, only the Servos are Activated
   
Errors & Buzzer: 
Gyro Not Found Buzzer 5 repeat
OLED Not Found Buzzer 3 Repeat
Buzzer 1 = System No Problem Starting
if there is 1 buzzer sound after the system starts
Buzzer Repeat 1 = Control Active
Buzzer Repeat 2 = Control Deactive
