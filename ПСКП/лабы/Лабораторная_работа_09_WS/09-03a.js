const WebSocket = require("ws");

const ws = new WebSocket("ws://localhost:4000");

ws.on("message", (message) => {
    console.log("on message: ", message.toString());
});

ws.on("pong", (data) => {
    console.log("on pong: ", data.toString());
});

setInterval(() => {
    console.log("client: ping");
    ws.ping("client: ping");
}, 5000);
