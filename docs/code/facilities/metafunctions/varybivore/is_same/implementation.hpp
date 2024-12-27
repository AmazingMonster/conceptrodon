/**********************/
/**** Dependencies ****/
/**********************/

template<auto, auto>
struct SolitaryIsSame
{ static constexpr bool value {false}; };

template<auto Variable>
struct SolitaryIsSame<Variable, Variable>
{ static constexpr bool value {true}; };

/************************/
/**** Implementation ****/
/************************/

template<auto Target, auto...Variables>
struct IsSame
{
    static constexpr bool value
    {(...&&SolitaryIsSame<Variables, Target>::value)};
};

template<auto Target, auto...Variables>
constexpr bool IsSame_v
{(...&&SolitaryIsSame<Variables, Target>::value)};

/*****************/
/**** Example ****/
/*****************/

static_assert(IsSame<1, 1, 1, 1>::value);
static_assert(! IsSame<1, 1.0, 1>::value);