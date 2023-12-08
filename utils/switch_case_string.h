#ifndef _SWITCH_CASE_STRING_H_
#define _SWITCH_CASE_STRING_H_

#define SWITCH(str)  switch(switch_string::str_hash_for_switch(str))
#define CASE(str)    static_assert(switch_string::str_is_correct(str) && (switch_string::str_len(str) <= switch_string::MAX_LEN),\
"CASE string contains wrong characters, or its length is greater than 9");\
case switch_string::str_hash(str, switch_string::str_len(str))
#define DEFAULT  default

namespace switch_string
{
    const unsigned char MAX_LEN = 9;
    const unsigned long long N_HASH = static_cast<unsigned long long>(-1);

    constexpr unsigned long long raise_128_to(const unsigned char power)
    {
        return 1ULL << 7 * power;
    }

    constexpr bool str_is_correct(const char* const str)
    {
        return (static_cast<signed char>(*str) > 0) ? str_is_correct(str + 1) : (*str ? false : true);
    }

    constexpr unsigned char str_len(const char* const str)
    {
        return *str ? (1 + str_len(str + 1)) : 0;
    }

    constexpr unsigned long long str_hash(const char* const str, const unsigned char current_len)
    {
        return *str ? (raise_128_to(current_len - 1) * static_cast<unsigned char>(*str) + str_hash(str + 1, current_len - 1)) : 0;
    }

    inline unsigned long long str_hash_for_switch(const char* const str)
    {
        return (str_is_correct(str) && (str_len(str) <= MAX_LEN)) ? str_hash(str, str_len(str)) : N_HASH;
    }

    //inline unsigned long long str_hash_for_switch(const std::string& str)
    //{
    //    return (str_is_correct(str.c_str()) && (str.length() <= MAX_LEN)) ? str_hash(str.c_str(), str.length()) : N_HASH;
    //}
}

#endif  //_SWITCH_CASE_STRING_H_