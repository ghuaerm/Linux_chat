# Linux_chat
## **基于Linux的网络聊天室**
## 运行步骤
### 步骤1：
首先编译server.c 和client.c文件，gcc命令是用来编译C/C++语言等，-o后面加的是输出的文件名，-lpthread（因为在文件中使用了动态库pthread，因此在编译时要用包含指定的库，用“-l库名”来进行指定）。命令如下：

        $gcc server.c -o server -lpthread 
        $gcc client.c -o client -lpthread 

其中编译的中间过程（预处理、编译、汇编和链接）可自行查看官方文档了解，这里不作说明。
 
### 步骤2：
服务器开启之后建立多个窗口来依次注册“宫本武藏”“娜可露露”“不知火舞”三个用户，选择1 public选项分别发送一条群聊消息。如图所示
![创建用户](https://github.com/ghuaerm/Linux_chat/blob/master/image/1.png)
### 步骤3：
接着选择2 private测试私聊发送消息的功能，显示在线用户列表后选择用户进行聊天。
![宫本武藏与不知火舞的聊天界面](https://github.com/ghuaerm/Linux_chat/blob/master/image/2.png)
![宫本武藏与娜可露露的聊天界面](https://github.com/ghuaerm/Linux_chat/blob/master/image/3.png)
### 步骤4：
进入不知火舞和娜可露露的聊天界面，测试用户接收消息的功能
![不知火舞的聊天界面](https://github.com/ghuaerm/Linux_chat/blob/master/image/4.png)
![娜可露露的聊天界面](https://github.com/ghuaerm/Linux_chat/blob/master/image/5.png)
### 步骤5：
以上的聊天室操作都在server中进行监听，下面显示的是所有客户端操作的内容
![服务器的监听界面](https://github.com/ghuaerm/Linux_chat/blob/master/image/6.png)
步骤6：
最后选择3 exit退出系统，服务器监听到用户退出之后删除该用户，CTRL+C结束程序。
![用户退出并删除用户](https://github.com/ghuaerm/Linux_chat/blob/master/image/7.png)
## 结语
本设计是针对Linux网络聊天室的设计，用户的注册和登录；相比于其他的聊天室完善了查询在线用户列表的功能；使用socket套接字,TCP/IP协议和多线程技术实现聊天室的基本功能；所有的显示通过终端的字符界面呈现出来。由于自己能力的有限，没能做出一个窗体，让系统更完美化。一开始想的是用QT实现的真正带窗口的聊天室，但是项目有点大，越研究内容越多，最终没能实现，以后再做。