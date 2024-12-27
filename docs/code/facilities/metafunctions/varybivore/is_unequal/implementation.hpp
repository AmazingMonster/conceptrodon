/************************/
/**** Implementation ****/
/************************/

template<auto Target, auto...Variables>
struct IsUnequal
{
    static constexpr auto value
    { (...&&(Target < Variables || Variables < Target)) };
};

template<auto Target, auto...Variables>
constexpr bool IsUnequal_v
{ (...&&(Target < Variables || Variables < Target)) };

/*****************/
/**** Example ****/
/*****************/

static_assert(! IsUnequal<1, 1.0, 2, 3>::value);
static_assert(IsUnequal<1, 2, 2, 3>::value);