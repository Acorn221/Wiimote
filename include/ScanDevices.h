#include "setup.h"

/**
 * @brief Scanned device list
 * All the scanned devices are stored in this list
 */
struct scanned_device_t {
  bd_addr_t bd_addr;
  uint8_t psrm;
  uint16_t clkofs;
};

/**
 * @brief Manufacturer MAC address start 
 * This is to filter out the devices that are not from the target manufacturer
 */
struct manufacturer_t {
	uint8_t manufacturer[3];
	manufacturer_t *next;
};

/**
 * @brief Scanned device list class
 * This class is used to store the scanned devices
 * and to scan for said devices
 */
class ScanDevices {
	public:
		ScanDevices();
		int scanned_device_find(struct bd_addr_t* bd_addr);
		int scanned_device_add(struct scanned_device_t scanned_device);
		void scanned_device_clear(void);
		void set_target_manufacturer(struct manufacturer_t manu);
		bool scan_for_devices(bool scan);
	private:
		int scanned_device_list_size;
		static const int SCANNED_DEVICE_LIST_SIZE = 16;
		scanned_device_t scanned_device_list[SCANNED_DEVICE_LIST_SIZE];
		char tmp_data[256];
		_tx_queue_t *_tx_queue;
};