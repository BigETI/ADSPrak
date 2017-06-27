#include <fstream>
#include <string>
#include <vector>

class IOSystem
{
private:
	std::fstream file;
	std::vector<std::streampos> pos;
	unsigned char bitstream = 0;			// 8 Bit in einem char sammeln 
	int bit_anz = 0;						// anzahl der Bit in bitstream
	bool read_bitstream = true;
public:
	~IOSystem()
	{
		file.close();
	}
	bool open_write(std::string datei_name)
	{
		file.open(datei_name, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
		return file.is_open();
	}
	bool open_read(std::string datei_name)
	{
		file.open(datei_name, std::ios::in | std::ios::binary);
		return file.is_open();
	}
	void close()
	{
		file.close();
	}
	bool write_block(char * block, unsigned int size)
	{
		file.write(block, size);
		return file.good();
	}
	bool read_block(char * block, unsigned int size)
	{
		file.read(block, size);
		return file.good();
	}
	template <class _T> bool write_zahl(typename _T zahl)
	{
		file.write((char *)& zahl, sizeof(zahl));
		return file.good();
	}
	template <class _T> bool read_zahl(typename _T & zahl)
	{
		file.read((char *)& zahl, sizeof(zahl));
		return file.good();
	}
	bool write_bit(bool b)
	{	
		if (b) 
		{
			bitstream = bitstream | 1 << (7 - bit_anz);
		}
		if (bit_anz == 7)
		{
			file.write((char *)& bitstream, 1);
			bit_anz = 0;
			bitstream = 0;
			return file.good();
		} else
			bit_anz++;
		return true;
	}
	bool write_bit_flush()
	{
		if (bit_anz)
		{
			file.write((char *)& bitstream, 1);
			bit_anz = 0;
			bitstream = 0;
			return file.good();
		}
		return true;
	}
	bool read_bit(bool & b)
	{
		if (read_bitstream)
		{
			file.read((char *)& bitstream, 1);
			bit_anz = 7;
			read_bitstream = false;
			if (!file.good() || file.fail()) return false;
		}
		if (!bit_anz) read_bitstream = true;
		b = bitstream & (1 << bit_anz);
		bit_anz--;
		return true;
	}
	bool read_bit_flush()
	{
		read_bitstream = true;
		return true;
	}
	int get_pos()
	{
		pos.push_back(file.tellg());
		return (int)(pos.size());
	}
	void set_pos(int number)
	{
		if (number)	file.seekg(pos[number-1]);
	}
};