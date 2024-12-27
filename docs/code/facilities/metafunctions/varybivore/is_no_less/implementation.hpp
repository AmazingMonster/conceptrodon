/************************/
/**** Implementation ****/
/************************/

template<auto Target, auto...Variables>
struct IsNoLess
{
    static constexpr bool value
    { (...&&(not (Target < Variables))) };
};

template<auto Target, auto...Variables>
constexpr bool IsNoLess_v
{ (...&&(not (Target < Variables))) };

/*****************/
/**** Example ****/
/*****************/

static_assert(IsNoLess<5, 4, 3, 2>::value);
static_assert(! IsNoLess<4, 5, 3, 4>::value);