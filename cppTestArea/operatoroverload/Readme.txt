I made this as hello world to get Notepad++ working with gcc 4.8. 
Then at some point I wanted to mess around with operator overloading syntax so it turned into that.

To run this without any IDE, I had to get a working gcc compiler included in my path and then call it with some code file.

For gcc, I first got the whole thing, but it needed to be compiled and frankly had a ton of Unix stuff going on in the documentation that I didn't understand. Eventually I found mingw, which is a minimal gcc port for windows apps. I used this one:
http://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/rubenvb/gcc-4.8-release/
and put into my windows path the following:
C:\mingw64\bin;
which allows gcc.exe and g++ (and whatever else is in there) to be called from anywhere.

To get Notepad++ to call g++, I used NPPExec, an addon that comes with notepad++. I used its built in scripting to make a script that would call g++ and pass whatever command line arguments and my filename and outputfilename.

The following is the script ran by NppExec (and can handily be added as a menu item and keybound to ie F5):
npp_saveall
CD $(CURRENT_DIRECTORY)
g++ $(FILE_NAME) -o $(NAME_PART).exe -std=c++11
$(FILE_NAME).exe
