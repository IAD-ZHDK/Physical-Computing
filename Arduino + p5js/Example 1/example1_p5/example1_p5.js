/* jshint esversion: 8 */
let msg;
let serialOptions = { baudRate: 9600 };
let serial;
let clicked = false;
let bMsg = "OFF";
let fCol = 255;

function setup() {
  createCanvas(500, 500);
  background(255);
  
  // Setup Web Serial using serial.js
  serial = new Serial();
  serial.on(SerialEvents.CONNECTION_OPENED, onSerialConnectionOpened);
  serial.on(SerialEvents.CONNECTION_CLOSED, onSerialConnectionClosed);
  serial.on(SerialEvents.DATA_RECEIVED, onSerialDataReceived);
  serial.on(SerialEvents.ERROR_OCCURRED, onSerialErrorOccurred);

  //display messages and errors
  msg = createP('');
  
}

async function connectPort() {
  if (!serial.isOpen()) {
    await serial.connectAndOpen(null, serialOptions);
  } else {
    serial.autoConnectAndOpenPreviouslyApprovedPort(serialOptions);
  }
}

function draw() {

}

// Callback function by serial.js when there is an error on web serial
 function onSerialErrorOccurred(eventSender, error) {
  console.log("onSerialErrorOccurred", error);
  msg.html(error);
}

// Callback function by serial.js when web serial connection is opened

function onSerialConnectionOpened(eventSender) {
  console.log("onSerialConnectionOpened");
  msg.html("Serial connection opened successfully");
}

// Callback function by serial.js when web serial connection is closed

function onSerialConnectionClosed(eventSender) {
  console.log("onSerialConnectionClosed");
  msg.html("onSerialConnectionClosed");
}

//Callback function serial.js when new web serial data is received
 
function onSerialDataReceived(eventSender, newData) {
  console.log("onSerialDataReceived", newData);
  msg.html("onSerialDataReceived: " + newData);
}
 
async function serialWriteTextData() {
  const data = ["104, 0, 222, 15, 0, '\n'"]; 
  if (serial.isOpen()) {
    console.log("Writing to serial: ", data);
    serial.writeLine(data);
  }
}

//ALTERNATIVE METHOD FOR SENDING DATA WITH START "<" AND END  ">" MARKERS
/*
async function serialWriteTextData() {
  const data = new Uint8Array([14, 201, 108, 255, 11]); 

  if (serial.isOpen()) {
    console.log("Writing to serial: ", data);
    serial.writeLine("<" + data + ">");
  }
}
 */
