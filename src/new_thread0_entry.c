#include "new_thread0.h"
#include "ec_master.h"
#include "shell.h"

/* New Thread entry function */
/* pvParameters contains TaskHandle_t */
void new_thread0_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    /* TODO: add your own code here */
    EC_LOG_INFO("Hello CherryECAT!\r\n");
    int shell_init(const uart_instance_t *shell_uart, bool need_login);
    shell_init(&g_uart9, false);
    extern void cherryecat_thread_create(void);
    cherryecat_thread_create();
    while (1)
    {
        vTaskDelay (1);
    }
}
