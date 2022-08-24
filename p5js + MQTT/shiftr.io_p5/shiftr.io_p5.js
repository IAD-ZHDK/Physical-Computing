
// MQTT client details:
let broker = {
    hostname: '',
    port: 443
};

// MQTT client:
let client;

// client credentials:
// For shiftr.io type in both username and password

let creds = {
    clientID: '',
    userName: '',
    password: ''
}

// topic to subscribe to when you connect
// For shiftr.io, use whatever word you want 
let topicPosition = 'pos';
let topic = 'values';
let topic2 = 'ledBlink';


// position of the circle
let xPos, yPos;

//button click
let clicked = false;

let lastTimeSent = 0;
const sendInterval = 100;

function setup() {
    createCanvas(400, 400);
    // Create an MQTT client:
    client = new Paho.MQTT.Client(broker.hostname, broker.port, creds.clientID);
    // set callback handlers for the client:
    client.onConnectionLost = onConnectionLost;
    client.onMessageArrived = onMessageArrived;
    // connect to the MQTT broker:
    client.connect(
        {
            onSuccess: onConnect,       // callback function for when you connect
            userName: creds.userName,   // username
            password: creds.password,   // password
            useSSL: true   // use SSL
        }
    );
    // create a div for local messages:
    localMsg = createP("Local message");
    localMsg.position(20, 50);

    // create a div for the response:
    remoteMsg =  createP("Waiting for message"); 
    remoteMsg.position(20, 80);

    xPos = width/2;
    yPos = height/2;
}

function draw() {
    background(255);
    noStroke();
    // draw a circle when a message is received:
    fill(0);
    // circle moves with the message:
    circle(xPos, yPos, 30);
    
    if (millis() - lastTimeSent > sendInterval) {
        sendRandomMsg();
        lastTimeSent = millis();
    }
    
    
}

// called when the client connects
function onConnect() {
    localMsg.html('client is connected');
    client.subscribe(topicPosition);
}

// called when the client loses its connection
function onConnectionLost(response) {
    if (response.errorCode !== 0) {
        console.log(response.errorMessage);
        localMsg.html('onConnectionLost:' + response.errorMessage);
    }
}

// called when a message arrives
function onMessageArrived(message) {
    remoteMsg.html(message.payloadString);
    
    // assume the message payload is a JSON object  {"x":xPos, "y":yPos}
    // parse it and use the X and Y:
    var acc = JSON.parse(message.payloadString);
    xPos = acc.x;
    yPos = acc.y;
     
    
}

// called when you want to send a message:
function sendMqttMessage(msg, tpc) {
    // if the client is connected to the MQTT broker:
    if (client.isConnected()) {
        // start an MQTT message:
        message = new Paho.MQTT.Message(JSON.stringify(msg));
        // choose the destination topic:
        message.destinationName = tpc;
        // send it:
        client.send(message);
        // print what you sent:
        localMsg.html('I sent: ' + message.payloadString);
    }
}

// called when you want to send a message
function sendRandomMsg(){
    let r = floor(random(0, 4));
    switch (r) {
      case(0):
        sendMqttMessage("I", topic);
        break;
      case(1):
        sendMqttMessage("A", topic);
        break;
      case(2):
        sendMqttMessage("D", topic);
        break;
    }
  }
  
function sendBlink() {
  if(clicked){
    sendMqttMessage(0, topic2);
  } else {
    sendMqttMessage(1, topic2);
  }
  clicked = !clicked;
}
  
  
