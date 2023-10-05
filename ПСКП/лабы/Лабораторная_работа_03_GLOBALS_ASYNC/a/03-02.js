
const http = require("http");
const url = require("url");

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
            response.end(JSON.stringify({k: k, fact: fact(k)}));
        }
    }
    else {
        response.end("http://localhost:3000/fact?k=3")
    }

}).listen(3000);