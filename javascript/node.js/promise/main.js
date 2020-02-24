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
