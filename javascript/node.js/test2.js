function byteLength(s) {
  var totalLength = 0;
  var charCode;
  for (var i = 0; i < s.length; ++i) {
    charCode = s.charCodeAt(i);
    if (charCode < 0x0080) {
      ++totalLength;
    } else if (charCode < 0x0800) {
      totalLength += 2;
    } else if (charCode <= 0xffff) {
      totalLength += 3;
    } else {
      totalLength += 4;
    }
  }
  return totalLength;
}

console.log(byteLength('ÈË'));

