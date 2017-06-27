#include <vector>
#include <queue>
#include <map>
#include <stack>

class TreeNode
{
public:
	int grauwert;		// Grauwert
	int wslk;			// Wahrscheinlichket // Anzahl
	TreeNode *left, *right, *parent;	// linker, rechter Nachfolger und Eltern
	bool isleft = true;

public:
	TreeNode(int grauwert, int wslk)
	{
		this->wslk = wslk;
		this->grauwert = grauwert;
		
		left = 0;
		right = 0;
		parent = 0;
	}
	bool operator<(const TreeNode &other) const { return wslk > other.wslk; }
};

template<typename Type, typename Compare = std::less<Type> >
struct pless : public std::binary_function<Type *, Type *, bool> {
	bool operator()(const Type *x, const Type *y) const
	{
		return Compare()(*x, *y);
	}
};

class Kompression
{
private:
	std::priority_queue<TreeNode *, std::vector<TreeNode *>, pless<TreeNode>> Blaetter;
	TreeNode * Tree = 0;

public:
	void histogramm(std::vector<int> & grauwerte, std::vector<int> & histgr)
	{
		// Alle Grauwerte werden gezählt. -> Histogramm erzeugen 
		// Rückgabe in histgr
		for (unsigned int i = 0; i < grauwerte.size(); i++)
		{
			if (grauwerte[i] + 1 > histgr.size()) histgr.resize(grauwerte[i] + 1);
			histgr[grauwerte[i]] ++;
		}
	}
	void Erz_Blaetter(std::vector<int> & grauwerte, std::vector<int> & histgr)
	{
		TreeNode * BlattNode;
		for (unsigned int i = 0; i < histgr.size(); i++)
		{
			if (!histgr[i]) continue;
			BlattNode = new TreeNode(i, histgr[i]);
			Blaetter.push(BlattNode);
		}
	}
	void Erz_Tree()
	{
		TreeNode *no, *bl1, *bl2;
		while (Blaetter.size()>1)
		{
			bl1 = Blaetter.top();
			Blaetter.pop();
			bl2 = Blaetter.top();
			Blaetter.pop();
			no = new TreeNode(0, bl1->wslk + bl2->wslk);
			no->left = bl1;
			no->right = bl2;
			bl1->parent = no;
			bl2->parent = no;
			bl2->isleft = false;
			Blaetter.push(no);
		}
		Tree = Blaetter.top();
		Blaetter.pop();
	}
	
	void HuffmanCode(std::map<int, std::vector<bool> > & Code)
	{
		std::vector<bool> CodeTmp;
		TreeNode * tmp;
		std::stack<TreeNode *> stk;
		stk.push(Tree);
		while (!stk.empty())
		{
			tmp = stk.top();
			stk.pop();
	
			if (!(tmp->left && tmp->right))	// Blatt erreicht -> Code zu Grauwert speichern
			{
				CodeTmp.clear();
				for (TreeNode* tmp2 = tmp; tmp2; tmp2 = tmp2->parent) CodeTmp.push_back(!tmp2->isleft);
				CodeTmp.pop_back();
				std::reverse(CodeTmp.begin(), CodeTmp.end());
				Code[tmp->grauwert] = CodeTmp;
				CodeTmp.pop_back();
			}
			if (tmp->right) // kein Blatt -> Kind auf dem Stack ablegen
			{
				stk.push(tmp->right);
			}
			if (tmp->left) // kein Blatt -> Kind auf dem Stack ablegen
			{
				stk.push(tmp->left);
			}
		}
	}
	void HuffmanDeCode(std::map<int, std::vector<bool> > & Code, std::vector<bool> & bit, std::vector<int> & grauwerte)
	{
		grauwerte.clear();
		std::map<int, std::vector<bool>>::iterator i;
		unsigned int k = 0, l = 0;
		while(k < bit.size())
		{
			for (i = Code.begin(); i != Code.end(); i++)
			{
				do{
					if (l == i->second.size())
					{
						k += l;
						grauwerte.push_back(i->first);
						l = 0;
						i = Code.begin();
					}
					else if (k + l < bit.size() && i->second.at(l) == bit[k + l])
					{
						l++;
					}
					else
					{
						l = 0;
					}
				} while (l);
			}
		}
	}
};

