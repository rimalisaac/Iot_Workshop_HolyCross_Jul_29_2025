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


function doGet(e) {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var ldrValue = e.parameter.ldr;
  var timeStamp = new Date();

  sheet.appendRow([timeStamp, ldrValue]);
  return ContentService.createTextOutput("Data saved");
}

