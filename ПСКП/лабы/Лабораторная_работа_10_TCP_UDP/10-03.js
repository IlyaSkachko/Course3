const dgram = require("dgram");

const server = dgram.createSocket("udp4");

server.on("message", (message, rinfo) => {
    console.log(`Client message: ${message}`)
    const response = `ECHO: ${message}`;
    server.send(
        response,
        0,
        response.length,
        rinfo.port,
        rinfo.address,
        (err) => {
            if (err) {
                console.log(`Error: ${err}`);
            } else {
                console.log(`Response: ${response}`);
            }
        }
    );
});

server.on("listening", () => {
    const address = server.address();
    console.log(`UDP server listening on ${address.address}:${address.port}`);
});

server.on("error", (err) => {
    console.log(`UDP server error: ${err}`);
});

const port = 40000; 
server.bind(port);
