#ifndef _COLOR_H
#define _COLOR_H

class Color {
	double red, green, blue, special;
	
	public:
	
	Color ();
	Color (double, double, double, double);
	
	// method functions
	double brightness();
	double getColorRed();
	double getColorBlue();
	double getColorGreen();
	double getColorSpecial();
	double setColorRed(double);
	double setColorBlue(double);
	double setColorGreen(double);
	double setColorSpecial(double);
	

	Color clip();
	Color colorAdd(Color);
	Color colorScalar(double);
	Color colorAverage(Color);
	Color colorMultiply(Color);
};

Color::Color () {
	red = 0.5;
	green = 0.5;
	blue = 0.5;
}

Color::Color (double r, double g, double b, double s) {
	red = r;
	green = g;
	blue = b;
	special = s;
}

#endif
