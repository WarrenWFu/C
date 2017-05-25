//使用os.Args就可以获取到命令行参数，Args[0]为args.exe。
package main

import (
	"fmt"
	"os"
)

func main() {
	if len(os.Args) > 0 {
		v := os.Args[0]
		fmt.Printf(v)
	}
}
