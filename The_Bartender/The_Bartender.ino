#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SimpleRotary.h>

// Pin A, Pin B (from the three legs), Button Pin (from the two legs)
SimpleRotary rotary(5, 6, 7);

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

boolean intro = false;//flag for the intro (will be tonly one time)
boolean inDrinkMenu = false;// flag to separate between the main menu to the drink menu
boolean flagPouring =false; //flag for not pouring in the enter to the drink menu

int counterMenu = 1; //by this number i will know wich pump to use (wich drink to poure)
//counter the rotary button for the menu (options)
//start at 1 and end at 3 righ: +1 left: -1
//1- whiskey  2- taquila  3- vodka



int counterDrinkMenu = 1; //by this number i will know how much time i need to open the pump
//counter the rotary button for the drink menu: chaser, shot, glass (options)
//start at 1 and end at 4 righ: +1 left: -1
//1- chaser  2- shot   3- glass   4- back

//previousChoice flag: when to clean the LCD for the next choice
int previousChoice = 1;
int previousChoiceDrink = 1;

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
  char message[] = "The Bartender";
  char message2[] = "***MAKERIM***";
  char* ptr = message;
  char* ptr2 = message2;
  
  rotateButton = rotary.rotate();//receive the rotation of the button to the main menu
  //rotateButtonDrink = rotary.rotate();//receive the rotation of the button to the drink menu
  pushButton = rotary.push();//receive the pressing at the button
  if (rotateButton == 1 || rotateButton == 2)
    Serial.println(rotateButton);
  if (pushButton == 1)
    Serial.println(pushButton);


  if (intro == false) {//Intro - welcoming the user/ sliding sentence
    lcd.clear();
    lcd.setCursor(0, 0);
    for (int i = 0 ; i < (sizeof(message) / sizeof(*message)) - 1 ; ++i)
    {
      lcd.print(ptr[i]);
      delay(200);
    }
    lcd.setCursor(14, 1);


    for (int i = 0 ; i < (sizeof(message2) / sizeof(*message2)) - 1 ; ++i)
    {
      if (i == 2) {
        lcd.autoscroll();
      }
      lcd.print(ptr2[i]);
      delay(200);
    }
    lcd.noAutoscroll();
    lcd.clear();
    intro = true;
  }
  lcd.setCursor(0, 0);

  if (!inDrinkMenu) {
    counterDrinkMenu = 1;
    switch (rotateButton) {
      case 1:
        if (counterMenu == 3) {// 3 is the limit at the menu
          break;
        }
        counterMenu += 1;
        break;

      case 2:
        if (counterMenu == 1) {// 1 is the limit at the menu
          break;
        }
        counterMenu -= 1;
        break;
    }

    if (previousChoice != counterMenu) //clear the screen to the next option
      lcd.clear();
    Menu(counterMenu, pushButton, rotateButton);
    previousChoice = counterMenu;
  }
  else {
    //inDrinkMenu =true;
    //rotateButtonFunctionDrinkMenu(rotateButton, counterMenu , counterDrinkMenu, pushButton);
    flagPouring =true;
    switch (rotateButton) {
      case 1:
        if (counterDrinkMenu == 4) {// 3 is the limit at the menu
          break;
        }
        counterDrinkMenu += 1;
        break;

      case 2:
        if (counterDrinkMenu == 1) {// 1 is the limit at the menu
          break;
        }
        counterDrinkMenu -= 1;
        break;
    }
    if (previousChoiceDrink != counterDrinkMenu) //clear the screen to the next option
      lcd.clear();
    drinkMenu(counterMenu, counterDrinkMenu, pushButton);
    previousChoiceDrink = counterDrinkMenu;
  }
}
////////////////////////////////////////////////////
void rotateButtonFunctionMainMenu(int rotateButton, int counterMenu) {
  switch (rotateButton) {
    case 1:
      if (counterMenu == 3) {// 3 is the limit at the menu
        break;
      }
      counterMenu += 1;
      break;

    case 2:
      if (counterMenu == 1) {// 1 is the limit at the menu
        break;
      }
      counterMenu -= 1;
      break;
  }
}

void Menu(int counterMenu, int pushButton, int rotateButton) {//start music
  switch (counterMenu) {
    case 1:
      lcd.print("Whisky");
      break;
    case 2:
      lcd.print("Taquila");
      break;
    case 3:
      lcd.print("Vodka");
      break;
  }
  if (pushButton == 1) {
    //rotateButtonFunctionDrinkMenu(rotateButton , counterMenu , counterDrinkMenu, pushButton);
    inDrinkMenu = true;
    switch (rotateButton) {
      case 1:
        if (counterDrinkMenu == 4) {// 3 is the limit at the menu
          break;
        }
        counterDrinkMenu += 1;
        break;

      case 2:
        if (counterDrinkMenu == 1) {// 1 is the limit at the menu
          break;
        }
        counterDrinkMenu -= 1;
        break;
    }
    lcd.clear();
    drinkMenu(counterMenu, counterDrinkMenu, pushButton);
  }
}

void rotateButtonFunctionDrinkMenu(int rotateButton, int counterMenu , int counterDrinkMenu, int pushButton) {
  switch (rotateButton) {
    case 1:
      if (counterDrinkMenu == 4) {// 3 is the limit at the menu
        break;
      }
      counterDrinkMenu += 1;
      break;

    case 2:
      if (counterDrinkMenu == 1) {// 1 is the limit at the menu
        break;
      }
      counterDrinkMenu -= 1;
      break;
  }
}

void drinkMenu(int counterMenu, int counterDrinkMenu, int pushButton) { //drink music
  switch (counterDrinkMenu) {
    case 1:
      lcd.print("Chaser");
      break;
    case 2:
      lcd.print("Shot");
      break;
    case 3:
      lcd.print("Glass");
      break;
    case 4:
      lcd.print("Back");
      flagPouring =false;
      break;
  }
  if (previousChoiceDrink != counterDrinkMenu) { //clear the screen to the next option
    Serial.print("counterMenu, counterDrinkMenu: ");
    Serial.println(counterMenu);
    Serial.println(counterDrinkMenu);
  }
  if (pushButton == 1 && counterDrinkMenu != 4 && flagPouring==true)
    pouringBeverage(counterMenu, counterDrinkMenu);
  if (pushButton == 1 && counterDrinkMenu == 4) {
    inDrinkMenu = false; // return to the main menu
    counterDrinkMenu = 1;
  }
}

void pouringBeverage (int beverage, int amount) {
  lcd.clear();
  pouringAnimation();
}

void pouringAnimation() {
  for (int i = 0; i < 1; ++i) {
    runningManR();
    ManslipR();
    runningManL();
    ManslipL();
  }
  lcd.clear();
}
