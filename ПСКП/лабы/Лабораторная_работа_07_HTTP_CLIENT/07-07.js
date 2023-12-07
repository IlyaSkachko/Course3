const fs = require("fs");
const http = require("http");

const options = {
    hostname: "localhost",
    port: 3000,
    path: "/getFile",
    method: "GET"
};

const request = http.request(options, (response) => {
    const fileStream = fs.createWriteStream("Cat.png");

    response.pipe(fileStream);

    fileStream.on("finish", () => {
        console.log("Файл успешно сохранен");
    });
});

request.on("error", (e) => {
    console.error(`Ошибка при отправке запроса: ${e.message}`);
});

request.end();


const server = http.createServer((request, response) => {
    if (request.url === "/getFile" && request.method === "GET") {
        const fileStream = fs.createReadStream("MyFile.png");

        fileStream.on("open", () => {
            response.setHeader("Content-Type", "image/png");
            fileStream.pipe(response);
        });

        fileStream.on("error", (err) => {
            console.error("Ошибка при чтении файла:", err);
            response.writeHead(500, { "Content-Type": "text/plain" });
            response.end("Internal Server Error");
        });
    } else {
        response.writeHead(404, { "Content-Type": "text/plain" });
        response.end("Страница не найдена");
    }
}).listen(3000);