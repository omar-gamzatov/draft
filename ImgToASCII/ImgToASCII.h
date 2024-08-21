#pragma once
#include <iostream>
#include <fstream>
#include <bitset>

class ImgToASCII
{
	std::string img_path = "";
	std::string txt_path = "";
	std::ifstream img;
	std::ofstream txt;
	unsigned char byte = 0x00;

	void open_img();
	void close_img();
	void open_txt();
	void close_txt();

	void parse_comment();
	void parse_kvant_table();
	void parse_baseline_DCT();
	void parse_haffman_table();
	void parse_start_of_scan();

	std::pair<unsigned char, unsigned char> split_byte(unsigned char a) const;
	unsigned int join_bytes(unsigned char a, unsigned char b) const;



public:
	explicit ImgToASCII(const std::string imgpath, const std::string txtpath);
	~ImgToASCII();
	void parse_jpg();
};
