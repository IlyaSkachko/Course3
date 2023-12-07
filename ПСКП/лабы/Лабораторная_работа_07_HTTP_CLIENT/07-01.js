

const http = require("http");

const options = {
    host: "localhost",
    port: 3000,
    path: "/"
};

http.request(options, (response) => {
    console.log(`Status code: ${response.statusCode}`);
    console.log(`Status message: ${response.statusMessage}`);
    console.log(`IP server: ${response.socket.remoteAddress}`);
    console.log(`Port server: ${response.socket.remotePort}`);
}).end();


http.createServer((request, response) => {
    response.writeHead(200, {"Content-Type": "text/plain"});
    console.log("Server running...");
    response.end("Server running...");
}).listen(3000);