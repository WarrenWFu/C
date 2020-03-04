//////////////////////////////////////////////////////Promise/////////////////////////////////////////////////////////////////////
/* 
//setTimeout的Promise例子
function timeout(ms) {
  return new Promise((resolve, reject) => {
    setTimeout(resolve, ms, 'done');
  });
}

timeout(50).then((value) => {
  console.log(value);
});
 */
/* 
//理解Promise的执行顺序
let promise = new Promise((resolve, reject) => {
  console.log(1); 
  resolve();
  console.log(2);
});

promise.then(() => {
  console.log(4);
}); 

console.log(3);
*/
/* 
//Promise实现AJAX,浏览器中运行
var getJSON = function (url) {
  var promise = new Promise(function (resolve, reject) {
    var client = new XMLHttpRequest();
    client.open('GET', url);
    client.onreadystatechange = handler;
    client.responseType = 'json';
    client.setRequestHeader('Accept', 'application/json');
    client.send();
    function handler() {
      if (this.readyState !== 4) {
        return;
      }
      if (this.status === 200) {
        resolve(this.response);
      } else {
        reject(new Error(this.statusText));
      }
    }
  });
  return promise;
};

getJSON('/post.json').then(function (json) {
  console.log('Contents: ' + json);
}, function (error) {
  console.log('出错了', error);
});
 */
/* 
async function f() {
  return 'hello world';
}

f().then(v => console.log(v));
*/
/* 
//支持Promise的自动执行
var fs = require('fs');

var readFile = function (fileName) {
  return new Promise((resolve, reject) => {
    fs.readFile(fileName, 'utf8', (err, data) => {
      if (err) return reject(err);
      return resolve(data);
    });
  });
};

var gen = function* () {
  var f1 = yield readFile('./package.json'); //注意赋值是在第二个next()中
  var f2 = yield readFile('./package.json');
  console.log(f1.toString());
  console.log(f2.toString());
}

//var it = gen();
//it.next().value.then(data => {
//  it.next(data).value.then(data => {
//    it.next(data);
//  });
//});

//封装上面那段注掉的
function run(gen) {
  var it = gen();

  function next(data) {
    var res = it.next(data);
    if (res.done) {
      return res.value;
    }

    res.value.then(data => {
      next(data);
    });
  }

  next(); //调用上面那个next，不传参而已
}

run(gen);
 */
/* 
//验证Promise执行顺序
//var foo = new Promise((resolve, reject) => {
var foo = function (data) {
  return new Promise((resolve, reject) => {
    console.log(1);
    setTimeout(resolve, 1000, data);
    console.log(2);
  })
};

foo('yes').then(data => {
  console.log(4);
  console.log(data);
}).catch(err => {
  console.log(err);
});

console.log(3);
*/
/* 
//使用Promise封装TCP服务器，还是适合多重回调的情况，这种情况用Promise感觉多此一举
const net = require('net');

var server = undefined;

var p1 = new Promise((resolve, reject) => {
  return server = net.createServer(resolve);
});

p1.then(socket => {
  console.log('get a connection');
  socket.end('goodbye\n');
  socket.on('data', data => {
    console.log(data.toString());
  });
});

(new Promise((resolve, reject) => {
  return server.on('error', reject);
})).catch(err => {
  if (err.code === 'EADDRINUSE') {
    console.log('Address in use, retrying...');
  }
  throw err;
});

(new Promise((resolve, reject) => {
  return server.on('connect', reject);
})).then(() => {
  console.log('get a connection ------------');
});

(new Promise((resolve, reject) => {
  return server.listen({
    host: 'localhost',
    port: 61001,
    backlog: 100,
    exclusive: false //默认为false
  }, resolve);
})).then(() => {
  console.log('open server on', server.address());
});
 */
/////////////////////////////////////////////////////Generator/////////////////////////////////////////////////////////////////////
/* 
//理解Generator函数的执行逻辑
const fs = require('fs');

function* foo() {  
  console.log('1'); //只有执行了next,才能到这句
  yield console.log('2'); //第一个next执行

  yield fs.readFile('./package.json', 'utf8', (err, data) => { //第二个next执行此句，但是注意本身是一个异步函数，其回调还是要下一轮执行
    if (err) throw err;
    
    console.log('5');
  });

  console.log('4'); //第三个next执行
}

var it = foo();
it.next();
console.log('3');
it.next();
it.next();
 */
/* 
//使用throw
function* gen(x) {
  try {
    var y = yield x + 1;
  } catch (e) {
    console.log(e);
  }
  return y;
}

var g = gen(1);
g.next();
g.throw('出错了');
 */
/* 
//使用thunk函数来让Generator顺序执行
const thunkify = require('D:\\program\\node-v10.5.0-win-x64\\node_modules\\thunkify');
const fs = require('fs');

var readFileThunk = thunkify(fs.readFile);

function* gen() {
  var r1 = yield readFileThunk('./package.json', 'utf8');
  console.log(r1);
  var r2 = yield readFileThunk('./package.json', 'utf8');
  console.log(r2);
}

var g = gen();
var r1 = g.next();
r1.value((err, data) => {
  if (err) throw err;
  var r2 = g.next(data);
  r2.value((err, data) => {
    if (err) throw err;
    g.next(data);
  });
});
 */
/*  
//了解async函数的执行顺序
const fs = require('fs');

var readFile = function (fileName) {
  return new Promise((resolve, reject) => {
    fs.readFile(fileName, 'utf8', (err, data) => {
      if (err) return reject(err);
      return resolve(data);
    });
  });
};

async function asyncReadFile() {
  console.log(2);
  await console.log(3); //先执行console.log(3),然后将其返回值转换为Promise
  var r1 = await readFile('./package.json');
  console.log(r1);
  var r2 = await readFile('./package.json');
  console.log(r2);
  console.log(5);
}

console.log(1);
asyncReadFile();
console.log(4);
 */

