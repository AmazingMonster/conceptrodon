/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsNonoverloadedFunctionObject
{
    static constexpr bool value {false};
};

template<typename FO>
requires requires {&FO::operator();}
struct IsNonoverloadedFunctionObject<FO>
{
    static constexpr bool value {true};
};

template<typename FO>
constexpr bool IsNonoverloadedFunctionObject_v
{
    requires {&FO::operator();}
};

/*****************/
/**** Example ****/
/*****************/

/**** Testers ****/
struct NonoverloadedFO
{
    int operator()(int const, double&...) const volatile && noexcept { return 0; }
};

struct OverloadedFO
{
    int operator()(int const, double&...) const volatile && noexcept { return 0; }
    int operator()(double const, double&...) const volatile && noexcept { return 0; }
};

/**** Tests ****/
static_assert(IsNonoverloadedFunctionObject<NonoverloadedFO>::value);
static_assert(not IsNonoverloadedFunctionObject<OverloadedFO>::value);
