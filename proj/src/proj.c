#include <lcom/lcf.h>
#include "labjack.h"

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

//chamado pela lcom_run
int (proj_main_loop)(int argc, char **argv)
{
	return game_loop();
	/*queue_t *queue = queue_create(2);
	queue_push(queue, strdup("a"));
	queue_push(queue, strdup("b"));
	printf("%s\n", queue_at(queue, 0));
	printf("%s\n", queue_at(queue, 1));
	queue_pop(queue);
	printf("%s\n", queue_at(queue, 0));
	queue_push(queue, strdup("c"));
	printf("%s\n", queue_at(queue, 0));
	printf("%s\n", queue_at(queue, 1));*/
	return 0;
}
