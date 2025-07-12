#include<iostream>
#include<fstream>
using namespace std;

struct color { unsigned char r; unsigned char g; unsigned char b; };

int main() {
    ifstream fff("1.bmp", ios::binary);
    ofstream ggg("rez2.bmp", ios::binary);
    
    if (!fff) { cout << "No file 1.bmp. Can't open\n"; exit(1); }
    if (!ggg) { cout << "Can't create rez2.bmp\n"; exit(1); }

    char buf[100];
    color c, f; 
    int w, h;

    fff.read((char*)&buf, 18);
    ggg.write((char*)&buf, 18);
    fff.read((char*)&w, 4); 
    fff.read((char*)&h, 4); 
    w = 256; ggg.write((char*)&w, 4); 
    h = 256; ggg.write((char*)&h, 4); 
    fff.read((char*)&buf, 28);
    ggg.write((char*)&buf, 28);

    cout << "Background color (B G R): ";
    cin >> c.b >> c.g >> c.r;
    cout << "Square color (B G R): ";
    cin >> f.b >> f.g >> f.r;

    const int square_size = 64; 
    const int centr_w = w - square_size / 2; 
    const int centr_h = h - square_size / 2; 

    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            if ((i >= centr_h - square_size / 2) && 
                (i <= centr_h + square_size / 2) && 
                (j >= centr_w - square_size / 2) && 
                (j <= centr_w + square_size / 2)) {
                ggg.write((char*)&f, sizeof(f)); 
            } else {
                ggg.write((char*)&c, sizeof(c)); 
            }
        }
    }

    fff.close();
    ggg.close();
    return 0;
}