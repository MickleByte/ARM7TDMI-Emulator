const fs = require("fs");
var assemblyLog;
var memoryLog;
var registerLog;
var index = 0;
var buttons;

window.onload = () => {
  readLogs();
  document.getElementById("back5").onclick = function(){
    index += parseInt(document.getElementById("back5").dataset.value);
    writeLogs(index);
  }
  document.getElementById("back").onclick = function(){
    index += parseInt(document.getElementById("back").dataset.value);
    writeLogs(index);
  }
  document.getElementById("step").onclick = function(){
    index += parseInt(document.getElementById("step").dataset.value);
    writeLogs(index);
  }
  document.getElementById("step5").onclick = function(){
    index += parseInt(document.getElementById("step5").dataset.value);
    writeLogs(index);
  }
  document.getElementById("step10").onclick = function(){
    index += parseInt(document.getElementById("step10").dataset.value);
    writeLogs(index);
  }
}

async function readLogs(){
  memoryLog = await fs.readFileSync("..\\memoryLog.log").toString().split("\n");
  registerLog = await fs.readFileSync("..\\registerLog.log").toString().split("\n");
  assemblyLog = await fs.readFileSync("..\\assemblyLog.log").toString().split("\n");

  splitLogs();
}

function splitLogs(){
  for(var i = 0; i < memoryLog.length; i++){
    memoryLog[i] = memoryLog[i].split(" ");
  }
  for(var i = 0; i < registerLog.length; i++){
    registerLog[i] = registerLog[i].split(" ");
  }
  drawLogs();
}

function drawLogs(){
  for(var i = 0; i < memoryLog[0].length; i++){
    document.getElementById("memory").innerHTML += `<div id=mem${i}></div>`;
  }
  for(var i = 0; i < registerLog[0].length - 1; i++){
    document.getElementById("registers").innerHTML += `<div id=reg${i}></div>`;
  }
  for(var i = 0; i < assemblyLog.length; i++){
    document.getElementById("assembly").innerHTML += `<div id=asm${i}></div>`;
  }
  writeLogs(0);
}

function writeLogs(index){
  console.log(index);
  if(index < 0){
    index = 0;
  }
  else if(index >= memoryLog.length){
    index = memoryLog.length-1;
  }
  for(var i = 0; i < memoryLog[index].length; i++){
    document.getElementById(`mem${i}`).innerHTML = memoryLog[index][i];
  }
  for(var i = 0; i < registerLog[index].length - 1; i++){
    document.getElementById(`reg${i}`).innerHTML = registerLog[index][i];
  }
  for(var i = 0; i < assemblyLog.length; i++){
    document.getElementById(`asm${i}`).innerHTML = assemblyLog[i];
    if(i == parseInt(document.getElementById("reg15").innerHTML)-1){
      document.getElementById(`asm${i}`).style.background = "#7289DA";
      document.getElementById(`asm${i}`).style.color = "#FFFFFF";
    }
    else{
      document.getElementById(`asm${i}`).style.background = "none";
      document.getElementById(`asm${i}`).style.color = "#99AAB5";
    }
  }
}
