/************************/
/**** Implementation ****/
/************************/

template<auto Predicate, auto...Variables>
concept AnyFalsify = (...||(not Predicate(Variables)));

/***********************/
/**** First Example ****/
/***********************/

/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return false;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return false;};

/**** fun ****/
template<auto...Args>
requires (...||(not Pred_0(Args)))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||(not Pred_0(Args))) && (...||(not Pred_1(Args)))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());

/************************/
/**** Second Example ****/
/************************/

/**** pun ****/
template<auto...Args>
requires AnyFalsify<Pred_0, Args...>
constexpr bool pun(){return false;}

template<auto...Args>
requires AnyFalsify<Pred_0, Args...> && AnyFalsify<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<1>());