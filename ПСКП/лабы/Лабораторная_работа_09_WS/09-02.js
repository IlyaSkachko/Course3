const fs = require("fs");
const WebSocket = require("ws");

const wss = new WebSocket.Server({port: 4000, host: "localhost"});

let k = 0;

wss.on("connection", (ws) => {
    const duplex = WebSocket.createWebSocketStream(ws, {encoding: "utf-8"});

    let rfile = fs.createReadStream(`./download/download${++k}.txt`);

    rfile.on("data", (data) => {
        console.log(data.toString());
    });

    rfile.pipe(duplex);
});