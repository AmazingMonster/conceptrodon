/************************/
/**** Implementation ****/
/************************/

template<auto Predicate, typename...Elements>
concept Deceive = not Predicate(Elements::value...);

/***********************/
/**** First Example ****/
/***********************/

/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return false;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return false;};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (not Pred_0(Args::value...))
constexpr bool fun(){return false;}

template<typename...Args>
requires (not Pred_0(Args::value...)) && (not Pred_1(Args::value...))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());

/************************/
/**** Second Example ****/
/************************/

/**** pun ****/
template<typename...Args>
requires Deceive<Pred_0, Args...>
constexpr bool pun(){return false;}

template<typename...Args>
requires Deceive<Pred_0, Args...> && Deceive<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<Vay<1>>());