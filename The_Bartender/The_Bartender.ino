#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SimpleRotary.h>

// Pin A, Pin B (from the three legs), Button Pin (from the two legs)
SimpleRotary rotary(2,3,4);


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
boolean intro=false;
int counterMenu =1; //counter the rotary button for the menu
                    //start at 1 and end at 3 righ: +1 left: -1
int previousChoice=1;

void setup()
{
	// initialize the LCD
	lcd.begin();
  
  rotary.setTrigger(HIGH);
  
  // Set the debounce delay in ms  (Default: 2)
  rotary.setDebounceDelay(5);

  // Set the error correction delay in ms  (Default: 200)
  rotary.setErrorDelay(250);
  Serial.begin(9600);
  
}

void loop()
{
  
  byte rotateButton, pushButton;
  char message[]="The bartender";
  char message2[]="***MAKERIM***";
  char* ptr=message;
  char* ptr2 = message2;
  rotateButton = rotary.rotate();
  pushButton = rotary.push();


  
  if(intro == false){
  lcd.clear();
  lcd.setCursor(0,0);
  for(int i=0 ; i< (sizeof(message)/sizeof(*message))-1 ; ++i)
  {
    lcd.print(ptr[i]);
    delay(200);
  }
  lcd.setCursor(14,1);
  
  
  for(int i=0 ; i< (sizeof(message2)/sizeof(*message2))-1 ; ++i)
  {
    if(i==2){
      lcd.autoscroll();
    }
    lcd.print(ptr2[i]);
    delay(200);
  }
  lcd.noAutoscroll();
  lcd.clear();
  intro =true;
  }
  lcd.setCursor(0,0);
  switch(rotateButton){
    case 1:
          if(counterMenu==3){
            break;
          }
          counterMenu+=1;
          break;
          
    case 2:
          if(counterMenu==1){
            break;
          }
          counterMenu -=1;
          break;
  }
  if(previousChoice != counterMenu)//clear the screen to the next option
    lcd.clear();
  Menu(counterMenu, pushButton);
  
  
  previousChoice = counterMenu;
}

void Menu(int counterMenu, int pushButton){
  switch(counterMenu){
    case 1:
          lcd.print("Whisky");
          break;
    case 2:
          lcd.print("Arak");
          break;
    case 3:
          lcd.print("Vodka");
          break;
  }
  if(pushButton==1)
    pouringBeverage(counterMenu);
}

void pouringBeverage (int beverage){
  lcd.clear();



  pouringAnimation();
}

void pouringAnimation(){
  for(int i=0; i<3; ++i){
    runningManR();
    ManslipR();
    runningManL();
    ManslipL();
  }
  delay(1000);
  lcd.clear();
}
   
