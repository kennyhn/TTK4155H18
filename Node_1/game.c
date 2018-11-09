#include "game.h"
#include "can.h"
#include "oled.h"
#include "uart.h"
#include "sram.h"

void play_game(void){
  uint8_t x0 = 8;
  uint8_t y0 = 8;
  uint8_t r0 = 8;



  uint8_t x1 = 24;
  uint8_t y1 = 24;
  uint8_t r1 = 6;

  uint8_t x2 = 40;
  uint8_t y2 = 40;
  uint8_t r2 = 6;

  uint8_t x3 = 56;
  uint8_t y3 = 56;
  uint8_t r3 = 6;
  while(1){
    if (can_message_received){
      can_message_received = 0;
      break;
    }
    printf("kommer hit %d\n",x1);
    SRAM_OLED_reset();
    draw_circle(x0,y0,r0);
    draw_line(x0-2,x0+2, y0+2, y0+2);
    draw_line(x0+1,x0+2, y0-2,y0-2);
    draw_line(x0-2,x0-1, y0-2,y0-2);
    draw_circle(x1,y1,r1);
    draw_circle(x2,y2,r2);
    draw_circle(x3,y3,r3);

    send_console_message();
    x0+=3;
    x1+=3;
    x2+=3;
    x3+=3;

    if (x0 >= 120){
      x0 = 8;
    }
    if (x1 >= 120){
      x1 = 8;
    }
    if (x2 >= 120){
      x2 = 8;
    }
    if (x3 >= 120){
      x3 = 8;
    }
  }

}
