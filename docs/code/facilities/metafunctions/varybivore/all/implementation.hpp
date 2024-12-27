/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct All
{
    static constexpr bool value
    { (...&&(static_cast<bool>(Variables))) };
};

template<auto...Variables>
constexpr bool All_v
{ (...&&(static_cast<bool>(Variables))) };

/*****************/
/**** Example ****/
/*****************/

static_assert(All<1, 2, 3>::value);
static_assert(! All<0, 2, 3>::value);
static_assert(! All<nullptr, 2, 3>::value);
