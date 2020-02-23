#include "tm4c123gh6pm.h"
#include "Port_INIT.h"
#include "Fsm.h"
#include <stdbool.h>
#include "Systick_Timer.h"

unsigned char sevSeg[16][3]={

  {0x3f,3,1 },//0
  {0x06,0,0 },//1
  {0x5b,0,1 },//2  
  {0x4f,0,2 },//3  
  {0x66,1,0 },//4  
  {0x6d,1,1 },//5  
  {0x7d,1,2 },//6  
  {0x07,2,0 },//7  
  {0x7f,2,1 },//8  
  {0x67,2,2 },//9
  {0x77,0,3 },//A
  {0x7c,1,3 },//B
  {0x39,2,3 },//C 
  {0x5e,3,3 },//D
  {0x79,3,0 },//E
  {0x71,3,2 },//F
  
};

unsigned char keymap[4][4]={
  
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*'/*E*/,'0','#'/*F*/,'D'},
  
};

int key[2];

void keyIdent();
void sevenSegmentUpdate();

int main(){
  
  PORTA_init();//colomns
  PORTD_init();//rows
  PORTB_init();//7seg
  Configure_SysTick();//delay configuration
  while(1){
    //SysTick_Wait1ms(500);
    keyIdent();
    if(!((key[0]==4)&&(key[1]==4)))
      sevenSegmentUpdate();
  }
  
  return 0;
}

bool isAnyPressed(){

  if((GPIO_PORTA_DATA_R&(c1|c2|c3|c4))==0xf){
    //return true;
    return false;
  }
  else
    //return false;
    return true;
}

int whichCol(){

if(!((GPIO_PORTA_DATA_R&(c1))==0x0))
   return 0;
if(!((GPIO_PORTA_DATA_R&(c2))==0x0))
   return 1;
if(!((GPIO_PORTA_DATA_R&(c3))==0x0))
   return 2;
if(!((GPIO_PORTA_DATA_R&(c4))==0x0))
   return 3;
return 4;
}
      
void keyIdent(){
  
  int temp;
  GPIO_PORTD_DATA_R&=~(r1|r2|r3|r4);
  if(!isAnyPressed()){
    key[0]=4;
    key[1]=4;
    return;
  }

  GPIO_PORTD_DATA_R|=(r1|r2|r3|r4);
  GPIO_PORTD_DATA_R&=~(r1);
  temp=whichCol();
  if(!(temp==4)){
    key[0]=0;
    key[1]=temp;
    return;
  }
  
  GPIO_PORTD_DATA_R|=(r1|r2|r3|r4);
  GPIO_PORTD_DATA_R&=~(r2);
  temp=whichCol();
  if(!(temp==4)){
    key[0]=1;
    key[1]=temp;
    return;
  }
  
  GPIO_PORTD_DATA_R|=(r1|r2|r3|r4);
  GPIO_PORTD_DATA_R&=~(r3);
  temp=whichCol();
  if(!(temp==4)){
    key[0]=2;
    key[1]=temp;
    return;
  }
  
  GPIO_PORTD_DATA_R|=(r1|r2|r3|r4);
  GPIO_PORTD_DATA_R&=~(r4);
  temp=whichCol();
  if(!(temp==4)){
    key[0]=3;
    key[1]=temp;
    return;
  }
  
}

void sevenSegmentUpdate(){
  
  unsigned char  input[2];
  input[0] = *keymap[key[0]];
  input[1] = *keymap[key[1]];
  int index=0;
  for(int i=0;i<16;i++){
    if((input[0]==sevSeg[i][1])&&(input[1]==sevSeg[i][2])){
      index=i;
      break;
    }
  }
  GPIO_PORTB_DATA_R |= 0xff;
  GPIO_PORTB_DATA_R &= ~(sevSeg[index][0]);
}