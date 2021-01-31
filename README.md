# colortext
Generates gradient text for html pages using \<font\> tags for each letter with the color attribute set which is probably not a good idea but i just made it for fun. Works with UTF-8.
  
The source code passed through the program with colors ff0000, 0000ff, 00ff00 and ff0088:
  
![alt text](https://raw.githubusercontent.com/amendip/colortext/master/tmp.png)
  
## compile
This should be enough:
```
gcc program.c -o colortext
```
## run
Provide hex colors as arguments to the program and pipe some text into it or just write it and press `Ctrl+D` when finished.
Examples:
```
echo "the text" | colortext ff0000 00ff00 0000ff
```
```
cat afilewithtext | colortext ff0000 555500
```
### things to note
- You can specify as many colors as you want.
- Text cap is 32768 bytes or something like that.
- Newline characters are removed from the end of your string so the last visible character is the last color you specified
- I think it doesn't work if the colors are prefixed with anyting.
