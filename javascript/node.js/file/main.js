
var fs = require('fs');

//获取当前目录和当前文件绝对路径
//console.log(__dirname);
//console.log(__filename);

/* 
//检查对应文件是否存在, 存在err为null
fs.access('./test.txt', fs.constants.W_OK | fs.constants.R_OK, err => {
  console.log(err);
});
 */

//获取文件的权限，创建、访问和修改时间
//console.log(fs.statSync('./test.txt').mtime);

//异步读取整个文件, 如果没有encoding则返回ascii十进制的Buffer，否则是一个原生string
//fs.readFile('./test.txt', (err, data) => {
var foo = fs.readFile('./test.txt', 'utf8', (err, data) => {
  if (err) throw err;
  console.log(typeof data);
  console.log(data);
});

console.log(typeof foo);

