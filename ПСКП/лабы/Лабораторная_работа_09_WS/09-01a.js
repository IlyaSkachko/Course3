const fs = require("fs");
const WebSocket = require("ws");

const ws = new WebSocket("ws://localhost:4000");

let k = 0;

ws.on("open", () => {
    const duplex = WebSocket.createWebSocketStream(ws, {encoding: "utf8"});
    let rfile = fs.createReadStream(`./upload/file${++k}.txt`);
    rfile.on("data", (data) => {
        console.log(data.toString());
    });
    rfile.pipe(duplex);
});