/************************/
/**** Implementation ****/
/************************/

template<typename Target>
struct IsDifferentFrom
{
    template<typename Element>
    struct ProtoMold
    { static constexpr bool value {true}; };

    // This partial specialization will be chosen
    // if `Element` is deduced as `Target`.
    template<>
    struct ProtoMold<Target>
    { static constexpr bool value {false}; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr auto Mold_v 
    {ProtoMold<Args...>::value};
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<typename...Args>
using Metafunction = IsDifferentFrom<int>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int*>::value);
static_assert(!Metafunction<int>::value);