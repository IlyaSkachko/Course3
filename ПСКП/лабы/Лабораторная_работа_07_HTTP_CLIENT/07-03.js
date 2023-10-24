const http = require("http");
const url = require("url");
const querystring = require("querystring");



const data = JSON.stringify({
    x: 1,
    y: 2,
    s: "Hello",
});

const options = {
    hostname: "localhost",
    port: 3000,
    path: "/",
    method: "POST",
    headers: {
        "Content-Type": "application/json",
        "Content-Length": data.length,
    },
};

const request = http.request(options, (response) => {
    console.log("Статус:", response.statusCode);

    response.on("data", (d) => {
        process.stdout.write(d);
    });
});

request.write(data);
request.end();




http.createServer((request, response) => {
    if (request.method === "POST") {
        let body = "";

        request.on("data", (chunk) => {
            body += chunk;
        });

        request.on("end", () => {
            const parsed = querystring.parse(body);

            response.writeHead(200);
            response.end(JSON.stringify(parsed));
        });
    }
}).listen(3000);