#ifndef __C_SINGLE_FILE_H
#define __C_SINGLE_FILE_H


#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tchar.h>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cassert>

/**
** 文件： c_singe_file.h，c_singe_file_test.cpp
**
** 函数： trim_tstring
** 功能： 裁剪字符串，针对字符串首尾裁剪空格与制表符。
** 类型： c_single_file
** 功能： 封装CRT基本的文件读写操作。方便使用。
** 作者：junkun huang  e-mail：huangjunkun@gmail.com
** 日期：2011-07-21 /
*/
//using namespace std;
namespace junkun
{
/**
** 说明： 一些CRT的宏定义，配置用于多语言_UNICODE程序版本。
*/
#ifdef _UNICODE

#define strlen_t	wcslen
#define fgets_t		fgetws
#define fputs_t		fputws
#define fscanf_t	fwscanf
#define sscanf_t	swscanf
#define printf_t	wprintf
#define fprintf_t	fwprintf
#define sprintf_t	wsprintf
#define tcout		std::wcout
#define tcerr		std::wcerr
#define tcin		std::wcin
#define string_t	std::wstring
#define char_t		wchar_t
#else

#define strlen_t	strlen
#define fgets_t		fgets
#define fputs_t		fputs
#define printf_t	printf
#define fscanf_t	fscanf
#define sscanf_t	sscanf
#define fprintf_t	fprintf
#define sprintf_t	sprintf
#define tcout		std::cout
#define tcerr		std::cerr
#define tcin		std::cin
#define string_t	std::string
#define char_t		char

#endif

#ifndef isdigit_t
#define isdigit_t(ch) (ch >= _T('0') && ch <= _T('9'))
#endif
#ifndef isalpha_t
#define isalpha_t(ch) (((ch) >= _T('a') && (ch) <= _T('z')) || ((ch) >= _T('A') && (ch) <= _T('Z')))
#endif
#ifndef islower_t
#define islower_t(ch) ((ch) >= _T('a') && (ch) <= _T('z'))
#endif
#ifndef isupper_t
#define isupper_t(ch) ((ch) >= _T('A') && (ch) <= _T('Z'))
#endif

const unsigned CHAR_LOWER_UPPER_CHANGE_FACTOR = _T('z') - _T('a');
#ifndef tolower_t
#define tolower_t(ch) (isupper_t(ch) ? ((ch) + CHAR_LOWER_UPPER_CHANGE_FACTOR) : (ch))
//#define tolower_t(ch) isalpha_t(ch) ? (islower_t(ch) ? (ch) : (ch + CHAR_LOWER_UPPER_CHANGE_FACTOR)) : (ch)
#endif
#ifndef toupper_t
#define toupper_t(ch) (islower_t(ch) ? ((ch) - CHAR_LOWER_UPPER_CHANGE_FACTOR) : (ch))
//#define toupper_t(ch) isalpha_t(ch) ? (isupper_t(ch) ? (ch) : (ch + CHAR_LOWER_UPPER_CHANGE_FACTOR)) : (ch)
#endif
	//
	//////////////////////////////////////////////////////////////////////////
//#define LOG
#ifdef _DEBUG //LOG//
#ifndef __COUT_FOR_LOG_
#define __COUT_FOR_LOG_

// #define cout_trace tcout << __FUNCTION__ << " __cout4log trace:"
// #define cout_debug tcout << __FUNCTION__ << " __cout4log debug:"
// #define cout_info  tcout  << __FUNCTION__<< " __cout4log info:"

#define cout_trace(msg) do { tcout << __FUNCTION__ << " __cout4log trace:" << msg << "\n"; } while(0)
#define cout_debug(msg) do { tcout << __FUNCTION__ << " __cout4log debug:" << msg << "\n"; } while(0)
#define cout_info(msg)  do { tcout << __FUNCTION__ << " __cout4log info:" << msg << "\n"; } while(0)

#define assert_false_notify(msg) do { const bool msg(false); assert(msg); } while(0)

#endif // end __COUT_FOR_LOG_
#else

#ifndef __COUT_FOR_LOG_
#define __COUT_FOR_LOG_

#define cout_trace(msg) 0
#define cout_debug(msg) 0
#define cout_info(msg)  0

#define assert_false_notify(msg) 0

#endif // end __COUT_FOR_LOG_
#endif // end _DEBUG

#define SET_ASYNFRAME_THREAD_ID() do { g_asyn_frame_thread_id = GetCurrentThreadId(); } while(0)
#define IF_NOT_ASYNFRAME_THREAD_RETURN(ret) do { if ( g_asyn_frame_thread_id && g_asyn_frame_thread_id != GetCurrentThreadId() ) { assert(("该方法只能在下载库线程调用",NULL)); return ret; } } while(0)
#define IF_IN_ASYNFRAME_THREAD_RETURN(ret) do { if ( g_asyn_frame_thread_id && g_asyn_frame_thread_id == GetCurrentThreadId() ) { assert(("该方法不能在下载库线程调用",NULL)); return ret; } } while(0)

#define IF_POINTER_INVALID_RETURN(ptr,ret) do { assert(ptr); if ( !(ptr) ) return ret; } while(0)
#define IF_VAR_EQUAL_RETURN(var,value,ret) do { if ( (var)==(value) ) return ret; } while(0)
#define IF_HRESULT_ERROR_RETURN(lr) do { assert(SUCCEEDED(lr)); if ( FAILED(lr) ) return lr; } while(0)
#define IF_EMPTY_STRING_RETURN(S,hr) do { if (S.len==0||S.str==NULL) return hr; } while(0)

#ifndef SAFE_DELETE
#define SAFE_DELETE(a) do { if(NULL != (a)) {delete (a);(a)=NULL;} } while(0)
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) {if(p) {delete [] (p); (p)=NULL;} }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(a) do { if(NULL!=(a)) { (a)->Release(); (a)=NULL;} } while(0)
#endif

#ifndef FINAL_RELEASE
#define FINAL_RELEASE(a) do { ULONG ref = (a)->Release(); assert(("某 COM 指针 Release 之后引用计数不为0!",ref==0)); (a)=NULL; } while(0)
#endif

#ifndef SAFE_UNINIT_RELEASE
#define SAFE_UNINIT_RELEASE(a) do { if(NULL!=(a)) { (a)->Uninit(); (a)->Release(); (a)=NULL;} } while(0)
#endif

#ifndef SAFE_CLOSE_HANDLE
#define SAFE_CLOSE_HANDLE(a) do { if(NULL!=(a)&&INVALID_HANDLE_VALUE!=(a)){CloseHandle(a);(a)=NULL;} } while(0)
#endif


}// namespace junkun

namespace junkun
{
/**
** 函数： trim_tstring
** 功能： 裁剪字符串，针对字符串首尾裁剪空格与制表符。
*/

#define SPACE_TCHAR		_T(' ')
#define TAB_TCHAR		_T('\t')
#define RETURN_TCHAR	_T('\n')
	using namespace std;

	template <typename _TChar>
	basic_string<_TChar>  trim_tstring(const basic_string<_TChar>& srcString)
	{//
		if (srcString.empty())
			return basic_string<_TChar>();

		typename basic_string<_TChar>::const_iterator citer = srcString.begin();
		for (; citer != srcString.end(); ++citer)
			if (!(*citer == _TChar(SPACE_TCHAR) || *citer == _TChar(TAB_TCHAR)))
				break;

		typename basic_string<_TChar>::const_reverse_iterator criter = srcString.rbegin();
		for (; criter != srcString.rend(); ++criter)
			if (!(*citer == _TChar(SPACE_TCHAR) || *citer == _TChar(TAB_TCHAR)))
				break;
		typename basic_string<_TChar>::const_iterator end_pos(criter.base());

		return basic_string<_TChar>(citer, end_pos);
	}

/**
** 类型： c_single_file
** 功能： 封装CRT基本的文件读写操作。方便使用。
*/
	class c_single_file
	{
	public:
		//		using namespace std;
	public:
		c_single_file() : _file(0) {}
		c_single_file(const std::string& filename, const std::string& open_type="wb+")
			: _file(0)
		{
			if ( !open(filename, open_type))
			{
				assert_false_notify (c_single_file_open_return_false);
				//throw std::logic_error("c_single_file_open_return_false");
			}
		}
		c_single_file(const std::wstring& filename, const std::wstring& open_type=L"wb+")
			: _file(0)
		{
			if ( !open(filename, open_type))
			{
				assert_false_notify (c_single_file_open_return_false);
				//throw std::logic_error("c_single_file_open_return_false");
			}
		}

		~c_single_file()
		{
			close();
		}
		// member function
		bool open(const std::string& filename, const std::string& open_type="rb+")
		{
			_file = fopen(filename.c_str(), open_type.c_str());
			return (NULL != _file) ;
		}

		bool open(const std::wstring& filename, const std::wstring& open_type=L"rb+")
		{
			_file = _wfopen(filename.c_str(), open_type.c_str());
			return (NULL != _file) ;
		}

		size_t write(void* pData,size_t len)
		{
			assert(_file);
			return fwrite(pData, 1, len, _file);
		}

		size_t read(void* pData,size_t len)
		{
			assert(_file);
			return fread(pData, 1, len, _file);
		}

		bool close()
		{
			if (_file)
			{
				int res = fclose(_file);
				_file = NULL;
				return (0==res);
			}
			return false;
		}
		int flush()
		{
			assert (_file);
			return fflush(_file);
		}
		char* gets(char* c_str, unsigned len)
		{
			assert (_file);
			return fgets(c_str, len, _file);
		}
		wchar_t* gets(wchar_t* c_str, unsigned len)
		{
			assert (_file);
			return fgetws(c_str, len, _file);
		}
		int puts(char* c_str)
		{
			assert (_file);
			return fputs(c_str, _file);
		}
		int puts(wchar_t* c_str)
		{
			assert (_file);
			return fputws(c_str, _file);
		}

		int eof() { assert (_file); return feof(_file); }
		int error() { assert (_file); return ferror(_file); }
		bool is_opened() const { return NULL != _file; }
		FILE* file_ptr() { return _file; }

	private:
		FILE* _file;
	};//class c_single_file


}// namespace junkun

#endif

