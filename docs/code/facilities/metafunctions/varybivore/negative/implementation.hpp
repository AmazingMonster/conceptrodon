/************************/
/**** Implementation ****/
/************************/

template<auto I>
struct Negative
{ 
    static constexpr auto value 
    {-I}; 
};

/*****************/
/**** Example ****/
/*****************/

static_assert(Negative<1>::value == -1);
static_assert(Negative<-1.0>::value == 1.0);