const http = require("http");
const fs = require("fs");

http.createServer((request, response) => {
    if (request.url === "/fetch") {
        fs.readFile("fetch.html", (err, data) => {
            if (err) {
                response.writeHead(500, { "Content-Type": "text/plain" });
                response.end("Internal Server Error");
            } else {
                response.writeHead(200, {
                    "Content-Type": "text/html; charset=utf-8",
                });
                response.end(data);
            }
        });
    } else if (request.url === "/api/name") {
        const name = "Скачко Илья Александрович";
        response.writeHead(200, { "Content-Type": "text/plain; charset=utf-8" });
        response.end(name);
    } else {
        response.writeHead(404, { "Content-Type": "text/plain" });
        response.end("Not Found");
    }
}).listen(5000);

