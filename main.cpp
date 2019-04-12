#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Nod
{
protected:
    int info;
    Nod *st;
    Nod *dr;
    Nod *parent;
    static int nr;

public:
    Nod(int val=0)
    {
        info=val;
        dr=NULL;
        st=NULL;

    }
    Nod(const Nod& node)
    {
        info=node.info;
        st=node.st;
        dr=node.dr;
    }
    ~Nod()
    {
        info=0;
        st=NULL;
        dr=NULL;
    }
    static void init(int x)
    {
        nr=x;
    }
    int getInfo()
    {
        return info;
    }
    void setInfo(int val)
    {
        info=val;
    }
    Nod*& getSt()
    {
        return st;
    }
    void setSt(Nod* node)
    {
        st=node;
    }
    void setDr(Nod* node)
    {
        dr=node;
    }
    Nod*& getDr()
    {
        return dr;
    }
    Nod*& getParent()
    {
        return parent;
    }
    Nod& operator=(Nod& node)
    {
        if(this==&node)
            return node;
        st=node.st;
        dr=node.dr;
        info=node.info;
        return *this;
    }
    friend istream& operator>>(istream&,Nod&);
    friend ostream& operator<<(ostream&,Nod&);
};

int Nod::nr;

istream& operator>>(istream& in,Nod& node)
{
    int val;
    in>>val;
    node.setInfo(val);
    node.st=NULL;
    node.dr=NULL;
    return in;
}

ostream& operator<<(ostream& out,Nod& node)
{
    out<<node.info;
    return out;
}

class Nod_rosu_negru:public Nod
{
    char culoare[20];
    Nod_rosu_negru *parent,*st,*dr;
public:
    Nod_rosu_negru():Nod()
    {
        strcpy(culoare,"");
        strcpy(parent->culoare,"");
    }
    Nod_rosu_negru(int val):Nod(val)
    {
        st=NULL;
        dr=NULL;
        parent=NULL;
    }
    Nod_rosu_negru(int val,char cul[20]):Nod(val)
    {
        strcpy(culoare,cul);
        st=NULL;
        dr=NULL;
        parent=NULL;
    }
    Nod_rosu_negru(const Nod_rosu_negru& rbnode):Nod(rbnode)
    {
        strcpy(culoare,rbnode.culoare);
        strcpy(parent->culoare,rbnode.parent->culoare);
    }
    ~Nod_rosu_negru()
    {
        strcpy(culoare,"\0");
    }
    char* getCuloare()
    {
        return culoare;
    }
    void setCuloare(char* cul)
    {
        strcpy(culoare,cul);
    }
    Nod_rosu_negru*& getParent()
    {
        return parent;
    }
    Nod_rosu_negru*& getSt()
    {
        return st;
    }
    Nod_rosu_negru*& getDr()
    {
        return dr;
    }
    int getInfo()
    {
        return info;
    }
    Nod_rosu_negru& operator=(Nod_rosu_negru& rbnode)
    {
        info=rbnode.info;
        st=rbnode.st;
        dr=rbnode.dr;
        parent=rbnode.parent;
        strcpy(culoare,rbnode.culoare);
        return *this;
    }
    friend istream& operator>>(istream&,Nod_rosu_negru&);
    friend ostream& operator<<(ostream&,const Nod_rosu_negru&);
};

istream& operator>>(istream& in,Nod_rosu_negru& rbnode)
{
    in>>static_cast<Nod&>(rbnode);
    in>>rbnode.culoare;
    return in;
}
ostream& operator<<(ostream& out,Nod_rosu_negru& rbnode)
{
    out<<static_cast<Nod&>(rbnode);
    out<<rbnode.getCuloare()<<endl;
    return out;
}

class Arbore
{
protected:
    int nr_noduri;
public:
    Arbore(int val=0)
    {
        nr_noduri=val;
    }
    Arbore(Arbore& arb)
    {
        nr_noduri=arb.nr_noduri;
    }
    ~Arbore()
    {
        nr_noduri=0;
    }
    Arbore& operator=(Arbore& arb)
    {
        if(this == &arb)
        {
            return arb;
        }
        nr_noduri=arb.nr_noduri;
        return *this;
    }
    friend istream& operator>>(istream&,Arbore&);
    friend ostream& operator<<(ostream&,Arbore&);

    int getNrNoduri()
    {
        return nr_noduri;
    }
    void setNrNoduri(int val)
    {
        nr_noduri=val;
    }
    virtual void afisare(ostream&)=0;
    virtual void citire(istream&)=0;
    virtual int inaltime()=0;

};

istream& operator>>(istream& in,Arbore& arb)
{
    arb.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Arbore& arb)
{
    out<<arb.nr_noduri<<endl;
    arb.afisare(out);
    return out;
}

class ABC : public Arbore
{
private:
    Nod* rad;
    static int nr_arbori;
    void printPostorder(ostream& out, Nod* node)
    {
        if(node == NULL)
            return;
        printPostorder(out, node->getSt());
        printPostorder(out, node->getDr());
        out << node->getInfo() << " ";

    }
    void printInorder(ostream& out, Nod*& node)
    {
        if(node == NULL)
            return;
        printInorder(out, node->getSt());
        out << node->getInfo() << " ";
        printInorder(out, node->getDr());
    }

    void Inorder(Nod* node, int *&v)
    {
        static int index = 0;
        if(node == NULL)
            return;
        Inorder(node->getSt(), v);
        v[index++] = node->getInfo();
        Inorder(node->getDr(), v);
    }
    void printPreorder(ostream& out, Nod* node)
    {
        if(node == NULL)
            return;
        out << node->getInfo() << " ";
        printPreorder(out, node->getSt());
        printPreorder(out, node->getDr());
    }
    void postorderForDestructor(Nod* node)
    {
        if(node == NULL)
            return;
        postorderForDestructor(node->getSt());
        postorderForDestructor(node->getDr());
        delete node;
    }

    int treeHeight(Nod* nod)
    {
        if(nod == NULL)
            return -1;
        int heightLeftTree = treeHeight(nod->getSt());
        int heightRightTree = treeHeight(nod->getDr());

        if(heightLeftTree > heightRightTree)
            return heightLeftTree+1;
        return heightRightTree+1;
    }

public:
    ABC(int val=0):Arbore(val)
    {
        rad=NULL;
    }
    ABC(ABC&);
    ~ABC()
    {
        postorderForDestructor(rad);
    }
    Nod* getRadacina()
    {
        return rad;
    }

    static int getNrArbori();
    ABC& operator+(int val)
    {

        Nod *aux, *tata_aux;
        tata_aux = aux = rad;

        if(aux == NULL)
        {
            rad = new Nod(val);
            nr_noduri++;
            return *this;
        }

        while(aux != NULL)
        {
            tata_aux = aux;
            if(val > aux->getInfo())
                aux = aux->getDr();
            else
                aux = aux->getSt();
        }

        if(val > tata_aux->getInfo())
        {
            tata_aux->getDr() = new Nod(val);
            nr_noduri++;
        }
        else
        {
            tata_aux->getSt() = new Nod(val);
            nr_noduri++;
        }

        return *this;
    }
    ABC& operator = (ABC& bintree)
    {
        if(this == &bintree)
            return *this;

        delete this;
        int *v = new int[bintree.nr_noduri];
        Inorder(bintree.rad, v);

        operator+(3);

        for(int i = 0; i < bintree.nr_noduri; i++)
            if(v[i] != 3)
                operator+(v[i]);

        return *this;

    }
    void afisare(ostream& out)
    {
        out << "Preordine: ";
        printPreorder(out, rad);
        out << endl;

        out << "Inordine: ";
        printInorder(out, rad);
        out << endl;

        out << "Postordine: ";
        printPostorder(out, rad);
        out << endl;
    }
    void citire(istream& in)
    {
        int val;
        in >> val;
        *this = *this + val;

    }
    int inaltime()
    {
        return treeHeight(rad);
    }
};

class Arbore_bicolor : public Arbore
{
private:
    Nod_rosu_negru *rad;

    void printInorder(ostream& out, Nod* node)
    {
        if(node == NULL)
            return;
        printInorder(out, node->getSt());
        out << node->getInfo() << " ";
        printInorder(out, node->getDr());
    }
    void postorderForDestructor(Nod* node)
    {
        if(node == NULL)
            return;
        postorderForDestructor(node->getSt());
        postorderForDestructor(node->getDr());
        delete node;
    }
    int blackHeight(Nod_rosu_negru* rbnode)
    {
        if(rbnode == NULL)
            return 1;
        if(strcmp(rbnode->getCuloare(), "BLACK"))
            return 1 + this->blackHeight((Nod_rosu_negru*)rbnode->getDr());
        return this->blackHeight((Nod_rosu_negru*)rbnode->getDr());
    }
    void rotateLeft(Nod_rosu_negru *&root, Nod_rosu_negru *&pt)
    {
        Nod_rosu_negru *pt_right = (Nod_rosu_negru*)pt->getDr();

        pt->getDr() = pt_right->getSt();

        if (pt->getDr() != NULL)
            pt->getDr()->getParent() = pt;

        pt_right->getParent() = pt->getParent();

        if (pt->getParent() == NULL)
            root = pt_right;

        else if (pt == pt->getParent()->getSt())
            pt->getParent()->getSt() = pt_right;

        else
            pt->getParent()->getDr() = pt_right;

        pt_right->getSt() = pt;
        pt->getParent() = pt_right;
    }
    void rotateRight(Nod_rosu_negru *&root, Nod_rosu_negru *&pt)
    {
        Nod_rosu_negru *pt_left = (Nod_rosu_negru*)pt->getSt();
        pt->getSt() = pt_left->getDr();

        if (pt->getSt() != NULL)
            pt->getSt()->getParent() = pt;

        pt_left->getParent() = pt->getParent();

        if (pt->getParent() == NULL)
            root = pt_left;

        else if (pt == pt->getParent()->getSt())
            pt->getParent()->getSt() = pt_left;

        else
            pt->getParent()->getDr() = pt_left;

        pt_left->getDr() = pt;
        pt->getParent() = pt_left;
    }
    void fixViolation(Nod_rosu_negru *&root, Nod_rosu_negru *&pt)
    {
        Nod_rosu_negru *parent_pt = NULL;
        Nod_rosu_negru *grand_parent_pt = NULL;

        while ((pt != root) && !(strcmp(pt->getCuloare(), "BLACK")) && strcmp(pt->getParent()->getCuloare(), "RED"))
        {

            parent_pt = pt->getParent();
            grand_parent_pt = pt->getParent()->getParent();


            if (parent_pt == grand_parent_pt->getSt())
            {

                Nod_rosu_negru *uncle_pt = grand_parent_pt->getDr();

                if (uncle_pt != NULL && strcmp(uncle_pt->getCuloare(), "RED"))
                {
                    grand_parent_pt->setCuloare("RED");
                    parent_pt->setCuloare("BLACK");
                    uncle_pt->setCuloare("BLACK");
                    pt = grand_parent_pt;
                }

                else
                {

                    if (pt == parent_pt->getDr())
                    {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->getParent();
                    }

                    rotateRight(root, grand_parent_pt);
                    char cul[20];
                    strcpy(cul, parent_pt->getCuloare());
                    parent_pt->setCuloare(grand_parent_pt->getCuloare());
                    grand_parent_pt->setCuloare(cul);
                    pt = parent_pt;
                }
            }

            else
            {
                Nod_rosu_negru *uncle_pt = grand_parent_pt->getSt();


                if ((uncle_pt != NULL) && strcmp(uncle_pt->getCuloare(), "RED"))
                {
                    grand_parent_pt->setCuloare("RED");
                    parent_pt->setCuloare("BLACK");
                    uncle_pt->setCuloare("BLACK");
                    pt = grand_parent_pt;
                }
                else
                {

                    if (pt == parent_pt->getSt())
                    {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->getParent();
                    }


                    rotateLeft(root, grand_parent_pt);
                    char cul[20];
                    strcpy(cul, parent_pt->getCuloare());
                    parent_pt->setCuloare(grand_parent_pt->getCuloare());
                    grand_parent_pt->setCuloare(cul);
                    pt = parent_pt;
                }
            }
        }

        root->setCuloare("BLACK");
    }
    void Inorder(Nod_rosu_negru* node, int *&v)
    {
        static int index = 0;
        if(node == NULL)
            return;
        Inorder(node->getSt(), v);
        v[index++] = node->getInfo();
        Inorder(node->getDr(), v);
    }

public:
    Arbore_bicolor(int val = 0) : Arbore(val)
    {
        rad = NULL;
    }
    Arbore_bicolor(Arbore_bicolor& tree)
    {
        int *v = new int[tree.nr_noduri];
        Inorder(tree.rad, v);

        insert(3);

        for(int i = 0; i < tree.nr_noduri; i++)
            if(v[i] != 3)
                insert(v[i]);
    }
    ~Arbore_bicolor()
    {
        postorderForDestructor(rad);
    }

    Arbore_bicolor& operator=(Arbore_bicolor& tree)
    {
        if(this == &tree)
            return *this;

        delete this;
        int *v = new int[tree.nr_noduri];
        Inorder(tree.rad, v);

        insert(3);

        for(int i = 0; i < tree.nr_noduri; i++)
            if(v[i] != 3)
                insert(v[i]);

        return *this;

    }
    void insert(int val)
    {
        Nod_rosu_negru *aux, *tata_aux;
        tata_aux = aux = rad;
        Nod_rosu_negru *nod = new Nod_rosu_negru(val, "RED");
        if(aux == NULL)
        {
            rad = nod;
            nr_noduri++;
            return;
        }

        while(aux != NULL)
        {
            tata_aux = aux;
            if(val > aux->getInfo())
                aux = aux->getDr();
            else
                aux = aux->getSt();
        }

        if(val > tata_aux->getInfo())
        {
            tata_aux->getDr() = nod;
            nr_noduri++;
        }
        else
        {
            tata_aux->getSt() = nod;
            nr_noduri++;
        }
        nod->getParent() = tata_aux;

        fixViolation(rad, nod);

    }

    int inaltime()
    {
        int bh = blackHeight(rad);
        int h = pow(2, bh) - 1;

        return h;
    }
    void afisare(ostream& out)
    {
        out << "Inordine: ";
        printInorder(out, rad);
        out << endl;
    }
    void citire(istream& in)
    {
        int val;
        in >> val;
        this->insert(val);
    }
};

void citireObiecte(int nr_obiecte, Arbore **trees)
{
    cout << "Cate obiecte doriti sa cititi?" << endl;
    cin >> nr_obiecte;
    trees = new Arbore*[nr_obiecte];

    cout << "Tipuri de copaci" << endl;
    cout << "1. Arbore Binar de Cautare" << endl;
    cout << "2. Arbore Rosu Negru" << endl;

    for(int i = 0; i < nr_obiecte; i++)
    {
        int tip;
        cin >> tip;

        switch(tip)
        {
        case 1 :
            cout << "Introduceti radacina arborelui" << endl;
            int rad;
            cin >> rad;
            trees[i] = new ABC(rad);
            cout << "Cate noduri doriti sa introduceti?" << endl;
            cin >> rad;
            trees[i]->setNrNoduri(rad);
            for(int i = 0; i < rad; i++)
            {
                cout<<"Introduceti nodul";
                cin >> *trees[i];
            }
            break;
        case 2 :
            cout << "Introduceti radacina arborelui" << endl;
            int val;
            cin >> val;
            trees[i] = new Arbore_bicolor(val);
            cout << "Cate noduri doriti sa introduceti?" << endl;
            cin >> val;
            trees[i]->setNrNoduri(val);
            for(int i = 0; i < val; i++)
            {
                cout<<"Introduceti nodul";
                cin >> *trees[i];
            }
            break;

        default:
            cout << "Comanda invalida" << endl;
        }
    }

    for(int i = 0; i < nr_obiecte; i++)
        cout << trees[i];
}


int main()
{
    ABC a;
    Arbore_bicolor b;
    Arbore *trees[3];
    cout << "Meniu: " << endl;
    cout << "1. Citirea si afisarea unui ABC" << endl;
    cout << "2. Citirea si afisarea unui RBT" << endl;
    cout << "3. Citirea si afisarea a n obiecte" << endl;

    int comanda;
    int val;
    int tip;
    cin >> comanda;

    switch(comanda)
    {
    case 1 :
        cout << "Nr noduri = ?" << endl;
        cin >> val;
        for(int i = 0; i < val; i++)
            cin >> a;
        cout << a;
        break;

    case 2 :
        cout << "Nr noduri = ?" << endl;
        cin >> val;
        for(int i = 0; i < val; i++)
            cin >> b;
        cout << b;
        break;

    case 3 :
        for(int i = 0; i < 3; i++) {
            cout << "Tip arbore" << endl;
            cin >> tip;
            if(tip == 1) {
                cout << "Radacina: " << endl;
                cin >> tip;
                trees[i] = new ABC(tip);
                cout << "cate val doriti sa introd: " << endl;
                cin >> tip;
                for(int j = 0; j < tip; j++) {
                    cin >> *trees[i];
                }

            }
            else {
                cout << "Radacina: " << endl;
                cin >> tip;
                trees[i] = new Arbore_bicolor(tip);
                cout << "cate val doriti sa introd: " << endl;
                cin >> tip;
                for(int j = 0; j < tip; j++) {
                    cin >> *trees[i];
                }
            }
        }
        for(int i = 0; i < 3; i++)
            cout << *trees[i];
        break;

    default:
        cout << "Comanda invalida" << endl;
    }


    return 0;
}

