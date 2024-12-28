/************************/
/**** Implementation ****/
/************************/

template<auto, auto>
struct SolitaryIsSame
{ static constexpr bool value {false}; };

template<auto Variable>
struct SolitaryIsSame<Variable, Variable>
{ static constexpr bool value {true}; };

/*****************/
/**** Example ****/
/*****************/

static_assert(! SolitaryIsSame<1, 1.0>::value);
static_assert(SolitaryIsSame<1, 1>::value);