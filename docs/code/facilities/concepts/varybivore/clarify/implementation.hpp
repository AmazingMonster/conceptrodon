/************************/
/**** Implementation ****/
/************************/

template<auto Predicate, auto...Variables>
concept Clarify = Predicate(Variables...);

/***************/
/**** Tests ****/
/***************/

/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return true;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return true;};

/**** fun ****/
template<auto...Args>
requires Clarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires Clarify<Pred_0, Args...> && Clarify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());