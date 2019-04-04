const { app, BrowserWindow} = require('electron');
var window;

function createWindow () {
  window = new BrowserWindow({ width: 1280, height: 720});
  window.loadFile('index.html');
  window.on('closed', () => {
    window = null;
  });
}

app.on('ready', createWindow);

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.on('activate', () => {
  if (window === null) {
    createWindow();
  }
});
