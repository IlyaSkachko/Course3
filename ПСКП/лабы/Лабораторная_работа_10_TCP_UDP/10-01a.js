const net = require("net");

const HOST = "127.0.0.1";
const PORT = process.argv[2]?process.argv[2]:40000;

let client = new net.Socket();

let timerId = null;

client.connect(PORT, HOST, () => {
    console.log(`Client CONNECTED: ${client.remoteAddress}: ${client.remotePort}`);

    let k = 0;
    timerId = setInterval(() => {client.write(`client: ${k++}`)}, 1000);
    setTimeout(() => {clearInterval(timerId); client.end();}, 30000);
});

client.on("data", (data) => {console.log(`Client DATA: ${data}`)})
        .on("close", () => {console.log(`Client CLOSE`);})
        .on("error", (e) => {console.log(`Client ERROR ${e}`);});