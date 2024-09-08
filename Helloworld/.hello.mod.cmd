savedcmd_/home/hoang-anh/Project/Helloworld/hello.mod := printf '%s\n'   hello.o | awk '!x[$$0]++ { print("/home/hoang-anh/Project/Helloworld/"$$0) }' > /home/hoang-anh/Project/Helloworld/hello.mod
