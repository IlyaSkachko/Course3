const fs = require("fs");
const WebSocket = require("ws");

const ws = new WebSocket("ws://localhost:4000");

let k = 0;

ws.on("open", () => {
    const duplex = WebSocket.createWebSocketStream(ws, {encoding: "utf8"});
    let wfile = fs.createWriteStream(`./download/download${++k}.txt`);

    wfile.write("Task 2 Client");

    duplex.pipe(wfile);

    duplex.on("end", () => {
        wfile.end();
    });
});