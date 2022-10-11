/* jshint esversion: 8 */

let shapeFraction = 0; // tracks the new shape fraction off serial
let shape = 0; // tracks the new shape 
let serial; // the Serial object
let serialOptions = { baudRate: 9600 };

function setup() {
  createCanvas(400, 400);
  background(0);
  
  // Setup Web Serial using serial.js
  serial = new Serial();
  serial.on(SerialEvents.CONNECTION_OPENED, onSerialConnectionOpened);
  serial.on(SerialEvents.CONNECTION_CLOSED, onSerialConnectionClosed);
  serial.on(SerialEvents.DATA_RECEIVED, onSerialDataReceived);
  serial.on(SerialEvents.ERROR_OCCURRED, onSerialErrorOccurred);

  // Add in a lil <p> element to provide messages. This is optional
  msg = createP("");
}

async function connectPort() {
  if (!serial.isOpen()) {
    await serial.connectAndOpen(null, serialOptions);
  } else {
    serial.autoConnectAndOpenPreviouslyApprovedPort(serialOptions);
  }
}

function draw() {
  background(0);
  fill(255);
 
  const maxDiameter = min(width, height);
  let shapeDiameter = maxDiameter * shapeFraction;

  switch (shape) {
    case(0):
    circle(width / 2, height/2, shapeDiameter, 0, width);
    break;
    
    case(1):
    rectMode(CENTER);
    square(width / 2, height/2, shapeDiameter);
    break;
    
    case(2):
    translate(width/2, height/2);
    scale(shapeDiameter/width);
    triangle(0, -height/4, -width/4, height/4, width/4, height/4);
    break;
    
    case(3):
    stroke(255);
    strokeWeight(10);
    line(width / 2 - shapeDiameter, height/2 - shapeDiameter, width / 2 + shapeDiameter, height/2 + shapeDiameter, );
  }
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
  msg.html("onSerialDataReceived: " + newData);

  // split incoming string by commma
  if (newData.length != 0) {

    // returns the index of comma
    const indexOfComma = newData.indexOf(",");
    console.log(indexOfComma);

    // if comma is present in the string
    if (indexOfComma != -1) {
      let strDiameter = newData.substring(0, indexOfComma).trim();
      let strOutline = newData.substring(indexOfComma + 1, newData.length).trim();
      shapeFraction = parseFloat(strDiameter);
      shape = parseInt(strOutline);
    }
  }
  
  // another way of splitting incoming string by commma
  //if (newData.length != 0) {
  //  var values = newData.split(',');
  //  let strDiameter = values[0];
  //  let strOutline = values[values.length - 1];
  //  shapeFraction = parseFloat(strDiameter);
  //  shape = parseInt(strOutline);
    
  //}
}