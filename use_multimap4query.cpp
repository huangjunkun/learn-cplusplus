#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include <exception>
#include <algorithm>
#include <map>

using namespace std;


/**
** 源文件： use_multimap4query.cpp
** 1. 使用 std::multimap 结构做记录。添加、删除、测试（验证）记录条目。
** Just test for these function here.
** 详见代码逻辑。
** 作者：junkun huang
** 日期：2012-05-05 /
*/

namespace query_lib
{
typedef std::multimap<int, std::pair<std::string, size_t> > request_record_type;
static request_record_type	_request_record;


/// 记录或标记函数功能请求 标记类型 pair<func_id, pair<func_param, record> >
bool add_request_record(const request_record_type::value_type& obj)
{
    /// Lock lock(...);// todo lock
    request_record_type::iterator lower_it = _request_record.lower_bound(obj.first);
    for (; lower_it != _request_record.end(); ++lower_it )
    {
        if (lower_it->first != obj.first)
            break;
        else if ( lower_it->second.first == obj.second.first)
        {
            ++lower_it->second.second;
            return false;
        }
    }
    _request_record.insert(lower_it, obj);
    return true;
}
/// 擦除函数功能请求的记录或标记 标记类型 pair<func_id, pair<func_param, record> >
void del_request_record(const request_record_type::value_type& obj)
{
    /// Lock lock(...);// todo lock
    request_record_type::iterator lower_it = _request_record.lower_bound(obj.first);
    request_record_type::iterator upper_it = _request_record.upper_bound(obj.first);

    for (request_record_type::iterator iter = lower_it; iter != upper_it; ++iter)
    {
        if (iter->first == obj.first && iter->second.first == obj.second.first)
        {
            if (0 != iter->second.second)
            {
                --(iter->second.second);
            }
            else
                assert(false);
        }

    }
}
bool test_request_record(const request_record_type::value_type& obj)
{
    /// Lock lock(...);// todo lock
    request_record_type::iterator lower_it = _request_record.lower_bound(obj.first);
    request_record_type::iterator upper_it = lower_it;
    for (; upper_it != _request_record.end();
        ++upper_it )
    {
        if (upper_it->first != obj.first)
            break;
        else if ( upper_it->second.first == obj.second.first &&
            obj.second.second != 0)
            return true;
    }
    return false;
}

} /// namespace query_lib

int main()
{
    {
    using namespace query_lib;
    /// test and confirm map::lower_bound & map::upper_bound./
    multimap<int, int> mapNum;
    mapNum.insert(make_pair(1, 1));
    mapNum.insert(make_pair(2, 3));
    mapNum.insert(make_pair(2, 2));
    mapNum.insert(make_pair(2, 4));
    mapNum.insert(make_pair(3, 5));
//    mapNum[2] = 2;
//    mapNum[2] = 3;
//    mapNum[2] = 4;
//    mapNum[3] = 5;
    multimap<int, int>::iterator lower_it = mapNum.lower_bound(2);
    cout << " " << lower_it->first << ", " << lower_it->second << "\n";
    multimap<int, int>::iterator upper_it = mapNum.upper_bound(2);
    cout << " " << upper_it->first << ", " << upper_it->second << "\n";

    /// test and query_lib's function./
    bool add_ret = add_request_record(request_record_type::value_type(1, make_pair("123", 1)));
    cout << " add_ret:" << add_ret << "\n";
    bool test_ret = test_request_record(request_record_type::value_type(1, make_pair("123", 1)));
    cout << " test_ret:" << test_ret << "\n";
    test_ret = test_request_record(request_record_type::value_type(1, make_pair("124", 1)));
    cout << " test_ret:" << test_ret << "\n";

    del_request_record(request_record_type::value_type(1, make_pair("123", 1)));
    test_ret = test_request_record(request_record_type::value_type(1, make_pair("123", 1)));
    cout << " test_ret:" << test_ret << "\n";

    }

    /*********/
    //assert (!" assert false here.");
    cout << " Hello world!" << endl;
    return 0;
}
