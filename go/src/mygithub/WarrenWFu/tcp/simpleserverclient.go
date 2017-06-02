package main

import (
	"fmt"
	"log"
	"net"
)

func main() {
	///* 服务端 */
	//bQuit := false
	//listen, err := net.Listen("tcp", ":50001")
	//if err != nil {
	//	log.Fatal(err)
	//}

	//for {
	//	conn, err := listen.Accept()
	//	if err != nil {
	//		log.Println(err)
	//		time.Sleep(5 * 10e9)
	//	}

	//	if bQuit {
	//		break
	//	}

	//	go func(conn net.Conn) {
	//		log.Println("获取到一个连接")

	//		bsTmp := make([]byte, 1000)
	//		n, err := conn.Read(bsTmp)
	//		if err != nil {
	//			log.Println(err)
	//		} else {
	//			log.Printf("读到了%d个字节", n)
	//			log.Printf("内容[%s]", bsTmp)
	//		}

	//		//if reflect.DeepEqual(bsTmp, "quit")
	//		if sTmp := string(bsTmp); strings.Contains(sTmp, "/quit") {
	//			bQuit = true
	//		}

	//		conn.Close()
	//	}(conn)
	//}

	/* 客户端 */
	const sAddr = "127.0.0.1:50001"

	conn, err := net.Dial("tcp", sAddr)

	if err != nil {
		log.Fatal(err)
	}

	bsMsg := make([]byte, 128)

	log.Println("请输入要发送的信息")

	_, err = fmt.Scan(&bsMsg)
	if err != nil {
		log.Fatal(err)
	}

	conn.Write(bsMsg)

	conn.Close()
}
