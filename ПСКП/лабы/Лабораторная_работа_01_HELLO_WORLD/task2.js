
// const http = require("http");

// http.createServer(function(request, response){

//     response.end(
//         `
//         <html>
//             <head>
//                 <title>Request content</title>
//             </head>
//             <body>
//                 <h1 style="text-align:center">Output: </h1>
//                 <p style="text-align:center">URI: ${request.url}</p>
//                 <p style="text-align:center">Method: ${request.method}</p>
//                 <p style="text-align:center">Protocol version: ${request.httpVersion}</p>
//                 <p style="text-align:center">Headers: ${JSON.stringify(request.headers)}</p>
//                 <p style="text-align:center">Body: ${request.JSON}</p>
//             </body>
//         </html>
//         `
//     );
// }).listen(3000);



const http = require("http");

http.createServer(function(request, response) {
    let b = "";

    let headers = "";
    Object.entries(request.headers).forEach(([key, value]) => {
        headers += `<h4>${key}: ${value}</h4>`
    });

    request.on('data', str=>{b+=str; console.log('data', b);});
    response.writeHead(200, {"Content-Type": "text/html; charset=utf-8"});
    request.on("end", () => response.end(
            `
            <!DOCTYPE html>
            <html>
                <head>
                    <title>Request content</title>
                    <style>
                        h1, h2, h4 {
                            text-align: center;
                        }
                    </style>
                </head>
                <body>
                    <h1>Структура запроса: </h1>
                    <h2>Метод: ${request.method}</h2>
                    <h2>URI: ${request.url}</h2>
                    <h2>Версия: ${request.httpVersion}</h2>
                    <h2>Заголовки: </h2> ${headers}
                    <h2>Тело: ${b}</h2>
                </body>
            </html>
            `
    ))
}).listen(3000);