/************************/
/**** Implementation ****/
/************************/

template<auto Target, auto...Variables>
struct IsLess
{
    static constexpr bool value
    { (...&&(Target < Variables)) };
};

template<auto Target, auto...Variables>
constexpr bool IsLess_v
{ (...&&(Target < Variables)) };

/*****************/
/**** Example ****/
/*****************/

static_assert(IsLess<0, 2, 3, 4>::value);
static_assert(! IsLess<0, -1, 2, 3>::value);