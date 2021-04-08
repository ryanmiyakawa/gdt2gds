



import java.io.*;
import java.util.*;

public class gdtgencondtest{

 

    public static void main(String[] args) throws Exception{
    

	//String filename=keyboard.readLine();
	
	
	String filename="mygdtfile.gdt";
	PrintStream out;
	out= new PrintStream(new FileOutputStream(new File(filename)));
	



	//////////////////// FILE HEADER //////////////////////////////
	out.println("gds2{3");
	out.println("m=-4713-01-01 00:00:00 a=-4713-01-01 00:00:00");
	out.println("lib 'noname' 1 1e-09");

	
	double height;
	double bias = 10;
	double gap = 25;
	//height = 50;
	
	double gratingSize = 50;   //um
	double Xlim = -gratingSize/2*1000; //for centering
	double Ylim = -gratingSize/2*1000;

	double x = Xlim;  //start drawing patterns so the center of grating will be at origin
	double y = Ylim;
	
	double nextWidth; 



	for(height = 50; height >=15; height = height -5){

	
	if(height <= 16){
		height = 18;
		bias = 16;
	}

	out.println("cell{c=2007-05-04 15:41:26 m=2007-05-04 15:41:26 'grating" + String.valueOf(Math.round(height)) + "'");

	
	y = Xlim;
	x = Ylim;

	while(y < Ylim + gratingSize*1000){   // setting height of grating   to 100


		///// generates a single line of the grating with random brakes of gap = gap
		while(x < Xlim + gratingSize*1000)   // while x < 100 um
		{
		nextWidth = Math.random()*3*height+ 4.5*height;

		out.println("b{1 xy(" + roundDouble(x) + " " + roundDouble(y) + "  " + roundDouble(x+nextWidth) + " " + roundDouble(y) + " " + roundDouble(x+nextWidth) + " " + roundDouble(y+height-bias) + " " + roundDouble(x) + " " + roundDouble(y + height - bias) + ")}");
		x+= nextWidth + gap;

		}

		
		y = y + 2*height;
		x = Xlim;

	}

	
	out.println("}");





	out.println("cell{c=2007-05-04 15:41:26 m=2007-05-04 15:41:26 'grat" + String.valueOf(Math.round(height)) + "r'");


	double R = 18*5/height; // radial location of gratings
	String curCell = "grating" + String.valueOf(Math.round(height));
	double xloc, yloc;
	for(double angle = 0; angle < 360;  angle+= 180/6){
		xloc = R * Math.cos(angle*3.14159/180)*1000*1000;
		yloc = R * Math.sin(angle*3.14159/180)*1000*1000;
		double zoneAngle = angle+90;
		out.println("a{'" + curCell + "' a" + zoneAngle + " cr(1 1) xy(" + xloc + " " + yloc + " " + xloc + " " + yloc + " " + xloc + " " + yloc + ")}");
           //out.println("a{'" + curCell + "' a6 cr(4 1) xy(5 30 40 30 5 30)}");
	
	}

	

	out.println("}");

}







/*out.println("s{'grating50' xy(0 0)}");
out.println("s{'grating45' xy(75000 0)}");
out.println("s{'grating40' xy(150000 0)}");
out.println("s{'grating35' xy(225000 0)}");
out.println("s{'grating30' xy(300000 0)}");
out.println("s{'grating25' xy(375000 0)}");
out.println("s{'grating20' xy(450000 0)}");
out.println("s{'grating18' xy(525000 0)}");
*/



//out.println("}");








/////////// Closing brace /////////////

out.println("}");
//////////////////

	

}





static final String ZEROES = "000000000000";
static final String BLANKS = "            ";
	
	static String roundDouble( double val, int n, int w) 
	{
	//	rounding			
		double incr = 0.5;
		for( int j=n; j>0; j--) incr /= 10; 
		val += incr;
		
		String s = Double.toString(val);
		int n1 = s.indexOf('.');
		int n2 = s.length() - n1 - 1;
		
		if (n>n2)      s = s+ZEROES.substring(0, n-n2);
		else if (n2>n) s = s.substring(0,n1+n+1);

		if( w>0 & w>s.length() ) s = BLANKS.substring(0,w-s.length()) + s;
		else if ( w<0 & (-w)>s.length() ) {
			w=-w;
			s = s + BLANKS.substring(0,w-s.length()) ;
		}
		return s;
	}




static double roundDouble(double inp){
	double value;
	if(inp>=0){
	value =  (int)(inp * 1000 + .5);
	value = value/1000;
	}
	else{
	value = (int)(inp * 1000 - .5);
	value = value/1000;
	//System.out.println(String.valueOf(value));
	}

	return value;
}



}
