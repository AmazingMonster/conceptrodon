/**** Pred_0 ****/
template<typename...>
struct Pred_0
{
    static constexpr bool value {false};
};

/**** Pred_1 ****/
template<typename...>
struct Pred_1
{
    static constexpr bool value {false};
};

/**** fun ****/
template<typename...Args>
requires (...||(not Pred_0<Args>::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires (...||(not Pred_0<Args>::value)) && (...||(not Pred_1<Args>::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<int>());