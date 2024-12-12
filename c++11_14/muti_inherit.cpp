#include <iostream>

using namespace std;

class GrandFather
{
private:
    int data;
    int age;
    /* data */
public:
    GrandFather(/* args */);
    virtual ~GrandFather();
    virtual void say() = 0;
    virtual void getAge() = 0;
};

GrandFather::GrandFather(/* args */)
{
    cout << "GrandFather start" << endl;
}

GrandFather::~GrandFather()
{
       cout << "GrandFather end" << endl;
}

class Father : public  GrandFather
{
private:
    /* data */
public:
    Father(/* args */);
    virtual ~Father();
    virtual void say() override;
    virtual void getAge() override;
};

Father::Father(/* args */)
{
    cout << "Father start" << endl;
}

Father::~Father()
{
    cout << "father end" << endl;
}
void Father::say()
{
    cout << "Father say" << endl;
}
void Father::getAge()
{
     cout << "get Father age" << endl;   
}

class Son : public Father
{
private:
    /* data */
public:
    Son(/* args */);
    ~Son();
    void say();
    void getAge();
};

Son::Son(/* args */)
{
    cout << "Son start" << endl;
}

Son::~Son()
{
    cout << "Son end" << endl;
}

void Son::say()
{
    cout << "son say" << endl;
}
void Son::getAge()
{
     cout << "get son age" << endl;
}


int main(int argc, char const *argv[])
{
    {
        Son son;
        Father *pFather = &son;
        pFather->say();

        GrandFather* pGrandFather = &son;
        pGrandFather->getAge();
    }
    cout << endl;

    {
        Father father;
        GrandFather* pGrandFather = &father;
        pGrandFather->getAge();
    }



    return 0;
}
