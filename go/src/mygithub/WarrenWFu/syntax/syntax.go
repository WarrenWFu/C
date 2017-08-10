package main

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
