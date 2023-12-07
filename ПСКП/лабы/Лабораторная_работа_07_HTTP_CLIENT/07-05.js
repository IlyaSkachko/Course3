const http = require("http");
const xml2js = require("xml2js").parseString;
const xmlBuilder = require("xmlbuilder");

const postData = `
    <request id="28">
        <x value = "1"/>
        <x value = "2"/>
        <m value = "He"/>
        <m value = "llo"/>
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

const request = http.request(options, (response) => {
    let data = "";

    response.on("data", (chunk) => {
        data += chunk;
    });

    response.on("end", () => {
        console.log("body = ", data);
        xml2js(data, (err, str) => {
            if (err) console.log("error: xml parse");
        });
    });
});


request.end(postData.toString());

http.createServer((request, response) => {
    if (request.method === "POST") {
        let data = "";

        request.on("data", (chunk) => {
            data += chunk;
        });

        request.on("end", () => {
            xml2js(data, (err, result) => {
                if (err) {
                    console.error("Ошибка при парсинге XML:", err);
                    response.writeHead(500, {
                        "Content-Type": "application/xml",
                    });
                    response.end(`
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

                    response.writeHead(200, {
                        "Content-Type": "application/xml",
                    });
                    response.end(responseXML);
                }
            });
        });
    } else {
        response.writeHead(404, { "Content-Type": "text/plain" });
        response.end("Страница не найдена");
    }
}).listen(3000);
