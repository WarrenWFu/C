/*
//继承
function Animal(name) {
  this.name = name;
}

Animal.prototype.eat = function (food) {
  console.log('eating ' + food);
};

function Ferret() {}

//实现继承
Ferret.prototype = new Animal('Tobi');

//通过prototype来重写、调用父类函数
Ferret.prototype.eat = function (food) {
  Animal.prototype.eat.call(this, food);
  console.log(this.name + ' feels so happy');
};

var ferret = new Ferret();

ferret.eat('apple');

var bar = 123;
// bar = (function () {
//   return;
// })();
bar = new function () {return;};

console.log(bar === undefined);
console.log(bar instanceof Object);


*/

/* 
//简单的添加事件
var EventEmitter = require('events').EventEmitter, a = new EventEmitter; //注意这种变量定义方式

a.on('someevent', function () {
  console.log('event called');
});

a.emit('someevent');
 */


/* 
//使用forEach、map
[1, 2, 3].forEach(function (v) {
  console.log(v);
});

var v1 = [1, 2, 3];

var v2 = v1.map(function (v) {
  return v * 2;
});

v2.forEach(function (v) {
  console.log(v);
}); 
*/

/* 
//使用bind来改变上下文
function foo() {
  return this.hello == 'world';
}

var bar = foo.bind({hello: 'world'});
console.log(bar());
 */

/* 
//多重作用域的闭包使用
function foo() {
  var v1 = 'abc';

  function bar() {
    var v2 = '123';

    function baz() {  
      console.log(v1 + ' ' + v2);
    }

    return baz;
  }

  return bar;
}

var v3 = foo()();
v3();
 */
/* 
function wait(message) {
  setTimeout(function timer() {
    console.log(message);
  }, 1000);
}

wait('Hello, closure');
wait('Hello, world');
 */

/* 
//模块模式
function CoolModule() {
  var something = 'cool';
  var another = [1, 2, 3];

  function doSomething() {  
    console.log(something);
  }

  function doAnother() {  
    console.log(another.join('!'));
  }

  return {
    doSomething: doSomething,
    doAnother: doAnother
  };
}

var foo = CoolModule();

foo.doSomething();
foo.doAnother();
 */
/* 
//arguments代表实参数组，函数声明时有没有形参并不影响
function foo () {  
  console.log(arguments);
}

foo({a:1, b:2}, 2);
 */

/* 
//硬绑定包裹函数
function foo() {  
  console.log(this.a);
}

var v1 = {
  a: 2
};

var bar = function () {
  foo.call(v1);
};

bar(); // 2
setTimeout(bar, 100); // 2

bar.call(process); // 2
 */
/* 
//硬绑定的辅助绑定函数
function foo(something) { 
  console.log(this.a, something);
  return this.a + something;
}

function bind(fn, obj) {  
  return function () {  
    return fn.apply(obj, arguments);
  }
}

var obj = {
  a: 2
};

var bar = bind(foo, obj);
var v = bar(3); // 打印2 3
console.log(v); // 打印5
 */
/* 
//使用Function.prototype.bind替代上面的bind
function foo(something) { 
  console.log(this.a, something);
  return this.a + something;
}

var obj = {
  a: 2
};

var bar = foo.bind(obj);
var v = bar(3); // 打印2 3
console.log(v); // 打印5
 */

/* 
//理解数组就是对象，给数组添加属性，如果是数值型属性就会转换成增加或修改数组
var a = [1, 2, 3];
console.log(a.length);
a.foo = 'foo';
console.log(a.length);
a['3'] = 'foo';
console.log(a.length);
a['5'] = 'foo';
console.log(a.length);
console.log(a[4]);
console.log(a[5]);

console.log(a[1]);
a['1'] = 'a';
console.log(a[1]);
 */

/* 
//对象复制
var o1 = {
  a: '1',
  b: '2'
};
console.log(o1);

//使用JSON的parse和stringify方法实现复制
var o2 = JSON.parse(JSON.stringify(o1));
console.log(o2);

//使用ES6的Object.assign方法实现复制
var o3 = Object.assign({}, o1);
console.log(o2);
 */

/* 
//使用getOwnPropertyDescriptor和defineProperty获取和修改属性
var o1 = {
  a: 1
};

console.log(Object.getOwnPropertyDescriptor(o1, 'a'));

Object.defineProperty(o1, 'b', {
  value: 2,
  writable: true,
  configurable: false,
  enumerable: true
});

console.log(o1.b);
delete o1.a;
console.log(o1);
delete o1.b;
console.log(o1);
 */

/* 
//使用Object.create来创建原型继承
function Foo(name) {  
  this.name = name;
}

Foo.prototype.myName = function() {
  return this.name;
};

function Bar(name, label) {
  Foo.call(this, name);
  this.label = label;
}

Bar.prototype = Object.create(Foo.prototype);

Bar.prototype.myLabel = function() {
  return this.label;
}

var v1 = new Bar('v1', 'obj v1');

console.log(v1.myName());
console.log(v1.myLabel());
 */
/* 
//__proto__返回内置的prototype，node支持但不是标准
function Foo(a) {
  this.a = a;
}

var v1 = new Foo('1');
console.log(v1.__proto__ === Foo.prototype);
*/
/* 
//虽然数值是NaN，但是类型还可以是number
var v1 = 2/'foo';
console.log(typeof v1 === 'number'); //打印true
 */

/* 
//简单的Promise调用
var p = new Promise(function(resolve, reject){
  //做一些异步操作
  setTimeout(function(){
    console.log('done');
    //resolve('resolve');
    reject('reject');
  }, 1000);
});

console.log(1);

p.then(function (data) {  
  console.log(data);
}, function (reason, data) {
  console.log(reason);
  console.log(data);
});
 */

/* 
//对应原型的修改会影响到已经new出来的对象
function Foo() {  }
Foo.prototype.bar = function () {
  console.log('from bar');
};

var o1 = new Foo();

o1.bar();
Foo.prototype.fun1 = function () {
  console.log('from fun1');
};

o1.fun1();
*/

/* 
//实现一个阻塞的sleep方法
setTimeout(function () {
  console.log('no');
}, 0);

function sleep(d) {
  for (var i = Date.now(); Date.now() - i <= d;);
}

sleep(3000);

console.log('yes');
 */

/* 
var ma = require('fs');
var mb = require('module_b');

(ma.readFile('./node_modules/module_b.js', (err, data) => {
  if (err)
    throw err;
  console.log(data.toString());
}));
 */
/* 
//slice返回数组中的片段，splice删除数组中的片段，并将删除部分返回
var foo = [1, 2, 3, 4, 5];

console.log(foo.slice(0, 3)); //2个参数表示开始、结束下标不包括结束下标，返回1, 2, 3
console.log(foo.slice(3)); //1个参数表示开始的下标，返回4, 5
console.log(foo.slice(1, -1)); //-1表示最后一个元素的下标，返回2, 3, 4
console.log(foo.slice(-3, -2)); //-3表示倒数第3个元素的下标，返回3

var foo = [1, 2, 3, 4, 5];

console.log(foo.splice(1, 2), foo);
console.log(foo.splice(2), foo);
 */

/* 
//使用Vue.js的语法来定义对象，及其调动时的方法
var app5 = {
  el: '#app-5',
  data: {
    message: 'Hello Vue.js!'
  },
  methods: {
    reverseMessage: function () {
      this.data.message = this.data.message.split('').reverse().join('');
    }
  }
};

//console.log(app5.data.message);
console.log(app5.data.message);
app5.methods.reverseMessage.call(app5);//应该注意使用原生的Vue语法，要这样来调用定义的方法，因为reverseMessage是在methods对象中，说明隐式绑定是不可传递的
console.log(app5.data.message);
 */
/* 
//UTF-8获取字节数
function byteLength(s) {
  var totalLength = 0;
  var charCode;
  for (var i = 0; i < s.length; ++i) {
    console.log('-------------');
    charCode = s.charCodeAt(i);
    if (charCode < 0x0080) {
      ++totalLength;
    } else if (charCode < 0x0800) {
      totalLength += 2;
    } else if (charCode <= 0xffff) {
      totalLength += 3;
    } else {
      totalLength += 4;
    }
  }
  return totalLength;
}

console.log(byteLength('人a民'));
 */
/* 
//获取本地IP地址
const os = require('os');
function getIPAdress() {
  var interfaces = os.networkInterfaces();
  for (var devName in interfaces) {
    var iface = interfaces[devName];
    for (var idx in iface) {
      console.log(`${devName} ${iface[idx].family} ${iface[idx].address} ${iface[idx].internal}`);
      if (iface[idx].family === 'IPv4' && iface[idx].address !== '127.0.0.1' && !iface[idx].internal) {
        return iface[idx].address;
      }
    }
  }
}
console.log(getIPAdress());
 */
/* 
//对象和数组都可以使用forin，要区分还是要通过instanceof或typeof
var foo = {
  v1: 'a',
  v2: 'b',
  v3: 3
};

var bar = ['a', 'b', 3];

for (var v in foo) {
  console.log(v, foo[v]);
}

for (v in bar) {
  console.log(v, bar[v]);
}

console.log(foo instanceof Array);
console.log(typeof foo); //返回object
console.log(bar instanceof Array);
console.log(typeof bar); //返回object
 */
/* 
//函数调用自己的两种方式
function foo() {
  //console.log(++this.counter); //通过this配合call(自己)来调用
  console.log(++foo.counter);  //通过函数名，因为函数也是个对象，此时不需要用call(自己)
}

foo.counter = 0;

console.log(foo.toString());

//foo.call(foo);
//foo.call(foo);
//foo.call(foo);

foo();
foo();
foo();
 */
/* 
//模仿iterator
var it = makeIterator(['a', 'b']);

console.log(it.next().value);
console.log(it.next().value);
console.log(it.next().value);

function makeIterator(array) {
  var nextIndex = 0;

  return {
    next: function () {
      return nextIndex < array.length? 
        { value: array[nextIndex++], done: false } :
        { value: undefined, done: true };
    }
  };
}
 */
/* 
//使用数组的iterator
var foo = ['a', 'b', 'c'];

var it = foo[Symbol.iterator]();

console.log(it.next().value);
console.log(it.next().value);
console.log(it.next().value);
 */
/* 
//for...of
var arr = ['a', 'b', 'c', 'd'];
for (let a in arr) {
  console.log(a);
}

for (let a of arr) {
  console.log(a);
}
 */
/* 
function* helloWorldGenerator() {
  yield 'hello';
  yield 'world';
  return 'ending';
}

var hw = helloWorldGenerator();

console.log(hw.next().value); //返回hello
console.log(hw.next().value); //返回world
console.log(hw.next().value); //返回ending
 */
/* 
function* demo() {
  console.log('Hello' + (yield));
  console.log('Hello' + (yield 123));
}

var it = demo();
//console.log(it.next().value);
//console.log(it.next().value);
it.next();
it.next();
 */
/* 
//理解这个例子
var fs = require('fs');
var readFile = function (fileName) {
  return new Promise(function (resolve, reject) {
    fs.readFile(fileName, function (error, data) {
      if (error) return reject(error);
      resolve(data);
    });
  });
};

var gen = function* () {
  var f1 = yield readFile('./module_a.js');
  var f2 =yield readFile('./module_b.js');
  console.log(f1.toString());
  console.log(f2.toString());
};

var g = gen();

g.next().value.then( function (data) {
  g.next(data).value.then(function (data) {
    g.next(data);
  });
});
 */
/* 
//setTimeout可以传递参数
setTimeout((data) => {
  for (var v1 in data) {
    console.log(v1, data[v1]);
  }
}, 100, '1');
 */

var foo = (data) => console.log(data);

foo('test');
