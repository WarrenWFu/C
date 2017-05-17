package main

import (
	"fmt"
	"os"

	"github.com/WarrenWFu/stringutil"
)

var _ = os.Chdir

func main() {
	fmt.Printf(stringutil.Reverse("!og, olleH"))
}
