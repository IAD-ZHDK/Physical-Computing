let msg;
let serialOptions = { baudRate: 9600 };
let serial;
let bMsg = "OFF";
let input;
let buttonConnect,buttonDisconnect,buttonOnOff, buttonSend;
let clicked = false;

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
  
  buttonConnect = createButton('Connect Port');
  buttonConnect.position(20,20);
  buttonConnect.mousePressed(connectPort);
  
  buttonDisconnect = createButton('Disonnect Port');
  buttonDisconnect.position(150,20);
  buttonDisconnect.mousePressed(disconnectPort);
 
  input = createInput("255,32,80,111,0");
  input.position(20, 65);
  buttonSend = createButton('Send2Arduino');
  buttonSend.position(input.x + input.width, 65);
  buttonSend.mousePressed(serialWriteTextData);
  
  buttonOnOff = createButton('Switch');
  buttonOnOff.position(20,100);
  buttonOnOff.mousePressed(onOff);
  
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
 
function serialWriteTextData() {
  const inputData = input.value();

  let splitData = split(inputData, ',');
  console.log(splitData.length);
  
  if (splitData.length > 5) {
     splitData = splitData.splice(0,4); 
  }
  //'\n' is used as "end of line" character
  // it is imporant to add at the end of array so that Arduino knows that the received message is finished
  splitData.push("'\n'");

  if (serial.isOpen() ) {
    console.log("Writing array to serial: ", splitData);
    serial.writeLine(splitData);
  }
}

function onOff(){
   if (serial.isOpen() ) {
     
     if(clicked == true){
       clicked = false;
       switcher = ["off", '\n'];
     }else{
       clicked = true;
       switcher = ["on", '\n'];
     }
   
    console.log("Writing switch to serial: ", switcher);
    serial.writeLine(switcher);
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
