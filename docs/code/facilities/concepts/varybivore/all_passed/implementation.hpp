/************************/
/**** Implementation ****/
/************************/

template<auto Predicate, auto...Variables>
concept AllPassed = (...&&Predicate(Variables));

/***********************/
/**** First Example ****/
/***********************/

/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return true;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return true;};

/**** fun ****/
template<auto...Args>
requires (...&&Pred_0(Args))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&Pred_0(Args)) && (...&&Pred_1(Args))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());

/************************/
/**** Second Example ****/
/************************/

/**** pun ****/
template<auto...Args>
requires AllPassed<Pred_0, Args...>
constexpr bool pun(){return false;}

template<auto...Args>
requires AllPassed<Pred_0, Args...> && AllPassed<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<1>());