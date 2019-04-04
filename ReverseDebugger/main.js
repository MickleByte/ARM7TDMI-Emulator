const { app, BrowserWindow } = require('electron');
const fs = require("fs");
var win;
var assemblyLog;
var memoryLog;
var registerLog;
readLogs();

function createWindow () {
  win = new BrowserWindow({ width: 1280, height: 720 });
  win.loadFile('index.html');
  win.webContents.once('dom-ready', windowLoaded);
  win.on('closed', () => {
    win = null;
  });
}

function windowLoaded(){
  console.log("window loaded");
  for(var i = 0; i < memoryLog[i].length; i++){
    win.$("#memory").innerHTML += `<div id=mem${i}></div>`;
  }
}

app.on('ready', createWindow);

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.on('activate', () => {
  if (win === null) {
    createWindow();
  }
});

async function readLogs(){
  memoryLog = await fs.readFileSync("..\\memoryLog.log").toString();
  registerLog = await fs.readFileSync("..\\registerLog.log").toString();
  assemblyLog = await fs.readFileSync("..\\assemblyLog.log").toString();
  return true;
}

function splitLogs(){
  for(var i = 0; i < memoryLog.length; i++){
    memoryLog[i] = memoryLog[i].split(" ");
  }
  for(var i = 0; i < registerLog.length; i++){
    registerLog[i] = registerLog[i].split(" ");
  }
  for(var i = 0; i < assemblyLog.length; i++){
    assemblyLog[i] = assemblyLog[i].split(" ");
  }
}
