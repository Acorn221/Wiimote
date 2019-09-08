# Wiimote Bluetooth Connection Library for Arduino core for ESP32

## Example

```WiimoteDemo.ino.cpp
#include <Wiimote.h>

void setup() {
  Serial.begin(115200);
  Wiimote::init();
  Wiimote::register_callback(1, wiimote_callback);
}

void loop() {
  Wiimote::handle();
}

void wiimote_callback(uint8_t number, uint8_t* data, size_t len) {
  Serial.printf("wiimote number=%d len=%d ", number, len);
  for (int i = 0; i < len; i++) {
    Serial.printf("%02X ", data[i]);
  }
  Serial.print("\n");
}

```

## See Also
- http://wiibrew.org/wiki/Wiimote
- http://www.yts.rdy.jp/pic/GB002/GB002.html
	- http://www.yts.rdy.jp/pic/GB002/hcip.html
	- http://www.yts.rdy.jp/pic/GB002/hcic.html
	- http://www.yts.rdy.jp/pic/GB002/l2cap.html
- https://qiita.com/jp-96/items/ff3822ab81f7696172c0
- https://www.wdic.org/w/WDIC/Bluetooth
	- https://www.wdic.org/w/WDIC/HCI%20%28Bluetooth%29
	- https://www.wdic.org/w/WDIC/L2CAP
