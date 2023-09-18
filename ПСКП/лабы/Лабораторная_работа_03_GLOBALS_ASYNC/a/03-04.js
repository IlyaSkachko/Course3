
const http = require("http");
const url = require("url");
const fs = require("fs");

function fact(x) {
    if (x === 1 || x === 0 ) {
        return 1;
    } else {
        return x * fact(x - 1);
    }
}

http.createServer(function(request, response) {

    let path = url.parse(request.url).pathname;

    if (path === "/fact") {
        let param = url.parse(request.url, true).query.k;

        if (typeof param != "undefined") {
            let k = parseInt(param);
            response.writeHead(200, {"Content-Type": "application/json"});
            process.nextTick(() => response.end(JSON.stringify({k: k, fact: fact(k)})));
        }
    } else if (request.url === "/") {
        fs.readFile("03-03.html", function(err, data) {
            if (err) {
                response.writeHead(500, {"Content-Type": "text/plain"});
                response.end("Server Error");
            } else {
                response.writeHead(200, {"Content-Type": "text/html"});
                response.end(data);
            }
        });
    }
    else {
        response.end("http://localhost:5000/fact?k=3")
    }

}).listen(3000);