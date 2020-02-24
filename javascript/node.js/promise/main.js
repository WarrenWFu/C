//一个简单的promise例子
function getNumber() {
  var p = new Promise(function (resolve, reject) {
    //做一些异步操作
    setTimeout(function () {
      var num = Math.ceil(Math.random() * 10); //生成1-10的随机数
      if (num <= 9) {
        resolve(num);
      }
      else {
        reject('数字太大了');
      }
    }, 2000);
  });
  return p;
}

getNumber()
  .then(function (data) {
    console.log('resolved');
    console.log(data);
    console.log(somedata); //此处的somedata未定义
  })
  .catch(function (reason) {
    console.log('rejected');
    console.log(reason);
  });
