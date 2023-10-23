const http = require("http");
const fs = require("fs");
const {send} = require("m06_sia");
const { EventEmitter } = require("stream");


const em = new EventEmitter();

em.on("POST", async (request, response) => {

    console.log("DB.POST");
    request.on("data", async (data) => {
        let obj = JSON.parse(data);
        await send(obj.myEmail, obj.password, obj.message)
        .then((result) => {
            console.log("Successfully", result)
        })
        .catch(err => {
            console.log("Error", err);
        });
        response.end(JSON.stringify(obj));
    });

});


http.createServer((request, response) => {
    if (request.url === "/") {
        fs.readFile("./index.html", (err, data) => {
            if (err) {
                response.writeHead(500, { "Content-Type": "text/html" });
                response.end("<h1>Server Error</h1>");
            } else {
                response.writeHead(200, { "Content-Type": "text/html" });
                em.emit(request.method, request, response);
                response.end(data);
            }
        });
    }
}).listen(3000);
