const http = require("http");
const xml2js = require("xml2js").parseString;
const xmlBuilder = require("xmlbuilder");

const postData = `
  <request id="28">
     <x value = "1"/>
     <x value = "2"/>
     <m value = "na"/>
     <m value = "me"/>
  </request>
`;

const options = {
    hostname: "localhost",
    port: 3000,
    path: "/",
    method: "POST",
    headers: {
        "Content-Type": "application/xml",
        accept: "application/xml",
    },
};

const req = http.request(options, (res) => {
    let data = "";

    res.on("data", (chunk) => {
        data += chunk;
    });

    res.on("end", () => {
        console.log("http.response: end: body = ", data);
        xml2js(data, (err, str) => {
            if (err) console.log("error: xml parse");
        });
    });
});

req.on("error", (e) => {
    console.error(`Ошибка при отправке запроса: ${e.message}`);
});

req.end(postData.toString());

const server = http.createServer((req, res) => {
    if (req.method === "POST") {
        let data = "";

        req.on("data", (chunk) => {
            data += chunk;
        });

        req.on("end", () => {
            xml2js(data, (err, result) => {
                if (err) {
                    console.error("Ошибка при парсинге XML:", err);
                    res.writeHead(500, { "Content-Type": "application/xml" });
                    res.end(`
            <response>
              <status>500</status>
              <message>Internal Server Error</message>
            </response>
          `);
                } else {
                    const xSum = result.request.x.reduce(
                        (sum, x) => sum + Number(x.$.value),
                        0
                    );
                    const mConcatenated = result.request.m.reduce(
                        (concatenated, m) => concatenated + m.$.value,
                        ""
                    );

                    const responseXML = xmlBuilder
                        .create({
                            response: {
                                status: "200",
                                message: "OK",
                                receivedData: {
                                    xSum: String(xSum),
                                    mConcatenated: mConcatenated,
                                },
                            },
                        })
                        .end({ pretty: true });

                    res.writeHead(200, { "Content-Type": "application/xml" });
                    res.end(responseXML);
                }
            });
        });
    } else {
        res.writeHead(404, { "Content-Type": "text/plain" });
        res.end("Страница не найдена");
    }
});

server.listen(3000, () => {
    console.log("Сервер запущен по адресу http://localhost:3000");
});
