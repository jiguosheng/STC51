#include <Var.h>

void zuobiaoxi()
{
	unsigned char i=0;

	ClrRAM_12864();
	for(i=0;i<=63;i++)
	{
	 	LCD12864_DrawPoint(0,i,1);
		LCD12864_DrawPoint(63,i,1);
		LCD12864_DrawPoint(127,i,1);
	} 
	for(i=0;i<=127;i++)
	{
	 	LCD12864_DrawPoint(i,0,1);
		LCD12864_DrawPoint(i,31,1);
		LCD12864_DrawPoint(i,63,1);
	}
	for(i=0;i<=64;i++)
	{
	 	LCD12864_DrawPoint(2*i+1,30,1);
		LCD12864_DrawPoint(2*i+1,32,1);
	}
	for(i=0;i<=32;i++)
	{
	 	LCD12864_DrawPoint(62,i*2+1,1);
		LCD12864_DrawPoint(64,i*2+1,1);
	}
	LCD12864_Display(2,7,'X');
	LCD12864_Display(1,3,'Y');
}

void Line(char k,char b)
{
 	char x,X;
	char y,Y;

	zuobiaoxi();

	for(x=-63;x<=64;x++)
	{
		y=k*x+b;
		X=x+63;							  //几何坐标转化为LCD18264中的坐标
		Y=31-y;
		if(Y>=0 && Y<=63)
		{
			LCD12864_DrawPoint(X,Y,1);	  
		}
	}
}

void Circle(char x,char y,unsigned char r)
{
	char X;
	char Y;
	int o=0;

	zuobiaoxi();
	for(o=0;o<=360;o=o+10)
	{
	 	X=63+(x+r*cos(o/180.0*3.14));
		Y=31-(y+r*sin(o/180.0*3.14));
		if(Y>=0 && Y<=63)
		{
			LCD12864_DrawPoint(X,Y,1);	    
		}
	}
}

void Acircle(char x,char y,unsigned char a,unsigned char b)
{
	char X;
	char Y;
	int o=0;

	zuobiaoxi();
	for(o=0;o<=360;o=o+10)
	{
	 	X=63+(x+a*cos(o/180.0*3.14));
		Y=31-(y+b*sin(o/180.0*3.14));
		if(Y>=0 && Y<=63)
		{
			LCD12864_DrawPoint(X,Y,1);	    
		}
	}
}

void Sine(unsigned char k,unsigned char w,unsigned char o)
{
	char x,X;
	char y,Y;
 	//zuobiaoxi();

	for(x=-63;x<=64;x++)
	{
		//X=(char)(x+r*cos(O/180*3.1415926)+63);							  //几何坐标转化为LCD18264中的坐标
		//Y=(char)(31-(y+r*sin(O/180*3.1415926)));
		y=k*sin(w*(x/180.0*3.14)+o);
		X=x+63;
		Y=31-y;
		if(Y>=0 && Y<=63)
		{
			LCD12864_DrawPoint(X,Y,1);	    
		}
	}
}

void Cose(unsigned char k,unsigned char w,unsigned char o)
{
	char x,X;
	char y,Y;
 	zuobiaoxi();

	for(x=-63;x<=64;x++)
	{									  	
		y=k*cos(w*(x/180.0*3.14)+o);			 //几何坐标转化为LCD18264中的坐标
		X=x+63;
		Y=31-y;
		if(Y>=0 && Y<=63)
		{
			LCD12864_DrawPoint(X,Y,1);	    
		}
	}
}

void Sine_m(unsigned char k,unsigned char w,unsigned char o,unsigned char flag)
{
	char x,X;
	char y,Y;

	for(x=-63;x<=64;x++)
	{
		//X=(char)(x+r*cos(O/180*3.1415926)+63);							  //几何坐标转化为LCD18264中的坐标
		//Y=(char)(31-(y+r*sin(O/180*3.1415926)));
		y=k*sin(w*(x/180.0*3.14)+o);
		X=x+63;
		Y=31-y;
		if(Y>=0 && Y<=63)
		{
			LCD12864_DrawPoint(X,Y,flag);	    
		}
	}
}