/************************/
/**** Implementation ****/
/************************/

template<auto I>
struct Positive
{ 
    static constexpr auto value 
    {+I}; 
};

/*****************/
/**** Example ****/
/*****************/

static_assert(Positive<1>::value == 1);
static_assert(Positive<-1.0>::value == -1.0);