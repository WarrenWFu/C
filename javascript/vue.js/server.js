/* 
//一个简单的http服务端
const http = require('http');

const server = http.createServer((req, res) => {
  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.end('okay');
});

server.on('clientError', (err, socket) => {
  socket.end('HTTP/1.1 400 Bad Request\r\n\r\n');
});

server.listen(62001, '127.0.0.1', () => {
  console.log('open http server on', server.address());
});
 */

const http = require('http');
const fs = require('fs');
const os = require('os');

//常量
const expireSeconds = 20; //缓存过期时间，这里为了测试放成常量

const server = http.createServer((req, res) => {
  console.log(req.url);
  console.log(req.headers);

  //var suffix = req.url.substr(-4);
  var suffix = req.url.split('.').slice(-1);
  var headers = {};
  console.log(suffix);
  if ('ico' == suffix) {
    headers['Content-Type'] = 'application/x-ico';
  } else if ('jpg' == suffix) {
    headers['Content-Type'] = 'image/jpeg';
  } else if ('html' == suffix) {
    //直接使用HTML文件中的
    //headers = '';
    //headers['Cache-Control'] = 'max-age=20';
    //headers['Expires'] = 'public, max-age=60';
  } else {
    res.writeHead(404);
    res.end('Not Found');
    return;
  }

  //测试对应文件夹修改第一个参数，默认为__dirname
  fs.access(__dirname + '../' + req.url, fs.constants.R_OK, err => {
    //返回404
    if (err) {
      console.log(err);
      res.writeHead(404);
      res.end('Not Found');
      return;
    }

    //写入last-modified
    var lstModifiedTime = fs.statSync(__dirname + req.url).mtime;
    headers['Last-Modified'] = lstModifiedTime.toGMTString();

    //返回304
    if (req.headers['if-modified-since'] &&
      req.headers['if-modified-since'] == lstModifiedTime.toGMTString()) {
      //更新缓存过期时间
      headers['Cache-Control'] = 'max-age=' + expireSeconds;
      res.writeHead(304, headers);
      res.end();
    } else { //返回200
      //设置缓存过期时间
      headers['Cache-Control'] = 'max-age=' + expireSeconds;
      res.writeHead(200, headers);
      fs.createReadStream(__dirname + req.url).pipe(res);
    }

    var now = new Date();
    var month = now.getMonth() + 1;
    var date = now.getDate();
    var hours = now.getHours();
    var minutes = now.getMinutes();
    var seconds = now.getSeconds();
    console.log(`${month}/${date}-${hours}:${minutes}:${seconds}------------------------------------------------`);
    return;
  });

});

//设置keep
server.on('clientError', (err, socket) => {
  socket.end('HTTP/1.1 400 Bad Request\r\n\r\n');
});

server.on('clientError', (err, socket) => {
  socket.end('HTTP/1.1 400 Bad Request\r\n\r\n');
});

server.listen(61001, getIPAdress(), () => {
  console.log('open http server on', server.address());
});

function getIPAdress() {
  var interfaces = os.networkInterfaces();
  for (var devName in interfaces) {
    var iface = interfaces[devName];
    for (var idx in iface) {
      if (iface[idx].family === 'IPv4' && iface[idx].address !== '127.0.0.1' && !iface[idx].internal) {
        return iface[idx].address;
      }
    }
  }
}
