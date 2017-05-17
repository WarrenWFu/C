package main

import (
	"fmt"
	"os"

	"mygithub/WarrenWFu/stringutil"
)

var _ = os.Chdir

func main() {
	fmt.Printf(stringutil.Reverse("!og, olleH"))
}
