const WebSocket = require("ws");

const wss = new WebSocket.Server({ port: 4000, host: "localhost" });

let k = 0;
wss.on("connection", (ws) => {
    ws.on("pong", (data) => {
        console.log("on pong: ", data.toString());
    });
    ws.on("message", (data) => {
        console.log(`on message: ${data.toString()}`);
        ws.send(data);
    });
    setInterval(() => {
        wss.clients.forEach((client) => {
            if (client.readyState == ws.OPEN) {
                client.send(`09-03-server: ${++k}`);
            }
        });
    }, 15000);
    setInterval(() => {
        console.log(`server: ping`);
        ws.ping(`server: ping`);
    }, 5000);
});
