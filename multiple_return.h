#define TOKEN_PASTE(a, b) a##b
#define CONCAT(a,b) TOKEN_PASTE(a,b)
#define UQ(name) CONCAT(name, __LINE__) /* unique identifier */

#define CAT( A, B ) A ## B
#define SELECT( NAME, NUM ) CAT( NAME ## _, NUM )
#define GET_COUNT( _1, _2, _3, _4, _5, _6 /* ad nauseam */, COUNT, ... ) COUNT
#define VA_SIZE( ... ) GET_COUNT( __VA_ARGS__, 6, 5, 4, 3, 2, 1 )
#define VA_SELECT( NAME, ... ) SELECT( NAME, VA_SIZE(__VA_ARGS__) )(__VA_ARGS__)

/* support for up to 4 return types */
#define _mret_struct(...)        VA_SELECT( _mret_struct, __VA_ARGS__ )
#define _mret_struct_1(a)        struct _##a
#define _mret_struct_2(a,b)      struct _##a##b
#define _mret_struct_3(a,b,c)    struct _##a##b##c
#define _mret_struct_4(a,b,c,d)  struct _##a##b##c##d

#define ret(...)        VA_SELECT( _ret, __VA_ARGS__ )
#define _ret_1(a)       _mret_struct_1(a)       { a _0; }
#define _ret_2(a,b)     _mret_struct_2(a,b)     { a _0; b _1; }
#define _ret_3(a,b,c)   _mret_struct_3(a,b,c)   { a _0; b _1; c _2; }
#define _ret_4(a,b,c,d) _mret_struct_4(a,b,c,d) { a _0; b _1; c _2; d _3; }

#define mreturn(...)      return (_mret_struct(__VA_ARGS__))

/* TODO: use auto if C++/C23 instead of __auto_type */
#define _mret_decl(...)       VA_SELECT( _mret_decl, __VA_ARGS__ )
#define _mret_decl_1(a)       __auto_type a = UQ(__ret)._0;
#define _mret_decl_2(a,b)     __auto_type a = UQ(__ret)._0; __auto_type b = UQ(__ret)._1;
#define _mret_decl_3(a,b,c)   __auto_type a = UQ(__ret)._0; __auto_type b = UQ(__ret)._1; __auto_type c = UQ(__ret)._2;
#define _mret_decl_4(a,b,c,d) __auto_type a = UQ(__ret)._0; __auto_type b = UQ(__ret)._1; __auto_type c = UQ(__ret)._2; __auto_type d = UQ(__ret)._3;

#define _mret_assign(...)       VA_SELECT( _mret_assign, __VA_ARGS__ )
#define _mret_assign_1(a)       a = UQ(__ret)._0;
#define _mret_assign_2(a,b)     a = UQ(__ret)._0; b = UQ(__ret)._1;
#define _mret_assign_3(a,b,c)   a = UQ(__ret)._0; b = UQ(__ret)._1; c = UQ(__ret)._2;
#define _mret_assign_4(a,b,c,d) a = UQ(__ret)._0; b = UQ(__ret)._1; c = UQ(__ret)._2; d = UQ(__ret)._3;

#define m(...) _mret_struct(__VA_ARGS__) UQ(__ret); _m
#define _m(...)                       \
    _mret_decl(__VA_ARGS__)           \
    if (1) goto UQ(_body);            \
    else while (1)                    \
        if (1) {                      \
            _mret_assign(__VA_ARGS__) \
            break;                    \
        } else UQ(_body): UQ(__ret)
