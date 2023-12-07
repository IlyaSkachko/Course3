const dgram = require("dgram");

const client = dgram.createSocket("udp4");

const message = "Hello, server!";

setInterval(() => {
    client.send(message, 0, message.length, 40000, "localhost", (err) => {
        if (err) {
            console.log(`Error: ${err}`);
        } else {
            console.log(`Client message: ${message}`);
        }
    });
}, 5000);

client.on("message", (msg) => {
    console.log(`Response from server: ${msg}`);
});

client.on("error", (err) => {
    console.log(`UDP client error: ${err}`);
});
