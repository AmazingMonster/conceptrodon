/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct Any
{
    static constexpr bool value
    { (...||(static_cast<bool>(Variables))) };
};

template<auto...Variables>
constexpr bool Any_v
{ (...||(static_cast<bool>(Variables))) };

/*****************/
/**** Example ****/
/*****************/

static_assert(Any<1, 2, 3>::value);
static_assert(Any<0, 2, 3>::value);
static_assert(Any<nullptr, 2, 3>::value);
static_assert(! Any<nullptr, 0, 0>::value);
