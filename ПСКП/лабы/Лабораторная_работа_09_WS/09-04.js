const WebSocket = require("ws");

const wss = new WebSocket.Server({ port: 4000, host: "localhost" });

wss.on("connection", (ws) => {
    let k = 0;
    ws.on("message", (data) => {
        console.log("on message: ", JSON.parse(data));
        ws.send(
            JSON.stringify({
                server: ++k,
                client: JSON.parse(data).client,
                timestamp: new Date().toISOString(),
            })
        );
    });
});
