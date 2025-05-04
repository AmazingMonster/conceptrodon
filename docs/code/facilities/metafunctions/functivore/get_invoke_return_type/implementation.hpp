/**********************/
/**** Dependencies ****/
/**********************/

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

/************************/
/**** Implementation ****/
/************************/

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

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
    double operator()(int, int*, int**) const { return 0; }
};

/**** SupposedReturnType ****/
using SupposedReturnType = int;

/**** Tests ****/
static_assert(std::same_as<GetInvokeReturnType<decltype(fun)>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<AbominableFun>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(FunAddr)>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(&Tester::fun)>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<FO>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<FO>::Mold<int, int*, int**>, double>);
