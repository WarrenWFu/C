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

console.log();
console.log();
