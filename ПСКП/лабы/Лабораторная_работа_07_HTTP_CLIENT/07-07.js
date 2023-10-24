const fs = require('fs');
const http = require('http');

const options = {
    hostname: 'localhost',
    port: 3000,
    path: '/getFile',
    method: 'GET'
};

const req = http.request(options, (res) => {
    const fileStream = fs.createWriteStream('ReceivedFile.png');

    res.pipe(fileStream);

    fileStream.on('finish', () => {
        console.log('Файл успешно сохранен');
    });
});

req.on('error', (e) => {
    console.error(`Ошибка при отправке запроса: ${e.message}`);
});

req.end();


const server = http.createServer((req, res) => {
    if (req.url === '/getFile' && req.method === 'GET') {
        const fileStream = fs.createReadStream('MyFile.png');

        fileStream.on('open', () => {
            res.setHeader('Content-Type', 'image/png');
            fileStream.pipe(res);
        });

        fileStream.on('error', (err) => {
            console.error('Ошибка при чтении файла:', err);
            res.writeHead(500, { 'Content-Type': 'text/plain' });
            res.end('Internal Server Error');
        });
    } else {
        res.writeHead(404, { 'Content-Type': 'text/plain' });
        res.end('Страница не найдена');
    }
}).listen(3000);