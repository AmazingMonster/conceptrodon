/************************/
/**** Implementation ****/
/************************/

template<auto Target>
struct IsSameAs
{
    template<auto Variable>
    struct ProtoPage
    { static constexpr bool value {false}; };

    // This partial specialization will be chosen
    // if `Variable` is deduced as `Target`.
    template<>
    struct ProtoPage<Target>
    { static constexpr bool value {true}; };

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
using Metafunction = IsSameAs<1>
::Page<Args...>;

/**** Tests ****/
static_assert(!Metafunction<1.0>::value);
static_assert(Metafunction<1>::value);