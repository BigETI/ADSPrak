#define CIMGGIP_MAIN
#include "CImg.h"
#include "Huffman_IO.h"
#include <iostream>
#include "Kompression.h"
using namespace cimg_library;
using namespace std;

#define cimg_use_png 1

int main(void)
{
	vector<int> grauwerte, histogramm;
	Kompression HK;

	gip_load_image("Test2.bmp");

	//Grauwerte auslesen:
	for (unsigned int i = 0; i < gip_win_size_y; i++)
	{
		for (unsigned int k = 0; k < gip_win_size_x; k++)
		{
			grauwerte.push_back(gip_get_grey(k, i));
		}
	}

	// Histogramm erzeugen
	HK.histogramm(grauwerte, histogramm);

	//Ausgabe aller Grauwerte mit Häufigkeit:
	//cout << "Grauwerte:" << endl;
	//for (int i = 0; i < grauwerte.size(); i++)
	//{
	//	cout << grauwerte[i] << " : ("
	//		<< histogramm[grauwerte[i]] << ")" << std::endl;
	//}
	//cout << endl;

	HK.Erz_Blaetter(grauwerte, histogramm);
	HK.Erz_Tree();
	std::map<int, vector<bool>> Code;
	HK.HuffmanCode(Code);

	cout << Code.size() << endl;
	for (map<int, vector<bool>>::iterator i = Code.begin(); i != Code.end(); i++)
	{
		cout << i->first << ':';
		cout << '(' << i->second.size() << ") ";
		for (unsigned int k = 0; k < i->second.size(); k++)
		{
			cout << i->second[k] << ' ';
		}
		cout << endl;
	}

	vector<bool> bitmuster;
	
	Huffman_IO datei;

	datei.open_write("daten.bin");

	// Bildgröße in Datei speichern
	datei.write_img_size(gip_win_size_x, gip_win_size_y);
	
	// map in Datei übertragen

	datei.write_map(Code);

	// schreiben des Bitmusters des Code Vektors

	datei.write_code_vektor(grauwerte, Code);

	datei.close();

	unsigned int imgx, imgy;

	// Datei wieder lesen

	datei.open_read("daten.bin");

	datei.read_img_size(imgx, imgy);

	datei.read_map(Code);

	cout << "======================================================================================================" << endl;

	cout << Code.size() << endl;
	for (map<int, vector<bool>>::iterator i = Code.begin(); i != Code.end(); i++)
	{
		cout << i->first << ':';
		cout << '(' << i->second.size() << ") ";
		for (unsigned int k = 0; k < i->second.size(); k++)
		{
			cout << i->second[k] << ' ';
		}
		cout << endl;
	}
	cout << "Grauwerte -> aus Bit-Vektor wieder hergestellt:" << endl;
	vector<bool> bit;
	datei.read_code_vektor(bit);
	HK.HuffmanDeCode(Code,bit, grauwerte);

	//for (int i = 0; i < grauwerte.size(); i++)
	//{
	//	cout << grauwerte[i] << ", ";
	//}
	//cout << endl;

	datei.close();

	CImg<unsigned char> img_restore(imgx, imgy, 1, 1);

	//Grauwerte in img_restore übertragen:
	for (unsigned int i = 0; i != imgy; i++)
	{
		for (unsigned int k = 0; k != imgx; k++)
		{
			img_restore(k, i, 0) = grauwerte[i*imgx+k];
		}
	}
	CImgDisplay main_disp(img_restore, "Wieder hergestellt");

	system("PAUSE");

	return 0;
}
