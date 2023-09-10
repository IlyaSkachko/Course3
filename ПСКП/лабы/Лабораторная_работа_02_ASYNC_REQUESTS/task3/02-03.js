

const http = require("http");

http.createServer(function (request, response) {

    if (request.url === "/api/name") {
        response.writeHead("200", {"Content-type": "text/plain; charset=utf-8"});
        response.end("Скачко Илья Александрович");
    }

}).listen(5000, "127.0.0.1", function(){});