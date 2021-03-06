#include <OneButton.h>
#include <LedControl.h>
#include <time.h>
#include "matrix_message.h"
#include "doubly_linked_list.h"
#define demora 100
//***************************************************************************************
#define ROWS 16
#define COLS 8
#define TRUE 1
#define FALSE 0

unsigned char __none[][8]{ \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0} \
} ;

char Table[ROWS][COLS] = {{0}};
//char Table[ROWS][COLS] = {0};
int score = 0;

typedef struct {
    char **array;
    int width, row, col;
} Figura;
Figura actual;
Figura carro;
Figura actual2;

time_t start,end;


char GameOn = TRUE;
double timer = 500000; //half second

const Figura ShapesArray[1]= {
    {(char *[]){(char []){1,1},(char []){1,1}}, 2}
};


const Figura ShapesArray2[1]= {
   //{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3}
    {(char *[]){(char []){1,1},(char []){1,1}}, 2}
};

Figura CopiarFigura(Figura shape){
    Figura new_shape = shape;
    char **copyshape = shape.array;
    new_shape.array = (char**)malloc(new_shape.width*sizeof(char*));
    int i, j;
    for(i = 0; i < new_shape.width; i++){
        new_shape.array[i] = (char*)malloc(new_shape.width*sizeof(char));
        for(j=0; j < new_shape.width; j++) {
            new_shape.array[i][j] = copyshape[i][j];
        }
    }
    return new_shape;
}


//***************************************************************************************


LedControl lc = LedControl(52, 48, 50, 1);
int __DISPLAY__[16][8] = {{1}};
int message_start = 0;
//13 3 4 10 6 11 15 16
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
const int buttonPin = 30;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

OneButton button(4,false);
OneButton buttonLeft(7, false);
OneButton buttonRigth(3, false);

unsigned long inicio, finalizado, Ttranscurrido=1, Ttranscurrido_anterior=0;


void mostrar(byte simbol[16])
{

  for(int k=0; k<50;k++){
    for(int i=0; i<8;i++){
      lc.setRow(0,i,simbol[i]);
    }
    
    for(int i=0; i<8; i++){
      
      for(int j=0; j<8; j++){
        if(((simbol[i+8] >> 7-j) & 1) !=0){
          digitalWrite(col[j], HIGH);
        }else{
          digitalWrite(col[j], LOW);
        }
      }
      digitalWrite(fila[i], LOW);
      delay(digitalRead(A0)/60);
      digitalWrite(fila[i], HIGH);
     }
     
  }
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
      if(((unidades[i]>>7-j) & 1) !=0){
        digitalWrite(col[j], HIGH);
      }else{
        digitalWrite(col[j], LOW);
      }
    }
    /*delay(sensorValue/60);*/
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
        case 10: 
          mostrar_puntaje(uno,zero);
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

void setup()
{
 
  Serial.begin(9600);


   GetFigura();
   GetCarroFigura();
   ImprimirTablero();
         
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

  button.attachDoubleClick(start_doubleClick);
  button.attachClick(start_singleClick);
  button.attachLongPressStop(start_longClick);

  buttonLeft.attachClick(left_click);
  buttonRigth.attachClick(right_click);
  
  pinMode(buttonPin, INPUT);
}


void left_click(){
  Serial.print("Tecla izquierda");
}

void right_click(){
  Serial.print("Telca derecha");
}

void start_doubleClick(){
  Serial.print("double click\n");
}

void start_singleClick(){
  Serial.print("single click\n");
  if(__switch_function==2){ //SI estoy jugando paso a PAUSA y a MOSTRAR PUNTAJE
    __switch_function=3; //MENU DE PAUSA
  }else if(__switch_function==3){
    __switch_function=1; //Vamos a countdown con tiempo + tiempoguardado.
  }
}

void start_longClick(){
  Serial.print("Long click");
  if(__switch_function==0){
    Serial.print("Cambiando a cuenta regresiva");
    lc.clearDisplay(0);
    __switch_function=1;  
  }else if(__switch_function==3){
    __switch_function=0; //Vamos a mensaje
  }
}



void loop()
{
  
  sensorValue=analogRead(A0);
  buttonState = digitalRead(30);
  button.tick();
  buttonLeft.tick();
  buttonRigth.tick();
  switch (__switch_function){
    case 0:
      mostrar(current->message_sprite); // llama funcion mostrar_0
      // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
      if (buttonState == HIGH){
       current = current->next;
      }
      else{
        current = current->prev;
        
      }
      /*delay(demora);*/
      delay(sensorValue);
      Serial.print(sensorValue);
      Serial.print("\n");
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
      inicio = millis(); 
      Ttranscurrido_anterior = Ttranscurrido;
      __switch_function=2;
      break;
    case 2:
        
        finalizado = millis();
        Ttranscurrido = finalizado - inicio;
        Serial.print(Ttranscurrido+Ttranscurrido_anterior);
        Serial.print("\n");
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
         /* int c;
         GetFigura();
         GetCarroFigura();
         ImprimirTablero();*/
         // while(GameOn){
             
             // if ((c = getchar()) != NULL) {
                ManipularFiguras('s');

                // ManipularMovimiento(c);
           //}
              //}
          
      //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      break;
    case 3:
      
      int puntaje = ((Ttranscurrido+Ttranscurrido_anterior)/1000) ;
      administrar_puntaje((int)puntaje);
      break;
    case 4:
      Serial.print("CUENTA REGRESIVA 3 Segundos\n");
      break;
    default:
      Serial.print("");
  }
  /*delay(sensorValue/1000);*/
}

//******************************************************************************************************************************************************

void Display(unsigned char dat[8][8])    
{  
  for(int c = 0; c<8;c++)  
  {  
    digitalWrite(fila[c],LOW);//use thr column 
    //loop
    for(int r = 0;r<8;r++)  
    {  
      digitalWrite(col[r],dat[c][r]);    
    }  
    delay(analogRead(A0) / 60);
    Clear();  //Remove empty display light
  }  
}


void Display2(unsigned char dat[8][8])    
{  
  for(int c = 0; c<8;c++)  
  {  
    for(int r = 0;r<8;r++)  
    {  
      lc.setLed(0,c,r,dat[c][r]);
    }  
  }  
} 

void BorrarFigura(Figura shape){
    int i;
    for(i = 0; i < shape.width; i++){
        free(shape.array[i]);
    }
    free(shape.array);
}


int Ver_posicion(Figura shape){ //VE LA POSICION Y COPIA LA FIGURA
    char **array = shape.array;
    int i, j;
    for(i = 0; i < shape.width;i++) {
        for(j = 0; j < shape.width ;j++){
            if((shape.col+j < 0 || shape.col+j >= COLS || shape.row+i >= ROWS)){ //FUERA DE LOS BORDES
                if(array[i][j]){

                    return FALSE;
                }
            }
            else if(Table[shape.row+i][shape.col+j] && array[i][j])
            {

                return FALSE;
            }

        }
    }

    return TRUE;
}

int CheckPositionCarro(Figura shape){
    char **array = shape.array;
    int i, j;
    for(i = 0; i < shape.width;i++) {
        for(j = 0; j < shape.width ;j++){
            if((shape.col+j < 0 || shape.col+j >= COLS || shape.row >= ROWS)){

                if(array[i][j])
                {
                    printf("choque");
                    end=clock();
                    GameOn=FALSE;
                    return FALSE;
                }

            }
            else if(Table[shape.row+i][shape.col+j] && array[i][j])
               {
                printf("choque");
                end=clock();
                GameOn=FALSE;
                return FALSE;
            }
        }
    }

    return TRUE;
}




void GetFigura(){
    Figura new_shape = CopiarFigura(ShapesArray[rand()%1]);
    new_shape.col = rand()%(COLS-new_shape.width+1);
    new_shape.row = 0;
    BorrarFigura(actual);
    actual = new_shape;
    
    if(!Ver_posicion(actual)){
        GameOn = FALSE;
       // Display(__none);
       // Display2(__none);
    }
}


void GetFigura2(){
    Figura new_shape = CopiarFigura(ShapesArray[rand()%1]);
    new_shape.col = rand()%(COLS-new_shape.width+1);
    new_shape.row = 0;
    BorrarFigura(actual2);
    actual2 = new_shape;
    if(!Ver_posicion(actual2)){
        GameOn = FALSE;
       // Display(__none);
       // Display2(__none);
    }
}


void GetCarroFigura(){
    Figura new_shape = CopiarFigura(ShapesArray2[0]);
    new_shape.col = 3;
    new_shape.row = 15;
    carro = new_shape;
}

void WriteToTable(){
    if(actual.col == carro.col){

        GameOn = FALSE;

    }
    if(actual.col+1 == carro.col){

        GameOn = FALSE;

    }
    if(actual.col-1 == carro.col){

        GameOn = FALSE;

    }
}


void Clear()                          //Clean unused lights  
{  
  for(int i = 0;i<8;i++)  
  {  
    digitalWrite(fila[i],HIGH);  
    digitalWrite(col[i],LOW);  
  }
  double dificulty = ((Ttranscurrido+Ttranscurrido_anterior)/1000);
  Serial.print("Dificultad: ");
  Serial.print(100-dificulty);
  Serial.print("\n");
  /*Serial.print(10000/((Ttranscurrido+Ttranscurrido_anterior)/1000));*/
  if(100-dificulty>1){
    delay(100-dificulty);    
  }else if(100-dificulty>0){
     double dificulty = ((Ttranscurrido+Ttranscurrido_anterior)/1000)*0.1;
     delay(1-dificulty);    
  }else{
    delay(0.01);
  }
}  


void ImprimirTablero(){
    char Buffer[ROWS][COLS] = {{0}};
    char Buffer2[1][COLS] = {{0}};
    
    /*En la ultima fila de __display___ meter el buffer 2*/
    int i, j;
    for(i = 0; i < actual.width ;i++){
        for(j = 0; j < actual.width ; j++){
            if(actual.array[i][j])
                Buffer[actual.row+i][actual.col+j] = actual.array[i][j];
        }
    }

    for(i = 0; i < actual2.width ;i++){
        for(j = 0; j < actual2.width ; j++){
            if(actual2.array[i][j])
                Buffer[actual2.row+i][actual2.col+j] = actual2.array[i][j];
        }
    }

    for(i = 0; i < carro.width ;i++){
        for(j = 0; j < carro.width ; j++){
            if(carro.array[i][j])
                Buffer2[carro.row+i][carro.col+j] = carro.array[i][j];
        }
    }


    for(int i=0; i<8;i++){
      for(int j=0; j<8;j++){
        lc.setLed(0,i,j,__DISPLAY__[i][j]+Buffer[i][j]);
      }  
    }
    for(int x=8;x<16;x++){
      digitalWrite(fila[x-8],LOW);
      for(int y=0; y<8;y++){
        if(__DISPLAY__[x][y]+Buffer[x][y]){
          digitalWrite(col[y],HIGH);
        }
      }
      for(int y=0; y<8;y++){
        if(__DISPLAY__[x][y]+Buffer[x][y]){
          digitalWrite(col[y],LOW);
        }
      }
      Clear();
    }
    
      /*for(int x=8;x<16;x++){
      digitalWrite(fila[x-8],LOW);
      for(int y=0; y<8;y++){
        if(Table[x][y]+Buffer[x-8][y] == 1){
          digitalWrite(col[y],HIGH);
        }
      }
      
      delay(1);
      for(int y=0; y<8;y++){
        if(Table[x][y]+Buffer[x-8][y] == 1){
          digitalWrite(col[y],LOW);
        }
      }
      Clear();
      }*/
}

void visualizarMatriz(){
  for(int i=0;i<8;i++){
      for(int j=0;j<8;j++){
        lc.setLed(0,i,j,Table[i][j]);
      }
    }
}

void ManipularFiguras(int action){
   Figura temp = CopiarFigura(actual);
   switch(action){
       case 's':
           temp.row++;
           if(Ver_posicion(temp)){
               if(actual.row==5){
                   GetFigura2();
               }
               actual.row++;
               actual2.row++;
           }
           else {
               //WriteToTable();
               GetFigura();
           }
       break;
   }

   BorrarFigura(temp);
   ImprimirTablero();
}

void ManipularMovimiento(int action){

    Figura temp = CopiarFigura(carro);
    switch(action){
    case 'd':
        temp.col++;
        if(CheckPositionCarro(temp)){
             carro.col++;
        }

        break;
    case 'a':
        temp.col--;
        if(CheckPositionCarro(temp))
            carro.col--;
        break;
    }

    BorrarFigura(temp);
    ImprimirTablero();
}
