package main

import (
	"log"
	"net"
	"runtime"
	"time"
)

func main() {
	//设置CPU个数
	runtime.GOMAXPROCS(4)

	l, err := net.Listen("tcp", ":50001")

	if err != nil {
		log.Fatal(err)
	}

	defer l.Close()

	for {
		conn, err := l.Accept()
		if err != nil {
			log.Fatal(err)
		}

		//匿名函数
		go func(c net.Conn) {
			defer c.Close()

			var buf = make([]byte, 512)
			for {
				cnt, err := c.Read(buf)
				if err != nil {
					log.Printf("接收失败，原因[%s]", err)
					return
				}

				time.Sleep(10)

				if _, err := c.Write(buf[:cnt]); err != nil {
					log.Printf("发送失败，原因[%s]", err)
					return
				}
			}
		}(conn)
	}
}
