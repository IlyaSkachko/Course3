const net = require("net");

const HOST = "0.0.0.0";
const PORT = 40000;


let h = (n) => {return (sock) => {
    console.log(`CONNECTED ${n}: ${sock.remoteAddress}: ${sock.remotePort}`);
    sock.on("data", (data) => {
        console.log(`DATA ${n}: ${sock.remoteAddress}: ${data}`);
        sock.write(`ECHO ${n}: ${data}`);
    });

    sock.on("close", (data) => {
        console.log(`CLOSED ${n}: ${sock.remoteAddress}: ${sock.remotePort}`);
    });
}}

net.createServer(h(PORT)).listen(PORT, HOST).on("listening", () => {console.log(`TCP-server ${HOST}:${PORT}`)});