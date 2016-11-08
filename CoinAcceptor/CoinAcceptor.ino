#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

volatile uint8_t coin;
volatile short newCoin = false;
volatile uint8_t timeOut = 0;
uint8_t myCoin = 0;
uint8_t totalCoinsInserted = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Coin Acceptor Demo");
  lcd.begin(20, 4);
  lcd.print("Coin Acceptor Demo");
  pinMode(3,INPUT);
  digitalWrite(3,HIGH);
  attachInterrupt(digitalPinToInterrupt(3),countCoin,RISING);
  
}

void loop() {

  
  checkCoin();
  
  
  lcd.setCursor(0,1);
  lcd.print("Inserted: ");
  lcd.print(myCoin);lcd.print("  ");

  lcd.setCursor(0,2);
  lcd.print("Total: ");
  lcd.print(totalCoinsInserted);lcd.print("  ");
  
   delay(100);
}

void checkCoin()
{
   if(newCoin == true){

        if(coin == 10 || timeOut > 5){
           switch(coin){
                  case 1: myCoin = 1;
                          coin = 0;
                          newCoin = false;
                          break;
                  case 5: myCoin = 5;
                          coin = 0;
                          newCoin = false;
                          break;                          
                  case 10: myCoin = 10;
                          coin = 0;
                          newCoin = false;
                          break;      
                  default: myCoin = 0;
                          coin = 0;
                          newCoin = false;
                          break;
           }
           totalCoinsInserted += myCoin;
        }
        timeOut++;
        delay(5);
     }
}

void countCoin ()
{
  newCoin = true;
  coin++;
  timeOut = 0;
}

