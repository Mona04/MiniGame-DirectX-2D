#include <assert.h>
#include "scriptstdwstring.h"
#include "../scriptarray/scriptarray.h"
#include <stdio.h>
#include <string.h>

using namespace std;

BEGIN_AS_NAMESPACE

// This function takes an input wstring and splits it into parts by looking
// for a specified delimiter. Example:
//
// wstring str = "A|B||D";
// array<wstring>@ array = str.split("|");
//
// The resulting array has the following elements:
//
// {"A", "B", "", "D"}
//
// AngelScript signature:
// array<wstring>@ wstring::split(const wstring &in delim) const
static CScriptArray *wstringSplit(const wstring &delim, const wstring &str)
{
	// Obtain a pointer to the engine
	asIScriptContext *ctx = asGetActiveContext();
	asIScriptEngine *engine = ctx->GetEngine();

	// TODO: This should only be done once
	// TODO: This assumes that CScriptArray was already registered
	asITypeInfo *arrayType = engine->GetTypeInfoByDecl("array<wstring>");

	// Create the array object
	CScriptArray *array = CScriptArray::Create(arrayType);

	// Find the existence of the delimiter in the input wstring
	int pos = 0, prev = 0, count = 0;
	while( (pos = (int)str.find(delim, prev)) != (int)wstring::npos )
	{
		// Add the part to the array
		array->Resize(array->GetSize()+1);
		((wstring*)array->At(count))->assign(&str[prev], pos-prev);

		// Find the next part
		count++;
		prev = pos + (int)delim.length();
	}

	// Add the remaining part
	array->Resize(array->GetSize()+1);
	((wstring*)array->At(count))->assign(&str[prev]);

	return array;
}

static void wstringSplit_Generic(asIScriptGeneric *gen)
{
	// Get the arguments
	wstring *str   = (wstring*)gen->GetObject();
	wstring *delim = *(wstring**)gen->GetAddressOfArg(0);

	// Return the array by handle
	*(CScriptArray**)gen->GetAddressOfReturnLocation() = wstringSplit(*delim, *str);
}



// This function takes as input an array of wstring handles as well as a
// delimiter and concatenates the array elements into one delimited wstring.
// Example:
//
// array<wstring> array = {"A", "B", "", "D"};
// wstring str = join(array, "|");
//
// The resulting wstring is:
//
// "A|B||D"
//
// AngelScript signature:
// wstring join(const array<wstring> &in array, const wstring &in delim)
static wstring wstringJoin(const CScriptArray &array, const wstring &delim)
{
	// Create the new wstring
	wstring str = L"";
	if( array.GetSize() )
	{
		int n;
		for( n = 0; n < (int)array.GetSize() - 1; n++ )
		{
			str += *(wstring*)array.At(n);
			str += delim;
		}

		// Add the last part
		str += *(wstring*)array.At(n);
	}

	return str;
}

static void wstringJoin_Generic(asIScriptGeneric *gen)
{
	// Get the arguments
	CScriptArray  *array = *(CScriptArray**)gen->GetAddressOfArg(0);
	wstring *delim = *(wstring**)gen->GetAddressOfArg(1);

	// Return the wstring
	new(gen->GetAddressOfReturnLocation()) wstring(wstringJoin(*array, *delim));
}

// This is where the utility functions are registered.
// The wstring type must have been registered first.
void RegisterStdwstringUtils(asIScriptEngine *engine)
{
	int r;

	if( strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY") )
	{
		r = engine->RegisterObjectMethod("wstring", "array<wstring>@ split(const wstring &in) const", asFUNCTION(wstringSplit_Generic), asCALL_GENERIC); assert(r >= 0);
		r = engine->RegisterGlobalFunction("wstring join(const array<wstring> &in, const wstring &in)", asFUNCTION(wstringJoin_Generic), asCALL_GENERIC); assert(r >= 0);
	}
	else
	{
		r = engine->RegisterObjectMethod("wstring", "array<wstring>@ split(const wstring &in) const", asFUNCTION(wstringSplit), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterGlobalFunction("wstring join(const array<wstring> &in, const wstring &in)", asFUNCTION(wstringJoin), asCALL_CDECL); assert(r >= 0);
	}
}

END_AS_NAMESPACE
