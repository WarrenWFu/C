package main

import (
	"fmt"
)

/*
//使用os.Args就可以获取到命令行参数，Args[0]为args.exe。
func main() {
		if len(os.Args) > 0 {
			v := os.Args[0]
			fmt.Printf(v)
		}
}
*/

/*
//使用func foo() (error){...} 来匹配type hook func() error函数类型
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
//如果map找不到则ok为false
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
func main() {
	fmt.Println("begin")
}
