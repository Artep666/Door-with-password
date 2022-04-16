#include <LiquidCrystal.h>   
#include <Keypad.h>
#include <Servo.h>

//the password is 1234
int servostate;
int posOpen = 90;
int posClose = 0;
int a=0, b=0, c=0, d=0;
int var=0; 
int C1=1,C2=2,C3=3,C4=4;
char f='*'; 
/*---preparing keypad---*/
const byte rows = 4; 
const byte cols = 4;
char key[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte pinRows[rows] = {0, 6, 5, 4}; 
byte pinCols[cols] = {3, 2, 1};

Servo myservo;//our door lock
Keypad keypad = Keypad( makeKeymap(key), pinRows, pinCols, rows, cols );
LiquidCrystal lcd(8,9,10,11,12,13);

void setup(){
  lcd.begin(16,2); 
  pinMode(A0,OUTPUT); //green led,open
  pinMode(A1,OUTPUT); //red led,closed
  myservo.attach(7); 
  myservo.write(posOpen);
  servostate = 1;
}
  
void loop(){  
  char key = keypad.getKey();
  if (key){
   lcd.setCursor(6+var,1);
   lcd.print(key),lcd.setCursor(6+var,1),lcd.print(f);
   key=key-48;
   var++; 
   switch(var){
    case 1:
    a=key; 
    break;
    case 2:
    b=key; 
    break;
    case 3:
    c=key; 
    break;
    case 4:
    d=key; 
   delay(10);
     //when password is right
  if(a==C1 && b==C2 && c==C3 && d==C4){
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Access");
    lcd.setCursor(5,1);lcd.print("granted!");
    delay(2000);
      myservo.write(posClose);
     
      servostate = 0;
    delay(2000);
    
   
    digitalWrite(A0,HIGH);//right-green led
    delay(2000); 
    lcd.clear();
    digitalWrite(A0,LOW);
    delay(2000);
    }
     //when password is wrong
  else{
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Password");
    lcd.setCursor(4,1);
    lcd.print("Invalid!");
    delay(2000);
    digitalWrite(A1,HIGH); //wrong-red led
    delay(2000); 
    lcd.clear();
    digitalWrite(A1,LOW); 
    }

   var=0;
   lcd.clear();

  break;
     delay(1000);
  }

 }
 if(!key){lcd.setCursor(0,0),lcd.print("Enter Password:");}

  delay(20);
}