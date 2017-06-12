package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
)

//WebPage 表示网页
type WebPage struct {
	title string
	body  []byte
}

func readHtml(filename string) (*WebPage, error) {
	bytes, err := ioutil.ReadFile(filename + ".html")
	if err != nil {
		return nil, err
	}

	return &WebPage{title: filename, body: bytes}, nil
}

func viewMain(w http.ResponseWriter, r *http.Request) {
	var webPage *WebPage
	var err error
	if r.URL.Path == "/" {
		http.Redirect(w, r, "/index", http.StatusFound)
	} else if r.URL.Path == "/index" {
		if webPage, err = readHtml("main"); err != nil {
			fmt.Printf("处理[%s]请求失败，原因[%s]\n", "main", err)
			w.Write([]byte("page not found"))
		} else {
			w.Write(webPage.body)
		}
	} else {
		w.Write([]byte("page not found"))
	}
}

func main() {
	http.HandleFunc("/", viewMain)

	http.ListenAndServe(":8080", nil)
}
