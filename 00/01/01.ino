#include <Stepper.h>
#include <IRremote.h>
const byte rPin = A0;
IRrecv irr(rPin);
decode_results results;    
const int stepsPerRevolution = 2048;  
// change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 9, 11, 10, 12);
int x,y=0,z;    //判斷樓層 y初始值,x輸入樓層,z幾樓
bool d[10][7]={
{1,0,0,1,1,1,1},
{0,0,1,0,0,1,0},
{0,0,0,0,1,1,0},
{1,0,0,1,1,0,0},
{0,1,0,0,1,0,0},
{0,1,0,0,0,0,0},
{0,0,0,1,1,1,1},
{0,0,0,0,0,0,0},
{0,0,0,0,1,0,0},
{0,1,1,0,0,0,0}};   //共陽極七段顯示器

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  irr.enableIRIn();     //啟用紅外線接收器

  pinMode(2, OUTPUT);   //顯示器腳位
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  // set the speed at 60 rpm:
  myStepper.setSpeed(5);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  if (irr.decode(&results)) {
    Serial.print("收到資料為");
    Serial.println(results.value,HEX);
    Serial.println(results.value);
switch(results.value){
    case 16724175:
      for(int j=0;j<7;j++){  //顯示1
      digitalWrite(j+2,d[0][j]);
      x=0;
    }
      delay(1000);
    break;      
    case 16718055:
        for(int j=0;j<7;j++){  //顯示2
      digitalWrite(j+2,d[1][j]);
      x=1;
    }
      delay(1000);
    break;
    case 16743045:
        for(int j=0;j<7;j++){  //顯示3
      digitalWrite(j+2,d[2][j]);
      x=2;
    }
      delay(1000);
    break;
    case 16716015:
        for(int j=0;j<7;j++){  //顯示4
      digitalWrite(j+2,d[3][j]);
      x=3;
    }
      delay(1000);
    break;
    default:
     for(int j=0;j<7;j++){  //不顯示
      digitalWrite(j+2,d[9][j]);
    }
      delay(1000);
   
}
  irr.resume(); //準備接收下一個訊息
  }
   Serial.println(x);
  z=x-y;
  if(z>0){     //正轉
  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution*z);
  delay(500);
  }
  else if(z<0){
  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(stepsPerRevolution*z);
  delay(500);
  }
  y=x;
}
