#include <16f877a.h> 
#device ADC=10
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD
#use delay (clock=4000000)
#use fast_io(e)
#use fast_io(d)
#define use_portb_lcd TRUE 

#include <lcd.c> 
unsigned long int bilgi;
float voltaj,volta,sonuc;

void main ( )
{
   setup_psp(PSP_DISABLED);     
   setup_timer_1(T1_DISABLED);   
   setup_timer_2(T2_DISABLED,0,1);
   setup_CCP1(CCP_OFF);         
   setup_CCP2(CCP_OFF);         

   set_tris_a(0xFF);
   set_tris_c(0x00);

   setup_adc(adc_clock_div_32); 
   setup_adc_ports(ALL_ANALOG); 
   enable_interrupts(INT_AD);   
   enable_interrupts(GLOBAL);   

   lcd_init();                         

   while(true) 
   {
      set_adc_channel(0); 
      delay_us(20);       
      bilgi=read_adc();   
      voltaj=0.0048828125*bilgi*100;
   
      set_adc_channel(1); 
      delay_us(20);       
      bilgi=read_adc(); 
      volta=0.0048828125*bilgi*100; 
   
     sonuc=voltaj-volta;

     printf(lcd_putc,"\nDerece=%f C",sonuc);
   
     if(sonuc >= -11.0)
      {
      output_high(pin_b3);
      }
      else
      {
      output_low(pin_b3);
      }
   
     delay_ms(1000);
   }
}
