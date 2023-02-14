#include "setup.h"


/**
 * Queue
 */
typedef struct {
  size_t len;
  uint8_t data[];
} lendata_t;


static xQueueHandle _rx_queue = NULL;
static xQueueHandle _tx_queue = NULL;

static esp_err_t _queue_data(xQueueHandle queue, uint8_t* data, size_t len) {
  if (!data || !len) {
    log_w("No data provided");
    return ESP_OK;
  }
  lendata_t* lendata = (lendata_t*)malloc(sizeof(lendata_t) + len);
  if (!lendata) {
    log_e("lendata Malloc Failed!");
    return ESP_FAIL;
  }
  lendata->len = len;
  memcpy(lendata->data, data, len);
  if (xQueueSend(queue, &lendata, portMAX_DELAY) != pdPASS) {
    log_e("xQueueSend failed");
    free(lendata);
    return ESP_FAIL;
  }
  return ESP_OK;
}

/**
 * Utils
 */
static char formatHexBuffer[FORMAT_HEX_MAX_BYTES * 3 + 3 + 1];

static char* formatHex(uint8_t* data, uint16_t len) {
  for (uint16_t i = 0; i < len && i < FORMAT_HEX_MAX_BYTES; i++) {
    sprintf(formatHexBuffer + 3 * i, "%02X ", data[i]);
  }
  if (FORMAT_HEX_MAX_BYTES < len) {
    sprintf(formatHexBuffer + 3 * FORMAT_HEX_MAX_BYTES, "...");
  }
  return formatHexBuffer;
}
