#include "stdafx.h"
#include "Base64Tool.h"

//using namespace std;

std::string CBase64Tool::Encode(const BYTE* vby, unsigned long size)
{
    std::string retval;
    if (size == 0)
    {
        return retval;
    }
    retval.reserve(size/3*4+4);
    for (std::vector<unsigned char>::size_type i=0;i<size;i+=3)
    {
        unsigned char by1=0,by2=0,by3=0;
        by1 = vby[i];
        if (i+1<size)
        {
            by2 = vby[i+1];
        }
        if (i+2<size)
        {
            by3 = vby[i+2];
        }
        unsigned char by4=0,by5=0,by6=0,by7=0;
        by4 = by1>>2;
        by5 = ((by1&0x3)<<4)|(by2>>4);
        by6 = ((by2&0xf)<<2)|(by3>>6);
        by7 = by3&0x3f;
        retval += Encode(by4);
        retval += Encode(by5);
        if (i+1<size)
        {
            retval += Encode(by6);
        }
        else
        {
            retval += "=";
        }
        if (i+2<size)
        {
            retval += Encode(by7);
        }
        else
        {
            retval += "=";
        }
    }
    return retval;
}

std::string CBase64Tool::Encode(const std::string & vby)
{
    return Encode((const BYTE*)vby.c_str(), (unsigned long)vby.size());
}

std::string CBase64Tool::Decode(const std::string & _str)
{
   std::string str;
   for (std::string::size_type j=0;j<_str.length();j++)
   {
      if (IsBase64(_str[j]))
      {
         str += _str[j];
      }
   }
   std::string retval;
   if (str.length() == 0)
   {
      return retval;
   }
   retval.reserve(str.size()/4*3+3);
   for (std::string::size_type i=0;i<str.length();i+=4)
   {
      char c1='A',c2='A',c3='A',c4='A';
      c1 = str[i];
      if (i+1<str.length())
      {
         c2 = str[i+1];
      };
      if (i+2<str.length())
      {
         c3 = str[i+2];
      };
      if (i+3<str.length())
      {
         c4 = str[i+3];
      };
      unsigned char by1=0,by2=0,by3=0,by4=0;
      by1 = Decode(c1);
      by2 = Decode(c2);
      by3 = Decode(c3);
      by4 = Decode(c4);
      char cTmp = (by1<<2)|(by2>>4);
      retval.append( &cTmp,1 );
      if (c3 != '=')
      {
          cTmp = ((by2&0xf)<<4)|(by3>>2);
          retval.append( &cTmp,1 );
      }
      if (c4 != '=')
      {
          cTmp = ((by3&0x3)<<6)|by4;
          retval.append( &cTmp,1 );
      }
   }
   return retval;
}
