/************************/
/**** Implementation ****/
/************************/

template<auto Predicate, auto...Variables>
concept AnyClarify = (...||Predicate(Variables));

/***********************/
/**** First Example ****/
/***********************/

/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return true;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return true;};

/**** fun ****/
template<auto...Args>
requires (...||Pred_0(Args))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||Pred_0(Args)) && (...||Pred_1(Args))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());

/************************/
/**** Second Example ****/
/************************/

/**** pun ****/
template<auto...Args>
requires AnyClarify<Pred_0, Args...>
constexpr bool pun(){return false;}

template<auto...Args>
requires AnyClarify<Pred_0, Args...> && AnyClarify<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<1>());