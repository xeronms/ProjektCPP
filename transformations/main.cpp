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
    
    Rotate_X rx(90, obj.get_center_x(), obj.get_center_y(), obj.get_center_z());
    All_transformations a1;
    a1.Add_transformation(&rx);
    
    Rotate_Y ry(90, obj.get_center_x(), obj.get_center_y(), obj.get_center_z());
    All_transformations a2;
    a2.Add_transformation(&a1);
    a2.Add_transformation(&ry);
    
    Rotate_Z rz(90, obj.get_center_x(), obj.get_center_y(), obj.get_center_z());
    All_transformations a3;
    a3.Add_transformation(&a2);
    a3.Add_transformation(&rz);
    
    Translate t(100,0,0);
    All_transformations a4;
    a4.Add_transformation(&a3);
    a4.Add_transformation(&t);
    obj.edit_center_point(100,0,0);
    
    Translate t2(0,200,0);
    All_transformations a5;
    a5.Add_transformation(&a4);
    a5.Add_transformation(&t2);
    
    Rotate_Y r80(70, obj.get_center_x(), obj.get_center_y(), obj.get_center_z());
    a5[0][0][0][1]=r80;
    
    Rotate_X r45(45, obj.get_center_x(), obj.get_center_y(), obj.get_center_z());
    a5[0][0][0][0][0]=r45;
    
    Translate ty(0,0,0);
    
    a5[1]=ty;
        
	obj.make_transformation(a5);
	JiMP2::BMP bmp2(imgWidth, imgHeight);
	obj.draw_object(bmp2, 20,20,20, imgHeight);
	ofstream outfile2("final.bmp", ofstream::binary);
	outfile2<<bmp2;
	
	obj.make_reverse_transformation(a5);
	JiMP2::BMP bmp3(imgWidth, imgHeight);
	obj.draw_object(bmp3, 20,20,20, imgHeight);
	ofstream outfile3("final_reversed.bmp", ofstream::binary);
	outfile3<<bmp3;
	
	return 0;
}
