

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <stdexcept>

using namespace std;

namespace test_namespace
{

class exception1 : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "an exception1.";
    }
};

class exception2 : public exception1
{
public:
    virtual const char* what() const throw()
    {
        return "an exception2.";
    }
};

const unsigned BUFFER_MAX_LEN = 64;

void read_file_e(FILE* f, char* buf, size_t buf_size)
{
    if (NULL == f)
        throw std::logic_error("f is NULL.");
    // ... read file ....
}

bool read_file_r(FILE* f, char* buf, size_t buf_size)
{
    if (NULL == f)
        return false;
    // ... read file ....
    return true;
}

class read_info_class
{
public:
    enum { ITEM_COUNT = 30, INFO_MAX_LEN = BUFFER_MAX_LEN };
public:
    read_info_class()
        : _file(0) {}

    read_info_class(FILE* file)
        : _file(file) {}
    ~read_info_class()
    {
        if (_file)
            fclose(_file);
    }

    void set_file (FILE* new_f)
    {
        if (_file)
            fclose(_file);
        _file = new_f;
    }
    void read_info_for_item1_e()
    {
        //assert (_file);
        string info;
        info.resize(INFO_MAX_LEN);
        read_file_e(_file, const_cast<char*>(info.c_str()), info.size());
        _info_items.push_back(info);
        read_file_e(_file, const_cast<char*>(info.c_str()), info.size());
        _info_items.push_back(info);
        // ... if read more items than 30...
    }

    void read_info_for_item2_e()
    {
        /* ... */
    }
    void read_info_for_item3_e()
    {
        /* ... */
    }
    void read_info_for_item4_e()
    {
        /* ... */
    }
    void read_info_for_item5_e()
    {
        /* ... */
    }
    // ... more ...

    bool read_info_for_item1_r()
    {
        //assert (_file);
        string info;
        info.resize(INFO_MAX_LEN);
        if (!read_file_r(_file, const_cast<char*>(info.c_str()), info.size()))
            return false;
        _info_items.push_back(info);
        if (!read_file_r(_file, const_cast<char*>(info.c_str()), info.size()))
            return false;
        _info_items.push_back(info);
        // ... if read more items than 30...

        return true;
    }

    bool read_info_for_item2_r()
    {
        /* ... */  return true;
    }
    bool read_info_for_item3_r()
    {
        /* ... */  return true;
    }
    bool read_info_for_item4_r()
    {
        /* ... */  return true;
    }
    bool read_info_for_item5_r()
    {
        /* ... */  return true;
    }
    // ... more ...

private:
    FILE* _file;
    vector<string> _info_items;
    // more other var...
};

void do_read_func_e()
{
    // do something ...
    FILE* file = NULL;
    // open file and ...
    vector<char> buf(BUFFER_MAX_LEN);
    read_file_e(file, &buf[0], buf.size());
    // handle buf's data ...
    read_file_e(file, &buf[0], buf.size());
    // more ...
    read_info_class read_info;
    // initialize read_info and ...
    read_info.read_info_for_item1_e();
    read_info.read_info_for_item2_e();
    read_info.read_info_for_item3_e();
    read_info.read_info_for_item4_e();
    read_info.read_info_for_item5_e();
    // more read_info_for_item5_e ...
    return;
}

bool do_read_func_r()
{
    // do something ...
    FILE* file = NULL;
    // open file and ...
    vector<char> buf(BUFFER_MAX_LEN);
    if (!read_file_r(file, &buf[0], buf.size()))
        return false;
    // handle buf's data ...
    if (!read_file_r(file, &buf[0], buf.size()))
        return false;
    // more ...
    read_info_class read_info;
    // initialize read_info and ...
    if (!read_info.read_info_for_item1_r() ||
            !read_info.read_info_for_item2_r() ||
            !read_info.read_info_for_item3_r() ||
            !read_info.read_info_for_item4_r() ||
            !read_info.read_info_for_item5_r() ) /// || more read_info_for_item*_r ...
        return false;
    // ...
    return true;
}
void test_read_func_e()
{
    // ...
    try
    {
        do_read_func_e();
    }
    catch (std::exception& e)
    {
        std::cerr << " catch error:" << e.what() << endl;
    }
    // ... more ...
}

void test_read_func_r()
{
    if (!do_read_func_r())
    {
        std::cerr << " occur error from do_read_func_r." << endl;
    }
}
} /// namespace test_namespace

void test_exception_list()
{
    using namespace test_namespace;
    /// 说明：catch 异常列表顺序影响最后真正抓取异常情况，即处理异常的catch分支。
    /// 建议：在异常catch列表，异常子类（派生类）的处理需置于其异常基类处理之前！
    /// 针对违法该规则，异常基类处理置于异常子类之前，有些编译器给予友情提示，如：
    //    warning: exception of type 'derived_class' will be caught|
    //    warning:    by earlier handler for 'base_clase'|

    /// 两个例子说明如下：
    /// 1-1.
    try
    {
        std::cout << " throw a exception2.\n";
        throw exception2();
    }
    catch (const exception1& e)
    {
        std::cout << " catch (const exception1& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }
    catch (const exception2& e)
    {
        std::cout << " catch (const exception2& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }

    /// 1-2.
    try
    {
        std::cout << " throw a exception2.\n";
        throw exception2();
    }
    catch (const exception2& e)
    {
        std::cout << " catch (const exception2& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }
    catch (const exception1& e)
    {
        std::cout << " catch (const exception1& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }
    /// ---
    /// 2-1.
    try
    {
        std::cout << " throw a logic_error.\n";
        throw std::logic_error("a logic_error");
    }
    catch (const std::logic_error& e)
    {
        std::cout << " catch (const logic_error& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << " catch (const exception& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }

    /// 2-2.
    try
    {
        std::cout << " throw a logic_error.\n";
        throw std::logic_error("a logic_error");
    }
    catch (const std::exception& e)
    {
        std::cout << " catch (const exception& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }
    catch (const std::logic_error& e)
    {
        std::cout << " catch (const logic_error& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }
/// Output：
// throw a exception2.
// catch (const exception1& e).
// catch an exception2.
// throw a exception2.
// catch (const exception2& e).
// catch an exception2.
// throw a logic_error.
// catch (const logic_error& e).
// catch a logic_error
// throw a logic_error.
// catch (const exception& e).
// catch a logic_error
}

int main()
{
    {
    using namespace test_namespace;
    test_read_func_e();
    test_read_func_r();
    test_exception_list();
    }

    cout << " Hello world!" << endl;
    return 0;
}

/**
//稍微总结一下，try-throw-catch结构异常处理机制，优势的地方：
// 1. 便于集中处理不同的异常情况，尤其针对不同（多）逻辑层次的异常处理情况，但最好不要跨模块处理异常。
     // 针对不同（多）逻辑层次的异常处理，若不使用异常处理机制，则需要在错误（异常）出现地方地方一层层返回错误情况，直到得到处理，编写代码时负担累赘比较大。

// 2. 针对异常处理情况，其可扩展性比较好。
     // 如增加或减少一种异常的处理情况，涉及代码逻辑的修改比较小，只要取消最初的throw和catch处理对应情况。

// 3. 当发现错误情况，throw可立即中止该下面逻辑的执行，直至找到对应的catch情况，否则程序崩溃。
     // 既是优点也是缺点。

// 4. 免去手动编写很多的if-return逻辑，否则严重影响代码逻辑的清晰与美观，尤其对于那些具有代码洁癖的程序员。

// 5. 建议：在不影响程序运行性能的情况下，可考虑使用异常处理，尤其程序存在复杂的错误（异常）处理情况的。
     // 也就是说，复杂的错误处理逻辑，不是程序主要逻辑，即使使用了C++异常处理也不影响程序的整体性能。
// ***/
