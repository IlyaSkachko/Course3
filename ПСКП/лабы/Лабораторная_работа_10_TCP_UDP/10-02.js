const net = require("net");

const ports = [40000, 50000];

let sum = 0;

ports.forEach(port => {
    const server = net.createServer();

    server.on("connection", (sock) => {
        console.log(
            `Server connected: ${sock.remoteAddress}:${sock.remotePort} on port ${port}`
        );

        sock.on("data", (data) => {
            let clientNum = data.readInt32LE();
            sum += clientNum;
            console.log(`ClientNum: ${clientNum}\tSum: ${sum}`);
        });

        setInterval(() => {
            const buf = Buffer.alloc(4);
            buf.writeInt32LE(sum, 0);
            sock.write(buf);
        }, 5000);

        sock.on("close", () => {
            console.log(
                `Server closed: ${sock.remoteAddress} ${sock.remotePort} `
            );
        });

        sock.on("error", (e) => {
            console.log(`Server error: ${e.message}`);
        });
    });

    server.on("listening", () => {
        console.log(`Port: ${port}`);
    });

    server.on("error", (e) => {
        console.log(`Error on port ${port}: ${e.message}`);
    });

    server.listen(port, "127.0.0.1");
    return server;
});
