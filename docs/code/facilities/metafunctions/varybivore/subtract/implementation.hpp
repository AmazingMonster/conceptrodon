/************************/
/**** Implementation ****/
/************************/

template<auto Target, auto...Variables>
struct Subtract
{ 
    static constexpr auto value 
    {(Target -...- Variables)}; 
};

/*****************/
/**** Example ****/
/*****************/

static_assert(Subtract<3, 1, 2, -2, 2>::value == 0);