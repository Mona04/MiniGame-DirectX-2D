#include "scriptstdwstring.h"
#include <assert.h> // assert()
#include <sstream>  // std::wstringstream
#include <string> // strstr()
#include <stdio.h>	// sprintf()
#include <stdlib.h> // strtod()
#ifndef __psp2__
	#include <locale.h> // setlocale()
#endif

using namespace std;

// This macro is used to avoid warnings about unused variables.
// Usually where the variables are only used in debug mode.
#define UNUSED_VAR(x) (void)(x)

#ifdef AS_CAN_USE_CPP11
// The wstring factory doesn't need to keep a specific order in the
// cache, so the unordered_map is faster than the ordinary map
#include <unordered_map>  // std::unordered_map
BEGIN_AS_NAMESPACE
typedef unordered_map<wstring, int> map_t;
END_AS_NAMESPACE
#else
#include <map>      // std::map
BEGIN_AS_NAMESPACE
typedef map<wstring, int> map_t;
END_AS_NAMESPACE
#endif

class CStdWStringFactory : public asIStringFactory
{
public:
	CStdWStringFactory() {}
	~CStdWStringFactory()
	{
		// The script engine must release each wstring 
		// constant that it has requested
		assert(wstringCache.size() == 0);
	}

	const void * GetStringConstant(const wchar_t *data, asUINT length)
	{
		wstring str(data, length);
		map_t::iterator it = wstringCache.find(str);
		if (it != wstringCache.end())
			it->second++;
		else
			it = wstringCache.insert(map_t::value_type(str, 1)).first;

		return reinterpret_cast<const void*>(&it->first);
	}

	int  ReleaseStringConstant(const void *str)
	{
		if (str == 0)
			return asERROR;

		map_t::iterator it = wstringCache.find(*reinterpret_cast<const wstring*>(str));
		if (it == wstringCache.end())
			return asERROR;

		it->second--;
		if (it->second == 0)
			wstringCache.erase(it);
		return asSUCCESS;
	}

	int  GetRawStringData(const void *str, wchar_t *data, asUINT *length) const
	{
		if (str == 0)
			return asERROR;

		if (length)
			*length = (asUINT)reinterpret_cast<const wstring*>(str)->length();

		if (data)
			memcpy(data, reinterpret_cast<const wstring*>(str)->c_str(), reinterpret_cast<const wstring*>(str)->length());

		return asSUCCESS;
	}

	// TODO: Make sure the access to the wstring cache is thread safe
	map_t wstringCache;
};

//static CStdWStringFactory wstringFactory;


static void Constructwstring(wstring *thisPointer)
{
	new(thisPointer) wstring();
}

static void CopyConstructwstring(const wstring &other, wstring *thisPointer)
{
	new(thisPointer) wstring(other);
}

static void Destructwstring(wstring *thisPointer)
{
	thisPointer->~wstring();
}

static wstring &AddAssignwstringTowstring(const wstring &str, wstring &dest)
{
	// We don't register the method directly because some compilers
	// and standard libraries inline the definition, resulting in the
	// linker being unable to find the declaration.
	// Example: CLang/LLVM with XCode 4.3 on OSX 10.7
	dest += str;
	return dest;
}

// bool wstring::isEmpty()
// bool wstring::empty() // if AS_USE_STLNAMES == 1
static bool wstringIsEmpty(const wstring &str)
{
	// We don't register the method directly because some compilers
	// and standard libraries inline the definition, resulting in the
	// linker being unable to find the declaration
	// Example: CLang/LLVM with XCode 4.3 on OSX 10.7
	return str.empty();
}

static wstring &AssignUInt64Towstring(asQWORD i, wstring &dest)
{
	wstringstream stream;
	stream << i;
	dest = stream.str();

	return dest;
}

static wstring &AddAssignUInt64Towstring(asQWORD i, wstring &dest)
{
	wstringstream stream;
	stream << i;
	dest += stream.str();
	return dest;
}

static wstring AddwstringUInt64(const wstring &str, asQWORD i)
{
	wstringstream stream;
	stream << i;
	return str + stream.str();
}

static wstring AddInt64wstring(asINT64 i, const wstring &str)
{
	wstringstream stream;
	stream << i;
	return stream.str() + str;
}

static wstring &AssignInt64Towstring(asINT64 i, wstring &dest)
{
	wstringstream stream;
	stream << i;
	dest = stream.str();
	return dest;
}

static wstring &AddAssignInt64Towstring(asINT64 i, wstring &dest)
{
	wstringstream stream;
	stream << i;
	dest += stream.str();
	return dest;
}

static wstring AddwstringInt64(const wstring &str, asINT64 i)
{
	wstringstream stream;
	stream << i;
	return str + stream.str();
}

static wstring AddUInt64wstring(asQWORD i, const wstring &str)
{
	wstringstream stream;
	stream << i;
	return stream.str() + str;
}

static wstring &AssignDoubleTowstring(double f, wstring &dest)
{
	wstringstream stream;
	stream << f;
	dest = stream.str();
	return dest;
}

static wstring &AddAssignDoubleTowstring(double f, wstring &dest)
{
	wstringstream stream;
	stream << f;
	dest += stream.str();
	return dest;
}

static wstring &AssignFloatTowstring(float f, wstring &dest)
{
	wstringstream stream;
	stream << f;
	dest = stream.str();
	return dest;
}

static wstring &AddAssignFloatTowstring(float f, wstring &dest)
{
	wstringstream stream;
	stream << f;
	dest += stream.str();
	return dest;
}

static wstring &AssignBoolTowstring(bool b, wstring &dest)
{
	wstringstream stream;
	stream << (b ? "true" : "false");
	dest = stream.str();
	return dest;
}

static wstring &AddAssignBoolTowstring(bool b, wstring &dest)
{
	wstringstream stream;
	stream << (b ? "true" : "false");
	dest += stream.str();
	return dest;
}

static wstring AddwstringDouble(const wstring &str, double f)
{
	wstringstream stream;
	stream << f;
	return str + stream.str();
}

static wstring AddDoublewstring(double f, const wstring &str)
{
	wstringstream stream;
	stream << f;
	return stream.str() + str;
}

static wstring AddwstringFloat(const wstring &str, float f)
{
	wstringstream stream;
	stream << f;
	return str + stream.str();
}

static wstring AddFloatwstring(float f, const wstring &str)
{
	wstringstream stream;
	stream << f;
	return stream.str() + str;
}

static wstring AddwstringBool(const wstring &str, bool b)
{
	wstringstream stream;
	stream << (b ? "true" : "false");
	return str + stream.str();
}

static wstring AddBoolwstring(bool b, const wstring &str)
{
	wstringstream stream;
	stream << (b ? "true" : "false");
	return stream.str() + str;
}

static wchar_t *wstringCharAt(unsigned int i, wstring &str)
{
	if( i >= str.size() )
	{
		// Set a script exception
		asIScriptContext *ctx = asGetActiveContext();
		ctx->SetException("Out of range");

		// Return a null pointer
		return 0;
	}

	return &str[i];
}

// AngelScript signature:
// int wstring::opCmp(const wstring &in) const
static int wstringCmp(const wstring &a, const wstring &b)
{
	int cmp = 0;
	if( a < b ) cmp = -1;
	else if( a > b ) cmp = 1;
	return cmp;
}

// This function returns the index of the first position where the subwstring
// exists in the input wstring. If the subwstring doesn't exist in the input
// wstring -1 is returned.
//
// AngelScript signature:
// int wstring::findFirst(const wstring &in sub, uint start = 0) const
static int wstringFindFirst(const wstring &sub, asUINT start, const wstring &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	return (int)str.find(sub, (size_t)(start < 0 ? wstring::npos : start));
}

// This function returns the index of the first position where the one of the bytes in subwstring
// exists in the input wstring. If the characters in the subwstring doesn't exist in the input
// wstring -1 is returned.
//
// AngelScript signature:
// int wstring::findFirstOf(const wstring &in sub, uint start = 0) const
static int wstringFindFirstOf(const wstring &sub, asUINT start, const wstring &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	return (int)str.find_first_of(sub, (size_t)(start < 0 ? wstring::npos : start));
}

// This function returns the index of the last position where the one of the bytes in subwstring
// exists in the input wstring. If the characters in the subwstring doesn't exist in the input
// wstring -1 is returned.
//
// AngelScript signature:
// int wstring::findLastOf(const wstring &in sub, uint start = -1) const
static int wstringFindLastOf(const wstring &sub, asUINT start, const wstring &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	return (int)str.find_last_of(sub, (size_t)(start < 0 ? wstring::npos : start));
}

// This function returns the index of the first position where a byte other than those in subwstring
// exists in the input wstring. If none is found -1 is returned.
//
// AngelScript signature:
// int wstring::findFirstNotOf(const wstring &in sub, uint start = 0) const
static int wstringFindFirstNotOf(const wstring &sub, asUINT start, const wstring &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	return (int)str.find_first_not_of(sub, (size_t)(start < 0 ? wstring::npos : start));
}

// This function returns the index of the last position where a byte other than those in subwstring
// exists in the input wstring. If none is found -1 is returned.
//
// AngelScript signature:
// int wstring::findLastNotOf(const wstring &in sub, uint start = -1) const
static int wstringFindLastNotOf(const wstring &sub, asUINT start, const wstring &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	return (int)str.find_last_of(sub, (size_t)(start < 0 ? wstring::npos : start));
}

// This function returns the index of the last position where the subwstring
// exists in the input wstring. If the subwstring doesn't exist in the input
// wstring -1 is returned.
//
// AngelScript signature:
// int wstring::findLast(const wstring &in sub, int start = -1) const
static int wstringFindLast(const wstring &sub, int start, const wstring &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	return (int)str.rfind(sub, (size_t)(start < 0 ? wstring::npos : start));
}

// AngelScript signature:
// void wstring::insert(uint pos, const wstring &in other)
static void wstringInsert(unsigned int pos, const wstring &other, wstring &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	str.insert(pos, other);
}

// AngelScript signature:
// void wstring::erase(uint pos, int count = -1)
static void wstringErase(unsigned int pos, int count, wstring &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	str.erase(pos, (size_t)(count < 0 ? wstring::npos : count));
}


// AngelScript signature:
// uint wstring::length() const
static asUINT wstringLength(const wstring &str)
{
	// We don't register the method directly because the return type changes between 32bit and 64bit platforms
	return (asUINT)str.length();
}


// AngelScript signature:
// void wstring::resize(uint l)
static void wstringResize(asUINT l, wstring &str)
{
	// We don't register the method directly because the argument types change between 32bit and 64bit platforms
	str.resize(l);
}

// AngelScript signature:
// wstring formatInt(int64 val, const wstring &in options, uint width)
static wstring formatInt(asINT64 value, const wstring &options, asUINT width)
{
	bool leftJustify = options.find(L"l") != wstring::npos;
	bool padWithZero = options.find(L"0") != wstring::npos;
	bool alwaysSign  = options.find(L"+") != wstring::npos;
	bool spaceOnSign = options.find(L" ") != wstring::npos;
	bool hexSmall    = options.find(L"h") != wstring::npos;
	bool hexLarge    = options.find(L"H") != wstring::npos;

	wstring fmt = L"%";
	if( leftJustify ) fmt += L"-";
	if( alwaysSign ) fmt += L"+";
	if( spaceOnSign ) fmt += L" ";
	if( padWithZero ) fmt += L"0";

#ifdef _WIN32
	fmt += L"*I64";
#else
#ifdef _LP64
	fmt += L"*l";
#else
	fmt += L"*ll";
#endif
#endif

	if( hexSmall ) fmt += L"x";
	else if( hexLarge ) fmt += L"X";
	else fmt += L"d";

	wstring buf;
	buf.resize(width+30);
#if _MSC_VER >= 1400 && !defined(__S3E__)
	// MSVC 8.0 / 2005 or newer
	swprintf_s(&buf[0], buf.size(), fmt.c_str(), width, value);
#else
	sprintf(&buf[0], fmt.c_str(), width, value);
#endif
	buf.resize(wcslen(&buf[0]));

	return buf;
}

// AngelScript signature:
// wstring formatUInt(uint64 val, const wstring &in options, uint width)
static wstring formatUInt(asQWORD value, const wstring &options, asUINT width)
{
	bool leftJustify = options.find(L"l") != wstring::npos;
	bool padWithZero = options.find(L"0") != wstring::npos;
	bool alwaysSign  = options.find(L"+") != wstring::npos;
	bool spaceOnSign = options.find(L" ") != wstring::npos;
	bool hexSmall    = options.find(L"h") != wstring::npos;
	bool hexLarge    = options.find(L"H") != wstring::npos;

	wstring fmt = L"%";
	if( leftJustify ) fmt += L"-";
	if( alwaysSign ) fmt += L"+";
	if( spaceOnSign ) fmt += L" ";
	if( padWithZero ) fmt += L"0";

#ifdef _WIN32
	fmt += L"*I64";
#else
#ifdef _LP64
	fmt += L"*l";
#else
	fmt += L"*ll";
#endif
#endif

	if( hexSmall ) fmt += L"x";
	else if( hexLarge ) fmt += L"X";
	else fmt += L"u";

	wstring buf;
	buf.resize(width+30);
#if _MSC_VER >= 1400 && !defined(__S3E__)
	// MSVC 8.0 / 2005 or newer
	swprintf_s(&buf[0], buf.size(), fmt.c_str(), width, value);
#else
	sprintf(&buf[0], fmt.c_str(), width, value);
#endif
	buf.resize(wcslen(&buf[0]));

	return buf;
}

// AngelScript signature:
// wstring formatFloat(double val, const wstring &in options, uint width, uint precision)
static wstring formatFloat(double value, const wstring &options, asUINT width, asUINT precision)
{
	bool leftJustify = options.find(L"l") != wstring::npos;
	bool padWithZero = options.find(L"0") != wstring::npos;
	bool alwaysSign  = options.find(L"+") != wstring::npos;
	bool spaceOnSign = options.find(L" ") != wstring::npos;
	bool expSmall    = options.find(L"e") != wstring::npos;
	bool expLarge    = options.find(L"E") != wstring::npos;

	wstring fmt = L"%";
	if( leftJustify ) fmt += L"-";
	if( alwaysSign ) fmt += L"+";
	if( spaceOnSign ) fmt += L" ";
	if( padWithZero ) fmt += L"0";

	fmt += L"*.*";

	if( expSmall ) fmt += L"e";
	else if( expLarge ) fmt += L"E";
	else fmt += L"f";

	wstring buf;
	buf.resize(width+precision+50);
#if _MSC_VER >= 1400 && !defined(__S3E__)
	// MSVC 8.0 / 2005 or newer
	swprintf_s(&buf[0], buf.size(), fmt.c_str(), width, precision, value);
#else
	sprintf(&buf[0], fmt.c_str(), width, precision, value);
#endif
	buf.resize(wcslen(&buf[0]));

	return buf;
}

// AngelScript signature:
// int64 parseInt(const wstring &in val, uint base = 10, uint &out byteCount = 0)
static asINT64 parseInt(const wstring &val, asUINT base, asUINT *byteCount)
{
	// Only accept base 10 and 16
	if( base != 10 && base != 16 )
	{
		if( byteCount ) *byteCount = 0;
		return 0;
	}

	const wchar_t *end = &val[0];

	// Determine the sign
	bool sign = false;
	if( *end == L'-' )
	{
		sign = true;
		end++;
	}
	else if( *end == L'+' )
		end++;

	asINT64 res = 0;
	if( base == 10 )
	{
		while( *end >= L'0' && *end <= L'9' )
		{
			res *= 10;
			res += *end++ - L'0';
		}
	}
	else if( base == 16 )
	{
		while( (*end >= L'0' && *end <= L'9') ||
		       (*end >= L'a' && *end <= L'f') ||
		       (*end >= L'A' && *end <= L'F') )
		{
			res *= 16;
			if( *end >= L'0' && *end <= L'9' )
				res += *end++ - L'0';
			else if( *end >= L'a' && *end <= L'f' )
				res += *end++ - L'a' + 10;
			else if( *end >= L'A' && *end <= L'F' )
				res += *end++ - L'A' + 10;
		}
	}

	if( byteCount )
		*byteCount = asUINT(size_t(end - val.c_str()));

	if( sign )
		res = -res;

	return res;
}

// AngelScript signature:
// uint64 parseUInt(const wstring &in val, uint base = 10, uint &out byteCount = 0)
static asQWORD parseUInt(const wstring &val, asUINT base, asUINT *byteCount)
{
	// Only accept base 10 and 16
	if (base != 10 && base != 16)
	{
		if (byteCount) *byteCount = 0;
		return 0;
	}

	const wchar_t *end = &val[0];

	asQWORD res = 0;
	if (base == 10)
	{
		while (*end >= L'0' && *end <= L'9')
		{
			res *= 10;
			res += *end++ - L'0';
		}
	}
	else if (base == 16)
	{
		while ((*end >= L'0' && *end <= L'9') ||
			(*end >= L'a' && *end <= L'f') ||
			(*end >= L'A' && *end <= L'F'))
		{
			res *= 16;
			if (*end >= L'0' && *end <= L'9')
				res += *end++ - L'0';
			else if (*end >= L'a' && *end <= L'f')
				res += *end++ - L'a' + 10;
			else if (*end >= L'A' && *end <= L'F')
				res += *end++ - L'A' + 10;
		}
	}

	if (byteCount)
		*byteCount = asUINT(size_t(end - val.c_str()));

	return res;
}

// AngelScript signature:
// double parseFloat(const wstring &in val, uint &out byteCount = 0)
double parseFloat(const wstring &val, asUINT *byteCount)
{
	wchar_t *end;

	// WinCE doesn't have setlocale. Some quick testing on my current platform
	// still manages to parse the numbers such as "3.14" even if the decimal for the
	// locale is ",".
#if !defined(_WIN32_WCE) && !defined(ANDROID) && !defined(__psp2__)
	// Set the locale to C so that we are guaranteed to parse the float value correctly
	char *orig = setlocale(LC_NUMERIC, 0);
	setlocale(LC_NUMERIC, "C");
#endif

	double res = wcstod(val.c_str(), &end);

#if !defined(_WIN32_WCE) && !defined(ANDROID) && !defined(__psp2__)
	// Restore the locale
	setlocale(LC_NUMERIC, orig);
#endif

	if( byteCount )
		*byteCount = asUINT(size_t(end - val.c_str()));

	return res;
}

// This function returns a wstring containing the subwstring of the input wstring
// determined by the starting index and count of characters.
//
// AngelScript signature:
// wstring wstring::substr(uint start = 0, int count = -1) const
static wstring wstringSubwstring(asUINT start, int count, const wstring &str)
{
	// Check for out-of-bounds
	wstring ret;
	if( start < str.length() && count != 0 )
		ret = str.substr(start, (size_t)(count < 0 ? wstring::npos : count));

	return ret;
}

// wstring equality comparison.
// Returns true iff lhs is equal to rhs.
//
// For some reason gcc 4.7 has difficulties resolving the
// asFUNCTIONPR(operator==, (const wstring &, const wstring &)
// makro, so this wrapper was introduced as work around.
static bool wstringEquals(const std::wstring& lhs, const std::wstring& rhs)
{
	return lhs == rhs;
}

void RegisterStdWString_Native(asIScriptEngine *engine)
{
	int r = 0;
	UNUSED_VAR(r);

	// Register the wstring type
#if AS_CAN_USE_CPP11
	// With C++11 it is possible to use asGetTypeTraits to automatically determine the correct flags to use
	r = engine->RegisterObjectType("wstring", sizeof(wstring), asOBJ_VALUE | asGetTypeTraits<wstring>()); assert( r >= 0 );
#else
	r = engine->RegisterObjectType("wstring", sizeof(wstring), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); assert( r >= 0 );
#endif

	//r = engine->RegisterWStringFactory("wstring", &wstringFactory);

	// Register the object operator overloads
	r = engine->RegisterObjectBehaviour("wstring", asBEHAVE_CONSTRUCT,  "void f()",                    asFUNCTION(Constructwstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("wstring", asBEHAVE_CONSTRUCT,  "void f(const wstring &in)",    asFUNCTION(CopyConstructwstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("wstring", asBEHAVE_DESTRUCT,   "void f()",                    asFUNCTION(Destructwstring),  asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring &opAssign(const wstring &in)", asMETHODPR(wstring, operator =, (const wstring&), wstring&), asCALL_THISCALL); assert( r >= 0 );
	// Need to use a wrapper on Mac OS X 10.7/XCode 4.3 and CLang/LLVM, otherwise the linker fails
	r = engine->RegisterObjectMethod("wstring", "wstring &opAddAssign(const wstring &in)", asFUNCTION(AddAssignwstringTowstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );
//	r = engine->RegisterObjectMethod("wstring", "wstring &opAddAssign(const wstring &in)", asMETHODPR(wstring, operator+=, (const wstring&), wstring&), asCALL_THISCALL); assert( r >= 0 );

	// Need to use a wrapper for operator== otherwise gcc 4.7 fails to compile
	r = engine->RegisterObjectMethod("wstring", "bool opEquals(const wstring &in) const", asFUNCTIONPR(wstringEquals, (const wstring &, const wstring &), bool), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "int opCmp(const wstring &in) const", asFUNCTION(wstringCmp), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd(const wstring &in) const", asFUNCTIONPR(operator +, (const wstring &, const wstring &), wstring), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

	// The wstring length can be accessed through methods or through virtual property
	r = engine->RegisterObjectMethod("wstring", "uint length() const", asFUNCTION(wstringLength), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "void resize(uint)", asFUNCTION(wstringResize), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "uint get_length() const", asFUNCTION(wstringLength), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "void set_length(uint)", asFUNCTION(wstringResize), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	// Need to use a wrapper on Mac OS X 10.7/XCode 4.3 and CLang/LLVM, otherwise the linker fails
//	r = engine->RegisterObjectMethod("wstring", "bool isEmpty() const", asMETHOD(wstring, empty), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "bool isEmpty() const", asFUNCTION(wstringIsEmpty), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	// Register the index operator, both as a mutator and as an inspector
	// Note that we don't register the operator[] directly, as it doesn't do bounds checking
	r = engine->RegisterObjectMethod("wstring", "uint8 &opIndex(uint)", asFUNCTION(wstringCharAt), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "const uint8 &opIndex(uint) const", asFUNCTION(wstringCharAt), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	// Automatic conversion from values
	r = engine->RegisterObjectMethod("wstring", "wstring &opAssign(double)", asFUNCTION(AssignDoubleTowstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring &opAddAssign(double)", asFUNCTION(AddAssignDoubleTowstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd(double) const", asFUNCTION(AddwstringDouble), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd_r(double) const", asFUNCTION(AddDoublewstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectMethod("wstring", "wstring &opAssign(float)", asFUNCTION(AssignFloatTowstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring &opAddAssign(float)", asFUNCTION(AddAssignFloatTowstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd(float) const", asFUNCTION(AddwstringFloat), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd_r(float) const", asFUNCTION(AddFloatwstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectMethod("wstring", "wstring &opAssign(int64)", asFUNCTION(AssignInt64Towstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring &opAddAssign(int64)", asFUNCTION(AddAssignInt64Towstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd(int64) const", asFUNCTION(AddwstringInt64), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd_r(int64) const", asFUNCTION(AddInt64wstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectMethod("wstring", "wstring &opAssign(uint64)", asFUNCTION(AssignUInt64Towstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring &opAddAssign(uint64)", asFUNCTION(AddAssignUInt64Towstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd(uint64) const", asFUNCTION(AddwstringUInt64), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd_r(uint64) const", asFUNCTION(AddUInt64wstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectMethod("wstring", "wstring &opAssign(bool)", asFUNCTION(AssignBoolTowstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring &opAddAssign(bool)", asFUNCTION(AddAssignBoolTowstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd(bool) const", asFUNCTION(AddwstringBool), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd_r(bool) const", asFUNCTION(AddBoolwstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	// Utilities
	r = engine->RegisterObjectMethod("wstring", "wstring substr(uint start = 0, int count = -1) const", asFUNCTION(wstringSubwstring), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "int findFirst(const wstring &in, uint start = 0) const", asFUNCTION(wstringFindFirst), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "int findFirstOf(const wstring &in, uint start = 0) const", asFUNCTION(wstringFindFirstOf), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("wstring", "int findFirstNotOf(const wstring &in, uint start = 0) const", asFUNCTION(wstringFindFirstNotOf), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("wstring", "int findLast(const wstring &in, int start = -1) const", asFUNCTION(wstringFindLast), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "int findLastOf(const wstring &in, int start = -1) const", asFUNCTION(wstringFindLastOf), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("wstring", "int findLastNotOf(const wstring &in, int start = -1) const", asFUNCTION(wstringFindLastNotOf), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("wstring", "void insert(uint pos, const wstring &in other)", asFUNCTION(wstringInsert), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("wstring", "void erase(uint pos, int count = -1)", asFUNCTION(wstringErase), asCALL_CDECL_OBJLAST); assert(r >= 0);


	r = engine->RegisterGlobalFunction("wstring formatInt(int64 val, const wstring &in options = \"\", uint width = 0)", asFUNCTION(formatInt), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("wstring formatUInt(uint64 val, const wstring &in options = \"\", uint width = 0)", asFUNCTION(formatUInt), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("wstring formatFloat(double val, const wstring &in options = \"\", uint width = 0, uint precision = 0)", asFUNCTION(formatFloat), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("int64 parseInt(const wstring &in, uint base = 10, uint &out byteCount = 0)", asFUNCTION(parseInt), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("uint64 parseUInt(const wstring &in, uint base = 10, uint &out byteCount = 0)", asFUNCTION(parseUInt), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("double parseFloat(const wstring &in, uint &out byteCount = 0)", asFUNCTION(parseFloat), asCALL_CDECL); assert(r >= 0);

#if AS_USE_STLNAMES == 1
	// Same as length
	r = engine->RegisterObjectMethod("wstring", "uint size() const", asFUNCTION(wstringLength), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	// Same as isEmpty
	r = engine->RegisterObjectMethod("wstring", "bool empty() const", asFUNCTION(wstringIsEmpty), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	// Same as findFirst
	r = engine->RegisterObjectMethod("wstring", "int find(const wstring &in, uint start = 0) const", asFUNCTION(wstringFindFirst), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	// Same as findLast
	r = engine->RegisterObjectMethod("wstring", "int rfind(const wstring &in, int start = -1) const", asFUNCTION(wstringFindLast), asCALL_CDECL_OBJLAST); assert( r >= 0 );
#endif

	// TODO: Implement the following
	// findAndReplace - replaces a text found in the wstring
	// replaceRange - replaces a range of bytes in the wstring
	// multiply/times/opMul/opMul_r - takes the wstring and multiplies it n times, e.g. "-".multiply(5) returns "-----"
}

static void ConstructwstringGeneric(asIScriptGeneric * gen)
{
	new (gen->GetObject()) wstring();
}

static void CopyConstructwstringGeneric(asIScriptGeneric * gen)
{
	wstring * a = static_cast<wstring *>(gen->GetArgObject(0));
	new (gen->GetObject()) wstring(*a);
}

static void DestructwstringGeneric(asIScriptGeneric * gen)
{
	wstring * ptr = static_cast<wstring *>(gen->GetObject());
	ptr->~wstring();
}

static void AssignwstringGeneric(asIScriptGeneric *gen)
{
	wstring * a = static_cast<wstring *>(gen->GetArgObject(0));
	wstring * self = static_cast<wstring *>(gen->GetObject());
	*self = *a;
	gen->SetReturnAddress(self);
}

static void AddAssignwstringGeneric(asIScriptGeneric *gen)
{
	wstring * a = static_cast<wstring *>(gen->GetArgObject(0));
	wstring * self = static_cast<wstring *>(gen->GetObject());
	*self += *a;
	gen->SetReturnAddress(self);
}

static void wstringEqualsGeneric(asIScriptGeneric * gen)
{
	wstring * a = static_cast<wstring *>(gen->GetObject());
	wstring * b = static_cast<wstring *>(gen->GetArgAddress(0));
	*(bool*)gen->GetAddressOfReturnLocation() = (*a == *b);
}

static void wstringCmpGeneric(asIScriptGeneric * gen)
{
	wstring * a = static_cast<wstring *>(gen->GetObject());
	wstring * b = static_cast<wstring *>(gen->GetArgAddress(0));

	int cmp = 0;
	if( *a < *b ) cmp = -1;
	else if( *a > *b ) cmp = 1;

	*(int*)gen->GetAddressOfReturnLocation() = cmp;
}

static void wstringAddGeneric(asIScriptGeneric * gen)
{
	wstring * a = static_cast<wstring *>(gen->GetObject());
	wstring * b = static_cast<wstring *>(gen->GetArgAddress(0));
	wstring ret_val = *a + *b;
	gen->SetReturnObject(&ret_val);
}

static void wstringLengthGeneric(asIScriptGeneric * gen)
{
	wstring * self = static_cast<wstring *>(gen->GetObject());
	*static_cast<asUINT *>(gen->GetAddressOfReturnLocation()) = (asUINT)self->length();
}

static void wstringIsEmptyGeneric(asIScriptGeneric * gen)
{
	wstring * self = reinterpret_cast<wstring *>(gen->GetObject());
	*reinterpret_cast<bool *>(gen->GetAddressOfReturnLocation()) = wstringIsEmpty(*self);
}

static void wstringResizeGeneric(asIScriptGeneric * gen)
{
	wstring * self = static_cast<wstring *>(gen->GetObject());
	self->resize(*static_cast<asUINT *>(gen->GetAddressOfArg(0)));
}

static void wstringInsert_Generic(asIScriptGeneric *gen)
{
	wstring * self = static_cast<wstring *>(gen->GetObject());
	asUINT pos = gen->GetArgDWord(0);
	wstring *other = reinterpret_cast<wstring*>(gen->GetArgAddress(1));
	wstringInsert(pos, *other, *self);
}

static void wstringErase_Generic(asIScriptGeneric *gen)
{
	wstring * self = static_cast<wstring *>(gen->GetObject());
	asUINT pos = gen->GetArgDWord(0);
	int count = int(gen->GetArgDWord(1));
	wstringErase(pos, count, *self);
}

static void wstringFindFirst_Generic(asIScriptGeneric * gen)
{
	wstring *find = reinterpret_cast<wstring*>(gen->GetArgAddress(0));
	asUINT start = gen->GetArgDWord(1);
	wstring *self = reinterpret_cast<wstring *>(gen->GetObject());
	*reinterpret_cast<int *>(gen->GetAddressOfReturnLocation()) = wstringFindFirst(*find, start, *self);
}

static void wstringFindLast_Generic(asIScriptGeneric * gen)
{
	wstring *find = reinterpret_cast<wstring*>(gen->GetArgAddress(0));
	asUINT start = gen->GetArgDWord(1);
	wstring *self = reinterpret_cast<wstring *>(gen->GetObject());
	*reinterpret_cast<int *>(gen->GetAddressOfReturnLocation()) = wstringFindLast(*find, start, *self);
}

static void wstringFindFirstOf_Generic(asIScriptGeneric * gen)
{
	wstring *find = reinterpret_cast<wstring*>(gen->GetArgAddress(0));
	asUINT start = gen->GetArgDWord(1);
	wstring *self = reinterpret_cast<wstring *>(gen->GetObject());
	*reinterpret_cast<int *>(gen->GetAddressOfReturnLocation()) = wstringFindFirstOf(*find, start, *self);
}

static void wstringFindLastOf_Generic(asIScriptGeneric * gen)
{
	wstring *find = reinterpret_cast<wstring*>(gen->GetArgAddress(0));
	asUINT start = gen->GetArgDWord(1);
	wstring *self = reinterpret_cast<wstring *>(gen->GetObject());
	*reinterpret_cast<int *>(gen->GetAddressOfReturnLocation()) = wstringFindLastOf(*find, start, *self);
}

static void wstringFindFirstNotOf_Generic(asIScriptGeneric * gen)
{
	wstring *find = reinterpret_cast<wstring*>(gen->GetArgAddress(0));
	asUINT start = gen->GetArgDWord(1);
	wstring *self = reinterpret_cast<wstring *>(gen->GetObject());
	*reinterpret_cast<int *>(gen->GetAddressOfReturnLocation()) = wstringFindFirstNotOf(*find, start, *self);
}

static void wstringFindLastNotOf_Generic(asIScriptGeneric * gen)
{
	wstring *find = reinterpret_cast<wstring*>(gen->GetArgAddress(0));
	asUINT start = gen->GetArgDWord(1);
	wstring *self = reinterpret_cast<wstring *>(gen->GetObject());
	*reinterpret_cast<int *>(gen->GetAddressOfReturnLocation()) = wstringFindLastNotOf(*find, start, *self);
}

static void formatInt_Generic(asIScriptGeneric * gen)
{
	asINT64 val = gen->GetArgQWord(0);
	wstring *options = reinterpret_cast<wstring*>(gen->GetArgAddress(1));
	asUINT width = gen->GetArgDWord(2);
	new(gen->GetAddressOfReturnLocation()) wstring(formatInt(val, *options, width));
}

static void formatUInt_Generic(asIScriptGeneric * gen)
{
	asQWORD val = gen->GetArgQWord(0);
	wstring *options = reinterpret_cast<wstring*>(gen->GetArgAddress(1));
	asUINT width = gen->GetArgDWord(2);
	new(gen->GetAddressOfReturnLocation()) wstring(formatUInt(val, *options, width));
}

static void formatFloat_Generic(asIScriptGeneric *gen)
{
	double val = gen->GetArgDouble(0);
	wstring *options = reinterpret_cast<wstring*>(gen->GetArgAddress(1));
	asUINT width = gen->GetArgDWord(2);
	asUINT precision = gen->GetArgDWord(3);
	new(gen->GetAddressOfReturnLocation()) wstring(formatFloat(val, *options, width, precision));
}

static void parseInt_Generic(asIScriptGeneric *gen)
{
	wstring *str = reinterpret_cast<wstring*>(gen->GetArgAddress(0));
	asUINT base = gen->GetArgDWord(1);
	asUINT *byteCount = reinterpret_cast<asUINT*>(gen->GetArgAddress(2));
	gen->SetReturnQWord(parseInt(*str,base,byteCount));
}

static void parseUInt_Generic(asIScriptGeneric *gen)
{
	wstring *str = reinterpret_cast<wstring*>(gen->GetArgAddress(0));
	asUINT base = gen->GetArgDWord(1);
	asUINT *byteCount = reinterpret_cast<asUINT*>(gen->GetArgAddress(2));
	gen->SetReturnQWord(parseUInt(*str, base, byteCount));
}

static void parseFloat_Generic(asIScriptGeneric *gen)
{
	wstring *str = reinterpret_cast<wstring*>(gen->GetArgAddress(0));
	asUINT *byteCount = reinterpret_cast<asUINT*>(gen->GetArgAddress(1));
	gen->SetReturnDouble(parseFloat(*str,byteCount));
}

static void wstringCharAtGeneric(asIScriptGeneric * gen)
{
	unsigned int index = gen->GetArgDWord(0);
	wstring * self = static_cast<wstring *>(gen->GetObject());

	if (index >= self->size())
	{
		// Set a script exception
		asIScriptContext *ctx = asGetActiveContext();
		ctx->SetException("Out of range");

		gen->SetReturnAddress(0);
	}
	else
	{
		gen->SetReturnAddress(&(self->operator [](index)));
	}
}

static void AssignInt2wstringGeneric(asIScriptGeneric *gen)
{
	asINT64 *a = static_cast<asINT64*>(gen->GetAddressOfArg(0));
	wstring *self = static_cast<wstring*>(gen->GetObject());
	std::wstringstream sstr;
	sstr << *a;
	*self = sstr.str();
	gen->SetReturnAddress(self);
}

static void AssignUInt2wstringGeneric(asIScriptGeneric *gen)
{
	asQWORD *a = static_cast<asQWORD*>(gen->GetAddressOfArg(0));
	wstring *self = static_cast<wstring*>(gen->GetObject());
	std::wstringstream sstr;
	sstr << *a;
	*self = sstr.str();
	gen->SetReturnAddress(self);
}

static void AssignDouble2wstringGeneric(asIScriptGeneric *gen)
{
	double *a = static_cast<double*>(gen->GetAddressOfArg(0));
	wstring *self = static_cast<wstring*>(gen->GetObject());
	std::wstringstream sstr;
	sstr << *a;
	*self = sstr.str();
	gen->SetReturnAddress(self);
}

static void AssignFloat2wstringGeneric(asIScriptGeneric *gen)
{
	float *a = static_cast<float*>(gen->GetAddressOfArg(0));
	wstring *self = static_cast<wstring*>(gen->GetObject());
	std::wstringstream sstr;
	sstr << *a;
	*self = sstr.str();
	gen->SetReturnAddress(self);
}

static void AssignBool2wstringGeneric(asIScriptGeneric *gen)
{
	bool *a = static_cast<bool*>(gen->GetAddressOfArg(0));
	wstring *self = static_cast<wstring*>(gen->GetObject());
	std::wstringstream sstr;
	sstr << (*a ? "true" : "false");
	*self = sstr.str();
	gen->SetReturnAddress(self);
}

static void AddAssignDouble2wstringGeneric(asIScriptGeneric * gen)
{
	double * a = static_cast<double *>(gen->GetAddressOfArg(0));
	wstring * self = static_cast<wstring *>(gen->GetObject());
	std::wstringstream sstr;
	sstr << *a;
	*self += sstr.str();
	gen->SetReturnAddress(self);
}

static void AddAssignFloat2wstringGeneric(asIScriptGeneric * gen)
{
	float * a = static_cast<float *>(gen->GetAddressOfArg(0));
	wstring * self = static_cast<wstring *>(gen->GetObject());
	std::wstringstream sstr;
	sstr << *a;
	*self += sstr.str();
	gen->SetReturnAddress(self);
}

static void AddAssignInt2wstringGeneric(asIScriptGeneric * gen)
{
	asINT64 * a = static_cast<asINT64 *>(gen->GetAddressOfArg(0));
	wstring * self = static_cast<wstring *>(gen->GetObject());
	std::wstringstream sstr;
	sstr << *a;
	*self += sstr.str();
	gen->SetReturnAddress(self);
}

static void AddAssignUInt2wstringGeneric(asIScriptGeneric * gen)
{
	asQWORD * a = static_cast<asQWORD *>(gen->GetAddressOfArg(0));
	wstring * self = static_cast<wstring *>(gen->GetObject());
	std::wstringstream sstr;
	sstr << *a;
	*self += sstr.str();
	gen->SetReturnAddress(self);
}

static void AddAssignBool2wstringGeneric(asIScriptGeneric * gen)
{
	bool * a = static_cast<bool *>(gen->GetAddressOfArg(0));
	wstring * self = static_cast<wstring *>(gen->GetObject());
	std::wstringstream sstr;
	sstr << (*a ? "true" : "false");
	*self += sstr.str();
	gen->SetReturnAddress(self);
}

static void Addwstring2DoubleGeneric(asIScriptGeneric * gen)
{
	wstring * a = static_cast<wstring *>(gen->GetObject());
	double * b = static_cast<double *>(gen->GetAddressOfArg(0));
	std::wstringstream sstr;
	sstr << *a << *b;
	std::wstring ret_val = sstr.str();
	gen->SetReturnObject(&ret_val);
}

static void Addwstring2FloatGeneric(asIScriptGeneric * gen)
{
	wstring * a = static_cast<wstring *>(gen->GetObject());
	float * b = static_cast<float *>(gen->GetAddressOfArg(0));
	std::wstringstream sstr;
	sstr << *a << *b;
	std::wstring ret_val = sstr.str();
	gen->SetReturnObject(&ret_val);
}

static void Addwstring2IntGeneric(asIScriptGeneric * gen)
{
	wstring * a = static_cast<wstring *>(gen->GetObject());
	asINT64 * b = static_cast<asINT64 *>(gen->GetAddressOfArg(0));
	std::wstringstream sstr;
	sstr << *a << *b;
	std::wstring ret_val = sstr.str();
	gen->SetReturnObject(&ret_val);
}

static void Addwstring2UIntGeneric(asIScriptGeneric * gen)
{
	wstring * a = static_cast<wstring *>(gen->GetObject());
	asQWORD * b = static_cast<asQWORD *>(gen->GetAddressOfArg(0));
	std::wstringstream sstr;
	sstr << *a << *b;
	std::wstring ret_val = sstr.str();
	gen->SetReturnObject(&ret_val);
}

static void Addwstring2BoolGeneric(asIScriptGeneric * gen)
{
	wstring * a = static_cast<wstring *>(gen->GetObject());
	bool * b = static_cast<bool *>(gen->GetAddressOfArg(0));
	std::wstringstream sstr;
	sstr << *a << (*b ? "true" : "false");
	std::wstring ret_val = sstr.str();
	gen->SetReturnObject(&ret_val);
}

static void AddDouble2wstringGeneric(asIScriptGeneric * gen)
{
	double* a = static_cast<double *>(gen->GetAddressOfArg(0));
	wstring * b = static_cast<wstring *>(gen->GetObject());
	std::wstringstream sstr;
	sstr << *a << *b;
	std::wstring ret_val = sstr.str();
	gen->SetReturnObject(&ret_val);
}

static void AddFloat2wstringGeneric(asIScriptGeneric * gen)
{
	float* a = static_cast<float *>(gen->GetAddressOfArg(0));
	wstring * b = static_cast<wstring *>(gen->GetObject());
	std::wstringstream sstr;
	sstr << *a << *b;
	std::wstring ret_val = sstr.str();
	gen->SetReturnObject(&ret_val);
}

static void AddInt2wstringGeneric(asIScriptGeneric * gen)
{
	asINT64* a = static_cast<asINT64 *>(gen->GetAddressOfArg(0));
	wstring * b = static_cast<wstring *>(gen->GetObject());
	std::wstringstream sstr;
	sstr << *a << *b;
	std::wstring ret_val = sstr.str();
	gen->SetReturnObject(&ret_val);
}

static void AddUInt2wstringGeneric(asIScriptGeneric * gen)
{
	asQWORD* a = static_cast<asQWORD *>(gen->GetAddressOfArg(0));
	wstring * b = static_cast<wstring *>(gen->GetObject());
	std::wstringstream sstr;
	sstr << *a << *b;
	std::wstring ret_val = sstr.str();
	gen->SetReturnObject(&ret_val);
}

static void AddBool2wstringGeneric(asIScriptGeneric * gen)
{
	bool* a = static_cast<bool *>(gen->GetAddressOfArg(0));
	wstring * b = static_cast<wstring *>(gen->GetObject());
	std::wstringstream sstr;
	sstr << (*a ? "true" : "false") << *b;
	std::wstring ret_val = sstr.str();
	gen->SetReturnObject(&ret_val);
}

static void wstringSubwstring_Generic(asIScriptGeneric *gen)
{
	// Get the arguments
	wstring *str   = (wstring*)gen->GetObject();
	asUINT  start = *(int*)gen->GetAddressOfArg(0);
	int     count = *(int*)gen->GetAddressOfArg(1);

	// Return the subwstring
	new(gen->GetAddressOfReturnLocation()) wstring(wstringSubwstring(start, count, *str));
}

void RegisterStdWString_Generic(asIScriptEngine *engine)
{
	int r = 0;
	UNUSED_VAR(r);

	// Register the wstring type
	r = engine->RegisterObjectType("wstring", sizeof(wstring), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); assert( r >= 0 );

	//r = engine->RegisterwstringFactory("wstring", &wstringFactory);

	// Register the object operator overloads
	r = engine->RegisterObjectBehaviour("wstring", asBEHAVE_CONSTRUCT,  "void f()",                    asFUNCTION(ConstructwstringGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("wstring", asBEHAVE_CONSTRUCT,  "void f(const wstring &in)",    asFUNCTION(CopyConstructwstringGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("wstring", asBEHAVE_DESTRUCT,   "void f()",                    asFUNCTION(DestructwstringGeneric),  asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring &opAssign(const wstring &in)", asFUNCTION(AssignwstringGeneric),    asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring &opAddAssign(const wstring &in)", asFUNCTION(AddAssignwstringGeneric), asCALL_GENERIC); assert( r >= 0 );

	r = engine->RegisterObjectMethod("wstring", "bool opEquals(const wstring &in) const", asFUNCTION(wstringEqualsGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "int opCmp(const wstring &in) const", asFUNCTION(wstringCmpGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd(const wstring &in) const", asFUNCTION(wstringAddGeneric), asCALL_GENERIC); assert( r >= 0 );

	// Register the object methods
	r = engine->RegisterObjectMethod("wstring", "uint length() const", asFUNCTION(wstringLengthGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "void resize(uint)",   asFUNCTION(wstringResizeGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "uint get_length() const", asFUNCTION(wstringLengthGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "void set_length(uint)", asFUNCTION(wstringResizeGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "bool isEmpty() const", asFUNCTION(wstringIsEmptyGeneric), asCALL_GENERIC); assert( r >= 0 );

	// Register the index operator, both as a mutator and as an inspector
	r = engine->RegisterObjectMethod("wstring", "uint8 &opIndex(uint)", asFUNCTION(wstringCharAtGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "const uint8 &opIndex(uint) const", asFUNCTION(wstringCharAtGeneric), asCALL_GENERIC); assert( r >= 0 );

	// Automatic conversion from values
	r = engine->RegisterObjectMethod("wstring", "wstring &opAssign(double)", asFUNCTION(AssignDouble2wstringGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring &opAddAssign(double)", asFUNCTION(AddAssignDouble2wstringGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd(double) const", asFUNCTION(Addwstring2DoubleGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd_r(double) const", asFUNCTION(AddDouble2wstringGeneric), asCALL_GENERIC); assert( r >= 0 );

	r = engine->RegisterObjectMethod("wstring", "wstring &opAssign(float)", asFUNCTION(AssignFloat2wstringGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring &opAddAssign(float)", asFUNCTION(AddAssignFloat2wstringGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd(float) const", asFUNCTION(Addwstring2FloatGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd_r(float) const", asFUNCTION(AddFloat2wstringGeneric), asCALL_GENERIC); assert( r >= 0 );

	r = engine->RegisterObjectMethod("wstring", "wstring &opAssign(int64)", asFUNCTION(AssignInt2wstringGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring &opAddAssign(int64)", asFUNCTION(AddAssignInt2wstringGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd(int64) const", asFUNCTION(Addwstring2IntGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd_r(int64) const", asFUNCTION(AddInt2wstringGeneric), asCALL_GENERIC); assert( r >= 0 );

	r = engine->RegisterObjectMethod("wstring", "wstring &opAssign(uint64)", asFUNCTION(AssignUInt2wstringGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring &opAddAssign(uint64)", asFUNCTION(AddAssignUInt2wstringGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd(uint64) const", asFUNCTION(Addwstring2UIntGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd_r(uint64) const", asFUNCTION(AddUInt2wstringGeneric), asCALL_GENERIC); assert( r >= 0 );

	r = engine->RegisterObjectMethod("wstring", "wstring &opAssign(bool)", asFUNCTION(AssignBool2wstringGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring &opAddAssign(bool)", asFUNCTION(AddAssignBool2wstringGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd(bool) const", asFUNCTION(Addwstring2BoolGeneric), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("wstring", "wstring opAdd_r(bool) const", asFUNCTION(AddBool2wstringGeneric), asCALL_GENERIC); assert( r >= 0 );

	r = engine->RegisterObjectMethod("wstring", "wstring substr(uint start = 0, int count = -1) const", asFUNCTION(wstringSubwstring_Generic), asCALL_GENERIC); assert(r >= 0);
	r = engine->RegisterObjectMethod("wstring", "int findFirst(const wstring &in, uint start = 0) const", asFUNCTION(wstringFindFirst_Generic), asCALL_GENERIC); assert(r >= 0);
	r = engine->RegisterObjectMethod("wstring", "int findFirstOf(const wstring &in, uint start = 0) const", asFUNCTION(wstringFindFirstOf_Generic), asCALL_GENERIC); assert(r >= 0);
	r = engine->RegisterObjectMethod("wstring", "int findFirstNotOf(const wstring &in, uint start = 0) const", asFUNCTION(wstringFindFirstNotOf_Generic), asCALL_GENERIC); assert(r >= 0);
	r = engine->RegisterObjectMethod("wstring", "int findLast(const wstring &in, int start = -1) const", asFUNCTION(wstringFindLast_Generic), asCALL_GENERIC); assert(r >= 0);
	r = engine->RegisterObjectMethod("wstring", "int findLastOf(const wstring &in, int start = -1) const", asFUNCTION(wstringFindLastOf_Generic), asCALL_GENERIC); assert(r >= 0);
	r = engine->RegisterObjectMethod("wstring", "int findLastNotOf(const wstring &in, int start = -1) const", asFUNCTION(wstringFindLastNotOf_Generic), asCALL_GENERIC); assert(r >= 0);
	r = engine->RegisterObjectMethod("wstring", "void insert(uint pos, const wstring &in other)", asFUNCTION(wstringInsert_Generic), asCALL_GENERIC); assert(r >= 0);
	r = engine->RegisterObjectMethod("wstring", "void erase(uint pos, int count = -1)", asFUNCTION(wstringErase_Generic), asCALL_GENERIC); assert(r >= 0);


	r = engine->RegisterGlobalFunction("wstring formatInt(int64 val, const wstring &in options = \"\", uint width = 0)", asFUNCTION(formatInt_Generic), asCALL_GENERIC); assert(r >= 0);
	r = engine->RegisterGlobalFunction("wstring formatUInt(uint64 val, const wstring &in options = \"\", uint width = 0)", asFUNCTION(formatUInt_Generic), asCALL_GENERIC); assert(r >= 0);
	r = engine->RegisterGlobalFunction("wstring formatFloat(double val, const wstring &in options = \"\", uint width = 0, uint precision = 0)", asFUNCTION(formatFloat_Generic), asCALL_GENERIC); assert(r >= 0);
	r = engine->RegisterGlobalFunction("int64 parseInt(const wstring &in, uint base = 10, uint &out byteCount = 0)", asFUNCTION(parseInt_Generic), asCALL_GENERIC); assert(r >= 0);
	r = engine->RegisterGlobalFunction("uint64 parseUInt(const wstring &in, uint base = 10, uint &out byteCount = 0)", asFUNCTION(parseUInt_Generic), asCALL_GENERIC); assert(r >= 0);
	r = engine->RegisterGlobalFunction("double parseFloat(const wstring &in, uint &out byteCount = 0)", asFUNCTION(parseFloat_Generic), asCALL_GENERIC); assert(r >= 0);
}

void RegisterStdWString(asIScriptEngine * engine)
{
	if (strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY"))
		RegisterStdWString_Generic(engine);
	else
		RegisterStdWString_Native(engine);
}

END_AS_NAMESPACE




