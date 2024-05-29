#include "com_manager.h"

int com_manager_init(app_t *app)
{
	manager = (com_manager_t *) malloc(sizeof(com_manager_t));
	if (manager == NULL) return 1;

	manager->app = app;
	manager->current_ev = NO_EVENT;
	manager->status = WAITING;

	manager->queries = queue_create(20);
	if (manager->queries == NULL)
	{
		free(manager);
		return 1;
	}

	return 0;
}

int com_query_and_timeout(uint8_t msg, uint32_t timeout, void (*onTimeout)(uint8_t, app_t *))
{
	if (manager == NULL || manager->queries == NULL) return 1;

	com_query_t *query = (com_query_t *) malloc(sizeof(com_query_t));
	if (query == NULL) return 1;

	query->msg = msg;
	query->timeout = timeout;
	query->current_timeout = 0;
	query->executed = 0;
	query->onTimeout = timeout;

	if (timeout == 0)
	{
		onTimeout(true, manager->app);
		free(query);
		return 0;
	}

	return queue_push(manager->queries, query);
}

int com_check_timeout()
{
	if (manager == NULL || manager->queries == NULL) return 1;

	for (size_t i = 0; i < manager->queries->curr_size; i++)
	{
		com_query_t *query = queue_at(manager->queries, i);
		if (query == NULL || query->executed) continue;

		
	}
}
