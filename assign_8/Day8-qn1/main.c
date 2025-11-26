#include<stdio.h>
#include"circle.h"
#include"rectangle.h"
#include"square.h"

void main(void)
{
	int radius=2,side=3,length=4,breadth=3;
	printf("Area of circle :%d\n",circle(radius));
	printf("Area of rectangle :%d\n",rectangle(length,breadth));
	printf("Area of square :%d\n",square(side));

}
