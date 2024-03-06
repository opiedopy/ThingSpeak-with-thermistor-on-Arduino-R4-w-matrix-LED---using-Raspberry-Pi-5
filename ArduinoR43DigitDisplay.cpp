#include "Arduino.h"
#include "ArduinoR43DigitDisplay.h"

void top(int s, uint8_t frame[8][12]){
  frame[1][1+s] = 1;
  frame[1][2+s] = 1;
  frame[1][3+s] = 1;
}

void ul(int s, uint8_t frame[8][12]){
  frame[1][1+s] = 1;
  frame[2][1+s] = 1;
  frame[3][1+s] = 1;
}

void ur(int s, uint8_t frame[8][12]){
  frame[1][3+s] = 1;
  frame[2][3+s] = 1;
  frame[3][3+s] = 1;
}

void br(int s, uint8_t frame[8][12]){
  frame[4][3+s] = 1;
  frame[5][3+s] = 1;
}

void bl(int s, uint8_t frame[8][12]){
  frame[4][1+s] = 1;
  frame[5][1+s] = 1;
}

void mid(int s, uint8_t frame[8][12]){
  frame[3][1+s] = 1;
  frame[3][2+s] = 1;
  frame[3][3+s] = 1;
}

void bot(int s, uint8_t frame[8][12]) {
  frame[5][1+s] = 1;
  frame[5][2+s] = 1;
  frame[5][3+s] = 1;
}
void dot(int s, uint8_t frame[8][12]) {
  frame[6][s] = 1;
}
void underline(int s, uint8_t frame[8][12]) {
  frame[7][1+s] = 1;
  frame[7][2+s] = 1;
  frame[7][3+s] = 1;
}

void clear(uint8_t frame[8][12]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 12; j++) {
            frame[i][j] = 0;
        }
    }
}

void one(int s, uint8_t frame[8][12]){
  ur(s, frame);
  br(s, frame);
}
void two(int s, uint8_t frame[8][12]){
  top(s, frame);
  ur(s, frame);
  mid(s, frame);
  bl(s, frame);
  bot(s, frame);
}
void three(int s, uint8_t frame[8][12]){
  top(s, frame);
  ur(s, frame);
  mid(s, frame);
  br(s, frame);
  bot(s, frame);
}

void four(int s, uint8_t frame[8][12]){
  ur(s, frame);
  ul(s, frame);
  mid(s, frame);
  br(s, frame);
}

void five(int s, uint8_t frame[8][12]){
  top(s, frame);
  ul(s, frame);
  mid(s, frame);
  br(s, frame);
  bot(s, frame);
}

void six(int s, uint8_t frame[8][12]){
  top(s, frame);
  ul(s, frame);
  mid(s, frame);
  bl(s, frame);
  br(s, frame);
  bot(s, frame);
}

void seven(int s, uint8_t frame[8][12]){
  top(s, frame);
  ur(s, frame);
  br(s, frame);
}

void eight(int s, uint8_t frame[8][12]){
  top(s, frame);
  ur(s, frame);
  ul(s, frame);
  mid(s, frame);
  br(s, frame);
  bl(s, frame);
  bot(s, frame);
}

void nine(int s, uint8_t frame[8][12]){
  top(s, frame);
  ur(s, frame);
  ul(s, frame);
  mid(s, frame);
  br(s, frame);
}

void zero(int s, uint8_t frame[8][12]){
  top(s, frame);
  ur(s, frame);
  ul(s, frame);
  br(s, frame);
  bl(s, frame);
  bot(s, frame);
}

void decimal(int s, uint8_t frame[8][12]){
  dot(s, frame);
}

void empty(int s, uint8_t frame[8][12]){
}

void drawNumber(double num, uint8_t frame[8][12], int decimal_places){

  int digit_0, digit_1, digit_2, digit_3, dot_position;

  if ((num >= 100 && decimal_places > 3) || (decimal_places == 0)) {
      // No decimal point
      digit_0 = int(num / 1000);
      digit_1 = int(num / 100) % 10;
      digit_2 = int(num / 10) % 10;
      digit_3 = int(num) % 10;
      dot_position = 3; // 3 indicates no decimal
  } else if ((num >= 10 && decimal_places > 3) || (decimal_places == 1)) {
      // One decimal place
      digit_0 = int(num / 100);
      digit_1 = int(num / 10) % 10;
      digit_2 = int(num) % 10;
      digit_3 = int(num * 10) % 10;
      dot_position = 2;
  } else if ((num >= 1 && decimal_places > 3) || (decimal_places == 2)) {
      // Two decimal places
      digit_0 = int(num / 10);
      digit_1 = int(num) % 10;
      digit_2 = int(num * 10) % 10;
      digit_3 = int(num * 100) % 10;
      dot_position = 1;
  } else if ((num < 1 && decimal_places > 3) || (decimal_places == 3)) {
      // Three decimal places
      digit_0 = int(num);
      digit_1 = int(num * 10) % 10;
      digit_2 = int(num * 100) % 10;
      digit_3 = int(num * 1000) % 10;
      dot_position = 0; // Decimal at the start
  }

  /*
  Serial.print(" num = ");
  Serial.print(num);
  Serial.print(" decimal_places = ");
  Serial.print(decimal_places);
  Serial.print("   digit = ");
  Serial.print(digit_0);
  Serial.print("-");
  Serial.print(digit_1);
  Serial.print("-");
  Serial.print(digit_2);
  Serial.print("-");
  Serial.print(digit_3);
  Serial.print("   dot_position = ");
  Serial.println(dot_position);
  */
  
  //Clear display
  clear(frame);

  //display overflow as left underline
  if (digit_0 > 0){
    underline(0,frame);
  }
  
  if (digit_1 == 0 ){
     if (digit_1 == 0  && dot_position > 0){
       empty(0, frame);
     } else {
       zero(0, frame);
     } 
  } else if (digit_1 == 1){
    one(0, frame);
  } else if (digit_1 == 2){
    two(0, frame);
  } else if (digit_1 == 3){
    three(0, frame);
  } else if (digit_1 == 4){
    four(0, frame);
  }else if (digit_1 == 5){
    five(0, frame);
  }else if (digit_1 == 6){
    six(0, frame);
  }else if (digit_1 == 7){
    seven(0, frame);
  }else if (digit_1 == 8){
    eight(0, frame);
  }else if (digit_1 == 9){
    nine(0, frame);
  }

  if (digit_2 == 0){
     if (digit_1 == 0 && dot_position > 1){
       empty(4, frame);
     } else {
       zero(4, frame);
     } 
  } else if (digit_2 == 1){
    one(4, frame);
  } else if (digit_2 == 2){
    two(4, frame);
  } else if (digit_2 == 3){
    three(4, frame);
  } else if (digit_2 == 4){
    four(4, frame);
  }else if (digit_2 == 5){
    five(4, frame);
  }else if (digit_2 == 6){
    six(4, frame);
  }else if (digit_2 == 7){
    seven(4, frame);
  }else if (digit_2 == 8){
    eight(4, frame);
  }else if (digit_2 == 9){
    nine(4, frame);
  }

  if (digit_3 == 0){
     if (digit_1 == 0 && digit_2 == 0 && dot_position > 2){
       empty(8, frame);
     } else {
       zero(8, frame);
     } 
    zero(8, frame);
  } else if (digit_3 == 1){
    one(8, frame);
  } else if (digit_3 == 2){
    two(8, frame);
  } else if (digit_3 == 3){
    three(8, frame);
  } else if (digit_3 == 4){
    four(8, frame);
  } else if (digit_3 == 5){
    five(8, frame);
  } else if (digit_3 == 6){
    six(8, frame);
  } else if (digit_3 == 7){
    seven(8, frame);
  } else if (digit_3 == 8){
    eight(8, frame);
  } else if (digit_3 == 9){
    nine(8, frame);
  } 

  if (dot_position < 3){
    decimal(dot_position*4, frame);
  }

}