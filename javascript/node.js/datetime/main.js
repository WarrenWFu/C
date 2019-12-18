//JS本身的时间函数,local time指的是本地时区, UTC函数是基于协调世界时
var fooDate = new Date();

//基于local time,获取年(1000-9999)
console.log(fooDate.getFullYear());
//基于local time,获取月,开始于0
console.log(fooDate.getMonth()+1);
//基于local time, 获取日
console.log(fooDate.getDate());
//基于local time,获取本周第几天，
console.log(fooDate.getDay());
//基于local time,获取小时
console.log(fooDate.getHours());
//基于local time,获取分钟
console.log(fooDate.getMinutes());
//基于local time,获取秒
console.log(fooDate.getSeconds());
//基于local time,获取毫秒
console.log(fooDate.getMilliseconds());
