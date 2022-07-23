#include <map>
#include <memory>
#include <mutex>
#include <functional>
#include <assert.h>
#include <iostream>

class Book
{
    public:
        Book(const std::string &key){
            key_ = key;
        };
        ~Book(){};
        const std::string& key()
        {
            return key_;
        }
    private:
        std::string key_;
};

class BookFactory :public std::enable_shared_from_this<BookFactory>
{
    public:
        std::shared_ptr<Book> get(const std::string &key)
        {
            std::shared_ptr<Book> pBook;
            std::lock_guard<std::mutex>locker(mutex_);
            std::weak_ptr<Book>& wkBook = books_[key];
            pBook = wkBook.lock();
            if(!pBook)
            {
                pBook.reset(new Book(key), 
                    std::bind(&BookFactory::weakDeleteCallback,
                    std::weak_ptr<BookFactory>(shared_from_this())
                    , std::placeholders::_1));
                wkBook = pBook;
            }
            return pBook;
        }

    private:
        /*弱引用不会提升工厂的引用次数*/
        static void weakDeleteCallback(const std::weak_ptr<BookFactory>& wkFactory, Book *book)
        {
            std::shared_ptr<BookFactory> factory(wkFactory.lock());
            // 若工厂已消亡，则不调用其成员函数。
            if(factory)
            {
                factory->removeBook(book);
                std::cout << "weak callback" << std::endl;
            }
            delete book;
        }

        void removeBook(Book *book)
        {
            std::lock_guard<std::mutex> locker(mutex_);
            books_.erase(book->key());
        }
    private:
        mutable std::mutex mutex_;
        std::map<std::string, std::weak_ptr<Book>> books_;
};

void testLongLifeFactory()
{
    std::shared_ptr<BookFactory> factory(new BookFactory);
    {
        std::shared_ptr<Book> book;
        book = factory->get("demo book");
        std::shared_ptr<Book> book2 = factory->get("demo book");
        assert(book == book2);
    }
}

void testShortLifeFactory()
{
    std::shared_ptr<Book> book;
    {
        std::shared_ptr<BookFactory> factory(new BookFactory);
        book = factory->get("demo book");
        std::shared_ptr<Book> book2 = factory->get("demo book");
        assert(book == book2);
    }
}


int main(int argc, char const *argv[])
{
    testLongLifeFactory();
    testShortLifeFactory();
    return 0;
}
