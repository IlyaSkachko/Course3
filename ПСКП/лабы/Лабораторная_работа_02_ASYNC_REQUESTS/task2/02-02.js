const http = require("http");
const fs = require("fs");

const server = http
    .createServer((request, response) => {
        if (request.method === "GET" && request.url === "/png") {
            fs.readFile("pic.png", (err, data) => {
                if (err) {
                    response.writeHead(500, { "Content-Type": "text/plain" });
                    response.end("Internal Server Error");
                } else {
                    response.writeHead(200, { "Content-Type": "image/png" });
                    response.end(data);
                }
            });
        } else {
            response.writeHead(404, { "Content-Type": "text/plain" });
            response.end("Not Found");
        }
    })
    .listen(5000, "127.0.0.1", () => {});
