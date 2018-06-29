#include <iostream>
#include "obj.h"

using namespace std;

int main(int argc, char* argv[]) {
	Object obj;

	const uint16_t imgWidth = 800;
	const uint16_t imgHeight = 600;

	JiMP2::BMP bmp(imgWidth, imgHeight);
	try
	{
	    obj.read_file("cow.obj", imgWidth, imgHeight);
       obj.draw_object(bmp, 255, 0, 0, imgHeight);

        ofstream outfile("test.bmp", ofstream::binary);
        outfile << bmp;
        cout << "Done!" << endl;
	}catch(Exceptions* exc)
	{
	    exc->print_exception();
	}
	
    All_transformations AT;
    
	Rotate_X *t=new Rotate_X(45, obj.get_center_x(), obj.get_center_y(), obj.get_center_z());
    AT.Add_transformation(t);

    Rotate_Y *t2=new Rotate_Y(45, obj.get_center_x(), obj.get_center_y(), obj.get_center_z());
    AT.Add_transformation(t2);

	Rotate_Z *t3=new Rotate_Z(45, obj.get_center_x(), obj.get_center_y(), obj.get_center_z());
    AT.Add_transformation(t3);
	
	Translate *t4= new Translate(-50,100,0);
    AT.Add_transformation(t4);
	
	Scale *t5=new Scale(1.2, 0.8, 2, obj.get_center_x(), obj.get_center_y(), obj.get_center_z());
    AT.Add_transformation(t5);
    
    Scale exchange(0.8,0.5,1.5, obj.get_center_x(), obj.get_center_y(), obj.get_center_z());
    AT[5]=exchange;
	
	obj.make_transformation(AT);
	JiMP2::BMP bmp7(imgWidth, imgHeight);
	obj.draw_object(bmp7, 20,20,20, imgHeight);
	ofstream outfile7("final.bmp", ofstream::binary);
	outfile7<<bmp7;
	
	obj.make_reverse_transformation(AT);
	JiMP2::BMP bmp8(imgWidth, imgHeight);
	obj.draw_object(bmp8, 200, 0, 200, imgHeight);
	ofstream outfile8("reversed.bmp", ofstream::binary);
	outfile8<<bmp8;

	return 0;
}
