package main

import (
	"fmt"
)

//用这种方式保留import的包？
func useless() {
	fmt.Println()
}

/*
//使用os.Args就可以获取到命令行参数，Args[0]为执行程序本身带全路径。
func main() {
	if len(os.Args) > 0 {
		v := os.Args[0]
		fmt.Printf(v)
	}
}

*/

/*
//description 使用func foo() (error){...} 来匹配type hook func() error函数类型
type hook func() error

func foo() error {
	log.Println("test")

	return nil
}

func main() {
	var bar hook = foo
	bar()
}
*/

/*
//description 如果map找不到则ok为false
func main() {
	m := make(map[string]int, 10)

	m["1"] = 1
	m["2"] = 2
	m["3"] = 3
	m["4"] = 4

	if _, ok := m["5"]; !ok {
		log.Printf("not found")
	}

	for k, v := range m {
		log.Printf("key[%s]value[%d]", k, v)
	}
}
*/

/*
//description 接口可以内嵌到struct中

//Fooer test
type Fooer interface {
	Foo()
}

//Bar test
type Bar struct {
	x int
	Fooer
}

func main() {
	bar := Bar{x: 10}
	var barB Fooer

	barB = bar

	log.Println(barB)
}
*/

/*
//description 超过slice范围的取值抛出panic
func main() {
	s := []string{"1"}
	fmt.Println("len(nil) = ", len(s[1]))
}
*/

/*
//使用strconv库的函数来进行字符串转换操作，执行时直接go run syntax.go 100
func main() {
	if v, err := strconv.Atoi(os.Args[1]); err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(v)
	}
}
*/

/*
//description 编译错误，字符串初始化后不能修改
func main() {
	s := "hello"
	s[1] = 'X'

	fmt.Println(s)
}
*/

/*
//description 因为本源码编码是utf-8存储的时候是按照utf-8存储的，每个汉子三个字节
//使用range遍历的话，是转换成rune，代表的是unicode不是utf-8
func main() {
	s := "hello,世界"

	//	for i := 0; i < len(s); i++ {
	//		fmt.Println(i, s[i])
	//	}

	for i, ch := range s {
		fmt.Println(i, ch)
	}
}
*/

/*
//description 两个函数列表相同的接口是可以相互转换的
type Foo interface {
	function1()
	function2() int
}

type Bar interface {
	function1()
	function2() int
}

type Struct struct {
	Foo
}

func (s Struct) function1() {
}

func (s Struct) function2() int {
	return 1
}

func (s Struct) String() string {
	return fmt.Sprint("from String")
}

func main() {
	var s Foo = Struct{}

	if s2, ok := s.(Bar); ok {
		fmt.Println("实现了Bar", s2)
		s2.function1()
	} else {
		fmt.Println("没实现Bar", s)
	}
}
*/

/*
//description 使用锁lock.Lock()的简单例子
var counter int = 0

func Count(lock *sync.Mutex) {
	lock.Lock()
	counter++
	fmt.Println(counter)
	lock.Unlock()
}
func main() {
	lock := &sync.Mutex{}
	for i := 0; i < 10; i++ {
		go Count(lock)
	}
	for {
		lock.Lock()
		c := counter
		lock.Unlock()
		runtime.Gosched()
		if c >= 10 {
			break
		}
	}
}
*/

/*
//description select中的case执行不是按照从上到下的顺序执行的，而是随机的。
func main() {
	counter := 0
	ch := make(chan int, 1)
	for {
		select {
		case ch <- 0:
		case ch <- 1:
		}
		i := <-ch
		fmt.Println("Value received:", i)
		counter++
		if counter > 10 {
			break
		}
	}
}
*/
/*
//description 一个简单的渲染
type Person struct {
	userName string
}

func main() {
	t := template.New("fieldname example")
	t, _ = t.Parse("hello {{.userName}}!")
	p := Person{UserName: "Astaxie"}
	t.Execute(os.Stdout, p)
}
*/
/*
//description 一个嵌套渲染
type Friend struct {
	Fname string
}

type Person struct {
	UserName string
	Emails   []string
	Friends  []*Friend
}

func main() {
	f1 := Friend{Fname: "minux.ma"}
	f2 := Friend{Fname: "xushiwei"}
	t := template.New("fieldname example")
	t, _ = t.Parse(`hello {{.UserName}}!
			{{range .Emails}}
				an email {{.| html}}
			{{end}}
			{{with .Friends}}
			{{range .}}
				my friend name is {{.Fname}}
			{{end}}
			{{end}}
			`)
	p := Person{UserName: "Astaxie",
		Emails:  []string{"astaxie@beego.me", "astaxie@gmail.com"},
		Friends: []*Friend{&f1, &f2}}
	t.Execute(os.Stdout, p)
}
*/

/*
//每次const出现导致iota重置为0，每次iota出现递增1，所以注意const要用()包围，不要每行写一个
const a = iota
const b = iota //b也是0

func main() {
	fmt.Println(a, b)
}
*/

/*
//删除slice中一项, 比如下面是删除第二项
func main() {
	s := []int{1, 2, 3, 4}
	var s1 []int

	for i, v := range s {
		if v != 2 {
			s1 = append(s1, s[i])
		}
	}
	fmt.Println(s, " ", len(s), " ", cap(s))    //len为4，cap为4
	fmt.Println(s1, " ", len(s1), " ", cap(s1)) //len为3，cap为4
}

*/

/*
//字符串也可以使用range来遍历
func main() {
	s := "abc"

	for i, v := range s {
		fmt.Println(i, " ", v)
	}
}
*/
/*
//判断文件是否存在
func main() {
	_, err := os.Stat(filename)
	if err == nil || os.IsExist(err) {
		fmt.Println("文件存在")
	}
}
*/

/*
//[]byte转string, string转[]byte
func main() {
	//bs := []byte{'a', 0, 'b'}
	bs := []byte{'a', '1', 0, 'c', 'b'}
	n := bytes.IndexByte(bs, 0)
	s := string(bs[:n])
	fmt.Println(s)

	bs2 := []byte(s)
	fmt.Println(bs2)

}
*/

/*
//简单的调用shell命令
func main() {
	cmd := exec.Command("mkdir", "-p", "abc")
	cmd.Run()
}

*/

/*
//range数组得到的是数组下标和数组里面的值
func main() {
	bs := []byte{6, 5, 4}

	for i, v := range bs { //如果没有v也是可以的只轮询下标
		fmt.Println(i, " ", v)
	}
}
*/

/*
//strconv.ParseInt不能parse任何非数值的字符串
func main() {
	i, err := (strconv.ParseInt("2_1", 0, 0))
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(i)
	}

}
*/

/*
//二维数组(slice)的遍历
func main() {
	var matrix [5][4]*int
	//	matrix := make([][]*int, 5)
	//	for i := range matrix {
	//		matrix[i] = make([]*int, 4)
	//	}

	fmt.Println(len(matrix)) //打印的是行数而不是总数

	for _, v := range matrix {
		for iB, vB := range v {
			if vB == nil {
				fmt.Println(iB)
			}
		}
	}
}

*/

/*
//string与[]byte可以直接进行转换
func main() {
	s := "人"

	fmt.Println(len(s))
	fmt.Println(len([]byte(s)))

	n := []byte(s)

	for _, v := range n {
		fmt.Println(v)
	}
}
*/

/*
//就算strings.Split的第一个参数为空string，也至少返回长度为1的数组
func main() {
	var s string = ""

	ss := strings.Split(s, " ")
	for _ = range ss {
		fmt.Println("get one")
	}
}

*/

/*
//参数可变函数，也可以不传参数调用
func foo(s ...string) {
	for _, v := range s {
		fmt.Println(v)
	}
}

func main() {
	//foo("123")
	foo()
}
*/

/*
//通过反射获取结构体中的字段名称
type foo struct {
	name string
	desc string
}

func main() {
	f := foo{"fym", "good"}

	t := reflect.TypeOf(&f) //注意参数最好使用引用语义，否则Elem会报错

	fmt.Println(t.Elem().NumField()) //获取成员个数
	fmt.Println(t.Elem().Field(0).Name)
	fmt.Println(t.Elem().Field(1).Name)
}
*/

/*
//通过类型switch来检查类型，可惜type switch不能fallthrough，还是有很多重复代码
type foo struct {
	name string
	desc string
}

type bar struct {
	name string
}

func main() {
	var s interface{}

	s = &foo{"fym", "good"}

	switch v := s.(type) {
	case *foo:
		t := reflect.TypeOf(v)
		fmt.Println(t.Elem().Name())     //获取结构体名，如果是s是结构体，可以直接t.Name()
		fmt.Println(t.Elem().NumField()) //获取成员个数
		fmt.Println(t.Elem().Field(0).Name)
		fmt.Println(t.Elem().Field(1).Name)
	case *bar:
		t := reflect.TypeOf(v)
		fmt.Println(t.Elem().Name())
		fmt.Println(t.Elem().NumField()) //获取成员个数
		fmt.Println(t.Elem().Field(0).Name)
		fmt.Println(t.Elem().Field(1).Name)
	default:
		fmt.Println("unknown")
	}

}
*/

/*
//byte、rune、string之间的关系
func replaceAtIndex(in string, r rune, i int) string {
	out := []rune(in)
	out[i] = r
	fmt.Println(len(out)) //这里是3，表示为3个rune
	return string(out)    //这里自动转成了byte数组
}

func main() {
	rs, l := utf8.DecodeRuneInString("人") //注意因为本文件是utf-8的，所以这个“人”三个字节
	fmt.Println(l)                        //因为“人”是三个字节，所以l是3

	s2 := string(rs) //此时将rune转成了byte数组即string，即unicode转成了utf-8类型
	pc := []byte(s2)
	fmt.Printf("%x\n", pc[0])
	fmt.Printf("%x\n", pc[1])
	fmt.Printf("%x\n", pc[2])

	s := "123"
	fmt.Println(len(s))                  //此时是3
	s = replaceAtIndex(s, '人', len(s)-1) //最神奇的是这里utf-8的‘人‘自动转成了rune传入，这就导致这个函数会改变原来字符串的长度
	fmt.Println(len(s))                  //此时是5
	fmt.Println(s)
}
*/

/*
//nil指针同样可以调用method，method中不能对receiver进行操作
type DbOpr interface {
	query()
}

type Foo struct {
	name string

	DbOpr //此句可包含可不包含，建议不要包含，这样就可以松耦合
}

func (*Foo) query() {
	//f.name = "abc"

	fmt.Println("from query")
}

func main() {
	var foo *Foo

	if foo == nil {
		fmt.Println("isNil")
	}

	foo.query()       //可以直接调用虽然此时foo是nil
	(*Foo).query(nil) //也可以通过这种方式调用
}
*/

/*
//和C一样，不能假设int为4字节或8字节，只能保证至少为4字节，所以建议使用int64代替
func main() {
	var i int
	fmt.Println(unsafe.Sizeof(i))
}
*/

/*
//可以直接使用errors包来生成error实例
func main() {
	var e error
	e = errors.New("这是错误")

	fmt.Println(e)
}
*/

/*
//defer是只有在函数退出时才执行，而不是离开作用域的时候执行，下面的222还是最后打印
func main() {
	if len(os.Args) == 1 {
		fmt.Println("111")

		defer fmt.Println("222")
	}
	fmt.Println("333")
}
*/
