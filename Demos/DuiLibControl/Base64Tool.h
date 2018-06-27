#pragma once

#include <string>
#include <vector>

class CBase64Tool {
   static char Encode(unsigned char uc);
   static unsigned char Decode(char c);
   static bool IsBase64(char c);
 public:
   static std::string Encode(const BYTE* vby, unsigned long size);
   static std::string Encode( const std::string & vby);
   static std::string Decode( const std::string & str);
};

inline char CBase64Tool::Encode(unsigned char uc)
{
   if (uc < 26)
   {
      return 'A'+uc;
   }
   if (uc < 52)
   {
      return 'a'+(uc-26);
   }
   if (uc < 62)
   {
      return '0'+(uc-52);
   }
   if (uc == 62)
   {
      return '+';
   }
   return '/';
}

inline unsigned char CBase64Tool::Decode(char c)
{
   if (c >= 'A' && c <= 'Z')
   {
      return c - 'A';
   }
   if (c >= 'a' && c <= 'z')
   {
      return c - 'a' + 26;
   }
   if (c >= '0' && c <= '9')
   {
      return c - '0' + 52;
   }
   if (c == '+')
   {
      return 62;
   }
   return 63;
}

inline bool CBase64Tool::IsBase64(char c)
{
   if (c >= 'A' && c <= 'Z')
   {
      return true;
   }
   if (c >= 'a' && c <= 'z')
   {
      return true;
   }
   if (c >= '0' && c <= '9')
   {
      return true;
   }
   if (c == '+')
   {
      return true;
   }
   if (c == '/')
   {
      return true;
   }
   if (c == '=')
   {
      return true;
   }
   return false;
}

