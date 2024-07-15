2024/7/15 20:00:00

v1.03.2

1.   按键消抖还是加上去了，虽然感知不强(甚至没有)
2.   中断回调函数里面还是加上了while来判断是否按键有没有离开触发(也就是等待按键松开，卡住循环执行)





>   PS: 另外xwl你写的文档格式好怪啊，我整个都改写了一下QWQ

---



2024/7/15 18:47:00

v1.03.1

SOS!!修复一个紧急bug：

-   如下代码应该在用户代码区，否则每次CubeMX生成代码都会丢失该三行代码

![image-20240715185240583](assets/image-20240715185240583.png)


---

2024/7/13 16:49:32

v1.03

1.   为项目引入了串口通信，现在可以使用DMA的方式在USB接口与PC接收和发送信息了
2.   一些需要注意的地方
     -   代码中，当串口通信仅使用中断，不使用DMA，会出现丢失字节的问题（比如输入为1234567890，输出输入的字符串则可能得到123456890）
     -   目前使用的DMA通信要求当输入字符满足一定长度后，输出才会触发，如这里当设置输入长LENGTH=21时（根据要求即A55A+学号+A5A5+\n=21），输出即会返回这些字符串。不过实际使用时不一定为21（考虑到要求中所有字符不等长，并且还需要一些排错能力），并且还需要更复杂的判断逻辑，这里只是提供了DMA的架构。
3.   接下来处理GUI、通信逻辑等等，你们加油(ε: )

---

2024/7/12 17:25:43

v1.02

1.   改为了使用中断的方式处理按钮交互信息
2.   存在一些令人难以理解的机制
     -   每次中断结束，主函数执行都会重新执行一遍while循环
     -   <b>主频过快时，屏幕会出现严重的失真，当到达最高170Hz时，屏幕将完全无法显示任何东西</b>
     -   现使用的按钮消抖似乎没什么作用，尽管实际上好像也不需要这个消抖
3.   接下来将着手进行串口通讯相关内容——看起来很麻烦orz
4.   哦对了另外还有GUI没做，照着他那个来就行;)

---

7.10

全新(bushi)的开始

哈哈哈哈哈哈哈哈哈哈
