//一个简单的TCP服务端
const net = require('net');
/* const fs = require('fs');

fs.writeFile('./test.txt', '123', err => {
  if (err) {
    console.log('writeFile error ' + err);
    throw err;
  }
});
 */
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

//返回监听的地址
server.listen(61001, () => {
  console.log('open server on', server.address());
});
