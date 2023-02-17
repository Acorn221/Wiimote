#include "ScanDevices.h"

// ScanDevices constructor
ScanDevices::ScanDevices() {
	scanned_device_list_size = 0;
	searchForManufacturer = false;
}

/**
 * @brief Find a device in the scanned device list
 * 
 * @param bd_addr 
 * @return int The index of the device in the scanned device list
 */
int ScanDevices::scanned_device_find(struct bd_addr_t* bd_addr) {
  for (int i = 0; i < scanned_device_list_size; i++) {
    scanned_device_t* c = &scanned_device_list[i];
    if (memcmp(&bd_addr->addr, c->bd_addr.addr, BD_ADDR_LEN) == 0) {
      return i;
    }
  }
  return -1;
}

/**
 * @brief Add a device to the scanned device list, when it is discovered
 * 
 * @param scanned_device 
 * @return int 
 */
int ScanDevices::scanned_device_add(struct scanned_device_t scanned_device) {
  if (SCANNED_DEVICE_LIST_SIZE == scanned_device_list_size) {
    return -1;
  }

	if(searchForManufacturer) {
		log_d("No target manufacturer set, adding device to list");
		scanned_device_list[scanned_device_list_size++] = scanned_device;

	} else {
		bool foundManu = false;
		// creating a temp variable to iterate through the linked list
		manufacturer_t curr = target_manufacturers;
		
		// Check the manufacturer of the device
		while(curr.next != NULL) {
			if(memcmp(&scanned_device.bd_addr.addr, curr.manufacturer, 3) == 0) {
				log_d("Found device from target manufacturer, adding device to list");
				scanned_device_list[scanned_device_list_size++] = scanned_device;
				foundManu = true;
				break;
			}
			curr = *curr.next;
		}
		if(!foundManu) log_d("Device not from target manufacturer, not adding to list");
	}
  return scanned_device_list_size;
}

void ScanDevices::scanned_device_clear(void) {
  scanned_device_list_size = 0;
	log_d("Scanned device list cleared");
}

void ScanDevices::clear_target_manufacturer(void) {
	searchForManufacturer = false;
	log_d("Target manufacturer cleared");
}

void ScanDevices::set_target_manufacturer(struct manufacturer_t manu) {
	target_manufacturers = manu;
	searchForManufacturer = true;
	log_d("Target manufacturer set");
	while(manu.next != NULL) {
		manu = *manu.next;
		log_d("Target manufacturer set: %02X:%02X:%02X", manu.manufacturer[0], manu.manufacturer[1], manu.manufacturer[2]);
	}
}
/**
 * @brief Scan for devices
 * 
 * @param scan whether to start or stop scanning
 * @return true 
 * @return false 
 */
bool ScanDevices::scan_for_devices (bool scan) {
		if(scan){
			// Clear the scanned device list
			scanned_device_clear();
			// Start scanning
			uint8_t timeout = 10; //0x30;
			uint16_t len = make_cmd_inquiry(*tmp_data, 0x9E8B33, timeout, 0x00);
			if(_queue_data(_tx_queue, tmp_data, len) != ESP_OK){
				log_d("Error sending inquiry command on ScanDevices");
				return false;
			} else {
				log_d("Scanning for %d seconds", timeout);
				return true;
			}
		} else {
			uint16_t len = make_cmd_inquiry_cancel(tmp_data);
  		_queue_data(_tx_queue, tmp_data, len); // TODO: check return
		}

}

