#include<reg52.h>			//P1^5,P1^6,P1^7 are connected to phases by converting r y b to dc 5v individually.
#include<string.h>

#define lcd_data P2

sbit  lcd_rs   =  P2^0;  
sbit  lcd_en   =  P2^1;

sbit sw1=P1^0;
sbit sw2=P1^1;
sbit sw3=P1^2;

sbit on=P1^3;

sbit sw4=P3^0;
sbit sw5=P3^1;
sbit sw6=P3^2;

sbit re=P1^7;
sbit buz=P1^6;

void delay(unsigned int v)
{
unsigned int i,j;
for(i=0;i<=v;i++)
for(j=0;j<=275;j++);	 
}
		
void MSDelay(unsigned int value)
{
unsigned int x,y;
for(x=0;x<1275;x++)
for(y=0;y<value;y++);
}

void lcdcmd(unsigned char value)		   // LCD COMMAND
  {
       
	 lcd_data=value&(0xf0); //send msb 4 bits
      lcd_rs=0;	  //select command register
      lcd_en=1;	  //enable the lcd to execute command
	  delay(3);
	  lcd_en=0;  
      lcd_data=((value<<4)&(0xf0));	 //send lsb 4 bits
      lcd_rs=0;	 //select command register
      lcd_en=1;	 //enable the lcd to execute command
	  delay(3);
	  lcd_en=0;  
      
  }  

void lcd_init(void)
{
 lcdcmd(0x02);	
 lcdcmd(0x02);
 lcdcmd(0x28);  //intialise the lcd in 4 bit mode*/
 lcdcmd(0x28);  //intialise the lcd in 4 bit mode*/
 
 lcdcmd(0x0e);	//cursor blinking
 lcdcmd(0x06);	//move the cursor to right side
 lcdcmd(0x01);	//clear the lcd

}	

void lcddata(unsigned char value)

  {
       
      lcd_data=value&(0xf0); //send msb 4 bits
      lcd_rs=1;	  //select data register
      lcd_en=1;	  //enable the lcd to execute data
	  delay(3);
	  lcd_en=0;  
      lcd_data=((value<<4)&(0xf0));	 //send lsb 4 bits
      lcd_rs=1;	  //select data register
      lcd_en=1;	  //enable the lcd to execute data
	  delay(3);
	  lcd_en=0;  
      
     delay(3); 
  }  



void msgdisplay(unsigned char b[]) // send string to lcd
  {
unsigned char s,count=0;
for(s=0;b[s]!='\0';s++)
 {
  count++;	 
  if(s==16)
   lcdcmd(0xc0);
   if(s==32)
   {
   lcdcmd(1);
   count=0;
   }
  lcddata(b[s]);
 }
}


void main(void)
{		
	on=1;   
   sw1=sw2=sw3=1;
   sw4=sw5=sw6=1;
   re=1;
   buz=1;
 
  lcd_init();
				 //EMERGENCYALERT FORWOMEN SAFETY USING GSM & GPS
 msgdisplay("WELCOME"); //83
  			  delay(100);
 
  			 lcdcmd(1);					  msgdisplay("WATER LEVEL INDICATOR"); delay(800);
		lcdcmd(1);	 lcdcmd(0x0C);//	msgdisplay("WATER LEVEL");
		lcdcmd(0x80);	msgdisplay("OH TANK:");
		lcdcmd(0xC0);	msgdisplay("UG TANK:");
while(1)
 {
		//TURN ON MOTOR	//
	
 ////////////	overhead start	////////////
 // level full indicator OVERHEAD 	//			
  
  if(on==0){	
  // if( sw1==0 && sw2==0 && sw3==0){
	if( sw1==0 && sw2==0){ 
	 lcdcmd(0x88);	 msgdisplay("FULL   "); delay(100); 
	 re=1; buz=0; 
  }

// level full indicator OVERHEAD	//			 
 //if( sw1==1 && sw2==0 && sw3==0){
 if( sw1==1 && sw2==0){
	 lcdcmd(0x88);	 msgdisplay("MEDIUM"); delay(100);  
	 re=0;
	  buz=1;
  }

 // if( sw1==1 && sw2==1 && sw3==1){
//	 lcdcmd(0x88);	 msgdisplay("LOW   "); delay(100);  
	// re=0;
	// buz=1;
  //}
 		  
// level full indicator GROUND 	//	
 		
  if(sw4==0 && sw5==0 && sw6==0){
	 
	 lcdcmd(0xC8);	 msgdisplay("FULL   "); delay(100); 
	 re=0; buz=1; 
  }

// level full indicator GROUND	//			 
  if(sw4==1 && sw5==0 && sw6==0){
	 lcdcmd(0xC8);	 msgdisplay("MEDIUM"); delay(100);  
	 re=0; buz=1;
  }

// level full indicator GROUND	//			
	if(sw4==1 && sw5==1 && sw6==0){
	 lcdcmd(0xC8);	 msgdisplay("LOW   "); delay(100);  
	 re=1;	 buz=0;
  }

 }
 
}
} 															