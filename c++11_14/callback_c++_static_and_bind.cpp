#include <iostream>
#include <string>
#include <functional>
#include <memory>

// C++ 类成员回调函数， 静态函数，bind 两种方式   

class boss
{
private:
    /* data */
public:
    boss(/* args */);

    // bind成员函数回调
    void printfNotice(const std::string message){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << __LINE__ << std::endl;
        std::cout << message << std::endl;
    }
    // 静态成员函数回调
    static void printfNoticeStatic(const std::string message){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << __LINE__ << std::endl;
        std::cout << message << std::endl;
    }

    ~boss();
};

boss::boss(/* args */)
{
}

boss::~boss()
{
}

class noticer
{
private:
    /* data */
public:
    typedef std::function<void(const std::string&)> callbackFunc;
    noticer(std::shared_ptr<boss>recr);
    ~noticer();

    void addCallbackFunc(void(boss::*callback)(const std::string));
    void addCallbackStaticFunc(const callbackFunc &callback);

    void adviceMsg(const std::string &message);
    void adviceMsgStatic(const std::string &message);

private:
    callbackFunc noticeCallback;
    callbackFunc noticeCallback_2;
    std::shared_ptr<boss>receiver;
};

noticer::noticer(std::shared_ptr<boss>recr)
{
    receiver = recr;

}

void noticer::addCallbackFunc(void(boss::*callback)(const std::string)){
    noticeCallback = std::bind(callback, receiver, std::placeholders::_1);
    // noticeCallback = std::bind(&boss::printfNotice, receiver, std::placeholders::_1);
}

void noticer::addCallbackStaticFunc(const callbackFunc &callback){
    noticeCallback_2 = callback;
}

void noticer::adviceMsg(const std::string &message){
    noticeCallback(message);
}

void noticer::adviceMsgStatic(const std::string &message){
    noticeCallback_2(message);
}

noticer::~noticer()
{
}

int main(int argc, char const *argv[])
{
    std::shared_ptr<boss> receiver(new boss());
    noticer notice(receiver);

    notice.addCallbackFunc(&boss::printfNotice);
    notice.addCallbackStaticFunc(boss::printfNoticeStatic);

    notice.adviceMsg("hello world!");
    notice.adviceMsgStatic("hello world!");

    return 0;
}
