任务点2

STM32时钟工作主频为170Mhz，通过按键和LCD设计显示菜单

查阅资料，分别实现如下功能：

串口工作在115200波特率，无校验位，一个停止位。

串口开启发送与接收的DMA，并开启中断。

功能界面1第1行汉字显示：串口通信演示系统

第2行汉字显示：成员姓名1+学号

第3行汉字显示：成员姓名2+学号

第4行汉字显示：成员姓名3+学号

第5行汉字显示：请按键将信息发到串口

按键1按下 -> 先发送“KEY1 Press!”字符串及换行符 到电脑端串口调试助手显示 

然后发送A55A+学号1+A5A5字符串到电脑端串口调试助手显示   

按键2按下 -> 发送“KEY2 Press!”字符串到电脑端串口调试助手显示  

然后发送A55A+学号2+A5A5字符串到电脑端串口调试助手显示    

按键3按下，发送“KEY3 Press!”字符串到电脑端串口调试助手显示  

然后发送A55A+学号3+A5A5字符串到电脑端串口调试助手显示    

功能界面2 在电脑端串口调试助手，发送“A55A+学号（1-3）+A5A5”字符串，STM32收到后返回：学号1，同时LCD进入显示界面2，上面显示第一行显示姓名，第二行显示学号。下半屏显示头像照片（一半屏幕显示照片即可），如果STM32收到的如果不是“A55A+学号（1-3）+A5A5”字符串（例如学号错误），则直接返回“A55A+学号（1-3）+A5A5”字符串，并发送“Data Format Error！”，此时LCD显示功能界面1发送“A55AA5A5”字符串，STM32收到后LCD显示功能界面1