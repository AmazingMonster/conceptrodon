/************************/
/**** Implementation ****/
/************************/

template<typename Predicate, typename...Elements>
concept AllConfess = (...&&Predicate{}(Elements::value));

/***********************/
/**** First Example ****/
/***********************/

/**** Pred_0 ****/
using Pred_0 = decltype([](auto...){return true;});

/**** Pred_1 ****/
using Pred_1 = decltype([](auto...){return true;});

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...&&Pred_0{}(Args::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...&&Pred_0{}(Args::value)) && (...&&Pred_1{}(Args::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());

/************************/
/**** Second Example ****/
/************************/

/**** pun ****/
template<typename...Args>
requires AllConfess<Pred_0, Args...>
constexpr bool pun(){return false;}

template<typename...Args>
requires AllConfess<Pred_0, Args...> && AllConfess<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<Vay<1>>());