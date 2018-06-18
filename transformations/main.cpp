#include <iostream>
#include "obj.h"

using namespace std;

int main(int argc, char* argv[]) {
	Object first_and_only;

	const uint16_t imgWidth = 800;
	const uint16_t imgHeight = 600;

	JiMP2::BMP bmp(imgWidth, imgHeight);
	try
	{
	    first_and_only.read_file("cow.obj", imgWidth, imgHeight);
        first_and_only.draw_object(bmp, 255, 0, 0, imgHeight);

        ofstream outfile("test.bmp", ofstream::binary);
        outfile << bmp;
        cout << "Done!" << endl;
	}catch(Exceptions* exc)
	{
	    exc->print_exception();
	}

	/*first_and_only.transform(120,100,0);
	JiMP2::BMP bmp2(imgWidth, imgHeight);
	first_and_only.draw_object(bmp2, 200, 100, 100, imgHeight);
	ofstream outfile2("after.bmp", ofstream::binary);
	outfile2 << bmp2;
	//first_and_only.show();*/

	/*first_and_only.scale(1.5,1.5,1.5);
	JiMP2::BMP bmp3(imgWidth, imgHeight);
	first_and_only.draw_object(bmp3, 100, 50, 50, imgHeight);
	ofstream outfile3("after_scaling.bmp", ofstream::binary);
	outfile3 << bmp3;*/

	first_and_only.rotate_X(45);
	JiMP2::BMP bmp4(imgWidth, imgHeight);
	first_and_only.draw_object(bmp4, 100, 50, 50, imgHeight);
	ofstream outfile4("after_rotatingX.bmp", ofstream::binary);
	outfile4 << bmp4;
	//first_and_only.show();
	cout<<endl<<endl<<"<------------------------------------->\n";

        first_and_only.rotate_Y(45);
	JiMP2::BMP bmp5(imgWidth, imgHeight);
	first_and_only.draw_object(bmp5, 100, 50, 50, imgHeight);
	ofstream outfile5("after_rotatingY.bmp", ofstream::binary);
	outfile5 << bmp5;
	//first_and_only.show();
	cout<<endl<<endl<<"<------------------------------------->\n";

	/*first_and_only.rotate_Z(45);
	JiMP2::BMP bmp6(imgWidth, imgHeight);
	first_and_only.draw_object(bmp6, 100, 50, 50, imgHeight);
	ofstream outfile6("after_rotatingZ.bmp", ofstream::binary);
	outfile6 << bmp6;
        first_and_only.show();
	cout<<endl<<endl<<"<------------------------------------->\n";*/

	return 0;
}
