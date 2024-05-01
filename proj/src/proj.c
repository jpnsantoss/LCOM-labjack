#include <lcom/lcf.h>
#include "labjack.h"
#include "dvr_graphics.h"
#include "io.h"

// Any header files included below this line should have been created by you

int main(int argc, char *argv[])
{
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/src/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int counter = 0;
extern uint8_t scancode;
extern int output;

int (move_xpm_mouse)(xpm_map_t xpm, uint16_t x, uint16_t y)
{
	uint8_t bit_no = 0;
	int ipc_status, r;
	message msg;
	struct packet pp;
	int bytes[3];
	int index = 0;
	t_gph gph = vg_get_info();

	if (kbc_write(0xF4, true))
		return 1;

	if (mouse_subscribe_int(&bit_no))
		return 1;

	int count = 0;
    while (count < 1000)
	{
    	if (driver_receive(ANY, &msg, &ipc_status)) continue;

    	if (!is_ipc_notify(ipc_status)) continue;

		if (_ENDPOINT_P(msg.m_source) != HARDWARE) continue;

    	if (!(msg.m_notify.interrupts & bit_no)) continue;
      	
		count++;
		mouse_ih();

		if (index == 0 && (output & BIT(3)))
		{
			bytes[index] = output;
			index++;
		}
		else if (index > 0)
		{
			bytes[index] = output;
			index++;
		}
		if (index == 3)
		{
			mouse_fill_packet(bytes, &pp);
			mouse_print_packet(&pp);
			
			x += pp.delta_x;
      		y -= pp.delta_y;

      		if (x < 0 || x > gph.x_res) {
        		x = 0;
        		break;
      		}

      		if (y < 0 || y > gph.y_res) {
        		y = 0;
        		break;
      		}

      		vg_clear_screen();
      		if (vg_print_xpm(xpm, x, y)) return 1;
		
			index = 0;
		}
	}
}

//chamado pela lcom_run
int (proj_main_loop)(int argc, char **argv)
{
	if (vg_map_memory(0x105)) return 1;
	if (vg_enter_graphic_mode(0x105)) return 1;
  	
	if(print_xpm(penguin, 56, 76)) return 1
 	sleep(1);
    
    // Mover a imagem com o mouse
    if (move_xpm_mouse(penguin, 50, 50)) return 1;
  	return vg_exit();
}
