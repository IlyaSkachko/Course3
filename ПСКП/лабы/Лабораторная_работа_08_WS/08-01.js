


require("http")
    .createServer((request, response) => {
        if (request.method == "GET" && request.url == "/start") {
            response.writeHead(200, {
                "Content-Type": "text/html; charset=utf-8",
            });
            response.end(require("fs").readFileSync("./08-01.html"));
        } else {
            response.writeHead(400, { "Content-Type": "text/plain" });
            response.end("Bad Request");
        }
    })
    .listen(3000);

console.log("ws server: 3000");

let k = 0;

const WebSocket = require("ws");

const wServer = new WebSocket.Server({
    port: 4000,
    host: "localhost",
    path: "/wServer",
});


wServer.on("connection", (ws) => {
    let clientMessage = " ";
        const intervalId = setInterval(() => {
            const response = `08-01-server: ${clientMessage}->${++k}`;
            ws.send(response);
        }, 3000);

        setTimeout(() => {
            clearInterval(intervalId);
            ws.close();
        }, 25000);
    ws.on("message", (message) => {
        clientMessage =  message.toString(); 
        console.log(`Received message => ${message}`);
    });

    ws.on("close", () => {
        console.log("Client disconnected");
    });
});

wServer.on("error", (e) => {
    console.log("ws server error", e);
});
console.log(
    `ws server: host: ${wServer.options.host}, port: ${wServer.options.port}, path: ${wServer.options.path}`
);
