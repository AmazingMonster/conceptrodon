/************************/
/**** Implementation ****/
/************************/

template<auto Target>
struct IsDifferentFrom
{
    template<auto Variable>
    struct ProtoPage
    { static constexpr bool value {true}; };

    // This partial specialization will be chosen
    // if `Variable` is deduced as `Target`.
    template<>
    struct ProtoPage<Target>
    { static constexpr bool value {false}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr auto Page_v 
    {ProtoPage<Args...>::value};
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<auto...Args>
using Metafunction = IsDifferentFrom<1>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<1.0>::value);
static_assert(Metafunction<0>::value);
static_assert(! Metafunction<1>::value);