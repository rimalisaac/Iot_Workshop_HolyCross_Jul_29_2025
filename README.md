Holy Cross Workshop

https://thingspeak.mathworks.com/

https://manus.im/invitation/M2QN3OI5CD8XM

https://www.arduino.cc/en/software/

https://cdn.sparkfun.com/assets/learn_tutorials/5/9/7/Windows-CH340-Driver.zip

http://arduino.esp8266.com/stable/package_esp8266com_index.json

🔧 Steps

Google sheet -> Extension -> App Script
1. Create Google Apps Script

  Go to Google Apps Script
  Create a New Project
  Paste this code

  function doGet(e) {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var ldrValue = e.parameter.ldr;
  var timeStamp = new Date();

  sheet.appendRow([timeStamp, ldrValue]);
  return ContentService.createTextOutput("Data saved");
}


Save and Deploy > New deployment → Select Web app.
  Execute as: Me

  Who has access: Anyone

Authorize

Copy the Web App URL (looks like https://script.google.com/macros/s/.../exec).


function doGet(e) {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var temp = e.parameter.temp;
  var hum = e.parameter.hum;
  var timestamp = new Date();

  if (temp && hum) {
    sheet.appendRow([timestamp, temp, hum]);
    return ContentService.createTextOutput("Data Stored Successfully");
  } else {
    return ContentService.createTextOutput("Missing Parameters");
  }
}

