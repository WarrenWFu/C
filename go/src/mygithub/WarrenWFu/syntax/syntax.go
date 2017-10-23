package main

import (
	"encoding/json"
	"fmt"

	_ "github.com/mattn/go-sqlite3"
)

//用这种方式保留import的包？
func useless() {
	fmt.Println()
}

/*
//类型switch
	switch f := arg.(type) {
	case bool:
		p.fmtBool(f, verb)
	case float32:
		p.fmtFloat(float64(f), 32, verb)
	case float64:
		p.fmtFloat(f, 64, verb)
	case complex64:
		p.fmtComplex(complex128(f), 64, verb)
	case complex128:
		p.fmtComplex(f, 128, verb)
	case int:
		p.fmtInteger(uint64(f), signed, verb)
	case int8:
		p.fmtInteger(uint64(f), signed, verb)
	case int16:
		p.fmtInteger(uint64(f), signed, verb)
	case int32:
		p.fmtInteger(uint64(f), signed, verb)
	case int64:
		p.fmtInteger(uint64(f), signed, verb)
	case uint:
		p.fmtInteger(uint64(f), unsigned, verb)
	case uint8:
		p.fmtInteger(uint64(f), unsigned, verb)
	case uint16:
		p.fmtInteger(uint64(f), unsigned, verb)
	case uint32:
		p.fmtInteger(uint64(f), unsigned, verb)
	case uint64:
		p.fmtInteger(f, unsigned, verb)
	case uintptr:
		p.fmtInteger(uint64(f), unsigned, verb)
	case string:
		p.fmtString(f, verb)
	case []byte:
		p.fmtBytes(f, verb, "[]byte")
	case reflect.Value:
		// Handle extractable values with special methods
		// since printValue does not handle them at depth 0.
		if f.IsValid() && f.CanInterface() {
			p.arg = f.Interface()
			if p.handleMethods(verb) {
				return
			}
		}
		p.printValue(f, verb, 0)
	default:
		// If the type is not simple, it might have methods.
		if !p.handleMethods(verb) {
			// Need to use reflection, since the type had no
			// interface methods that could be used for formatting.
			p.printValue(reflect.ValueOf(f), verb, 0)
		}
	}
*/

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
//通过类型switch来检查类型，还是有很多重复代码
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

/*
//使用:=声明变量时，如果左侧的变量在本作用域中声明则不新建，否则新建一个覆盖外部同名变量
func main() {
	var err error

	j, err := func(i int) (int, error) { //这里尽管j为新建变量，err没有被从重建
		return i + 1, errors.New("error")
	}(0)
	_ = j

	if err == nil {
		fmt.Println("nil")
	} else {
		fmt.Println("not nil")
	}

	err = nil

	if len(os.Args) == 1 {
		i, err := func(i int) (int, error) { //这里因为i为新建变量，导致err也被新建
			return i + 1, errors.New("error")
		}(0)
		_ = i
		_ = err
	}

	if err == nil {
		fmt.Println("nil")
	} else {
		fmt.Println("not nil")
	}
}
*/

/*
//defer按照出现的相反顺序执行
func main() {
	defer fmt.Println("1")
	defer fmt.Println("2")
	defer fmt.Println("3")
	defer fmt.Println("4")
	defer fmt.Println("5")
	defer fmt.Println("6")
	defer fmt.Println("7")
	defer fmt.Println("8")
	defer fmt.Println("9")
	defer fmt.Println("10")
}
*/

/*
//使用这种方式实现defer对值语义变量的抓取
func foo(err *error) {
	if *err != nil {
		fmt.Println(*err)
	} else {
		fmt.Println("nil")
	}
}

func main() {
	var err error
	defer foo(&err)

	err = errors.New("为了测试")
}
*/

/*
//json处理数组
type Foo struct {
	Id   int
	Name string
}

func main() {
	res := []Foo{{1, "Tom"}, {2, "Jerry"}}

	s, _ := json.Marshal(res)
	fmt.Println(string(s))
}
*/

/*
type Foo struct {
	i int
}

//Go的数组可以很方便的储存多种类型的数据，对象和对象指针不能弄混
func main() {
	var params []interface{}

	params = append(params, 1)
	params = append(params, '人')
	params = append(params, "abc")
	params = append(params, Foo{1})

	for _, v := range params {
		switch v.(type) {
		case int:
			fmt.Println("int")
		case rune:
			fmt.Println("rune")
		case string:
			fmt.Println("string")
		case Foo: //*Foo和Foo不同
			fmt.Println("Foo")
		default:
			fmt.Println("unknown")
		}
	}
}
*/

/*
//初始化的时候可以什么都不填
type Foo struct {
	i int
	s string
}

func main() {
	var p interface{}
	p = &Foo{}

	fmt.Printf("%T\n", p)
	fmt.Printf("%d\n", p.(*Foo).i)
	fmt.Printf("%s\n", p.(*Foo).s)
}
*/

/*
//数据库操作参考
//MyError 结构表示自定义error
type MyError struct {
	desc string
}

func (m MyError) Error() string {
	return m.desc
}

func initDb(db *sql.DB) error {
	//建表
	sqlStmt := `
		CREATE TABLE FOO (ID INTEGER PRIMARY KEY AUTOINCREMENT, NAME CHAR(60) NOT NULL,
	ID2 INTEGER, NAME2 CHAR(60) NOT NULL);
		`
	var err error
	if _, err = db.Exec(sqlStmt); err != nil {
		return err
	}

	//默认用户
	sqlStmt = `INSERT INTO FOO(NAME, ID2, NAME2) VALUES('fym', 0, 'fym2')`
	if _, err = db.Exec(sqlStmt); err != nil {
		return err
	}

	return nil
}

type Foo struct {
	Id    int64
	Name  string
	Id2   int64
	Name2 string
}

func openTransaction(db *sql.DB) (*sql.Tx, error) {
	tx, err := db.Begin()
	if err != nil {
		return nil, err
	}

	return tx, nil
}

func insertSql(tx *sql.Tx, i interface{}) (int64, error) {
	if i == nil {
		return -1, errors.New("i不能为nil")
	}

	s := "INSERT INTO "
	s2 := " VALUES("
	val := reflect.ValueOf(i)
	if val.Kind() == reflect.Ptr {
		val = val.Elem() //如果是指针则获取其指向的值
	}

	var params []interface{}
	ts := val.Type()
	s += ts.Name() + "("
	for i := 0; i < val.NumField(); i++ {
		//		fmt.Println(ts.Field(i).Name) //获取val表示的结构体中字段的名称
		//		f := val.Field(i)
		//		fmt.Println(f.Type())      //获取字段的类型
		//		fmt.Println(f.Interface()) //获取字段的值
		if ts.Field(i).Name == "Id" {
			continue
		}
		s += ts.Field(i).Name + ","
		s2 += "?,"
		f := val.Field(i)
		params = append(params, f.Interface())
	}
	s = strings.Trim(s, ",")
	s += ")"
	s2 = strings.Trim(s2, ",")
	s2 += ")"

	s += s2
	log.Println(s)

	stmt, err := tx.Prepare(s)
	if err != nil {
		return -1, err
	}
	defer stmt.Close()

	res, err := stmt.Exec(params...)
	if err != nil {
		return -1, err
	}

	id, err := res.LastInsertId()
	if err != nil {
		return -1, err
	}

	return id, nil
}

func deleteSql(tx *sql.Tx, i interface{}, cond string) error {
	s := "DELETE FROM "
	val := reflect.ValueOf(i)
	if val.Kind() == reflect.Ptr {
		val = val.Elem()
	}

	s += val.Type().Name() + " "
	s += cond
	log.Println(s)

	_, err := tx.Exec(s)
	if err != nil {
		return err
	}

	return nil
}

func updateSql(tx *sql.Tx, i interface{}, cond string) error {
	if i == nil {
		return MyError{"o不能为nil"}
	}

	s := "UPDATE "
	val := reflect.ValueOf(i)
	if val.Kind() == reflect.Ptr {
		val = val.Elem() //如果是指针则获取其指向的值
	}

	var params []interface{}
	ts := val.Type()
	s += ts.Name() + " SET "
	for i := 0; i < val.NumField(); i++ {
		if ts.Field(i).Name == "Id" {
			continue
		}

		f := val.Field(i)
		//略过不想要设置的字段
		switch v := f.Interface().(type) {
		case float32:
			if v < 0 {
				continue
			}
		case float64:
			if v < 0 {
				continue
			}
		case int:
			if v < 0 {
				continue
			}
		case int8:
			if v < 0 {
				continue
			}
		case int16:
			if v < 0 {
				continue
			}
		case int32:
			if v < 0 {
				continue
			}
		case int64:
			if v < 0 {
				continue
			}
		case string:
		default:
			if reflect.TypeOf(v).Kind() == reflect.Ptr {
				log.Println("指针略过")
			}
			return MyError{"结构体字段不合格"}
		}

		s += ts.Field(i).Name + "=?,"
		params = append(params, f.Interface())
	}
	s = strings.Trim(s, ",")
	s += " " + cond

	log.Println(s)

	stmt, err := tx.Prepare(s)
	if err != nil {
		return err
	}
	defer stmt.Close()

	_, err = stmt.Exec(params...)
	if err != nil {
		return err
	}

	return nil
}

func (v *Foo) selectSql(tx *sql.DB, cond string, isExist bool) (res []*Foo, err error) {
	s := "SELECT * FROM FOO "
	s += cond

	rows, err := tx.Query(s)
	if err != nil {
		return nil, err
	}
	defer rows.Close()

	for rows.Next() {
		var tmp Foo
		if err = rows.Scan(&(tmp.Id), &(tmp.Name), &(tmp.Id2), &(tmp.Name2)); err != nil {
			return nil, err
		}
		res = append(res, &tmp)
	}

	if isExist && len(res) == 0 {
		return nil, MyError{"记录未找到"}
	}

	return res, nil
}

func main() {
	//设置log打印信息
	log.SetFlags(log.LstdFlags | log.Lshortfile)

	dbLocation := "public.db"

	var err error
	db, err := sql.Open("sqlite3", dbLocation)
	if err != nil {
		log.Printf("连接数据库错误，原因[%s]\n", err)
		return
	}
	defer db.Close()

	//不存在则创始化创建表
	if _, err = os.Stat(dbLocation); os.IsNotExist(err) {
		log.Println("创建public库")
		if err = initDb(db); err != nil {
			log.Printf("初始化数据库错误，原因[%s]\n", err)
			return
		}
	} else if err != nil {
		log.Printf("查看数据库文件失败，原因[%s]\n", err)
		return
	}

	tx, err := openTransaction(db)
	if err != nil {
		log.Printf("查看数据库文件失败，原因[%s]\n", err)
		return
	}
	defer func() {
		if p := recover(); p != nil {
			tx.Rollback()
			panic(p)
		} else if err != nil {
			tx.Rollback()
		} else {
			_ = tx.Commit()
		}
	}()

	//	for i := 0; i < 10; i++ {
	//		id, err := insertSql(tx, Foo{0, "rich", 1, "rich"})
	//		if err != nil {
	//			log.Println(err)
	//			break
	//		} else {
	//			log.Println(id)
	//		}
	//	}

	//	var foo Foo
	//	err = deleteSql(tx, &foo, "WHERE ID2 = 1")
	//	if err != nil {
	//		log.Println(err)
	//		return
	//	}

	//	foo := Foo{0, "poor", -1, "poor"}
	//	err = updateSql(tx, foo, "WHERE ID2 = 1")
	//	if err != nil {
	//		log.Println(err)
	//		return
	//	}

	var foo Foo
	res, err := foo.selectSql(db, "WHERE ID2 = 1", true)
	if err != nil {
		log.Println(err)
		return
	}

	for _, v := range res {
		log.Println(*v)
	}
}

*/

///*
//JSON也可以保存二维数组
func main() {
	ss := [][]string{{"00", "01", "02"}, {"10", "11", "12"}}

	s, _ := json.Marshal(ss)
	fmt.Println(string(s))
	//fmt.Println(ss)
}

//*/

//func quickSort(s []int) []int {
//	if len(s) == 0 || len(s) == 1 {
//		return s
//	}
//
//	base := s[0]
//	i := 1
//	j := len(s)-1
//
//	for {
//		if i == j {
//			quickSort(s[0:i])
//			if i >= len(s)
//			quickSort(s[i+1:])
//		}
//
//		if s[j] > base {
//			j--
//		} else if s[i] < base {
//			i++
//		}
//
//		else {
//			tmp := s[j]
//			s[j] = s[i]
//			s[i] = tmp
//		}
//	}
//
//	return s
//}

/*
//快排算法
func swap(a int, b int) (int, int) {
	return b, a
}

func partition(aris []int, begin int, end int) int {
	pvalue := aris[begin]
	i := begin
	j := begin + 1
	for j < end {
		if aris[j] < pvalue {
			i++
			aris[i], aris[j] = swap(aris[i], aris[j])
		}
		j++
	}
	aris[i], aris[begin] = swap(aris[i], aris[begin])
	return i
}

func quickSort(aris []int, begin int, end int) {
	if begin+1 < end {
		mid := partition(aris, begin, end)
		quickSort(aris, begin, mid)
		quickSort(aris, mid+1, end)
	}
}

func main() {
	is := []int{5, 2, 1, 9, 8, 6, 4, 3, 7, 0, 10}
	quickSort(is, 0, len(is))

	fmt.Println(is)
}
*/
