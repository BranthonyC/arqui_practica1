#include <OneButton.h>
#include <LedControl.h>
#include <time.h>
#include "matrix_message.h"
#include "doubly_linked_list.h"
#define demora 100



LedControl lc = LedControl(11, 13, 10, 1);
int __DISPLAY__[16][8] = {{1}};
int message_start = 0;
//13 3 4 10 6 1115 16
int col[] = {26, 43, 45, 23, 49, 24, 28 ,29 };
//9 14 8 12 1 7 2 5
int fila[] = {22, 27, 53, 25, 39, 51, 41, 47};
unsigned char mask = 1; // Bit mask
unsigned long time_;
unsigned long time_to_countdown;
unsigned long previus_time_to_countdown=0;
unsigned long ingame_time;
unsigned long previus_ingame_time=0;
unsigned long previusTime=0;
int interval=3000;
int __switch_function= 0;

int sensorValue = 0;

OneButton button(4,false);


void setup()
{
 
  Serial.begin(9600);

  //The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  lc.shutdown(0, false);
  //Set the brightness to a medium values (0~15 possible values)
  lc.setIntensity(0, 2);
  //and clear the display
  lc.clearDisplay(0);

  for(int i = 0; i < 8; i++){
    pinMode(col[i], OUTPUT);
    pinMode(fila[i], OUTPUT);
  }
  for(int i = 0; i < 8; i++){
    digitalWrite(fila[i], HIGH);
    digitalWrite(col[i], LOW);
  }

/*  insertLast(prueba);*/
  insertLast(message_0);
  insertLast(message_1);
  insertLast(message_2);
  insertLast(message_3);
  insertLast(message_4);
  insertLast(message_5);
  insertLast(message_6);
  insertLast(message_7);
  insertLast(message_8);
  insertLast(message_9);
  insertLast(message_10);
  insertLast(message_11);
  insertLast(message_12);
  insertLast(message_13);
  insertLast(message_14);
  insertLast(message_15);
  insertLast(message_16);
  insertLast(message_17);
  insertLast(message_18);
  insertLast(message_19);
  insertLast(message_20);
  insertLast(message_21);
  insertLast(message_22);
  insertLast(message_23);
  insertLast(message_24);
  insertLast(message_25);
  insertLast(message_26);
  insertLast(message_27);
  insertLast(message_28);
  insertLast(message_29);
  insertLast(message_30);
  insertLast(message_31);
  insertLast(message_32);
  insertLast(message_33);
  insertLast(message_34);
  insertLast(message_35);
  insertLast(message_36);
  insertLast(message_37);
  insertLast(message_38);
  insertLast(message_39);
  insertLast(message_40);
  insertLast(message_41);
  insertLast(message_42);
  insertLast(message_43);
  insertLast(message_44);
  insertLast(message_45);
  insertLast(message_46);
  insertLast(message_47);
  insertLast(message_48);
  insertLast(message_49);
  insertLast(message_50);
  insertLast(message_51);
  insertLast(message_52);
  insertLast(message_53);
  insertLast(message_54);
  insertLast(message_55);
  insertLast(message_56);
  insertLast(message_57);
  insertLast(message_58);
  insertLast(message_59);
  insertLast(message_60);
  insertLast(message_61);
  insertLast(message_62);
  insertLast(message_63);
  insertLast(message_64);
  insertLast(message_65);
  insertLast(message_66);
  insertLast(message_67);
  insertLast(message_68);
  insertLast(message_69);
  insertLast(message_70);
  insertLast(message_71);
  insertLast(message_72);
  insertLast(message_73);
  insertLast(message_74);
  insertLast(message_75);
  insertLast(message_76);
  insertLast(message_77);
  insertLast(message_78);
  insertLast(message_79);
  insertLast(message_80);
  insertLast(message_81);
  insertLast(message_82);
  insertLast(message_83);
  insertLast(message_84);
  insertLast(message_85);
  insertLast(message_86);
  insertLast(message_87);
  insertLast(message_88);
  insertLast(message_89);
  insertLast(message_90);
  insertLast(message_91);
  insertLast(message_92);
  insertLast(message_93);
  insertLast(message_94);
  insertLast(message_95);
  insertLast(message_96);
  insertLast(message_97);
  insertLast(message_98);
  insertLast(message_99);
  insertLast(message_100);
   insertLast(message_101);
  insertLast(message_102);
  insertLast(message_103);
  insertLast(message_104);
  insertLast(message_105);
  insertLast(message_124);
  insertLast(message_106);
  insertLast(message_107);
  insertLast(message_108);
  insertLast(message_109);
  insertLast(message_110);
  insertLast(message_125);
  insertLast(message_111);
  insertLast(message_112);
  insertLast(message_113);
  insertLast(message_114);
  insertLast(message_115);
  insertLast(message_116);
  insertLast(message_117);
  insertLast(message_118);
  insertLast(message_119);
  insertLast(message_120);
  insertLast(message_121);
  insertLast(message_122);
  insertLast(message_123);
  current = first;

  // initialize the pushbutton pin as an input:
  /*pinMode(buttonPin, INPUT);
  pinMode(startButton, INPUT);*/

  button.attachDoubleClick(start_doubleClick);
  button.attachClick(start_singleClick);
  button.attachLongPressStop(start_longClick);
}


void start_doubleClick(){
  Serial.print("double click\n");
}

void start_singleClick(){
  Serial.print("single click\n");
  if(__switch_function==2){ //Jugando
    __switch_function=3; //Vamos a pausa
  }else if(__switch_function==3){ //Si estamos en pausa
    __switch_function=1; //Vamos a countdown
  }
}

void start_longClick(){
  if(__switch_function==0){
    Serial.print("Cambiando a cuenta regresiva");
    lc.clearDisplay(0);
    __switch_function=1;  
  }
}
void loop()
{
  sensorValue=analogRead(A0)*0.1;
  Serial.print(sensorValue);
  Serial.print("\n");
  button.tick();
  /*delay(100);*/
  switch (__switch_function){
    case 0:
      mostrar(current->message_sprite); // llama funcion mostrar_0
      // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
      /*if (buttonState == HIGH) IF Switch cambia
      {
        current = current->prev;
      }
      else
      {
        current = current->next;
      }*/
      current = current->next;
      delay(demora);
      break;
    case 1:
      administrar_puntaje(33);
      delay(1000);
      administrar_puntaje(22);
      delay(1000);
      administrar_puntaje(11);
      delay(1000);
      administrar_puntaje(1);
      delay(1000);
      lc.clearDisplay(0);  
      __switch_function=2;
      break;
    case 2:
      ingame_time = millis();
      break;
    case 3:
      int puntaje = (ingame_time-previus_ingame_time)/1000 ;
      administrar_puntaje(puntaje);
      break;
    case 4:
      Serial.print("CUENTA REGRESIVA 3 Segundos\n");
      break;
    default:
      Serial.print("");
  }
  delay(sensorValue);
}


void mostrar_puntaje(byte decenas[8], byte unidades[8]){
  lc.setRow(0, 0, decenas[0]); // establece fila con valor de array cero en misma posicion  
  lc.setRow(0, 1, decenas[1]); // establece fila con valor de array cero en misma posicion  
  lc.setRow(0, 2, decenas[2]); // establece fila con valor de array cero en misma posicion  
  lc.setRow(0, 3, decenas[3]); // establece fila con valor de array cero en misma posicion  
  lc.setRow(0, 4, decenas[4]); // establece fila con valor de array cero en misma posicion  
  lc.setRow(0, 5, decenas[5]); // establece fila con valor de array cero en misma posicion  
  lc.setRow(0, 6, decenas[6]); // establece fila con valor de array cero en misma posicion  
  lc.setRow(0, 7, decenas[7]); // establece fila con valor de array cero en misma posicion

  for(int i=0; i<8; i++){
    digitalWrite(fila[i], LOW);
    for(int j=0; j<8; j++){
      if(((unidades[i] >> 7-j) & 1) !=0){
        digitalWrite(col[j], HIGH);
      }else{
        digitalWrite(col[j], LOW);
      }
    }
    digitalWrite(fila[i], HIGH);
   }
}
void mostrar(byte simbol[16])
{                             // funcion mostrar_0
  lc.setRow(0, 0, simbol[0]); // establece fila con valor de array cero en misma posicion  
  lc.setRow(0, 1, simbol[1]); // establece fila con valor de array cero en misma posicion  
  lc.setRow(0, 2, simbol[2]); // establece fila con valor de array cero en misma posicion  
  lc.setRow(0, 3, simbol[3]); // establece fila con valor de array cero en misma posicion  
  lc.setRow(0, 4, simbol[4]); // establece fila con valor de array cero en misma posicion  
  lc.setRow(0, 5, simbol[5]); // establece fila con valor de array cero en misma posicion  
  lc.setRow(0, 6, simbol[6]); // establece fila con valor de array cero en misma posicion  
  lc.setRow(0, 7, simbol[7]); // establece fila con valor de array cero en misma posicion
  for(int i=0; i<8; i++){
    digitalWrite(fila[i], LOW);
    for(int j=0; j<8; j++){
      if(((simbol[i+8] >> 7-j) & 1) !=0){
        digitalWrite(col[j], HIGH);
      }else{
        digitalWrite(col[j], LOW);
      }
    }
    digitalWrite(fila[i], HIGH);
   }
}

void administrar_puntaje(int puntaje){
    switch(puntaje){
        case 1:
          mostrar_puntaje(zero, uno);
          break;
        case 2:
          mostrar_puntaje(zero, dos);
          break;
        case 3:
          mostrar_puntaje(zero, tres);
          break;
        case 4:
          mostrar_puntaje(zero, cuatro);
          break;
        case 5:
          mostrar_puntaje(zero, cinco);
          break;
        case 6:
          mostrar_puntaje(zero, seis);
          break;
        case 7:
          mostrar_puntaje(zero, siete);
          break;
        case 8:
          mostrar_puntaje(zero, ocho);
          break;
        case 9:
          mostrar_puntaje(zero, nueve);
          break;
        
        case 11: 
          mostrar_puntaje(uno,uno);
          break;
        
        case 12: 
          mostrar_puntaje(uno,dos);
          break;
        
        case 13: 
          mostrar_puntaje(uno,tres);
          break;
        
        case 14: 
          mostrar_puntaje(uno,cuatro);
          break;
        
        case 15: 
          mostrar_puntaje(uno,cinco);
          break;
        
        case 16: 
          mostrar_puntaje(uno,seis);
          break;
        
        case 17: 
          mostrar_puntaje(uno,siete);
          break;
        
        case 18: 
          mostrar_puntaje(uno,ocho);
          break;
        
        case 19: 
          mostrar_puntaje(uno,nueve);
          break;
        
        case 20: 
          mostrar_puntaje(dos,zero);
          break;
        
        case 21: 
          mostrar_puntaje(dos,uno);
          break;
        
        case 22: 
          mostrar_puntaje(dos,dos);
          break;
        
        case 23: 
          mostrar_puntaje(dos,tres);
          break;
        
        case 24: 
          mostrar_puntaje(dos,cuatro);
          break;
        
        case 25: 
          mostrar_puntaje(dos,cinco);
          break;
        
        case 26: 
          mostrar_puntaje(dos,seis);
          break;
        
        case 27: 
          mostrar_puntaje(dos,siete);
          break;
        
        case 28: 
          mostrar_puntaje(dos,ocho);
          break;
        
        case 29: 
          mostrar_puntaje(dos,nueve);
          break;
        
        case 30: 
          mostrar_puntaje(tres,zero);
          break;
        case 31: 
          mostrar_puntaje(tres,uno);
          break;
        
        case 32: 
          mostrar_puntaje(tres,dos);
          break;
        
        case 33: 
          mostrar_puntaje(tres,tres);
          break;
        
        case 34: 
          mostrar_puntaje(tres,cuatro);
          break;
        
        case 35: 
          mostrar_puntaje(tres,cinco);
          break;
        
        case 36: 
          mostrar_puntaje(tres,seis);
          break;
        
        case 37: 
          mostrar_puntaje(tres,siete);
          break;
        
        case 38: 
          mostrar_puntaje(tres,ocho);
          break;
        
        case 39: 
          mostrar_puntaje(tres,nueve);
          break;
        
        case 40: 
          mostrar_puntaje(cuatro,zero);
          break;
        
        
        case 41: 
          mostrar_puntaje(cuatro,uno);
          break;
        
        case 42: 
          mostrar_puntaje(cuatro,dos);
          break;
        
        case 43: 
          mostrar_puntaje(cuatro,tres);
          break;
        
        case 44: 
          mostrar_puntaje(cuatro,cuatro);
          break;
        
        case 45: 
          mostrar_puntaje(cuatro,cinco);
          break;
        
        case 46: 
          mostrar_puntaje(cuatro,seis);
          break;
        
        case 47: 
          mostrar_puntaje(cuatro,siete);
          break;
        
        case 48: 
          mostrar_puntaje(cuatro,ocho);
          break;
        
        case 49: 
          mostrar_puntaje(cuatro,nueve);
          break;
        case 50: 
          mostrar_puntaje(cinco,zero);
          break;
        case 51: 
          mostrar_puntaje(cinco,uno);
          break;
        case 52: 
          mostrar_puntaje(cinco,dos);
          break;
        case 53: 
          mostrar_puntaje(cinco,tres);
          break;
        case 54: 
          mostrar_puntaje(cinco,cuatro);
          break;
        case 55: 
          mostrar_puntaje(cinco,cinco);
          break;
        case 56: 
          mostrar_puntaje(cinco,seis);
          break;
        case 57: 
          mostrar_puntaje(cinco,siete);
          break;
        case 58: 
          mostrar_puntaje(cinco,ocho);
          break;
        case 59: 
          mostrar_puntaje(cinco,nueve);
          break;
        case 60: 
          mostrar_puntaje(seis,zero);
          break;
        case 61: 
          mostrar_puntaje(seis,uno);
          break;
        case 62: 
          mostrar_puntaje(seis,dos);
          break;
        case 63: 
          mostrar_puntaje(seis,tres);
          break;
        case 64: 
          mostrar_puntaje(seis,cuatro);
          break;
        case 65: 
          mostrar_puntaje(seis,cinco);
          break;
        case 66: 
          mostrar_puntaje(seis,seis);
          break;
        case 67: 
          mostrar_puntaje(seis,siete);
          break;
        case 68: 
          mostrar_puntaje(seis,ocho);
          break;
        case 69: 
          mostrar_puntaje(seis,nueve);
          break;
        case 70: 
          mostrar_puntaje(siete,zero);
          break;
        case 71: 
          mostrar_puntaje(siete,uno);
          break;
        case 72: 
          mostrar_puntaje(siete,dos);
          break;
        case 73: 
          mostrar_puntaje(siete,tres);
          break;
        case 74: 
          mostrar_puntaje(siete,cuatro);
          break;
        case 75: 
          mostrar_puntaje(siete,cinco);
          break;
        case 76: 
          mostrar_puntaje(siete,seis);
          break;
        case 77: 
          mostrar_puntaje(siete,siete);
          break;
        case 78: 
          mostrar_puntaje(siete,ocho);
          break;
        case 79: 
          mostrar_puntaje(siete,nueve);
          break;
        case 80: 
          mostrar_puntaje(ocho,zero);
          break;
        case 81: 
          mostrar_puntaje(ocho,uno);
          break;
        case 82: 
          mostrar_puntaje(ocho,dos);
          break;
        case 83: 
          mostrar_puntaje(ocho,tres);
          break;
        case 84: 
          mostrar_puntaje(ocho,cuatro);
          break;
        case 85: 
          mostrar_puntaje(ocho,cinco);
          break;
        case 86: 
          mostrar_puntaje(ocho,seis);
          break;
        case 87: 
          mostrar_puntaje(ocho,siete);
          break;
        case 88: 
          mostrar_puntaje(ocho,ocho);
          break;
        case 89: 
          mostrar_puntaje(ocho,nueve);
          break;
        case 90: 
          mostrar_puntaje(nueve,zero);
          break;
        case 91: 
          mostrar_puntaje(nueve,uno);
          break;
        case 92: 
          mostrar_puntaje(nueve,dos);
          break;
        case 93: 
          mostrar_puntaje(nueve,tres);
          break;
        case 94: 
          mostrar_puntaje(nueve,cuatro);
          break;
        case 95: 
          mostrar_puntaje(nueve,cinco);
          break;
        case 96: 
          mostrar_puntaje(nueve,seis);
          break;
        case 97: 
          mostrar_puntaje(nueve,siete);
          break;
        case 98: 
          mostrar_puntaje(nueve,ocho);
          break;
        default:
          mostrar_puntaje(nueve, nueve);
          break;
      }
}
