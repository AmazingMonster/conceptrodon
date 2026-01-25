/************************/
/**** Implementation ****/
/************************/

template<typename Predicate, auto...Variables>
concept AnyPassed = (...||Predicate{}(Variables));

/***********************/
/**** First Example ****/
/***********************/

/**** Pred_0 ****/
using Pred_0 = decltype([](auto...){return true;});

/**** Pred_1 ****/
using Pred_1 = decltype([](auto...){return true;});

/**** fun ****/
template<auto...Args>
requires (...||Pred_0{}(Args))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||Pred_0{}(Args)) && (...||Pred_1{}(Args))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());

/************************/
/**** Second Example ****/
/************************/

/**** pun ****/
template<auto...Args>
requires AnyPassed<Pred_0, Args...>
constexpr bool pun(){return false;}

template<auto...Args>
requires AnyPassed<Pred_0, Args...> && AnyPassed<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<1>());