#include <SPI.h>
//EPD
#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"
#include "Ap_29demo.h"  
#include "GUI_Paint.h"
#include "fonts.h"

#if 1 
   unsigned char BlackImage[EPD_ARRAY];//Define canvas space  
#endif




void setup() {
    pinMode(D5, INPUT);  //BUSY
    pinMode(D0, OUTPUT); //RES 
    pinMode(D3, OUTPUT); //DC   
    pinMode(D1, OUTPUT); //CS  

   //SPI
   SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0)); 
   SPI.begin ();  

   Serial.begin(9600);
   Serial.print(111);
}

//Tips//
/*
1.Flickering is normal when EPD is performing a full screen update to clear ghosting from the previous image so to ensure better clarity and legibility for the new image.
2.There will be no flicker when EPD performs a partial refresh.
3.Please make sue that EPD enters sleep mode when refresh is completed and always leave the sleep mode command. Otherwise, this may result in a reduced lifespan of EPD.
4.Please refrain from inserting EPD to the FPC socket or unplugging it when the MCU is being powered to prevent potential damage.)
5.Re-initialization is required for every full screen update.
6.When porting the program, set the BUSY pin to input mode and other pins to output mode.
*/
void loop() {
   unsigned char i;
   Serial.print(111);
// #if 1 //Full screen refresh, fast refresh, and partial refresh demostration.

    
			EPD_Init(); //Full screen refresh initialization.
			EPD_WhiteScreen_White(); //Clear screen function.
			EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.	

		 /************Full display(2s)*******************/
			EPD_Init(); //Full screen refresh initialization.
			EPD_WhiteScreen_ALL(gImage_1); //To Display one image using full screen refresh.
			EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
			delay(2000); //Delay for 2s.
						
			/************Fast refresh mode(1.5s)*******************/
			EPD_Init_Fast(); //Fast refresh initialization.
			EPD_WhiteScreen_ALL_Fast(gImage_1); //To display one image using fast refresh.
			EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
			delay(2000); //Delay for 2s.
	// #endif	
  // #if 1 //Partial refresh demostration.
  // //Partial refresh demo support displaying a clock at 5 locations with 00:00.  If you need to perform partial refresh more than 5 locations, please use the feature of using partial refresh at the full screen demo.
  // //After 5 partial refreshes, implement a full screen refresh to clear the ghosting caused by partial refreshes.
  
  // //////////////////////Partial refresh time demo/////////////////////////////////////
      EPD_Init(); //Electronic paper initialization.  
      EPD_SetRAMValue_BaseMap(gImage_basemap); //Please do not delete the background color function, otherwise it will cause unstable display during partial refresh.
      EPD_Init_Part(); //Pa refresh initialization.
      for(i=0;i<6;i++)
      {
        EPD_Dis_Part_Time(200,180,Num[1],Num[0],gImage_numdot,Num[0],Num[i],5,104,48); //x,y,DATA-A~E,Resolution 48*104                 
      }       
      
      EPD_DeepSleep();  //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.
      EPD_Init(); //Full screen refresh initialization.
      EPD_WhiteScreen_White(); //Clear screen function.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.
  // #endif  


	// #if 1 //Partial refresh demostration.
	//Partial refresh demo support displaying a clock at 5 locations with 00:00.  If you need to perform partial refresh more than 5 locations, please use the feature of using partial refresh at the full screen demo.
	//After 5 partial refreshes, implement a full screen refresh to clear the ghosting caused by partial refreshes.
	//////////////////////Partial refresh time demo/////////////////////////////////////
		Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 0, WHITE); //Set canvas parameters, GUI image rotation, please change 0 to 0/90/180/270.
    Paint_SelectImage(BlackImage); //Select current settings.

    /**************Drawing demonstration**********************/   
		EPD_Init(); //Full screen refresh initialization.
		Paint_Clear(WHITE); //Clear canvas.
		//Point.   
    Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT); //point 1x1.
    Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT); //point 2x2.
    Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT); //point 3x3.
    Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT); //point 4x4.
		//Line.
    Paint_DrawLine(20, 10, 70, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1); //1x1line 1.
    Paint_DrawLine(70, 10, 20, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1); //1x1line 2.
		//Rectangle.
    Paint_DrawRectangle(20, 10, 70, 60, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1); //Hollow rectangle 1.
    Paint_DrawRectangle(85, 10, 130, 60, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1); //Hollow rectangle 2.
    //Circle.
		Paint_DrawCircle(150, 90, 30, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1); //Hollow circle.
    Paint_DrawCircle(200, 90, 30, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1); //solid circle.
    EPD_Display(BlackImage); //Display GUI image.
		EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
    delay(2000); //Delay for 2s.		
		
    /***********Letter demo***************************/
		EPD_Init(); //Full screen refresh initialization.
		Paint_Clear(WHITE); //Clear canvas.
    // Paint_DrawString_EN(0, 0, "Good Display", &Font8, WHITE, BLACK);  //5*8.
		// Paint_DrawString_EN(0, 10, "Good Display", &Font12, WHITE, BLACK); //7*12.
		// Paint_DrawString_EN(0, 25, "Good Display", &Font16, WHITE, BLACK); //11*16.
		Paint_DrawString_EN(0, 45, "Good Display", &Font20, WHITE, BLACK); //14*20.
		Paint_DrawString_EN(0, 80, "Good Display", &Font24, WHITE, BLACK); //17*24
    Paint_DrawString_CN(0, 180, "你好", &Font24CN, WHITE, BLACK);
    EPD_Display(BlackImage);//Display GUI image.
		EPD_DeepSleep(); //EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
    delay(2000); //Delay for 2s.
			
		/*************Numbers demo************************/
		EPD_Init(); //Full screen refresh initialization.
		Paint_Clear(WHITE); //Clear canvas.
    Paint_DrawNum(0, 0, 123456789, &Font8, WHITE, BLACK);  //5*8.
		Paint_DrawNum(0, 10, 123456789, &Font12, WHITE, BLACK); //7*12.
		Paint_DrawNum(0, 25, 123456789, &Font16, WHITE, BLACK); //11*16.
		Paint_DrawNum(0, 45, 123456789, &Font20, WHITE, BLACK); //14*20.
		Paint_DrawNum(0, 70, 123456789, &Font24, WHITE, BLACK); //17*24.
    EPD_Display(BlackImage); //Display GUI image.
		EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
    delay(2000); //Delay for 2s.	 		
	
		//Full screen update clear the screen.
		EPD_Init(); //Full screen refresh initialization.
		EPD_WhiteScreen_White(); //Clear screen function.
		EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
		delay(2000);	//Delay for 2s.	

// #endif

    delay(300000);  // The program stops here   
}




//////////////////////////////////END//////////////////////////////////////////////////
