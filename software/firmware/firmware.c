#include "system.h"
#include "periphs.h"
#include "iob-uart.h"
#include "iob_timer.h"
#include <time.h>

int main()
{
  unsigned long long elapsed;
  unsigned int elapsedu;

  //init timer and uart
  timer_init(TIMER_BASE);
  uart_init(UART_BASE, FREQ/BAUD);

  uart_printf("\nHello world!\n");
 
  long int numero[100];
  int i;
  srand(time(0));

  for(i=0;i<100;i++)
  {
	numero[i] = rand();
	uart_printf("%d \n ", numero[i]);
	if (i!=0)
		numero[i]=numero[i-1]+numero[i];
  }

  uart_txwait();

  //read current timer count, compute elapsed time
  elapsed  = timer_get_count(TIMER_BASE);
  elapsedu = timer_time_us(TIMER_BASE);

  uart_printf("\nExecution time: %d clock cycles\n", (unsigned int) elapsed);
  uart_printf("\nExecution time: %dus @%dMHz\n\n", elapsedu, FREQ/1000000);

  uart_txwait();
}
