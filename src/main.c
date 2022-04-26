#include "simba.h"

int main() {
  struct uart_driver_t uart;

  sys_start();
  console_module_init();
  uart_module_init();
  uart_init(&uart, &uart_device[0], 115200, NULL, 0);
  uart_start(&uart);
  sys_set_stdout(&uart.chout);

  esp_wifi_set_op_mode(esp_wifi_op_mode_station_t);
  if (esp_wifi_station_init("TOP", "SECRET", NULL, NULL) != 0) {
    std_printf(OSTR("Failed to configure station.\r\n"));
  }

  esp_wifi_station_connect();

  while (1) {
    esp_wifi_print(sys_get_stdout());
    thrd_sleep(2);
  }

  return 0;
}
