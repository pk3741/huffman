#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <list>
#include <algorithm>


std::vector<std::pair<std::string, int> > getWages(std::string input)
{
    std::map<std::string, int> wages;
    for (size_t i = 0; i < input.size(); i++)
    {
        wages[std::string(1,input[i])]++;
    }
    std::vector<std::pair<std::string, int> > v(wages.begin(), wages.end());
    return v;
}

class Leaf
{
public:
    std::string data;
    int wage;
    std::shared_ptr<Leaf> lchild;
    std::shared_ptr<Leaf> rchild;
    std::string code;
    Leaf() : data(""), wage(0), lchild(nullptr), rchild(nullptr), code("") {};
    Leaf(std::string ndata, int nwage) : data(ndata), wage(nwage), lchild(nullptr), rchild(nullptr), code("") {};
    Leaf(int nwage, Leaf* l, Leaf* r, std::string ndata) : wage(nwage), lchild(l), rchild(r), data(ndata), code("") {};

    Leaf(const Leaf& leaf)
    {
        data = leaf.data;
        wage = leaf.wage;
        lchild = leaf.lchild;
        rchild = leaf.rchild;
        code = leaf.code;
    }
    void print(std::shared_ptr<Leaf> leaf, std::vector<std::pair<std::string, std::string>> &codes_vec)
    {
        std::cout << leaf->data << " " << leaf->wage << ", code: " <<leaf->code << std::endl;

        std::string str = leaf->data;
        std::string code = leaf->code;
        for (size_t i = 0; i < str.length(); i++)
        {
            for (size_t j = 0; j < codes_vec.size(); j++)
            {
                if (std::string(1,str[i]) == codes_vec[j].first)
                {
                    codes_vec[j].second += code;
                }
            }
        }


        if (leaf->lchild)
        {
            leaf->lchild->code = "0";
            print(leaf->lchild, codes_vec);
        }
        if (leaf->rchild)
        {
            leaf->rchild->code = "1";
            print(leaf->rchild, codes_vec);
        }
    }

    ~Leaf()
    {
        
    }
};

bool compLeaf(const Leaf& a, const Leaf& b) { return a.wage < b.wage; }
bool sortbysec(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)
{
    return (a.second < b.second);
}

int main()
{
    std::string input;
    std::cout << "Podaj ciag znakow: ";
    std::cin >> input;
    std::vector<std::pair<std::string, int>> wages = getWages(input);

    std::vector<std::pair<std::string, std::string>> codes;

    for (size_t i = 0; i < wages.size(); i++)
    {
        codes.push_back(std::pair<std::string, std::string>(wages[i].first, ""));
    }

    std::cout << "Codes: \n";
    for (size_t i = 0; i < codes.size(); i++)
    {
        std::cout << codes[i].first << " " << codes[i].second << std::endl;
    }
    std::cout << "\n";

    std::reverse(wages.begin(), wages.end());
    std::sort(wages.begin(), wages.end(), sortbysec);

    std::cout << "\n";
    //aaaaaaabbbbbbbbcccddddddddddeeeeeeeeffff
    for (size_t i = 0; i < wages.size(); i++)
    {
        std::cout << wages[i].first << " " << wages[i].second << std::endl;
    }


    std::cout << "\n";
    std::list<Leaf> leaves;
    for (size_t i = 0; i < wages.size(); i++)
    {
        leaves.push_back(Leaf(wages[i].first, wages[i].second));
    }

    int i = 0;

    bool working = true;
    while (working)
    {
        if (leaves.size() > 1)
        {
            for (auto it = leaves.cbegin(); it != leaves.cend(); it++) {
                std::cout << (*it).data << (*it).wage << std::endl;
            }
            std::cout << "\n";
            Leaf * left = new Leaf(leaves.front());
            std::cout << "taking: " << left->wage << std::endl;
            //left->code = "0";
            leaves.pop_front();
            Leaf * right = new Leaf(leaves.front());
            std::cout << "taking: " << right->wage << std::endl;
            //right->code = "1";
            leaves.pop_front();
            
            leaves.push_back(Leaf(left->wage + right->wage, left, right, left->data+ right->data));
            leaves.sort(compLeaf);
            std::cout << "Epoch " << i << ":" << std::endl;
            for (auto it = leaves.cbegin(); it != leaves.cend(); it++) {
                std::cout << (*it).data << (*it).wage << std::endl;
            }
            std::cout << "\n";
            leaves.sort(compLeaf);
            i++;
        }
        else
        {
            leaves.front().print(std::make_shared<Leaf>(leaves.front()), codes);
            working = false;
        }
        
    }

    std::cout << "codes: \n";
    for (size_t i = 0; i < codes.size(); i++)
    {
        std::cout << codes[i].first << " " << codes[i].second << std::endl;
    }


   




}
