#include <compat/fopen_utf8.h>
#include <encodings/utf.h>

#ifdef _WIN32
#undef fopen

FILE* fopen_utf8(const char * filename, const char * mode)
{
#if defined(_XBOX)
   return fopen(filename, mode);
#elif defined(LEGACY_WIN32)
   char * filename_local = utf8_to_local_string_alloc(path);
   FILE* ret = fopen(filename_local, mode);
   free(filename_local);
   return ret;
#else
   wchar_t * filename_w = utf8_to_utf16_string_alloc(filename);
   wchar_t * mode_w = utf8_to_utf16_string_alloc(mode);
   FILE* ret = _wfopen(filename_w, mode_w);
   free(filename_w);
   free(mode_w);
   return ret;
#endif
}
#endif