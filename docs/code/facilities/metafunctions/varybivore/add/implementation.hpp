/************************/
/**** Implementation ****/
/************************/

template<auto Init, auto...Variables>
struct Add
{ 
    static constexpr auto value 
    { (Init+...+Variables) }; 
};

template<auto Init, auto...Variables>
constexpr auto Add_v 
{ (Init+...+Variables) }; 

/*****************/
/**** Example ****/
/*****************/

static_assert(Add<1, 2, 3>::value == 6);
