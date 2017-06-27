#include "IOSystem.h"
#include <string>
#include <vector>
#include <map>

class Huffman_IO
{
private:
	IOSystem file;
	bool open_w = false, open_r = false;
public:
	~Huffman_IO()
	{
		this->close();
	}
	bool open_write(std::string dateiname)
	{
		if (open_r) return false;
		open_w = file.open_write(dateiname);
		return open_w;
	}
	bool open_read(std::string dateiname)
	{
		if (open_w) return false;
		open_r = file.open_read(dateiname);
		return open_r;
	}
	bool write_map(std::map<int, std::vector<bool>> & Code)
	{
		if (open_r) return false;
		// Anzahl der Zeilen in der Map speichern
		if (!file.write_zahl(Code.size())) return false;	// Anzahl der Zeilen in der map
		for (std::map<int, std::vector<bool>>::iterator i = Code.begin(); i != Code.end(); i++)	// Durchlaufe alle Zeilen
		{
			if (!file.write_zahl(i->first)) return false;			// Schreibe: Grauwert
			if (!file.write_zahl(i->second.size())) return false;	// Schreibe: Anzahl der Bit in der Zeile (Codelänge)
			for (unsigned int k = 0; k < i->second.size(); k++)
			{
				if (!file.write_bit(i->second[k])) return false;	// Schreibe: Huffman-Codewort für den Grauwert
			}
			if(!file.write_bit_flush()) return false;
		}
		return true;
	}
		bool write_code_vektor(std::vector<int> & grauwerte, std::map<int, std::vector<bool>> & Code)
	{
		int pos_anz_bitvec;		// Filepointer merken für die Anzahl der Bit im Bit-Vector zu spreichern
		int pos_aktuell;		// Filepointer wieder auf aktuellen Wert setzen 
		int anz_vec_bit = 0;	// Anzahl der geschriebenen Code-Vektor-Bits
		if (open_r) return false;
		// Position merken um später die Anzahl der Bit eintragen zu können
		pos_anz_bitvec = file.get_pos();
		unsigned int anz_bit = 0;
		if (!file.write_zahl(anz_bit)) return false;	// Platzhalter für die Anzahl der Bits
		// schreiben des Bitmusters
		std::map<int, std::vector<bool>>::iterator i;
		for (unsigned int k = 0; k < grauwerte.size(); k++)
		{
			i = Code.find(grauwerte[k]);
			if (i != Code.end())
			{
				for (unsigned int l = 0; l < i->second.size(); l++)
				{
					if (!file.write_bit(i->second[l])) return false;	// Schreibe: Huffman-Codewort für den Grauwert
				}
				anz_bit += static_cast<unsigned int>(i->second.size());
			}
		}
		if (!file.write_bit_flush()) return false;
		pos_aktuell = file.get_pos();	// Aktuelle Filepointer-Position merken
		file.set_pos(pos_anz_bitvec);	// Dateiposition zur Speicherung der Grösse des Bit-Vektors wieder anfahren
		if (!file.write_zahl(anz_bit)) return false;	// Platzhalter für die Anzahl der Bits
		file.set_pos(pos_aktuell); // Filepointer wieder auf letzte Position rücksetzen
		return true;
	}
	bool close()
	{
		if (open_w)
		{
			if (!file.write_bit_flush()) return false;		// Bitpuffer leeren
		}
		open_w = false;
		open_r = false;
		file.close();
		return true;
	}
		bool read_map(std::map<int, std::vector<bool>> & Code)
	{
		Code.clear();
		if (open_w) return false;
		// Anzahl der Zeilen in der Map lesen
		unsigned int anzahl, bit_anzahl;
		int grauwert;
		bool b;
		std::vector<bool> tmp;
		if (!file.read_zahl(anzahl)) return false;	// Anzahl der Zeilen in der map
		for (unsigned int i = 0; i < anzahl; i++)			// Durchlaufe alle Zeilen
		{
			if (!file.read_zahl(grauwert)) return false;			// Lese: Grauwert
			if (!file.read_zahl(bit_anzahl)) return false;			// Lese: Anzahl der Bit in der Zeile (Codelänge)
			tmp.resize(bit_anzahl);
			for (unsigned int k = 0; k < bit_anzahl; k++)
			{
				if (!file.read_bit(b)) return false;				// Lese: Huffman-Codewort für den Grauwert
				tmp[k] = b;
			}
			file.read_bit_flush();
			Code[grauwert] = tmp;
			tmp.clear();
		}
		return true;
	}
	bool read_code_vektor(std::vector<bool> & bit)
	{
		if (open_w) return false;
		// lesen des Bitmusters
		bool b;
		unsigned int i = 0, anz_bit;
		file.read_bit_flush();
		file.read_zahl(anz_bit);
		bit.resize(anz_bit);
		while (i < anz_bit && file.read_bit(b))
		{
			bit[i] = b;
			i++;
		}
		return true;
	}
	bool write_img_size(unsigned int x, unsigned int y)
	{
		if (!file.write_zahl(x)) return false;
		if (!file.write_zahl(y)) return false;
		return true;
	}
	bool read_img_size(unsigned int & x, unsigned int & y)
	{
		if (!file.read_zahl(x)) return false;
		if (!file.read_zahl(y)) return false;
		return true;
	}
};