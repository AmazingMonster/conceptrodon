<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AreSameVariadicTypeSignatureAs`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#are_same_variadic_type_signatrue_as">To Index</a></p>

## Description

`Functivore::AreSameVariadicTypeSignatureAs` accepts a function-like type and returns a metafunction.
When invoked by a list of function-like types, the metafunction returns true if their type signatures, including ellipsis, are the same as that of the previously provided function-like type and returns false if otherwise.

<pre><code>   F
-> Args...
-> ...&&(Args `same variadic type signature as` F)</code></pre>

## Type Signature

```Haskell
AreSameVariadicTypeSignatureAs
 :: typename
 -> typename...
 -> auto
```

## Structure

```C++
template<typename>
struct AreSameVariadicTypeSignatureAs
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value{RESULT};
    };
};
```

## Examples

We will compare a few function-like types to `int(int, int*, ...)`.

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }
inline int variadic_fun(int, int*...){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;
using VariadicAbominableFun = int(int, int*...) const;

/**** function pointers ****/
inline auto FunAddr { &fun };
inline auto VariadicFunAddr { &variadic_fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
    inline int variadic_fun(int, int*...) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

struct VariadicFO
{
    int operator()(int, int*...) const { return 0; }
};

/**** Metafunction ****/
using Metafunction_0 = AreSameVariadicTypeSignatureAs<int(int, int*)>;
using Metafunction_1 = AreSameVariadicTypeSignatureAs<int(int, int*...)>;

/**** Tests ****/
static_assert(Metafunction_0::Mold_v<decltype(fun)>);
static_assert(Metafunction_0::Mold_v<decltype(FunAddr)>);
static_assert(Metafunction_0::Mold_v<AbominableFun>);
static_assert(Metafunction_0::Mold_v<decltype(&Tester::fun)>);
static_assert(Metafunction_0::Mold_v<FO>);
static_assert(! Metafunction_0::Mold_v<VariadicFO>);

static_assert(Metafunction_1::Mold_v<decltype(variadic_fun)>);
static_assert(Metafunction_1::Mold_v<decltype(VariadicFunAddr)>);
static_assert(Metafunction_1::Mold_v<VariadicAbominableFun>);
static_assert(Metafunction_1::Mold_v<decltype(&Tester::variadic_fun)>);
static_assert(Metafunction_1::Mold_v<VariadicFO>);
static_assert(! Metafunction_1::Mold_v<FO>);
```

## Implementation

The implementation of `AreSameVariadicTypeSignatureAs` relies on dissecting the structure of the function-like types into return types and parameter types using the metafunction `Analyzer`.

```C++
template <typename Known>
struct AreSameVariadicTypeSignatureAs
{
    template<typename...Unknowns>
    struct ProtoMold
    {
        static constexpr bool value
        {
            (...&&(
                std::is_same_v
                <
                    typename Analyzer<Unknowns>::variadic_type_signature,
                    typename Analyzer<Known>::variadic_type_signature
                >
            ))
        };
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;

    template<typename...Unknowns>
    static constexpr bool Mold_v
    {
        (...&&(
            std::is_same_v
            <
                typename Analyzer<Unknowns>::variadic_type_signature,
                typename Analyzer<Known>::variadic_type_signature
            >
        ))
    };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQCspK4AMngMmAByPgBGmMQSkhqkAA6oCoRODB7evv5BaRmOAmER0SxxCVLJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Yk1TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpgprozIeJgKd8cX17dnAJOvyulxBZgAzOFkN4sHcTOC3AQAJ4vAD6BGITEICnh2FBoP%2B%2BzuV2YtCRAC94t8jsCCJgWCkDHS4QjkS9mGxcaDZsQvA5iaSKfFlMRUEQ2Zg4QB2KxSh7wqzXUF0hlMyXwxEoxisSUAJUwBFIdwlHMwADoLVdiMAceC8dceXyCAKxELiCKxWKtRr9QQIFabRazSsuUqZaC7pG7l4MkY7gA3Zp4Jj4ZDorWojLAZgETbq8EPO6%2B/3WhRBkPgxUguUK/HXFWMpjMjUmnVFg1G1tsIMB232q6O/kk12U92i8XehHF3tBo3l0PVqtR6Ox4AJpMpvBpiWZvDZpt5lmF6el2d3eeV/E1y9K%2Bv0xvN1la03tw3G586nulheD53Dsmjh6E4vD6BoloGForHcaAMLMC4mOG1zLjG4RromxDJqm6ZolmOaHvCx5gTOkG1mG8o3iCd6qk2%2Baauyba%2Bp2H7dpa352tyGJOi6AHCuOXogVORGnhac6QdBAhwexYZLlGKFxuhmFbthmC7vuubEPmhF%2BsRZqicGpHVuRVbKveaotsxkoAGIMD%2BnFDoKo4gHcKReDEtBbtxbpAfxmAatZuLSrKRl1lcDZmU%2B9FsHc/lSQOdl/g58R%2BQw%2BwLk5LluR5/5eXxErJQFCFBQZJnUXS5mRZKACy9LWUxFV3I0vIOHmtlNQlI5JQi1UsNZDXxXmIAgKlsXpa57nIJ5gG5ZObjdTF2CBQhwW3qFpk0eV2pRZZADyC4aQAjl4eAaV8B1HSdi1mAAbDtg2oC8mJEMQEAVkVDrxZNnVuDtaXOWNWWJcQGpYNCEoQOYN3bXdD1NiQL0VgthVLcVfyAmjQIEscdwAJKqvSjBNL01KHMChLo4CwIlQ%2BtFdpKADSDCoAA7jZsW/sSGlCDqABqG6pgAKlqQh7nhGkDleMmRmF60RZt5oWnIDAANaMyzfYRlG7PeZVnjoBrkZI0hy6a4THkwbMmCqCkxB3DEqCeOu3i%2BUbxuLS7rtRhAQYQxD4Pux7xuzOgg14AomY6qi8b6wHxsatHMce7Tn1Awiisq8zsG4oNCmbtuGa4QeGmkPHCfG0n2WjhqDMZ1nIA51hO4F%2BpztXKXsexW3Kwhv7UbIxRy598Z7vS2Vsuml%2BNoLshq53DrtDoEedza7rGo6VyFHRyPvlj5%2BCvK6rmcdybTZmxJdJWzbdsO3P6CR9Hhutx7XsWj711%2B4/CdByHYcKBHUc967OOACY7l0BhqNOB8%2BzZz5kpRuItC6YGLsAgOoCOopzcNXFmtd66wPzvA5uJdAFH1dl3e%2B15jLkJCmTcmpMsbYFUKwRkkofiY3JiwlahI7hUC8AweoElibnFBOEdyEQ7jhGdNwhgEBxFGnEfsEMMo7gaXUgwO4GgFTSnlNcYRCwxGCHXBhXOqJJHSMELIwQ%2Bx5yKOUZsVR6jKyaKoVjJgdsWDhBcfQLhPC%2BGwQEcCOSa4riuPcW5TAlkeGL3EaYt8cioLmwIAZAJdxeaGNTEE1AbjmChPCaogiei/QyPyZYsS8SUY3CxpInxzlUDiPiF8dhVwdGiKYF4Ig0UeFXHQOgG2hU4TXUkY4iiTTJQtLaSkxSyAcmdO6YFPpV0cFpgGYPJx9w0i1Jtm0tgSwbaVN6PUmkHE2p3H5p8OkQNpLR2GfkrxUjCmxPErBZ0vSbHEDsRo5G7srniIMRM4xPDonmIIMU4MDzZizJeW8hxHzDJlM4bsrIdxUAxG0HUAg%2BySaHK4j9C5nz9H3XiLDZ6KwAVFLiWfcFBpbFqPeTWMiZT2bjNztixcly8Uwyei9ElcjyygqedYylrzqVQtpTCjeqN7jVSaPCgQfjQRJMlUwaVDBUQaEXlaTAXM2CMoFkLfBeZxYIiiXcixCNEkzwVUq1EXA1Wcx5jA5AgsXjCzUvq20bgjVmKKRePEYryn3BObMdFgj3onzTEwBQSgWgQAtd43oKrBo3zvgiEGtAwaSIRq9DiobUThsjX6GNvC40aATbrJNbgU1gymV04gGaDKzGzbm%2BI%2BaDSKtjVkeNIBE1RwROkzJHiwk8NxJmkNjgw0RqbdGltlri2dtLd28tdRU1anBtdANZzBrpqHXW02Y682TqlW2gQHau1%2BV2naYdcUG3jqjWAMAs8p2HuVTOk9CJtVbh%2Bue%2BlO6c3XubQewt7auAlvnmWity6Fl/IYLWii9bR0/r3QWnxVrgO33nWBl4EA32TI6dW6DVZYNKUbVGxDcagOzpA/OrDvaQn0ByVumD36iN/tbQBo9ZGX0LtBsuiGa7Rh13tZBvDWa4NMf3SxpD7G50aiwx%2B7AF6CO7onbe%2B9/6JMobLbJ16HA1i0E4AEXgfgOBaFIKgTgbhrDWDuAoDYWx1QQh4KQAgmhtNrCViAAI4IzRSgCAEKUXAAhmC4AADiC1wLgZhpC6Y4JIXgLAJAaGSIZ4zpmOC8AUCAZITmjPadIHAWAMBEAgA2AQFyhoKAQDQAyOg8RIg6k4KoILV0AC0V1JB3GAMgCaUgzRmF4JgfAT08DBy4DIQQIgxDsCkKN%2BQSg1DOdILoEbTNMQpE4DwHTemDPzZS9tVppXEVUDuA15rrX2udbuN1swdwIAeCq/QHp9mVi8Cy1oNYEAkCVZSNVsg5XPvfZAMAKQZg%2BB0DOeliAMR5sxHccQJEa3eDQ%2BYLD7ayLUXw9IJVtgghtoMDJPNrAMQvDADcGIWg6XuC8CwCwQwwBxDZdIPgDS9R4yfHm5bOorSdgOdqVF4z7kYiYlhx4LA82MR4DixT0gLPiB2yUE8anRgRGgGy2sKgBgbTcw%2BEzba7J0f8DG6IcQU39czZUOoeni39A05QBZyw%2Bg8AxHS5ANY909mcCa0HAiphLDWDMMl6XGEsBO5el0HoWQXAMHcJ4doehQgLHKJUPQhRMgCCmH4EbyfehDAT8sUPqKGhzDT3oWoPj%2BgtGzyMKothC/R7yCN%2Bt5f4%2BV4kGsazmxtgt/0Jt0gSXeApaO41lrbWOtdckD167uBCAkD6eCLgT3HPOa7qQBAmAUyjBD25yQnmACc4IpRJEkBFq6CWAhXW3136LsWQCz7NFdLgV0gvb9C1dAIkh/O76uj37bnA0sZYXyr3LArd7IrPbVpcgSgP7e7WrNgTgZoFgeMKUJrJgaCAwOMLgbfM0LgM0YzfrKfQPPQE3cbI3aQE3RQM3ebXQYHZbJgVbCnDbDgfTL/enHbUA50VAQ7Y7IfFAmnC7DArA1VG7DJL7e7GfMwefF7HLYAyA%2BIcAirIQ/7aEGndArgZIGgVNOpSgSHenRHZoOHSXHQ5HVHBwdHTHAmHHPHenAnInEnWgMndHKnGnOnYzRnfPFncnHA1QDnOkdHHnebfnQXJEYXHYYzMXCXBzaXWXTAeXRw1CRfPgdXBQTXTAbXXXSXQgw3SbEg2QMgubC3EAYHVA4wW3GwfnYPF3FIN3DgD3AgPWAsb3KwSwP3PvAPIbVnZ3PPHxCPKPXIdPYISPCvbZJPdIFPbIWvXozPLIAYxPevbofPAQMvVoMY4vWY0vOYKY3PBvRYno4vNYpvQYufdYdvSbegxg3vEzTgAfE7NrRQtAvg7AifAbafcwWfcQxfNYFfNfBIEPKLGLUgOLcEDAjQSQbzbfKUKUcEQ/SQVrEbM4lLX/TLOIvLQrYrUrWQ6Q4gaAnYOA07FgBQeMCaeMdAs0NUWYPrR4/AkbdIibRIabHI83YzXQcEUgag2g9bC/U47/DgXbErVpA7I7HEvEgkokkk50QQu7KkZ48EV4gAqQ%2BQ%2B7NEuU0YfElIFISOdA1EEU1EVQVrEHdQ4gcHLQ4zAwvQhzY0lHFFYwyXUw7HXHPQ5wzAQnYnUncnBzBwxXYIynY6Vw1nendnZATnHwwQboPwh3AIoI0XDCMI3gCI9IKI%2BkGIowOItXJgDXLXHXRgPXWQIgzI2k2beknQa/K3RM%2Bo6we3R3eAcoyo3YL%2BEsxo/3eIQPNokPEvXoLoovEbOPMoZvDPYY3ods1IXsyYvY6Yjo3oBY/slsgvAYdYqvTYic3Yrs/Y1vGzDvA4qLDk5gi47UtrXE/EhMYUmiMFCASfJ6GfOfZ7N45fVfLAL4%2Bg34uLMwDA8EcEHzIElQjQZ8qUB/Jg5LH/WwP/CQpfTfK6HrSQQ/ILYE0LYLILL8i/cELbTc1Lf/V7eg3rH8vvP8wCtYaXDIZwSQIAA)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/are_same_variadic_type_signature_as/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/are_same_variadic_type_signature_as.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/are_same_variadic_type_signature_as.test.hpp)
