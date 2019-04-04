

#include <stdio.h>
#include <stdlib.h>      
#include <time.h>          //using standard library time.h for using srand(TIME(null))
#include <math.h>          //using math.h for using mathematical  function 
#include "SwinGame.h"        //user-defined header type Swingame.h
#define size 800             //setting array size to 800
#define bt_height 40		//setting default button height to 40
#define bt_width 110        ///setting default button height to 110
struct sample  //defining structure  for the rectangle 
{
	int value;
	color clr;                  //variable in user defined 
};


//this function draws a button and writes text on it 
void draw_button(color clr,char text[100],float x,float y)                                        
{
	fill_rectangle(clr,x,y,bt_width,bt_height); //draws rectangle of color clr at position x and y of default height and weidth
	draw_text(text,ColorWhite,"arial.ttf",11,x+35,y+10);   //writes text on the button 
	
}

//this function returns true when button is clicked  
bool button_click(float x,float y)
{
	float right_value,buttom_value;      //declaring float _>right_value and ,button_value
	right_value=x+bt_width;             //right_value determines the right end  of the button                
	buttom_value=y+bt_height;           //right_value determines the down end  of the button        
	if ( mouse_clicked(LEFT_BUTTON))      //when left button of mouse is clicked 
	 if ((mouse_x() >=x) && (mouse_x() <=right_value) && (mouse_y() >=y) && (mouse_y()<=buttom_value))      //if mouse is clicked with in the button boundary  ,return true
		return true;
	
}	


color get_color(int num)     //THIS FUNCTION GIVES RANDOM COLOUR GIVEN CODES accroding to height 
{
	color clr;          //variable in user defined data type 
	float hue;          
	
	hue=(float) num/screen_height();  //CALCULATINH HUE
	clr=hsbcolor(hue,0.7,0.8);  //FILLS COLOR
	return clr;      //returns clr value 
}

//this function fills the structure array with a integer value and height 
void fill_array(struct sample temp[])
{
	int i,height;   
	height=screen_height()-100; //subtracting 100  from screen_height as the bars font touch the top of the screen 
	for(i=0;i<size;i++)           //loop till i is not 800
	{
		temp[i].value=rand()%height;  //FILL RANDOM VALUE FOR BAR
		temp[i].clr=get_color(temp[i].value);  //FUNCTION_CALLED TO GET CLR FOR EACH BAR
	}
}

void draw_bar(struct sample data[]) //THIS FUCNTION DRAWS BAR
{
	int i;
	float x,y;
	int rectwidth=1 ;     //width of the bar 
	
	for(i=0;i<size;i++)    //DRAW till size is less than 800
	{
		x=i*rectwidth;                    //X POSTIING TO DRAW
		y=screen_height()-data[i].value;   //Y POSTING TO DRAW
		fill_rectangle(data[i].clr,x,y,rectwidth,data[i].value);  //DRAW RECTANGLE of given clr at position x and y 
	}
}

void bubblesort(struct sample data[])  //THIS FUCNTION is for bubble
{
	int i,j,temp;
	for (i=0;i<size-1;i++)            //OUTER LOOP
	{
		for (j=0;j<size-1-i;j++)    //INNER LOOP
		{
			 if (data[j].value>data[j+1].value)  //if the next array value is smaller than current value
					{
					//swapping the values of data[j].value and data[j+1].value  
						temp=data[j].value;
						data[j].value=data[j+1].value; 
						data[j+1].value=temp;
					}
		}
	}
}



void insertionsort(struct sample data[])  //THIS FUCNTION SORTS THE BARS by insertion sort 
{
	int i,j,temp;
	for (i=1;i<size;i++)            //OUTER LOOP
	{
		
		temp=data[i].value;        //assigning the i element integer to temp  
		
		for (j=i;j>0 && data[j-1].value>temp;j--)  //INNER LOOP : starting from i and looping till i is 1;
			data[j].value=data[j-1].value;    //assigning  the previous  value is smaller than current value

		data[j].value=temp;              //assigning temp to the value of jth element of array
	}
}
		
	

void selectionsort(struct sample data[])  //THIS FUCNTION SORTS THE BARS WHEN KEYS ARE PRESSED
{
	int i,j,temp,min;
	
	for (i=0;i<size-1;i++)            //OUTER LOOP
	{
		
		min=i;  //sets i to min 
		
		for (j=i+1;j<size;j++) {  //INNER LOOP
			if (data[j].value<data[min].value)  //if value of j  th is less than  min 
			   min=j;
			
		}
		temp=data[i].value;   //swap data[i].value and data{i].value;
		data[i].value=data[min].value;
		data[min].value=temp;
	}
			
}


void merge(struct sample data[], int p, int q, int r)
{
    int i, j, k;
    int n1 = q - p + 1; //set n1 to diff of mid value -first value +1
    int n2 =  r - q; //set n2 to diff of last value and mid value 
 
   
    struct sample L[n1], R[n2];  //declaring sub arrays 
	
	
    
    for (i = 0; i < n1; i++)
        L[i] = data[p+i];  
    for (j = 0; j < n2; j++)
        R[j] = data[q +j+1];
 
   
    i = 0; 
    j = 0; 
    k = p; 
	
	//while i is less than n1 and j is less than n2 
    while (i < n1 && j < n2)
    {
        if (L[i].value <= R[j].value) //checking for value 
        {
            data[k].value = L[i].value; //assigning L[i].value to data[k].value 
            i++;
        }
        else
        {
            data[k].value = R[j].value; //assigning R[i].value to data[k].value 
            j++;
        }
        k++;
    }
 
	
    while (i < n1)   //if i is less than n1 
    {
        data[k].value = L[i].value;
        i++;
        k++;
    }
 
    
    while (j < n2)  //if j is less than n2
    {
        data[k].value = R[j].value;
        j++;
        k++;
    }
    
}
 


			
	
	
	
void mergeSort(struct sample data[],int p,int r)  //THIS FUCNTION SORTS THE BARS by merge sort 
{
	
	int q;
	
	if (p<r){ //while index of last element is greater than index of first 
		
		q=floor((p+r)/2);  //finding middle index 
		mergeSort(data,p,q);  //dividing into sub array 
		
		mergeSort(data,q+1,r); //dividing into sub array 
		
		merge(data,p,q,r);   //merging the  sub array 
	}
	
}
//this function according to pivot value 
int partition(struct sample data[],int p,int r)
{
	int q=data[r].value;  //pivot 
	int z=p-1;
	int temp;
	for(int i=p;i<=r-1;i++) //while i is less than the maximum of array minus 1
	{
		if (data[i].value<q)   //if values is less than pivot 
		{
			z++;
			temp=data[z].value; //swap values 
			data[z].value=data[i].value;
			data[i].value=temp;
		}
	}
	temp=data[z+1].value;
	data[z+1].value=data[r].value;
	data[r].value=temp;
	return (z+1); //return z+1;
}
	
			
			
	
	
	
	
void quickSort(struct sample data[],int p,int r) //this fucntion sorts the bars by quick sort 
{
	int q;
	if (p<r){    //if p is less than r ie array has more than one element 
		q=partition(data,p,r);  //calls partition function 
		
			quickSort(data,p,q-1);  //recurrsive function 
			quickSort(data,q+1,r);
		
	}
}
		

//this function calls draw_button function)		
void buttonDraw(){
	draw_button(ColorBlue,"Bubble Sort",15,30);  //for bubble sort
	draw_button(ColorBlue,"Insertion Sort",148,30); //for insertion sort
	draw_button(ColorBlue,"Selection Sort",281,30);  //for selection sort 
	draw_button(ColorBlue,"Merge Sort",414,30);  //for merge 
	draw_button(ColorBlue,"Quick Sort",547,30); //for quick sort 
	draw_button(ColorRed,"Reset",680,30);  //reset button 
	fill_rectangle(ColorSkyBlue,0,90,screen_width(),3);  //line 
}


int main()
{
	struct sample data[size];                     //DECLCARING STRUCT VARIABLE
	open_graphics_window("Array rectangles",800,600);  //OPENS GRAPHICS WINDOW
	srand(time(NULL));  //FOR TIME
	fill_array(data);  //CALLING FILL_ARRAY BY PASSING ARRAY  DATA
	
	do
	{
		process_events();
		clear_screen(ColorWhite); //clear screen to white 
		buttonDraw();
		draw_bar(data); //CALLING DRAW BAR FUCNTION
		if (button_click(15,30))  {                    //if button for bubble sort is clicked 
			bubblesort(data); 
		}
		if (button_click(148,30)){ //if button for insertion sort is clicked 
		
			insertionsort(data);
		}
		if (button_click(281,30)){  //if button for selection sort is clicked 
			
			selectionsort(data);
		}
		if (button_click(414,30)){      //if button for merge  sort is clicked 
			
			
			mergeSort(data,0,size-1);
		}
		if (button_click(547,30)){           //if button for quick  sort is clicked 
			
			
			quickSort(data,0,size-1);
		}
		if (button_click(680,30)){          //if button for reset is clicked 
			
			fill_array(data);   //draw array bars 
		}
		
		refresh_screen(60);           //refresh screen
		
		
	}while(!(window_close_requested()));      //CLOSE ONLY WHEN USER WANTS
    return 0; 
}
