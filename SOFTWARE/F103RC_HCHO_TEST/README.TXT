实验器材:
	MiniSTM32F103开发板V3版本
	
实验目的:
	学习在STM32上面的图片显示方法,实现一个简单的数码相框.
	
硬件资源:
	1,DS0(连接在PA8) 
	2,串口1(波特率:9600,PA9/PA10连接在板载USB转串口芯片CH340上面)
	3,ALIENTEK 2.8/3.5/4.3/7寸TFTLCD模块(通过GPIO驱动,连接关系见lcd.h)
	4,SD卡,通过SPI1连接 
	5,W25Q64(SPI FLASH芯片,连接在SPI1上)
	6,按键KEY0(PC5)/KEY1(PA15)/KEY_UP(PA0,也称之为WK_UP)  
		
实验现象:
	本实验开机的时候先检测字库，然后检测SD卡是否存在，如果SD卡存在，则开始查找SD卡根目录下的PICTURE文件夹，
	如果找到则显示该文件夹下面的图片文件（支持bmp、jpg、jpeg或gif格式），循环显示，通过按KEY0和KEY1可以快
	速浏览下一张和上一张，KEY_UP按键用于暂停/继续播放，DS1用于指示当前是否处于暂停状态。如果未找到PICTURE
	文件夹/任何图片文件，则提示错误。同样我们也是用DS0来指示程序正在运行。
	本实验也可以通过USMART调用ai_load_picfile和minibmp_decode解码任意指定路径的图片.
	
注意事项:  
	1,4.3寸和7寸屏需要比较大电流,USB供电可能不足,请用外部电源供电(5V电源，接VOUT2即可).
	2,本例程在LCD_Init函数里面(在ILI93xx.c),用到了printf,如果不初始化串口1,将导致液晶无法显示!! 
	3,LCD模块在开发板的LCD接口上面，必须靠右插 
	4,不要把1820和PA0的跳线帽跳上,否则可能导致按键"不灵". 
	5,该实验须自备SD卡一个，并在SD卡根目录新建：PICTURE文件夹，并放入一些图片（BMP/JPG/JPEG/GIF）。    
	6,如果有些jpg/jpeg格式不能显示的话，用XP自带的画图工具打开，再保存一下，一般就可以显示了。
	7,JPEG/JPG/BMP图片，程序会根据LCD分辨率自动缩放，以适应LCD，而GIF则必须小于屏幕分辨率才可以显示。
	
	  
					正点原子@ALIENTEK
					2014-3-14
					广州市星翼电子科技有限公司
					电话：020-38271790
					传真：020-36773971
					购买：http://shop62103354.taobao.com
					http://shop62057469.taobao.com
					公司网站：www.alientek.com
					技术论坛：www.openedv.com