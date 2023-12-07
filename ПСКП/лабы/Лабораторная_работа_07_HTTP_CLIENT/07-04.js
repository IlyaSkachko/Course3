const http = require("http");
const url = require("url");
const querystring = require("querystring");


let params = JSON.stringify({_comment: "Lab_7", x:1, y:2, s:"message", m: ["a", "b", "c"], o: {surname: "Skachko", name: "Ilya"}});

let options = {
    host: "localhost",
    path: "/",
    port: 3000,
    method: "POST",
    headers: {
        "Content-Type": "application/json", "accept": "application/json"
    }
};

const request = http.request(options, (response) => {
    console.log(`Статус ответа: ${response.statusCode}`);
    console.log(`Сообщение к статусу ответа: ${response.statusMessage}`);

    let data = "";
    response.on("data", (chunk) => {
        data += chunk.toString();
    });

    response.on("end", () => {
        console.log("Данные: ", data);
        console.log("Данные(parse): ", JSON.parse(data));
    });
});



request.write(params);
request.end();




http.createServer((request, response) => {
    if (request.method === "POST") {

        let body = "";
        request.on("data", chunk => {
            body += chunk;
        });

        request.on("end", () => {
            const requestData = JSON.parse(body);
            const comment = requestData._comment;
            const x = Number.parseInt(requestData.x);
            const y = Number.parseInt(requestData.y);
            const s = requestData.s;
            const o = requestData.o;
            const m = requestData.m;

            response.writeHead(200, { "Content-Type": "text/plain" });
            const res = {
                "__comment": "Ответ: " + comment,
                "x:" : x,
                "y:" : y,
                "x_plus_y": x + y,
                "Concatination_s_o": s +": "+ o.name,
                "Length_m": m.length
            };

            response.end(JSON.stringify(res));
        });
    }
}).listen(3000);