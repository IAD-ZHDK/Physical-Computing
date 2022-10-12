/* jshint esversion: 8 */

let serial; // the Serial object
let serialOptions = { baudRate:9600 };
let col;
let dn = "DAY";
let buttonConnect,buttonDisconnect;

function setup() {
  createCanvas(400, 400);
  background(200);
  // Setup Web Serial using serial.js
  serial = new Serial();
  serial.on(SerialEvents.CONNECTION_OPENED, onSerialConnectionOpened);
  serial.on(SerialEvents.CONNECTION_CLOSED, onSerialConnectionClosed);
  serial.on(SerialEvents.DATA_RECEIVED, onSerialDataReceived);
  serial.on(SerialEvents.ERROR_OCCURRED, onSerialErrorOccurred);
 
  // Add in a lil <p> element to provide messages. This is optional
  msg = createP("");
  col = color(255,250,205);
  textSize(100);
  textAlign(CENTER, CENTER);
  textFont("Roboto");
  
  buttonConnect = createButton('Connect Port');
  buttonConnect.position(20,20);
  buttonConnect.mousePressed(connectPort);
  
  buttonDisconnect = createButton('Disonnect Port');
  buttonDisconnect.position(150,20);
  buttonDisconnect.mousePressed(disconnectPort);
}

async function connectPort() {
  if (!serial.isOpen()) {
    await serial.connectAndOpen(null, serialOptions);
  } else {
    serial.autoConnectAndOpenPreviouslyApprovedPort(serialOptions);
  }
}

async function disconnectPort() {
  if (serial.isOpen()) {
    serial.close();
  }
}

function draw() {
  background(200);
  fill(col);
  text(dn, width/2, height/2);
  
}

function onSerialErrorOccurred(eventSender, error) {
  console.log("onSerialErrorOccurred", error);
}

function onSerialConnectionOpened(eventSender) {
  console.log("onSerialConnectionOpened");
}

function onSerialConnectionClosed(eventSender) {
  console.log("onSerialConnectionClosed");
}

function onSerialDataReceived(eventSender, newData) {
  let potVal = int(newData);
  msg.html("onSerialDataReceived: " + potVal);
  console.log("Received data from Arduino: " +potVal);
  
  if(potVal==1) {
    col = color(255,250,205);
    dn = "DAY";
  } else {
    col = color(0,0,200);
    dn = "NIGHT";
  }
  
}
