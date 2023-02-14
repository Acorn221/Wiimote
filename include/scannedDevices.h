#include "setup.h"

/**
 * Scanned device list
 */

struct scanned_device_t {
  bd_addr_t bd_addr;
  uint8_t psrm;
  uint16_t clkofs;
};

static int scanned_device_list_size = 0;
#define SCANNED_DEVICE_LIST_SIZE 16
static scanned_device_t scanned_device_list[SCANNED_DEVICE_LIST_SIZE];
static int scanned_device_find(struct bd_addr_t* bd_addr) {
  for (int i = 0; i < scanned_device_list_size; i++) {
    scanned_device_t* c = &scanned_device_list[i];
    if (memcmp(&bd_addr->addr, c->bd_addr.addr, BD_ADDR_LEN) == 0) {
      return i;
    }
  }
  return -1;
}

static int scanned_device_add(struct scanned_device_t scanned_device) {
  if (SCANNED_DEVICE_LIST_SIZE == scanned_device_list_size) {
    return -1;
  }
  scanned_device_list[scanned_device_list_size++] = scanned_device;
  return scanned_device_list_size;
}

static void scanned_device_clear(void) {
  scanned_device_list_size = 0;
}
