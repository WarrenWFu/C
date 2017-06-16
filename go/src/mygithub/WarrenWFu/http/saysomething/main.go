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

var templates = template.Must(template.ParseFiles("index.html"))

func readHtml(filename string) (*WebPage, error) {
	bytes, err := ioutil.ReadFile(filename + ".html")
	if err != nil {
		return nil, err
	}

	return &WebPage{Title: filename, Body: bytes}, nil
}

func viewMain(w http.ResponseWriter, r *http.Request) {
	if r.URL.Path == "/" {
		http.Redirect(w, r, "/index", http.StatusFound)
	} else if r.URL.Path == "/index" {
		webPage := &WebPage{Body: []byte("说点什么吧")}
		templates.ExecuteTemplate(w, "index.html", webPage)
	} else if r.URL.Path == "/said" {
		webPage := &WebPage{Body: []byte(r.FormValue("text1"))}
		templates.ExecuteTemplate(w, "index.html", webPage)
	} else {
		http.NotFound(w, r)
	}
}

func main() {
	http.HandleFunc("/", viewMain)

	if err := http.ListenAndServe(":8080", nil); err != nil {
		fmt.Printf("启动监听失败，原因[%s]\n", err)
	}
}
