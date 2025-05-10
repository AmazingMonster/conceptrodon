/**********************/
/**** Dependencies ****/
/**********************/

#include <concepts>
#include <type_traits>

/**** Analyzer ****/
template <typename>
struct AnalyzerPrototype {};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...)>
{
    using variadic_type_signature = Ret(Args...);
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args..., ...)>
{
    using variadic_type_signature = Ret(Args..., ...);
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...) const>
{
    using variadic_type_signature = Ret(Args...);
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args..., ...) const>
{
    using variadic_type_signature = Ret(Args..., ...);
};

template<typename Fn>
struct Analyzer: public AnalyzerPrototype<Fn> {};

template<typename Fn>
struct Analyzer<Fn*>
: public AnalyzerPrototype<Fn> {};

template<typename MemFn, typename Structure>
struct Analyzer<MemFn Structure::*>
: public AnalyzerPrototype<MemFn> {};

template<typename FO>
requires requires {&FO::operator();}
struct Analyzer<FO>
: public Analyzer<decltype(&FO::operator())> {};

/**** TypicalGetVariadicTypeSignature ****/
template<typename Fn>
struct TypicalGetVariadicTypeSignature
{ using type = Analyzer<Fn>::variadic_type_signature;};

/**** GetVariadicTypeSignature ****/
template<typename...Args>
using GetVariadicTypeSignature = TypicalGetVariadicTypeSignature<Args...>::type;

/**** GetInvokeReturnType ****/
template<typename Fn>
struct GetInvokeReturnType
{
    template<typename...Args>
    using Mold = std::invoke_result_t<GetVariadicTypeSignature<Fn>, Args...>;
};

template<typename Fn>
requires std::is_class_v<Fn>
struct GetInvokeReturnType<Fn>
{
    template<typename...Args>
    using Mold = std::invoke_result_t<Fn, Args...>;
};

/************************/
/**** Implementation ****/
/************************/

template<typename Fun, typename Result, typename...Args>
concept InvokeResultIn
= std::same_as<typename GetInvokeReturnType<Fun>::template Mold<Args...>, Result>;

/***************/
/**** Tests ****/
/***************/

struct FO
{
    void operator()() volatile & {};
};

// This will fail.
static_assert(std::same_as<std::invoke_result_t<FO, int, int*, int**, int***>, void>);

// This will also fail.
static_assert(std::same_as<GetInvokeReturnType<FO>::Mold<int, int*, int**, int***>, void>);