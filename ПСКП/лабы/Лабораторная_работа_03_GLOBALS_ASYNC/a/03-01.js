const http = require("http");
const process = require("process");

let state = "norm";

http.createServer(function (request, response) {
    if (state != null) {
        response.writeHead(200, {
            "Content-Type": "text/html",
            charset: "utf-8",
        });
        response.end(getHtmlState(state));
    } else {
        response.writeHead(500, {"Content-Type": "text/html"});
        response.end("<h1 text-align=center>Server Error</h1>")

    }
}).listen(3000);

process.stdin.setEncoding("utf-8");

process.stdin.on("readable", () => {
    let chunk = null;

    while ((chunk = process.stdin.read()) != null) {
        if (chunk.trim() == "exit") {
            process.exit(0);
        } else if (chunk.trim() == "norm") {
            process.stdout.write(
                `${state}->${chunk.trim()}\nreg = ${state}--> ${chunk.trim()}\n`
            );
            state = chunk.trim();
        } else if (chunk.trim() == "idle") {
            process.stdout.write(
                `${state}->${chunk.trim()}\nreg = ${state}--> ${chunk.trim()}\n`
            );
            state = chunk.trim();
        } else if (chunk.trim() == "test") {
            process.stdout.write(
                `${state}->${chunk.trim()}\nreg = ${state}--> ${chunk.trim()}\n`
            );
            state = chunk.trim();
        } else if (chunk.trim() == "stop") {
            process.stdout.write(
                `${state}->${chunk.trim()}\nreg = ${state}--> ${chunk.trim()}\n`
            );
            state = chunk.trim();
        } else {
            process.stdout.write(chunk.trim() + "\n");
        }
    }
});

console.log("Server running at http://localhost:3000/");

function getHtmlState(state) {
    return `
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Document</title>
    </head>
    <body>
        <h1 style="text-align: center;">${state}</h1>
    </body>
    </html>
    `;
}
