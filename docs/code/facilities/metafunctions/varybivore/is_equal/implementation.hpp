/************************/
/**** Implementation ****/
/************************/

template<auto Target, auto...Variables>
struct IsEqual
{
    static constexpr bool value
    { (...&&(not (Target < Variables) && not (Variables < Target))) };
};

template<auto Target, auto...Variables>
constexpr bool IsEqual_v
{ (...&&(not (Target < Variables) && not (Variables < Target))) };

/*****************/
/**** Example ****/
/*****************/

static_assert(IsEqual<1, 1.0, 1>::value);
static_assert(! IsEqual<1, 2, 2>::value);