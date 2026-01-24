/************************/
/**** Implementation ****/
/************************/

template<auto...>
struct Yes
{
    static constexpr bool value {true};
};

/*****************/
/**** Example ****/
/*****************/

static_assert(Yes<0>::value);