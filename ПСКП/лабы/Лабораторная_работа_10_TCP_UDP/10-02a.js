const net = require('net');


const serverPort = parseInt(process.argv[2]);
const X = parseInt(process.argv[3]);

const client = new net.Socket();

client.connect(serverPort, '127.0.0.1', () => {
    console.log(`Connected to server on port ${serverPort}`);

    setInterval(() => {
        const buf = Buffer.alloc(4);
        buf.writeInt32LE(X, 0);
        client.write(buf);
    }, 1000);
});

client.on('data', (data) => {
    const sum = data.readInt32LE();
    console.log(`Sum from server: ${sum}`);
});

client.on('close', () => {
    console.log('Connection to server closed');
});

client.on('error', (e) => {
    console.log(`Client error: ${e.message}`);
});

