const http = require("http");
const url = require("url");
const querystring = require("querystring");


const options = {
    hostname: "localhost",
    port: 3000,
    path: "/?x=1&y=2",
    method: "GET",
};

http.request(options, (response) => {
    let body = "";

    response.on("data", (chunk) => {
        body += chunk;
    });

    response.on("end", () => {
        console.log("Статус:", response.statusCode);
        console.log("Данные:", body);
    });
}).end();



http.createServer((request, response) => {

    const x = url.parse(request.url, true).query.x;
    const y = url.parse(request.url, true).query.y;

    response.writeHead(200);
    response.end(`x=${x}    y=${y}`);

}).listen(3000);