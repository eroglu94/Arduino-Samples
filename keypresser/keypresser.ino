#include <oddebug.h>
#include <usbconfig-prototype.h>
#include <usbconfig.h>
#include <usbdrv.h>
#include <UsbKeyboard.h>
#include <usbportability.h>

// Derived from this project
// http://www.practicalarduino.com/projects/virtual-usb-keyboard

// Requires the use of the "UsbKeyboard" library available from
// http://code.google.com/p/vusb-for-arduino/


long counter = 0;

void setup()
{
  // Disable timer0 since it can mess with the USB timing. Note that
  // this means some functions such as delay() will no longer work.
  TIMSK0&=!(1<<TOIE0);

  // Clear interrupts while performing time-critical operations
  cli();

  // Force re-enumeration so the host will detect us
  usbDeviceDisconnect();
  delayMs(250);
  usbDeviceConnect();

  // Set interrupts again
  sei();

  //initialization period....
  for (int initCounter = 0; initCounter < 100; initCounter++)  {
    delayMs(2);
    UsbKeyboard.update();
  }
}

void loop()
{
  UsbKeyboard.update();
  delayMs(100);
  UsbKeyboard.sendKeyStroke(KEY_X);
}

// Define our own delay function so that we don't have to rely on
// operation of timer0, the interrupt used by the internal delay()
void delayMs(unsigned int ms)
{
  for (int i = 0; i < ms; i++) {
    delayMicroseconds(1000);
  }
}
