const WebSocket = require("ws");

const ws = new WebSocket("ws://localhost:4000/wServer");

ws.on("open", () => {
    ws.send("message 1");
    ws.send("message 2");
    ws.on("message", message => {
        console.log(`Received message => ${message}`);
    });
    setTimeout(() => {
        ws.close();
    }, 5000);
});