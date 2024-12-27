/************************/
/**** Implementation ****/
/************************/

template<auto Target, auto...Variables>
struct IsGreater
{
    static constexpr bool value
    { (...&&(Variables < Target)) };
};

template<auto Target, auto...Variables>
constexpr bool IsGreater_v
{ (...&&(Variables < Target)) };

/*****************/
/**** Example ****/
/*****************/

static_assert(IsGreater<5, 2, 3, 4>::value);
static_assert(! IsGreater<4, 2, 3, 4>::value);