/**********************/
/**** Dependencies ****/
/**********************/

template<auto, auto>
struct SolitaryIsDifferent
{ static constexpr bool value {true}; };

template<auto Variable>
struct SolitaryIsDifferent<Variable, Variable>
{ static constexpr bool value {false}; };

/************************/
/**** Implementation ****/
/************************/

template<auto Target, auto...Variables>
struct IsDifferent
{
    static constexpr bool value
    {(...&&SolitaryIsDifferent<Variables, Target>::value)};
};

template<auto Target, auto...Variables>
constexpr bool IsDifferent_v
{(...&&SolitaryIsDifferent<Variables, Target>::value)};

/*****************/
/**** Example ****/
/*****************/

static_assert(IsDifferent<1, 2, 3, 4>::value);
static_assert(! IsDifferent<1, 1.0, 1>::value);
static_assert(IsDifferent<1, 1.0>::value);