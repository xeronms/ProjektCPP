#ifndef OBJ_H
#define OBJ_H
#include <vector>
#include "bmp.h"
#include "transform.h"
#include <fstream>

class Vertex{
public:
    double x;
    double y;
    double z;
};

class Face{
public:
    unsigned int v1;
    unsigned int v2;
    unsigned int v3;
};

class Object{
    std::vector<Vertex> tabv;
    std::vector<Face> tabf;
    unsigned int faces;
    int start_x, start_y;
    double center_x, center_y, center_z;
public:
    Object();
    void read_file(const char* file_name, const uint16_t& img_width, const uint16_t& img_height);
    void draw_object(JiMP2::BMP &bmp, unsigned char r, unsigned char g, unsigned char b, const uint16_t& height)const;
    void show()const;
    void make_transformation(All_transformations& AT);
    void make_reverse_transformation(All_transformations& AT);
    double get_center_x();
    double get_center_y();
    double get_center_z();
    void edit_center_point();
    ~Object();
};

Matrix vertex_to_matrix(const Vertex& ver);
Vertex matrix_to_vertex(Matrix mat);

#endif
