const net = require('net');

const server = net.createServer(socket => {
  console.log('get a connection');
  socket.end('goodbye\n');
  socket.on('data', data => {
    console.log(data.toString());
  });
}).on('error', err => {
  throw err;
});

//针对connect可以注册两个函数，上面createServer中已经注册了connection事件的函数
// eslint-disable-next-line no-unused-vars
server.on('connection', socket => {
  console.log('get a connection ------------');
});

server.listen(61001, () => {
  console.log('open server on', server.address());
});
