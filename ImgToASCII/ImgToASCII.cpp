#include "ImgToASCII.h"

void ImgToASCII::open_img()
{
	img.open(img_path, std::ios_base::in | std::ios_base::binary);

}
void ImgToASCII::close_img()
{
	img.close();
}
void ImgToASCII::open_txt()
{
	txt.open(txt_path);
}
void ImgToASCII::close_txt()
{
	txt.close();
}

std::pair<unsigned char, unsigned char> ImgToASCII::split_byte(unsigned char a) const
{
	return std::make_pair((a >> 4), (a & 0xf));
}

unsigned int ImgToASCII::join_bytes(unsigned char a, unsigned char b) const
{
	return ((a << 8) + b);
}

ImgToASCII::ImgToASCII(const std::string imgpath, const std::string txtpath)
	: img_path(imgpath), txt_path(txtpath) {}

ImgToASCII::~ImgToASCII()
{
	close_img();
	close_txt();
}

void ImgToASCII::parse_comment()
{
	unsigned char size[2]{ 0, 0 };

	img >> size[0] >> size[1];
	std::cout << std::endl << "Коммментарий (размер " << ((size[0] << 4) + size[1]) - 2 << " бт): " << std::endl;

	for (unsigned int i = 0; i < ((size[0] << 4) + size[1]) - 2; ++i)
	{
		img >> std::noskipws >> byte;
		std::cout << byte;
	}
	std::cout << std::endl;
}

void ImgToASCII::parse_kvant_table()
{
	unsigned char size[2]{ 0, 0 };

	img >> size[0] >> size[1];
	img >> byte;
	std::pair<unsigned char, unsigned char> id = split_byte(byte);
	if (id.first)
		std::cout << std::endl << "Таблица квантования (2 байта), ID: " << std::hex << (unsigned int)id.second << std::endl;
	else
		std::cout << std::endl << "Таблица квантования (1 байт), ID: " << std::hex << (unsigned int)id.second << std::endl;

	for (unsigned int i = 0; i < ((size[0] << 4) + size[1]) - 3; ++i)
	{
		img >> byte;
		std::cout << std::hex << (unsigned int)byte << " ";
	}
	std::cout << std::endl;
}

void ImgToASCII::parse_baseline_DCT()
{
	unsigned char size[2]{ 0, 0 };
	unsigned char reso[2]{ 0, 0 };

	img >> size[0] >> size[1];
	std::cout << std::endl << "Baseline DCT: " << std::endl;
	img >> byte;
	std::cout << "Разрядность каналов: " << (unsigned int)byte << std::endl;

	unsigned int width, height;
	img >> reso[0] >> reso[1];
	height = join_bytes(reso[0], reso[1]);
	img >> reso[0] >> reso[1];
	width = join_bytes(reso[0], reso[1]);
	std::cout << "Разрешение изображения: " << std::dec << width << "x" << height << std::endl;

	img >> byte;
	std::cout << "Количество каналов: " << (unsigned int)byte << std::endl;
	for (unsigned int i = 0; i < 3; ++i)
	{
		img >> byte;
		std::cout << "ID: " << std::hex << (unsigned int)byte << " | ";
		img >> byte;
		std::pair<unsigned char, unsigned char> thinning = split_byte(byte);
		std::cout << "Горизонтальное прореживание: " << std::hex << (unsigned int)thinning.first  << " | ";
		std::cout << "Вертикальное   прореживание: " << std::hex << (unsigned int)thinning.second << " | ";
		img >> byte;
		std::cout << "ID таблицы квантования: " << std::hex << (unsigned int)byte << " | ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void ImgToASCII::parse_haffman_table()
{
	unsigned char size[2]{ 0, 0 };
	unsigned int length = 0;
	img >> size[0] >> size[1];
	img >> byte;
	std::pair<unsigned char, unsigned char> id = split_byte(byte);

	if (id.first)
		std::cout << std::endl << "Таблица Хаффмана (AC коэф.), ID: " << std::hex << (unsigned int)id.second << std::endl;
	else
		std::cout << std::endl << "Таблица Хаффмана (DC коэф.), ID: " << std::hex << (unsigned int)id.second << std::endl;

	std::cout << "Длины кодов: ";
	for (unsigned int i = 1; i <= 16 ; ++i)
	{
		img >> byte;
		length += (unsigned int)byte;
		std::cout << std::hex << (unsigned int)byte << " ";
	}
	std::cout << std::endl << "Коды: ";
	for (unsigned int i = 0; i < length; ++i)
	{
		img >> byte;
		std::cout << std::hex << (unsigned int)byte << " ";
	}
	std::cout << std::endl;
}

void ImgToASCII::parse_start_of_scan()
{
	unsigned char size[2]{ 0, 0 };
	unsigned char chanel_cnt;

	std::cout << std::endl << "Start of Scan:" << std::endl;
	img >> size[0] >> size[1];
	std::cout << "Размер SOS: " << std::dec << join_bytes(size[0], size[1]) << std::endl;

	img >> chanel_cnt;
	for (unsigned int i = 0; i < chanel_cnt; ++i)
	{
		img >> byte;
		std::cout << "Идентификатор канала: " << std::hex << (unsigned int)byte << std::endl;
		img >> byte;
		std::pair<unsigned char, unsigned char> id = split_byte(byte);
		std::cout << "Идентификатор таблицы Хаффмана для DC коэффициентов: " << (unsigned int)id.first  << std::endl;
		std::cout << "Идентификатор таблицы Хаффмана для AC коэффициентов: " << (unsigned int)id.second << std::endl << std::endl;
	}
	img >> byte;
	std::cout << "Start of spectral or predictor selection: " << std::hex << (unsigned int)byte << std::endl;
	img >> byte;
	std::cout << "End of spectral selection: " << std::hex << (unsigned int)byte << std::endl;
	img >> byte;
	std::cout << "Successive approximation bit position: " << std::hex << (unsigned int)byte << std::endl;

	while (img >> byte)
	{
		std::cout << std::bitset<8>((unsigned int)byte);
	}
}

void ImgToASCII::parse_jpg()
{
	open_img();
	open_txt();

	while (img >> byte)
	{
		if (byte == 0xff)
		{
			img >> byte;
			switch (byte)
			{
			case 0xD8:
				std::cout << "Начало" << std::endl;
				break;
			case 0xFE:
				parse_comment();
				break;

			case 0xDB:
				parse_kvant_table();
				break;

			case 0xC0:
				parse_baseline_DCT();
				break;

			case 0xC4:
				parse_haffman_table();
				break;

			case 0xDA:
				parse_start_of_scan();
				std::cout << std::endl << "Закодированные данные: " << std::endl;
				break;

			case 0xD9 :
				std::cout << std::endl << "Конец" << std::endl;
				break;

			default:
				std::cout << std::hex << (unsigned int)byte << " ";
				break;
			}
		}
	}
}
//101011101110011101100001111100100

