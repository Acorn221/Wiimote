#include "setup.h"

struct l2cap_connection_t {
  uint16_t connection_handle;
  uint16_t psm;
  uint16_t local_cid;
  uint16_t remote_cid;
};