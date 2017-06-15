package main

import (
	"fmt"
	"html/template"
	"io/ioutil"
	"net/http"
)

//WebPage 表示网页
type WebPage struct {
	Title string
	Body  []byte
}

func readHtml(filename string) (*WebPage, error) {
	bytes, err := ioutil.ReadFile(filename + ".html")
	if err != nil {
		return nil, err
	}

	return &WebPage{Title: filename, Body: bytes}, nil
}

func viewMain(w http.ResponseWriter, r *http.Request) {
	//	fmt.Println("method", r.Method)
	//	fmt.Printf("URL[%v]\n", r.URL)
	//	fmt.Printf("请求头[%v]\n", r.Header)
	//	bsBody := make([]byte, 1024)
	//	r.Body.Read(bsBody)
	//	fmt.Printf("请求体[%s]\n", bsBody)

	if r.URL.Path == "/" {
		http.Redirect(w, r, "/index", http.StatusFound)
	} else if r.URL.Path == "/index" {
		if webPage, err := readHtml("main"); err != nil {
			fmt.Printf("处理[%s]请求失败，原因[%s]\n", "main", err)
			w.Write([]byte("page not found"))
		} else {
			w.Write(webPage.Body)
		}
	} else if r.URL.Path == "/said" {
		if t, err := template.ParseFiles("./main.html"); err != nil {
			fmt.Printf("处理[%s]请求失败，原因[%s]\n", "main", err)
			w.Write([]byte("page not found"))
		} else {
			body := r.FormValue("text1")
			//bodyType := reflect.ValueOf(body)
			//fmt.Printf("%s, %s\n", body, bodyType.Type())
			webPage := &WebPage{Body: []byte(body)}
			t.Execute(w, webPage)
		}
	} else {
		w.Write([]byte("page not found"))
	}
}

func main() {
	http.HandleFunc("/", viewMain)

	http.ListenAndServe(":8080", nil)
}
