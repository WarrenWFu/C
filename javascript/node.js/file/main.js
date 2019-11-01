
var fs = require('fs');

//获取当前目录和当前文件绝对路径
//console.log(__dirname);
//console.log(__filename);

//检查对应文件是否存在, 存在err为null
fs.access('./abc.txt', fs.constants.W_OK | fs.constants.R_OK, err => {
  console.log(err);
});


