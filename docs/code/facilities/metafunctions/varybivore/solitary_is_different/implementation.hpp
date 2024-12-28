/************************/
/**** Implementation ****/
/************************/

template<auto, auto>
struct SolitaryIsDifferent
{ static constexpr bool value {true}; };

template<auto Variable>
struct SolitaryIsDifferent<Variable, Variable>
{ static constexpr bool value {false}; };

/*****************/
/**** Example ****/
/*****************/

static_assert(SolitaryIsDifferent<1, 1.0>::value);
static_assert(!SolitaryIsDifferent<1, 1>::value);