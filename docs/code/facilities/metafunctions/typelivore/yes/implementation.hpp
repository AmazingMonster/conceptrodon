/************************/
/**** Implementation ****/
/************************/

template<typename...>
struct Yes
{
    static constexpr bool value {true};
};

/*****************/
/**** Example ****/
/*****************/

static_assert(Yes<int>::value);