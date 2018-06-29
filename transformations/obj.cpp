#include "obj.h"
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <sstream>

using namespace std;

namespace JiMP2 {

BMP::BMP(uint16_t width, uint16_t height) :
		bitmapCoreHeader(width, height) {

	assert(IS_LITTLE_ENDIAN);
	assert(width > 0);
	assert(height > 0);

	const unsigned int rowSize = ((bitmapCoreHeader.bitsPerPixel * width + 31)
			/ 32) * 4;
	const unsigned int imgSize = rowSize * height;

	bmpFileHeader.size = 14 + bitmapCoreHeader.size + imgSize;
	bmpFileHeader.dataOffset = 14 + bitmapCoreHeader.size;

	pixelData = new unsigned char[imgSize];
	std::memset(pixelData, 255, imgSize);
}

BMP::~BMP() {
	delete[] pixelData;
}

void BMP::setPixel(uint16_t x, uint16_t y, unsigned char r, unsigned char g,
		unsigned char b) {
    if( x>0 && y>0 && x<=bitmapCoreHeader.bmpWidth && y<=bitmapCoreHeader.bmpHeight)
    {
         assert(bitmapCoreHeader.bitsPerPixel == 24);

        const size_t rowSize = ((bitmapCoreHeader.bitsPerPixel
                * bitmapCoreHeader.bmpWidth + 31) / 32) * 4;
        const size_t offset = rowSize * (bitmapCoreHeader.bmpHeight - y)
                + x * (bitmapCoreHeader.bitsPerPixel / 8);

        pixelData[offset + 0] = b;
        pixelData[offset + 1] = g;
        pixelData[offset + 2] = r;
    }
}

std::ostream& operator<<(std::ostream& os, const BMP& bmp) {
	os.write(bmp.bmpFileHeader.id, sizeof(bmp.bmpFileHeader.id));
	os.write((const char*) &bmp.bmpFileHeader.size,
			sizeof(bmp.bmpFileHeader.size));
	os.write(bmp.bmpFileHeader.reserved, sizeof(bmp.bmpFileHeader.reserved));
	os.write((const char*) &bmp.bmpFileHeader.dataOffset,
			sizeof(bmp.bmpFileHeader.dataOffset));

	os.write((const char*) &bmp.bitmapCoreHeader.size,
			sizeof(bmp.bitmapCoreHeader.size));
	os.write((const char*) &bmp.bitmapCoreHeader.bmpWidth,
			sizeof(bmp.bitmapCoreHeader.bmpWidth));
	os.write((const char*) &bmp.bitmapCoreHeader.bmpHeight,
			sizeof(bmp.bitmapCoreHeader.bmpHeight));
	os.write((const char*) &bmp.bitmapCoreHeader.colorPlanes,
			sizeof(bmp.bitmapCoreHeader.colorPlanes));
	os.write((const char*) &bmp.bitmapCoreHeader.bitsPerPixel,
			sizeof(bmp.bitmapCoreHeader.bitsPerPixel));

	const unsigned int rowSize = ((bmp.bitmapCoreHeader.bitsPerPixel
			* bmp.bitmapCoreHeader.bmpWidth + 31) / 32) * 4;
	const unsigned int imgSize = rowSize * bmp.bitmapCoreHeader.bmpHeight;

	os.write((const char*) bmp.pixelData, imgSize);

	return os;
}
}

void swap_points(int &p1x, int &p1y, int &p2x, int &p2y)
{
    p1x^=p2x;
    p2x^=p1x;
    p1x^=p2x;
    p1y^=p2y;
    p2y^=p1y;
    p1y^=p2y;
}

void rysuj_linie(int p1x, int p1y, int p2x, int p2y, unsigned char r, unsigned char g, unsigned char b, JiMP2::BMP &bmp)
{
	if(p1x>p2x) swap_points(p1x, p1y, p2x, p2y);

	if(p1x<p2x && p1y<p2y)
    {
        if((float(p2y-p1y)/(p2x-p1x))<=1)
        {
            for(int i = p1x; i <= p2x; ++i)
            {
                bmp.setPixel(i, p1y+((i-p1x)*float((p2y-p1y))/(p2x-p1x)), r, g, b);
            }
        }
        else
        {
            for(int j = p1y; j <= p2y; ++j)
            {
                bmp.setPixel(p1x+((j-p1y)*float((p2x-p1x))/(p2y-p1y)), j, r, g, b);
            }
        }
    }
    else if(p1x<p2x && p1y==p2y)
    {
        for (int  i = p1x; i <= p2x; ++i)
        {
            bmp.setPixel(i, p1y,  r, g, b);
        }
    }
    else if(p1x==p2x && p1y<p2y)
    {
        for (int i = p1y; i <= p2y; ++i)
        {
            bmp.setPixel(p1x, i,  r, g, b);
        }
    }
    else if(p1x==p2x && p1y>p2y)
    {
        for (int i = p2y; i <= p1y; ++i)
        {
            bmp.setPixel(p1x, i,  r, g, b);
        }
    }
    else if(p1x<=p2x && p1y>p2y)
    {
        if(float((p1y-p2y))/(p2x-p1x)<=1)
        {
            for (int i = p1x; i <= p2x; ++i)
            {
                bmp.setPixel(i, p1y-((i-p1x)*float((p1y-p2y))/(p2x-p1x)),  r, g, b);
            }
        }
        else
        {
            for(int j = p1y; j >= p2y; --j)
            {
                bmp.setPixel(p1x+((p1y-j)*float((p2x-p1x))/(p1y-p2y)), j,  r, g, b);
            }
        }
    }
}

Object::Object(): faces(0){}

void Object::read_file(const char* file_name, const uint16_t& img_width, const uint16_t& img_height)
{
    fstream file;
    file.open(file_name, ios::in);
    if(file.good()==false)
    {
        throw new Exception_file();
    }
    stringstream ss;
    string temp;
    string line;
    double temp_double;
    unsigned temp_int;
    unsigned Vcounter=0, Fcounter=0;
    double min_x, max_x, min_y, max_y, min_z, max_z;
    char command;
    Vertex vtemp;
    Face ftemp;
    unsigned arg_count;
    unsigned line_number=0;

    while(getline(file, line))
    {
        if(line[1]!=' ') continue;
        ss.clear();
        ss.str(line);
        arg_count=-1;
        while(ss>>temp) ++arg_count;
        ss.clear();
        ss.str(line);
        ss>>command;

        switch(command)
        {
        case 'v':
            if(arg_count!=3) throw new Exception_arg(line_number);
            ss>>temp_double;
            vtemp.x=temp_double;
            if(Vcounter==0 || vtemp.x<min_x) min_x=vtemp.x;
            if(Vcounter==0 || vtemp.x>max_x) max_x=vtemp.x;
            ss>>temp_double;
            vtemp.y=temp_double;
            if(Vcounter==0 || vtemp.y<min_y) min_y=vtemp.y;
            if(Vcounter==0 || vtemp.y>max_y) max_y=vtemp.y;
            ss>>temp_double;
            vtemp.z=temp_double;
            if(Vcounter==0 || vtemp.z<min_z) min_z=vtemp.z;
            if(Vcounter==0 || vtemp.z>max_z) max_z=vtemp.z;
            tabv.push_back(vtemp);
            ++Vcounter;
            break;
        case 'f':
            if(arg_count!=3) throw new Exception_arg(line_number);
            ss>>temp_int;
            ftemp.v1=temp_int-1;
            //ss>>temp;
            ss>>temp_int;
            ftemp.v2=temp_int-1;
            //ss>>temp;
            ss>>temp_int;
            ftemp.v3=temp_int-1;
            tabf.push_back(ftemp);
            ++Fcounter;
            break;
        default:
            continue;
        }
        ++line_number;
    }

    faces=Fcounter;
    double width=fabs(max_x-min_x);
    double height=fabs(max_y-min_y);

    int scalar;
    if(img_width/width<img_height/height)
    {
        scalar=0.9*img_width/width;
    }
    else
    {
        scalar=0.9*img_height/height;

    }

    for(int i=0; i<Vcounter; ++i)
    {
        tabv[i].x=scalar*tabv[i].x;
        tabv[i].y=scalar*tabv[i].y;
        tabv[i].z=scalar*tabv[i].z;
    }
    start_x=scalar*min_x*(-1);
    start_y=scalar*min_y*(-1);
    center_x=(max_x-min_x)/2;
    center_y=(max_y-min_y)/2;
    center_z=(max_z-min_z)/2;
}

Object::~Object()
{
    tabv.clear();
    tabf.clear();
}

void Object::draw_object(JiMP2::BMP &bmp, unsigned char r, unsigned char g, unsigned char b, const uint16_t& height)const
{
    for(int i=0; i<faces; ++i)
    {
        rysuj_linie(1+tabv[tabf[i].v1].x+start_x, height+(-1)*(1+tabv[tabf[i].v1].y+start_y), 1+tabv[tabf[i].v2].x+start_x, height+(-1)*(1+tabv[tabf[i].v2].y+start_y), r, g, b, bmp);
        rysuj_linie(1+tabv[tabf[i].v2].x+start_x, height+(-1)*(1+tabv[tabf[i].v2].y+start_y), 1+tabv[tabf[i].v3].x+start_x, height+(-1)*(1+tabv[tabf[i].v3].y+start_y), r, g, b, bmp);
        rysuj_linie(1+tabv[tabf[i].v1].x+start_x, height+(-1)*(1+tabv[tabf[i].v1].y+start_y), 1+tabv[tabf[i].v3].x+start_x, height+(-1)*(1+tabv[tabf[i].v3].y+start_y), r, g, b, bmp);
    }
}

void Object::show()const
{
    cout<<"faces: "<<faces<<endl;
    for(int i=0; i<100; ++i)
    {
        cout<<tabv[tabf[i].v1].x<<" "<<tabv[tabf[i].v1].y<<" "<<tabv[tabf[i].v1].z<<" ";
        cout<<tabv[tabf[i].v2].x<<" "<<tabv[tabf[i].v2].y<<" "<<tabv[tabf[i].v2].z<<" ";
        cout<<tabv[tabf[i].v3].x<<" "<<tabv[tabf[i].v3].y<<" "<<tabv[tabf[i].v3].z<<endl;
    }
}

void Object::make_transformation(All_transformations& AT)
{
    AT.Create_transformation();
    for(vector<Vertex>::iterator it=tabv.begin(); it!=tabv.end(); ++it)
		*it=matrix_to_vertex(AT*vertex_to_matrix(*it));
}

void Object::make_reverse_transformation(All_transformations& AT)
{
    AT.Create_reverse_transformation();
    for(vector<Vertex>::iterator it=tabv.begin(); it!=tabv.end(); ++it)
		*it=matrix_to_vertex(AT*vertex_to_matrix(*it));
}

double Object::get_center_x() {return center_x;}
double Object::get_center_y() {return center_y;}
double Object::get_center_z() {return center_z;}

Matrix vertex_to_matrix(const Vertex& ver)
{
    Matrix B(4,1);
    B.set_el(1,1,ver.x);
    B.set_el(2,1,ver.y);
    B.set_el(3,1,ver.z);
    B.set_el(4,1,1);
    return B;
}

Vertex matrix_to_vertex(Matrix mat)
{
    Vertex ver;
    ver.x=mat.get_el(1,1);
    ver.y=mat.get_el(2,1);
    ver.z=mat.get_el(3,1);
    return ver;
}
