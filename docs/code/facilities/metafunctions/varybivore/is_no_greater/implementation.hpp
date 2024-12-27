/************************/
/**** Implementation ****/
/************************/

template<auto Target, auto...Variables>
struct IsNoGreater
{
    static constexpr bool value
    { (...&&(not (Variables < Target))) };
};

template<auto Target, auto...Variables>
constexpr bool IsNoGreater_v
{ (...&&(not (Variables < Target))) };

/*****************/
/**** Example ****/
/*****************/

static_assert(IsNoGreater<5, 5, 6, 7>::value);
static_assert(! IsNoGreater<4, 2, 3, 4>::value);