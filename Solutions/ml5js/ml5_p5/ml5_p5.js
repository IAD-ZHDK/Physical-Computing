/* jshint esversion: 8 */

let video;
// Create a KNN classifier
const knnClassifier = ml5.KNNClassifier();
let handPose; 
let poses = [];

let classificationResult = "";
let allowedToPredict = false;
let handPoseModelReady = false;

let serialOptions = { baudRate: 9600};
let serial;

let timestampLastTransmit = 0;
const MIN_TIME_BETWEEN_TRANSMISSIONS_MS = 500;

async function connectPort() {
  if (!serial.isOpen()) {
    await serial.connectAndOpen(null, serialOptions);
  } else {
    serial.autoConnectAndOpenPreviouslyApprovedPort(serialOptions);
  }
}

function setup() {
  const canvas = createCanvas(640, 480);
  canvas.parent('videoContainer');
  video = createCapture(VIDEO);
  video.size(width, height);

  // Create the UI buttons
  createButtons();
  
  
  // Setup Web Serial using serial.js
  serial = new Serial();
  serial.on(SerialEvents.CONNECTION_OPENED, onSerialConnectionOpened);
  serial.on(SerialEvents.CONNECTION_CLOSED, onSerialConnectionClosed);
  serial.on(SerialEvents.DATA_RECEIVED, onSerialDataReceived);
  serial.on(SerialEvents.ERROR_OCCURRED, onSerialErrorOccurred);

  // If we have previously approved ports, attempt to connect with them
  serial.autoConnectAndOpenPreviouslyApprovedPort(serialOptions);

  // Create a new handpose method with a single detection
  handPose = ml5.handpose(video, modelReady);
  // This sets up an event that fills the global variable "poses"
  // with an array every time new poses are detected
  handPose.on('predict', function(results) {
    poses = results;
  });
  // Hide the video element, and just show the canvas
  video.hide();
}

function draw() {
  image(video, 0, 0, width, height);


  if (!handPoseModelReady) {
    textSize(32);
    textAlign(CENTER);
    fill(255);
    noStroke();
    select('#status').html('Waiting for handPose model to load..."');
    
  }
  
  // We can call both functions to draw all keypoints and the skeletons
  drawKeypoints();
  
  fill(0,0,0);
  textSize(64);
  //text(classificationResult, width/2, height/2);
  
  if (classificationResult == "One") {
    text("One", width/2, height/2);
  } else if (classificationResult == "Two") {
    text("Two", width/2, height/2);
  } else if (classificationResult == "Three"){
    text("Three", width/2, height/2);
  }else if (classificationResult == "Four"){
    text("Four", width/2, height/2);
  } else {
    text("Five", width/2, height/2);
  }
  
  
  if (poses.length>0 && allowedToPredict) {
    if (frameCount % 200 == 0) {
      classify(); 
    }
  }
}

function modelReady(){
  select('#status').html('Model Loaded');
  handPoseModelReady = true;
}

// Add the current frame from the video to the classifier
function addExample(label) {
  if(poses.length > 0){
    for (let i = 0; i < poses.length; i += 1) {
      const landmarks = poses[0].landmarks;
    //We then need to adjust these labels before we can fed them into our classifier. 
    //We therefore use the map() method, which takes out the x and y position of every element in our Array landmarks 
    //and writes them in our new array predictionArray.
      const predictionArray = landmarks.map(p => [p[0], p[1]]);
    //We add the example to our classifier using the array we just created and 
    //the label that was given into the function by our button. 
      knnClassifier.addExample(predictionArray, label);
      updateCounts();
    }
  }
}

// Predict the current frame.
function classify() {

  const numLabels = knnClassifier.getNumLabels();
  if (numLabels <= 0) {
    console.error('There is no examples in any label');
    return;
  }
  
  if(poses.length > 0){
    for (let i = 0; i < poses.length; i += 1) {
      const landmarks = poses[0].landmarks;
      // The input from handpose is adjusted the same way as in addExamples()
      const predictionArray = landmarks.map(p => [p[0], p[1]]);
      //The data is now used to classify which label a certain hand position has. 
      knnClassifier.classify(predictionArray, gotResults);
      allowedToPredict = true;
     }
  }
  
}

// A util function to create UI buttons
function createButtons() {
  
  // When the ONE button is pressed, add the current frame
  // from the video with a label of "One" to the classifier
  buttonOne = select('#addClassOne');
  buttonOne.mousePressed(function() {
    addExample('One');
  });

  // When the Two button is pressed, add the current frame
  // from the video with a label of "Two" to the classifier
  buttonTwo = select('#addClassTwo');
  buttonTwo.mousePressed(function() {
    addExample('Two');
  });
  
  // When the Three button is pressed, add the current frame
  // from the video with a label of "C" to the classifier
  buttonThree = select('#addClassThree');
  buttonThree.mousePressed(function() {
    addExample('Three');
  });
  
  // When the Three button is pressed, add the current frame
  // from the video with a label of "C" to the classifier
  buttonFour = select('#addClassFour');
  buttonFour.mousePressed(function() {
    addExample('Four');
  });
  
  
  // When the Three button is pressed, add the current frame
  // from the video with a label of "C" to the classifier
  buttonFive = select('#addClassFive');
  buttonFive.mousePressed(function() {
    addExample('Five');
  });

  // Reset buttons
  resetBtnOne = select('#resetOne');
  resetBtnOne.mousePressed(function() {
    clearLabel('One');
  });
  
  resetBtnTwo = select('#resetTwo');
  resetBtnTwo.mousePressed(function() {
    clearLabel('Two');
  });
  
  resetBtnThree = select('#resetThree');
  resetBtnThree.mousePressed(function() {
    clearLabel('Three');
  });
  
   resetBtnFour = select('#resetFour');
  resetBtnFour.mousePressed(function() {
    clearLabel('Four');
  });
  
   resetBtnFive = select('#resetFive');
  resetBtnFive.mousePressed(function() {
    clearLabel('Five');
  });

  // Predict button
  buttonPredict = select('#buttonPredict');
  buttonPredict.mousePressed(classify);

  // Clear all classes button
  buttonClearAll = select('#clearAll');
  buttonClearAll.mousePressed(clearAllLabels);
  
  
  // Load saved classifier dataset
  buttonSetData = select('#load');
  buttonSetData.mousePressed(loadMyKNN);

  // Get classifier dataset
  buttonGetData = select('#save');
  buttonGetData.mousePressed(saveMyKNN);
  
  
}

// Show the results
function gotResults(err, result) {
  // Display any error
  if (err) {
    console.error(err);
  }

  if (result.confidencesByLabel) {
    const confidences = result.confidencesByLabel;
    // result.label is the label that has the highest confidence
    if (result.label) {
      classificationResult = result.label;
      select('#result').html(result.label);
      select('#confidence').html(`${confidences[result.label] * 100} %`);
      sendDataToArduino(result.label);
    }
      select('#confidenceOne').html(`${confidences['One'] ? confidences['One'] * 100 : 0} %`);
      select('#confidenceTwo').html(`${confidences['Two'] ? confidences['Two'] * 100 : 0} %`);
      select('#confidenceThree').html(`${confidences['Three'] ? confidences['Three'] * 100 : 0} %`);
      select('#confidenceFour').html(`${confidences['Four'] ? confidences['Four'] * 100 : 0} %`);
      select('#confidenceFive').html(`${confidences['Five'] ? confidences['Five'] * 100 : 0} %`);
  }

 if (poses.length>0) { 
   classify();
  
 }
}

// Update the example count for each label  
function updateCounts() {
  const counts = knnClassifier.getCountByLabel();
  
  select('#exampleOne').html(counts['One'] || 0);
  select('#exampleTwo').html(counts['Two'] || 0);
  select('#exampleThree').html(counts['Three'] || 0);
  select('#exampleFour').html(counts['Four'] || 0);
  select('#exampleFive').html(counts['Five'] || 0);
}


// Clear the examples in one label
function clearLabel(classLabel) {
  knnClassifier.clearLabel(classLabel);
  updateCounts();
}

// Clear all the examples in all labels
function clearAllLabels() {
  knnClassifier.clearAllLabels();
  updateCounts();
}


// Save dataset as myKNNDataset.json
function saveMyKNN() {
    knnClassifier.save('myKNNDataset');
}

// Load dataset to the classifier
function loadMyKNN() {
    knnClassifier.load('./myKNNDataset.json', updateCounts);
}

function drawKeypoints() {
  for (let i = 0; i < poses.length; i += 1) {
    const prediction = poses[i];
    for (let j = 0; j < prediction.landmarks.length; j += 1) {
      const keypoint = prediction.landmarks[j];
      fill(255, 255, 255);
      noStroke();
      ellipse(keypoint[0], keypoint[1], 10, 10);
    }
  }
}

/**
 * Callback function by serial.js when there is an error on web serial
 * 
 * @param {} eventSender 
 */
function onSerialErrorOccurred(eventSender, error) {
  console.log("onSerialErrorOccurred", error);

}

/**
 * Callback function by serial.js when web serial connection is opened
 * 
 * @param {} eventSender 
 */
function onSerialConnectionOpened(eventSender) {
  console.log("onSerialConnectionOpened");
}

/**
 * Callback function by serial.js when web serial connection is closed
 * 
 * @param {} eventSender 
 */
function onSerialConnectionClosed(eventSender) {
  console.log("onSerialConnectionClosed");
}

/**
 * Callback function serial.js when new web serial data is received
 * 
 * @param {*} eventSender 
 * @param {String} newData new data received over serial
 */
function onSerialDataReceived(eventSender, newData) {
  console.log("onSerialDataReceived", newData);
}

/**
 * Callback function serial.js when new web serial data is received
 * 
 * @param {*} eventSender 
 * @param {String} newData new data received over serial
 */
function sendDataToArduino(label) {
  const timeSinceLastTransmitMs = millis() - timestampLastTransmit;
  if (timeSinceLastTransmitMs > MIN_TIME_BETWEEN_TRANSMISSIONS_MS) {
      if (label == "One"){
           serial.writeLine("<" + 0 + ">");
           console.log(0);
      }else if (label == "Two") {
         serial.writeLine("<" + 1 + ">");
             console.log(1);
       }else if (label == "Three") {
         serial.writeLine("<" + 2 + ">");
         console.log(2);
      }else if (label == "Four") {
         serial.writeLine("<" + 3 + ">");
      }else{
         serial.writeLine("<" + 4 + ">");
      }
        
        
      
      timestampLastTransmit = millis();
       
  } else {
     console.log("Did not send  '" + label + "' because time since last transmit was " + timeSinceLastTransmitMs + "ms");
  }
  
}
