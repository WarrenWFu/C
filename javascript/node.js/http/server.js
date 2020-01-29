//一个简单的http服务端
const http = require('http');

const server = http.createServer((req, res) => {
  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.end('okay');
});

server.listen(62001, '127.0.0.1', () => {
  console.log('open http server on', server.address());
});
