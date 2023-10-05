const http = require("http");
const url = require("url");
const fs = require("fs");

let data = require("./DB.js");

let db = new data.DB();

db.on("GET", async (request, response) => {
    console.log("DB.GET");
    response.end(JSON.stringify( await db.select()));
});

db.on("POST", async (request, response) => {
    console.log("DB.POST");
    request.on("data", async data => {
        let obj = JSON.parse(data);
        await db.insert(obj);
        response.end(JSON.stringify(obj));
    });
});
db.on("PUT", async (request, response) => {
    console.log("DB.PUT");
    request.on("data", async data => {
        let obj = JSON.parse(data);
        await db.update(obj);
        response.end(JSON.stringify(obj));
    });
});

db.on("DELETE", async (request, response) => {
    console.log("DB.DELETE");
    request.on("data", async data => {
        let obj = JSON.parse(data);
        response.end(JSON.stringify(await db.delete(obj.id)));
    });
});

http.createServer((request, response) => {
    if (url.parse(request.url).pathname === "/") {
        let html = fs.readFileSync("./index.html");
        response.writeHead(200, {
            "Content-Type": "text/html"
        });
        response.end(html);
    } else if (url.parse(request.url).pathname === "/api/db") {
        db.emit(request.method, request, response);
    }
}).listen(3000);