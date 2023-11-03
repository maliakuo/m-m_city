/*
This program prints out Serial data to be read in by ESP32
in order to trigger motor movement.

*/

// GPIO Pins 19, 18, 5, 17


// evaluate to find the name of your arduino
SerialPort.listDevices;
// see post window

// make sure serial monitor is not open in arduino IDE
// then open port
(
~port = SerialPort(
	"/dev/cu.usbserial-10", // your arduino's name
	baudrate: 9600, // must match arduino rate
	crtscts: true
);
)

// send to arduino
// maximum brightness
~port.put(255);

// minimum
~port.put(0);

// random flicker
r = Routine { loop { ~port.put(1.exprand(255)); 0.3.wait } }.play;

// stop
r.stop;

// close before quitting
~port.close;