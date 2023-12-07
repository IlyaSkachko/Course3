const fs = require("fs");
const http = require("http");

const fileStream = fs.createReadStream("MyFile.png");

const options = {
    hostname: "localhost",
    port: 3000,
    path: "/upload",
    method: "POST",
    headers: {
        "Content-Type": "multipart/form-data",
    }
};

const request = http.request(options, (response) => {
    let data = "";

    response.on("data", (chunk) => {
        data += chunk;
    });

    response.on("end", () => {
        console.log(`Статус ответа: ${response.statusCode}`);
        console.log(`Ответ: ${data}`);
    });
});


fileStream.pipe(request);


http.createServer((request, response) => {
    if (request.url === "/upload" && request.method === "POST") {
        const fileStream = fs.createWriteStream("MyFileCopy.png");

        request.on("data", (chunk) => {
            fileStream.write(chunk);
        });

        request.on("end", () => {
            fileStream.end();
            response.writeHead(200, { "Content-Type": "text/plain" });
            response.end("All load!");
        });
    } else {
        response.writeHead(404, { "Content-Type": "text/plain" });
        response.end("Страница не найдена");
    }
}).listen(3000);