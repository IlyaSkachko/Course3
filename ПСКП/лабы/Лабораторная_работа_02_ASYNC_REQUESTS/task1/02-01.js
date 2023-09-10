const http = require("http");

const fs = require("fs");

http.createServer(function (request, response) {
    if (request.url == "/html") {
        fs.readFile("index.html", "utf8", function (error, data) {
            if (error) {
                response.writeHead("500", { "Content-type": "text-plain" });
                response.end("Internal Server Error");
            } else {
                response.writeHead("200", { "Content-type": "text/html" });
                response.end(data);
            }
        });
    }
}).listen(5000, "127.0.0.1", function () {});
