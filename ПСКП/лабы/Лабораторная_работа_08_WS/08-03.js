// const WebSocket = require("ws");
// const http = require("http");


// const server = http.createServer((request, response) => {
//     response.writeHead(200, { 'Content-Type': 'text/plain' });
//     request.end('Server is running');
// }).listen(4000);

// const wss = new WebSocket.Server({server});

// const clients = new Set();
// let k = 0;

// wss.on("connection", (ws) => {
//     clients.add(ws);
//     console.log("Client connected");
//     ws.on("message", (message) => {
//         clients.forEach((client) => {
//             if (client !== ws && client.readyState === WebSocket.OPEN) {
//                 client.send(message + `${++k}`);
//             }
//         });
//     });

//     ws.on("close", () => {
//         clients.delete(ws);
//     });
// });





const WebSocket = require("ws");

const wss = new WebSocket.Server({port: 5000, host: "localhost", path: "/broadcast"});

wss.on("connection", (ws) => {
    ws.on("message", (message) => {

        wss.clients.forEach((client) => {
            if (client.readyState === WebSocket.OPEN) client.send(`server: ${message}`);
        })
    })

    ws.on("close", () => {
        console.log("wss socket closed");
    })
});