#include "Keyboard.h"

int butb=0;//bouton back
int buts=1;//bouton slash
int butt=2;//bouton tiret
int butp=3;//bouton point

int ledb=9;//LED du bouton back
int leds=7;//LED du bouton slash
int ledt=4;//LED du bouton tiret
int ledp=2;//LED du bouton point


int nb=0;//nombre de signaux dans la liste
int lettre[]={0,0,0,0};




void setup() {
  //démarrage de la carte
  delay(10);
  //orientation des broches pour les leds (output)
  pinMode(leds, OUTPUT);
  pinMode(ledt, OUTPUT);
  pinMode(ledp, OUTPUT);
  pinMode(ledb, OUTPUT);
  delay(10);
  digitalWrite(ledp, 1);//animation
  //démarrage du keyboard
  Keyboard.begin();
  delay(800);
  digitalWrite(ledt, 1);//animation
  //démarrage de la liaison série s'il y en a une
  Serial.begin(9600);
  delay(800);
  digitalWrite(leds, 1);//animation
  delay(800);
  digitalWrite(ledb, 1);//animation
  delay(800);

  digitalWrite(ledp, 0);
  digitalWrite(leds, 0);
  digitalWrite(ledt, 0);
  digitalWrite(ledb, 0);
  delay(10);

}

////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  if (analogRead(buts)>512){
    digitalWrite(leds, 1);
    Serial.print("/");
    Serial.print(decodeLetter(lettre));
    if (lettre[0]==0){
      Keyboard.print(decodeLetter(lettre));
    }
    nb=0;
    lettre[0]=0;
    lettre[1]=0;
    lettre[2]=0;
    lettre[3]=0;
    while (analogRead(buts)>512){}
  }
  else {
    digitalWrite(leds, 0);
  }

  ////////////////////////////////////////////////////
  
  if (analogRead(butp)>512){
    digitalWrite(ledp, 1);
    if (nb<4){
      lettre[nb]=1;
    }
    Serial.print(".");
    if (nb>0){
      Keyboard.write(KEY_BACKSPACE);//delete key
    }
    Keyboard.print(decodeLetter(lettre));
    nb++;
    while (analogRead(butp)>512){}
  }
  else {
    digitalWrite(ledp, 0);
  }

  //////////////////////////////////////////////
  
  if (analogRead(butt)>512){
    digitalWrite(ledt, 1);
    if (nb<4){
      lettre[nb]=3;
    }
    Serial.print("-");
    if (nb>0){
      Keyboard.write(KEY_BACKSPACE);//delete key
    }
    Keyboard.print(decodeLetter(lettre));
    nb++;
    while (analogRead(butt)>512){}
  }
  else {
    digitalWrite(ledt, 0);
  }

  ////////////////////////////////////////////////
  
  if (analogRead(butb)>512){
    digitalWrite(ledb, 1);
    Serial.print("*");
    Keyboard.write(KEY_BACKSPACE);//delete key
    nb=0;
    lettre[0]=0;
    lettre[1]=0;
    lettre[2]=0;
    lettre[3]=0;
    while (analogRead(butb)>512){}}
  else {
    digitalWrite(ledb, 0);
  }
  
  delay(5);//attente de 5 ms avant le retour au début de la boucle
}



////////////////////////////////////////////////////////////////////////////////////////////


String decodeLetter(int* letter){
  if (letter[0]==1){
    if (letter[1]==1){
      if (letter[2]==1){
        if (letter[3]==1){return "H";}//....
        else if (letter[3]==3){return "V";}//...-
        else {return "S";}}//...
      else if (letter[2]==3){
        if (letter[3]==1){return "F";}//..-.
        else if (letter[3]==3){return "?";}//..--
        else {return "U";}}//..-
      else {return "I";}}//..
      
    else if (letter[1]==3){
      if (letter[2]==1){
        if (letter[3]==1){return "L";}//.-..
        else if (letter[3]==3){return "?";}//.-.-
        else {return "R";}}//.-.
      else if (letter[2]==3){
        if (letter[3]==1){return "P";}//.--.
        else if (letter[3]==3){return "J";}//.---
        else {return "Z";}}//.-- W<=>Z (clavier AZERTY/QWERTY)
      else {return "Q";}}//.- Q<=>A (clavier AZERTY/QWERTY)
      
    else {return "E";}}//.


  else if (letter[0]==3){
    if (letter[1]==1){
      if (letter[2]==1){
        if (letter[3]==1){return "B";}//-...
        else if (letter[3]==3){return "X";}//-..-
        else {return "D";}}//-..
      else if (letter[2]==3){
        if (letter[3]==1){return "C";}//-.-.
        else if (letter[3]==3){return "Y";}//-.--
        else {return "K";}}//-.-
      else {return "N";}}//-.
      
    else if (letter[1]==3){
      if (letter[2]==1){
        if (letter[3]==1){return "W";}//--.. W<=>Z (clavier AZERTY/QWERTY)
        else if (letter[3]==3){return "A";}//--.- Q<=>A (clavier AZERTY/QWERTY)
        else {return "G";}}//--.
      else if (letter[2]==3){
        if (letter[3]==1){return "?";}//---.
        else if (letter[3]==3){return "CH";}//----
        else {return "O";}}//---
      else {return ":";}}//-- :<=>M (clavier AZERTY/QWERTY)
      
    else {return "T";}}//-

  else{return " ";}
    
}

