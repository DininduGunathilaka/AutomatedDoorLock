#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>
Servo myservo;
int pos=0; // position of servo motor
LiquidCrystal lcd(A4, A5, A3, A2, A1, A0);
const byte rows=4;
const byte cols=3;
 
char key[rows][cols]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[rows]={0,1,2,3};
byte colPins[cols]={4,5,6};
Keypad keypad= Keypad(makeKeymap(key),rowPins,colPins,rows,cols);
char* id1="#001*";
char* id2="#002*";
char* id3="#003*";

char* password1="145278*";
char* password2="354691*";
char* password3="789541*";

int currentposition=0;
int stage=1; 
int flag=1;
int wrongpsw=0;
int wrongid=0;
const int buzzer = 12; 
 
 
void setup()
{
 
displayscreen();
myservo.attach(9); //Servo motor connection
pinMode(LED_BUILTIN, OUTPUT);
pinMode(buzzer, OUTPUT); 
lcd.begin(16,2); 
}
 
void loop()
{
if( flag==1)
{
displayscreen(); 
}

int l;
char code=keypad.getKey();
if(code!=NO_KEY)
{
flag=2;
switch(stage)
{ 
  case 1 :
  {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ID:");
        lcd.setCursor(7,1);
        lcd.print(" ");
        lcd.setCursor(7,1);
        for(l=0;l<=currentposition;++l)
            { 
                lcd.print(code);
            }

            if ((code==id1[currentposition])||(code==id2[currentposition])||(code==id3[currentposition]))
                {
                    ++currentposition;
                    if(currentposition==5)
                      {  
                            displayscreenid();
                            currentposition=0;
                            wrongid=0;                          
                      }
                } 
            else
                {
                  incorrectid();
                  flag=1;
                  currentposition=0; 
                  wrongid+=1;
                  if(wrongid>=3)
                  {
                     counterid(); 
                  }

                  
                }
          
          break;
       
    
  }
  case 2 :
  {
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Password:");
        lcd.setCursor(7,1);
        lcd.print(" ");
        lcd.setCursor(7,1);
        for(l=0;l<=currentposition;++l)
            { 
                lcd.print("*");
            }

            if ((code==password1[currentposition])||(code==password2[currentposition])||(code==password3[currentposition]))
                {
                    ++currentposition;
                    if(currentposition==7)
                      {  
                          unlock();
                          wrongpsw=0;
                          currentposition=0;
                          stage=1;
                      }
                } 
            else
                {
                  incorrectpsw();
                  currentposition=0;
                  wrongpsw+=1;
                  if(wrongpsw>=3)
                  {
                     counterpsw(); 
                  }
                }
            break;
    
  }
  
}

}
}


//------------------ Function 1- Unlock the door--------------//
 
void unlock()
{
delay(500);
lcd.clear(); 
lcd.setCursor(4,0);
lcd.println("Unlocked ");

for(pos = 180; pos>=0; pos-=5) // open the door
{
myservo.write(pos); 
delay(5); 
}
digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
delay(2000);
for(pos = 0; pos <= 180; pos +=5) // close the door
{ // in steps of 1 degree
myservo.write(pos); 
delay(15);
digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
currentposition=0;
lcd.clear();
displayscreen();
 
}
}
 
//--------------------Function 2- Wrong ID--------------//
 
void incorrectid()
{
delay(500);
lcd.clear();
lcd.setCursor(1,0);
lcd.print("The Wrong ID");
lcd.setCursor(0,1);
lcd.println("Enter ID again!!");
delay(2000);
lcd.clear();
displayscreen();
}

//--------------------Function 3- Wrong Password--------------//
 
void incorrectpsw()
{
delay(500);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("The Wrong PSW");
lcd.setCursor(2,1);
lcd.println("Enter it again!!");
delay(2000);
lcd.clear();
displayscreenid();
}
 
//-------Function 4 - CLEAR THE SCREEN--------------------/
void clearscreen()
{
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(0,1);
lcd.println(" ");
lcd.setCursor(0,2);
lcd.println(" ");
lcd.setCursor(0,3);
lcd.println(" ");
}

//------------Function 5 - Real time Display--------------------//
void displayscreen()
{

lcd.setCursor(3,0);
lcd.println("Welcome!!!");
lcd.setCursor(0 ,1);
 
lcd.println("Enter ID and [*]");
}

//------------Function 6 - Display after correct ID--------------------//
void displayscreenid()
{
lcd.clear(); 
lcd.setCursor(2,0);
lcd.println("ENTER THE PSW");
lcd.setCursor(3 ,1);
 
lcd.println("Press [*]");
stage=2;
}

//--------------Function 7 -freeze Count down wrong password------------------//
void counterpsw()
{ 
lcd.clear(); 
lcd.setCursor(2,0);
lcd.println("System Freezed");
tone(buzzer, 1000);
delay(2000);       
noTone(buzzer);     
lcd.clear(); 
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:::"); 
lcd.setCursor(4,1);
lcd.print("30");
delay(500);
lcd.clear();

      for(int c=29;c>0;c--)
    {
      lcd.setCursor(2,0);
      lcd.println("GET IN WITHIN:");
      delay(500);
      lcd.setCursor(4,1); //2
      lcd.print(c);
      delay(500);
      lcd.clear();
    }
displayscreenid();
}

//--------------Function 8 -freeze Count down for wrong id------------------//
void counterid()
{ 
lcd.clear(); 
lcd.setCursor(2,0);
lcd.println("System Freezed");
delay(1000);
lcd.clear(); 
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:::"); 
lcd.setCursor(4,1);
lcd.print("30");
delay(500);
lcd.clear();

      for(int c=29;c>0;c--)
    {
      lcd.setCursor(2,0);
      lcd.println("GET IN WITHIN:");
      delay(500);
      lcd.setCursor(4,1); //2
      lcd.print(c);
      delay(500);
      lcd.clear();
    }
lcd.setCursor(1,0);
lcd.println("Enter ID again!!");
lcd.setCursor(1,1);
lcd.println("And Press [*]");
delay(1000);
lcd.clear();
}

 
