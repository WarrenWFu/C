package main

import (
	"bufio"
	"io"
	"io/ioutil"
	"log"
	"os"
)

func main() {
	var sFilePath = "./test.txt"

	//判断文件是否存在
	if _, err := os.Stat(sFilePath); os.IsNotExist(err) {
		log.Println(err)
	}

	//打开文件,这里用了O_CREATE标志，也可以使用os.Create来创建
	f, err := os.OpenFile(sFilePath, os.O_RDWR|os.O_CREATE, 0755)
	if err != nil {
		log.Fatal(err)
	}
	//关闭文件
	defer f.Close()

	//使用io.WriteString来写文件
	var sTmpA = "测试\n"
	var bsTmpA = []byte(sTmpA)
	if n, err := io.WriteString(f, sTmpA); err != nil {
		log.Println(err)
	} else {
		log.Printf("写入了%d个字节", n)
	}

	//使用 *File.Write和*File.WriteString来写入文件
	if n, err := f.Write(bsTmpA); err != nil {
		log.Println(err)
	} else {
		log.Printf("写入了%d个字节", n)
	}

	if n, err := f.WriteString(sTmpA); err != nil {
		log.Println(err)
	} else {
		log.Printf("写入了%d个字节 ", n)
	}

	//使用ioutil.WriteFile来写文件, 注意这是重新写入
	var sFilePathB = "./test1.txt"
	if err = ioutil.WriteFile(sFilePathB, bsTmpA, 0666); err != nil {
		log.Println(err)
	}

	//使用bufio.NewWriter写入
	w := bufio.NewWriter(f)
	if n, err := w.WriteString(sTmpA); err != nil {
		log.Println(err)
	} else {
		w.Flush() //注意一定要Flush，否则并没有真的写进去
		log.Printf("写入了%d个字节 ", n)
	}

}
