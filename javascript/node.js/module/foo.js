//模块foo
import {hello} from "/module/bar.js";
var hungry = "hippo";
function awesome() {
  console.log(
    hello(hungry).toUpperCase()
  );
}
export {awesome};
