// In this file we will encrypt the stored keys using base64 and addition of the 3 strings to the given string
//we are not using standard encryption techniques because that will need additional libraries
//which requires installation
#ifndef BASE64_H
#define BASE64_H

#include<vector>
#include<string>

namespace Base64
{
    std::string base64_encode(const std::string &);
 //i find the following declaration to be incorrect
    const std::string &SALT1 = "LM::TB::BB";
    const std::string &SALT2 = "_:/_77";
    const std::string &SALT3 = "line=wowC++";

    std::string EncryptB64(std::string s)
    {
        s = SALT1 + s + SALT2 + SALT3;
        s = base64_encode(s);
        s.insert(7,SALT3);         //inserting salt3 to our encrypted string after 7th character
        s += SALT1;
        s = base64_encode(s);
        s += SALT2 + SALT3 +SALT1; // original code = SALT1+SALT2+SALT3;
        s = base64_encode(s);
        s.insert(1,"L");
        s.insert(7,"M");
        return s;
    }

    const std::string &BASE64_CODES ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

    std::string base64_encode(const std::string &s)
    {
        std::string ret;     //output string
        int val = 0;         //index that we will use to map index to our base64 table/array
        int bits = -6;       //will be used to represent the no. of bits in a sub group
        const unsigned int b63 = 0x3f                     //unsigned int = positive , 3F is hexadecimal for 63

        for(const auto &c :s)         //c will be assigned characters from string s  this feature is new in c++ 11
        {
            val = val(<<8) + c ;       //resulting no. will be left shifted val = val + 2^8
            bits += 8;                // this will add bits ,as base64 work with octets
            while(bits>=0)
            {
                ret.push_back(BASE64_CODES[(val>>bits) & b63]);      //inserts the mapped no. or char in output string
                bits -= 6;
            }
        }

        if(bits >-6)
            ret.push_back(BASE64_CODES[((val<<8) >> (bits+8)) & b63]);

        while(ret.size()%4)
            ret.push_back('=');

        return ret;
    }
}
#endif // BASE64_H

