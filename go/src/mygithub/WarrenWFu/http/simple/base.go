package main

import (
	"fmt"
	"html/template"
	"log"
	"net/http"
)

type helloHandler struct{}

func (h *helloHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	w.Write([]byte("Hello World!"))

}

func login(w http.ResponseWriter, r *http.Request) {
	//r.Method返回http请求的方法
	fmt.Println("method", r.Method)
	fmt.Println("请求头", r.Header)
	bsBody := make([]byte, 1024)
	r.Body.Read(bsBody)
	///注意这是将[]byte转换成string方便打印,取了下面就读不出来了
	fmt.Println("请求体", string(bsBody))
	if r.Method == "GET" {
		t, _ := template.ParseFiles("login.gtpl")
		log.Println(t.Execute(w, nil))
	} else {
		//使用FormValue自动调用ParseForm，返回POST或PUT的第一个对应的值，
		//使用Form要显式调用，但可以加上[]
		fmt.Println("username", r.FormValue("username"))
		r.ParseForm()
		//fmt.Println("username", r.Form["username"])
		fmt.Println("password", r.Form["password"])
	}
}

func main() {
	http.Handle("/", &helloHandler{})
	http.HandleFunc("/login", login)

	err := http.ListenAndServe(":8081", nil)
	if err != nil {
		log.Fatalf("ListenAndServe failed, reason[%s]", err)
	}
}
