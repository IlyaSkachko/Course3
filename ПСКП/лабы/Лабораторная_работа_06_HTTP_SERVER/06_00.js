const http = require("http");
const url = require("url");
const fs = require("fs");
const xml2js = require("xml2js");
const pathM = require("path");

const server = http
    .createServer((request, response) => {
        let path = url.parse(request.url).pathname;

        if (request.method == "GET") {
            if (path == "/connection") {
                response.writeHead(200, {
                    "Content-Type": "text/html",
                });
                response.write(`<h1>${server.keepAliveTimeout}</h1>`);
                let param = url.parse(request.url, true).query.set;
                if (typeof param != "undefined") {
                    server.keepAliveTimeout = parseInt(param);
                    response.write(
                        `<h1>KeepAliveTimeout=${server.keepAliveTimeout}</h1>`
                    );
                    response.end();
                }
            }
            if (path === "/headers") {
                response.writeHead(200, { "Content-Type": "text/plain" });
                response.write("Request headers:\n");
                response.write(JSON.stringify(request.headers, null, 2));

                response.write("\n\n\nResponse headers:\n");
                for (let key in response.headers) {
                    response.write(key + ": " + response.headers[key] + "\n");
                }

                response.end();
            }
            if (path === "/parameter") {
                let x = Number.parseInt(url.parse(request.url, true).query.x);
                let y = Number.parseInt(url.parse(request.url, true).query.y);

                if (x != "undefined" && y != "undefined") {
                    response.writeHead(200, { "Content-Type": "text/html" });
                    if (!isNaN(x) && !isNaN(y)) {
                        response.write(
                            `
                            <p>x + y = ${x + y}</p>
                            <p>x - y = ${x - y}</p>
                            <p>x * y = ${x * y}</p>
                            <p>x / y = ${x / y}</p>
                            `
                        );
                        response.end();
                    } else {
                        response.end("<h1>Error</h1>");
                    }
                }
            }
            if(path.startsWith("/parameter"))
            {
                const [,_, xStr, yStr] = path.split("/"); // Разбираем x и y из пути
        
                if (!isNaN(xStr) && !isNaN(yStr)) { // Проверяем, являются ли x и y числами
                    const x = Number.parseInt(xStr);
                    const y = Number.parseInt(yStr);
        
                    response.writeHead(200, { "Content-Type": "text/html" });
                    response.end(`
                        <p>x + y = ${+x + +y}</p>
                        <p>x - y = ${+x - +y}</p>
                        <p>x * y = ${+x * +y}</p>
                        <p>x / y = ${+x / +y}</p>
                    `);
                }
            }
            if (path === "/socket") {
                const clientIp = request.socket.remoteAddress; 
                const clientPort = request.socket.remotePort;
                const serverIp = request.socket.localAddress;
                const serverPort = request.socket.localPort;

                response.writeHead(200, {"Content-Type": "text/html", "charset": "utf-8"});
                response.end(`
                    <p>Client IP: ${clientIp}</p>
                    <p>Client port: ${clientPort}</p>  
                    <p>Server IP: ${serverIp}</p>
                    <p>Server port: ${serverPort}</p>
                `);
            }
            if (path === "/resp-status") {
                let code = url.parse(request.url, true).query.code;
                let mess = url.parse(request.url, true).query.mess;

                response.writeHead(+code ,mess, { "Content-Type": "text/html" });
                response.end(`
                    <h1>Code: ${code}</h1>
                    <h1>Status: ${mess}</h1>
                `);
            }
            if (path === "/files") {
                fs.readdir("./static", (err, files) => {
                    if (err) {
                        response.writeHead(500, { "Content-Type": "text/plain" });
                        response.end("Internal Server Error");
                    } else {
    
                        const fileCount = files.length;
                        response.writeHead(200, { "Content-Type": "text/plain", "X-static-files-count": fileCount.toString() });
                        response.end(`${fileCount}`);
                    }
                });
            }
            if (path.startsWith("/files")) {
                const [, , file] = path.split("/");
        
                if (file !== undefined) {
                    const filePath = pathM.join(__dirname, "static", file);
        
                    try {
                        const fileContent = fs.readFileSync(filePath);
        
                        response.writeHead(200, { "Content-Type": "text/plain" });
                        response.end(fileContent);
                    } catch (err) {
                        response.writeHead(404, { "Content-Type": "text/plain" });
                        response.end("Error 404: File Not Found");
                    }
                }
            }
            if (path === "/upload") {
                fs.readFile("upload.html", (err, data) => {
                    if (err) {
                        response.writeHead(500, {"Content-Type": "text/plain"});
                        response.end("Internal Server Error");
                        return;
                    }
    
                    response.writeHead(200, {"Content-Type": "text/html"});
                    response.end(data);
                });
            }
            if (path === "/formparameter") {
                fs.readFile("form.html", (err, data) => {
                    if (err) {
                        response.writeHead(500, {"Content-Type": "text/plain"});
                        response.end("Internal Server Error");
                        return;
                    }
    
                    response.writeHead(200, {"Content-Type": "text/html"});
                    response.end(data);
                });
            }
        }

        if (request.method == "POST") {
            if (path === "/formparameter") {
                let body = "";
                request.on("data", chunk => {
                    body += chunk.toString();
                });

                request.on("end", () => {
                    const formData = new URLSearchParams(body);
                    const values = {};
                    formData.forEach((value, key) => {
                        values[key] = value;
                    });

                    response.writeHead(200, { "Content-Type": "text/plain" });
                    response.end(JSON.stringify(values));
                });
            }
            if (path === "/json") {
                request.on("end", () => {
                    try {
                        const requestData = JSON.parse(data);
                        const comment = requestData._comment;
                        const x = requestData.x;
                        const y = requestData.y;
                        const s = requestData.s;
                        const o = requestData.o;
                        const m = requestData.m;
    
                        const resp = {
                            "__comment": "Ответ: " + comment,
                            "x: ": x,
                            "y:": y,
                            "x_plus_y": x + y,
                            "Concatination_s_o": s +": "+ o.name,
                            "Length_m": m.length
                        };
    
                        response.writeHead(200, { "Content-Type": "application/json" });
                        response.end(JSON.stringify(resp));
                    } catch (error) {
                        response.writeHead(400, { "Content-Type": "text/plain" });
                        response.end("Bad Request");
                    }
    

                    /*
                    {
                        "_comment": "lab6",
                        "x": 1,
                        "y": 2,
                        "s": "message",
                        "m":["a", "b", "c"],
                        "o": {"surname": "Skachko", "name": "Ilya"}
                    }
                    */
                });
            }
            if (path === "/xml") {
                let data = "";

                request.on("data", chunk => {
                    data += chunk;
                });
    
                request.on("end", () => {
                    xml2js.parseString(data, (err, result) => {
                        if (err) {
                            response.writeHead(400, { "Content-Type": "text/plain" });
                            response.end("Bad Request");
                            return;
                        }
    
                        const req = result.request;
                        const id = req.$.id;
                        const xs = req.x.map(x => +x.$.value || 0);
                        const ms = req.m.map(m => m.$.value);
    
                        const sumX = xs.reduce((acc, curr) => acc + curr, 0);
                        const concatM = ms.join("");
    
                        const res = {
                            res: {
                                $: { id: id, req: id },
                                sum: { $: { element: "x", result: sumX.toString() } },
                                concat: { $: { element: "m", result: concatM } }
                            }
                        };
    
                        const builder = new xml2js.Builder();
                        const xml = builder.buildObject(res);
    
                        response.writeHead(200, { "Content-Type": "application/xml" });
                        response.end(xml);
                    });
                });
    
                /*
                    <request id="28">
                        <x value = "1"/>
                        <x value = "2"/>
                        <m value = "na"/>
                        <m value = "me"/>
                    </request>
                */
            }
            if (path === "/upload") {
                let data = [];
                request.on('data', chunk => {
                    data.push(chunk);
                });
    
                request.on('end', () => {
                    const boundary = request.headers['content-type'].split('=')[1];
                    const fileData = Buffer.concat(data).toString();
                    const fileStart = fileData.indexOf('filename="') + 10;
                    const fileEnd = fileData.indexOf('"', fileStart);
                    const fileName = fileData.slice(fileStart, fileEnd);
    
                    const filePath = pathM.join(__dirname, 'static', fileName);
    
                    const fileContentStart = fileData.indexOf('\r\n\r\n') + 4;
    
                    fs.writeFile(filePath, fileData.slice(fileContentStart), (err) => {
                        if (err) {
                            response.writeHead(500, {'Content-Type': 'text/plain'});
                            response.end('Internal Server Error');
                        } else {
                            response.writeHead(200, {'Content-Type': 'text/plain'});
                            response.end('File uploaded successfully!');
                        }
                    });
                });
            }
        }
    })
    .listen(3000);
