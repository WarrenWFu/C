
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
console.log(fs.statSync('./test.txt').mtime);


