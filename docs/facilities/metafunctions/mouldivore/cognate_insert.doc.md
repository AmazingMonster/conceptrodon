<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateInsert`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-insert">To Index</a></p>

## Description

`Mouldivore::CognateInsert` accepts an operation.
Its first layer accepts a list of elements.
Its second layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function inserts its arguments into their corresponding positions, which is indicated by the index list, of the previously provided element list.
Then, The function instantiates the operation with the inserted list.

<pre><code>   Oper
-> E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>m</sub>
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>k</sub>
-> Oper
   <
             E<sub>0</sub>,
             E<sub>1</sub>,
              &vellip;
       E<sub>I<sub>0</sub>-1</sub>, Arg<sub>0</sub>, E<sub>I<sub>0</sub></sub>,
       E<sub>I<sub>1</sub>-1</sub>, Arg<sub>1</sub>, E<sub>I<sub>1</sub></sub>,
              &vellip;
       E<sub>I<sub>n</sub>-1</sub>, Arg<sub>n</sub>, E<sub>I<sub>n</sub></sub>,
              &vellip;
             E<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateInsert
 :: template<typename...> class...
 -> typename...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateInsert
{
    template<auto...>
    alias Page
    {
        template<typename...>
        alias Mold
        {
            template<typename...>
            alias Mold = RESULT;
        };
    };
};
```

## Examples

We will insert `Vay<-1>, Vay<-3>, Vay<-5>` to indices `1, 2, 3` of `Vay<0>, Vay<2>, Vay<4>` and invoke `Operation` with the result.

```C++
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

template<typename...>
struct Operation;

template<typename...Args>
using Metafunction = CognateInsert<Operation>
::Mold<Vay<0>, Vay<2>, Vay<4>>
::Page<1, 2, 3>
::Mold<Args...>;

using SupposedResult = Operation
<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

using Result = Metafunction<Vay<-1>, Vay<-3>, Vay<-5>>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateInsert` by combining `Pagelivore::CognateSegment` and `Omennivore::InsertValues`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<std::make_index_sequence<I>, std::make_index_sequence<J>...>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many elements we must pass to reach the first target position.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub>
-> Capsule
   <
       std::index_sequence&lt;0, 1, ..., I<sub>0</sub>&gt;,
       std::index_sequence&lt;0, 1, ..., I<sub>1</sub>-I<sub>0</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>i</sub>-I<sub>i-1</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>n</sub>-I<sub>n-1</sub>&gt;
   ></code></pre>

`Capsule` is a vessel holding the results. It can be declared as follows:

```C++
template<typename...>
struct Capsule;
```

Finally, we will transfer the `std::index_sequence`s and relevant arguments to `Pagelivore::CognateSegment`.

We will use `Send` to connect operations.

```C++
template<typename...>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

Here is the entire implementation.

```C++
template<template<typename...> class Operation>
struct CognateInsert
{
    template<typename...Elements>
    struct ProtoMold
    {
        template<size_t I, size_t...J>
        using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J>...>;

        template<size_t...I>
        struct ProtoPage
        {
            template<typename...NewElements>
            using Mold = Send
            <
                typename Send
                <
                    typename CognateSegment<Detail_t>
                    ::template Page<I...>
                >::template Road<InsertTypes>
                ::template Mold<NewElements...>
                ::template Mold<Elements...>
            >
            ::template Road<Operation>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIGYAHADspAAOqAqETgwe3r4BwVk5jgLhkTEs8Ykp6XaYDnlCBEzEBAU%2BfkG2mPblDK3tBJXRcQlJabZtHV1FvQqzoxHjNZP1AJS2qF7EyOwc5oERyN5YANQmgW5ejrSEAJ7X2CYaAILHp%2BeYVzfIS3QWCoLzenzMJwYZy8l2ubgIjwymAA%2BgRiExCApQR8wQB6ABUhPxF2wqgIrgAYsRZBcifjcWDySwMgZyXCEUjmGwAHS87HvJbELwOElkynUwRXVJWVIAEWuVhxHyZLKYbJuKtZmHZiMYrEwvO5LwuZyYCgUFw8ggxkTIFw5ep5vOw9DYgixgVeH0FwoIovJDHQVNkcKtbVWxDhLswboICkNoM9YJM0rBF3T9pjqvV8N1XINvKimAA7tHYx6ve8MxcvDkjBcALKedB/WWW2Q2hJwoul12MOOG0gkvvuhNJwKKz5yhXJ5VZrXs%2Bdq7U3Jh3VBj7Amgzmi5CTAARy8jAOQ7XRENADV2ngmLF6BWwT6RaSA0GJQQ4fujyeV25r8Qt73pg8Z8uOlYppO1aasucLnhuvIWJgwARAwETAI%2BHzVrW6EXMoTDAL81xtt%2Bx5Qn%2BSEoQwaFGKB3JDgBQEPpuM44tOE6zu8BJEnhxCYDQqi0kSDJzsyC4anm%2BpDjkABeKKfkmHxoORGR%2BsofECa29pCiuk54nSlpMBkChePQQmEiJ7wwTmDr5ix3por6hnGaZumcdxhIXAAkgwSgdAAKrqFp0pZ1l/rZ%2Br2QKjkij5fkEIFSIWpBKbyhxSpcQZFhmr8bg5eZ9KMkuObwYaXn8s%2BfpxQkCVBXCgIgCAERYKoyJKD%2B5Fwl5LGKVOUEZmFOqcvqFw9mW/ZDhFTpGr11aVbxqBEE2tDoGmGYpVh1YDcV2qbVtfxuGt%2B3VriuIXAA6r8tZEQAbBo6n8XgqhdS8CZ3faqAXIwPgJMuVx3cGgj%2Be0hFxiYd1Gntx3pg9AkvZ6hqAwlIOYHGpBHdD9qSdN2XIAA1sDxCg1iUPVvy0NLGqeDICaAhLJgABuYgXPBFx4Ogjy0BAmwY9WAC0xp5S59C8%2BtNyi/tSOE8Tg4S1tY0jgQ6Ok8duMEyjA58ir6aJnp2uZmJsEScN03vMAfExv2mFVsdOH1stLbERcWBnA6EDs5zcJmxb5abtzPPpTbOvsXrQcG9m4XYwW3Le5glvuuTGZ28AjbNlp6mLagDte%2Bbce%2B2BryB6lrGfKJEdweuZVnpXvIAFIVTFVW%2BTViUgfVBDoI1zWYK17VkQcXWbtJHdd4GPdtYe/d/rXPUQamUODcbjq/BSeDEEsCvx0rWMm78%2B7Kegm%2BxpNUdRXNjcLUtzYYxtYfQTtctwnLJ1nZdNZKP990aU98PYG9GgfS%2BgwH66JySfylhrLEENn4Zlhj/G45UEa8ggUTVGChlZ32OqdC6V0P7gy/o9Z6Nx65IKNO9IgFxgCfSYMgaku4CAIF%2BPgSmnV9YvwuPEAgxY44MHtMWT6swZYwJht/IhbgSF/15A2dm6B6DSzQRgzGA1T6IRoerVBYN9aJ32pTRwNNlL0yZrQFm642Ycy5jzfWAtPTORMiLLR4s2EZhQTLXkiilEXFXuvAgR8JrCMbDIuRkDZZOPTPvAQh8SzjUEO4pRat5Ga0hpgnW45Q7Q0XrmXehpY5b2ttDZOqcVpaRdrQN2HtaA5x9lbP2mwA79WDmlNJ21DY2RUTHXOuTtHv1wg7dO1Ir4rUqXnapBcS7FyLh8DyxIABKTQ9g5AZrlfKIUiotL/KVXkXlq4XjrifLJvIADyDCEikV/Nbea1UAp1RuA1JqY9e6T1/IPAuw9O53JahPDqA9iFDwuEcxhxBTnkTovyW%2B981lDWXp4teG8omKz2VC8JgZfExJ3svQ0/yEgorBrNDM80M4DNWlDMFx1BoOMOqEi42C37XU/nAsRiDJFkIARQ76bBQG3Q0C4tB%2BCkkeN4oQ3%2BiMPwJPQf46luDOX0rhBI/%2BgCqEs1odkC0xznZ4BYQPSl2DOHcMYHwgRwT/HSuIa9KRgTMCitiZjKa0d4mQMfrinRbQ9G018uSIxJiKHlO5nLaxW5XzihDOS/xNrvLNyuUlOEmLAWPOBWfDxjUwqFNWjcaN2KQWOsxomnaya4R2o0Rmys0MunVmzWs3NwbKXcsSVa6GXjYW9i3rW460igRBILSE5JW0kWRMbbGB1hcmn7QyTa7JHTywlqTnWFOvSnYlLKeYoZuSal1JviHTi4Ly5LzsryHJE7M0FNnYENsBKs7XxuHukZM1B3JnXRlKZFxErUzEMoVAGQCqhQfquGu16nwXyEAgO4BARYTKsl%2BvKP6G5ChFE%2B0QtBX3vpSne0uYGIXfoofWhSlZ5qwZfW%2BuEmHQXzzDgUh0WkANAZA4dVJt7GmcQyazTD2zPo9qg05XD8H8M3CY3uJoESiP1O6fWMjTsKMEGA3%2BQjNG2J0Yygx0xPHWY9uYxi45682MwcRM%2BzjGQCMwu3spv5anC23sE6R3UN9j3%2BkDYISF%2BZH1abgwhqNxnNyJos5mstEc8IEUk/pocrHpNTlkyhh9%2B5AwftWVuzJ6LRkOWg36cLjtUzIai%2BJeE4HR0F23GaC0YZOx2iy9yaJOLsP/tcKGDsEYoyKxM71El6YR2ZbacaU0u4DlIlAXkLp81ZSowxBU4lxH8nTrRVpDrv1Bg1eXaMwOZNUsL0y81/Z16cvmjHVUhOB7RvTNQEwR2Vm%2BvhgqRe8dV6XjuaRGMhbqHovyZ2attrFogWnk9QhbkjE7wPg04lirNwXt/k%2B8BOrc9BNNbQxBh7rWdwWgm11gQPWL5HYG2uwT2FRsias3DqmCObhA%2BYrNwT4yh3h3S/d970PcsbeGVtotU7cLTIG1pZHdAl352vZdtyMmxmTIMh4YAzByT7mALGSLZcyfgY2Y9mHfzOs44YD99sAvlzC/7WxMH4HZLyW8tJPAclUSGgkRjXr/XWdDbR806LWuDe8gANKTvTHxI8a8QIXAgAmMwN1zA3QgLbg6Fxa61LlgUgAEjIxgqJxty6mwgoctc%2Ba256kTm7m70tS8vbTjGBT8KEXI39mL9mOPOdO5txJF2QAOi6V5rUFxGes5uCzk7bgM9l89NXv6YegQR6wzzriZ0fL4AOBaUQvCxAKE%2BvEC4GRcuYBbAU/Btzu4PK%2BdqaBi2Ic2sRwli4nesC8KQyFjGGTrdVV1/rgghut9OV34wdubyl%2BfKnl1OPs9Udy2P3r%2BShp7eZurE7rwLuFo7ufInu3uvu/ugeliXaBSjekeTs2OMebgWyAeCeSeG6tsGOuoeegYdmI0ReXGSBL%2BBcnODuFw7eYCdeTesBPec260KeluZObSLeeS9O9sacTsN%2BCuJeNOre2AJBRcN2D6/OgumAlyfoKy4uRsGWG%2BLWNiT2suk23WvU80why4YhpmR%2By2sWxWtWV%2BIop62c5u7%2Bmun%2BkeyBJ%2Bl%2Bv%2BrBKc1BWkQsdif4tyLATAeMKID%2BfcTyCCLwryjUzhrhyI7hsa3y4ipqv6oG6SJh5%2BZUpB%2BK/SqAOeu0XaDW1qWhO63I6apB6OPS7BVmSW/iT8lK0EUcvGOBhRYsFKXa/KoaqhQuyE/aDeputAqImRCaFeOaCRzyv6ZRKSfBbR5au2%2B2XU4atUkaVhSi5Bvw2cNw6a8a/K6YExuaNwJWJmlKLR8xfR3mAxKabgCBShN6Wi9Bw6kuP6zBpB2evmfSmcHR3BM2YRyeh%2B6%2Bd2TBZ2meUMh6ORJ6cRUxzeLxvB12DxmUdIQJQJlkD6/kIEcYYugJwJMJlkyYEI3wMIRENwdwdATwoKkhJUpijKf62%2BTYDAmcDAzw6uFwui1Mrq9MqgGQxAb2FwRix4UoFg5UIcUoAJI6shZW2%2BuxuOoc7JK27wRM1sh6/WVAXgUIgwdhqAyu5I6hqa0eexYIjU3x%2BJhJzwNwGg3hqcBJRARJcIZgmpKpOpapbgkgiYlYjU1xbgXAQ4ZgQ4gQ/ISp56zegpaBGUBSQgXgGQpQs%2Bsydifo8B8pCOOINwhpAgxpGpnoQ4oZupNwfMXABpAgqpepCZ2pYZcIfM9pkZWpSZNwppWZ0ZxpfM/gZpveBSvppk/pVmDYIpYpzQuObgBZ6Z8Z%2BZiZRp6ZmZ2AUZrZaZsZxZ4EveZJyAyIM%2BHQEAtyCg%2Bow5HobgHpXp2QPpIEFZQ45ZpSLwdSHA2wtAnA/gvAfgHAWgpAqAnAh0lg1gpJuw%2BwREEIPApABAmgG52weMAQZg3IqQZgkgyQyQ/gGgAAnP4GYBoDdMkMEFuRwJILwCwBIBoBoKQHuQeUeRwLwAoCADBXefuRuaQHALADAIgCALsAQBkHcOQJQGgMyHQFivqJwKoMkDdHzDdJIJQsgDTFINyGYLwLPoQCQOzHoPwIICIGIOwFIDIIIIoCoOoOhaQLoNacWOiBkJwDwJudubufeYeZwAcncIRX6KgFQBcNRbRfRYxcxZIKxW7h4GRfQDSccFwJsLwGhVoNsBAEgKRRkORWQBQBAM5a5SAMAFILaTQKUgkMhRALECpbEBEO0I8PJbwGFcwMQI8AcrENoE0GhTeaRbGAcgwLQJFRJVgLEF4MAHlLQLQMhdwLwFgM4UYOIDlS7s0IsiVQeT3HMuSFFeQIIP0CpQ8LEOiHFR4FgCpWiHgJBaVaQIssQLEPOX1hVcAA8EYPedsFQAYBhJeHgCWBNnuTebxcIHBoJdIJtaJWoCpVJfoIYMYNYNYPoHgLEMhZANsG%2BoMCVXzICMRKYKeZYABbwKgKNYBFgNddzH0AMHkC4IGPMH4NaWEKsNULUHoKULkAICDdDdkLDQwGMJDZMNaY0HWUMMsPDejf0MlS0MsCjRMIkOjdjZ4N0HoJTB0ETesCTdsOPnsAcBIIpRwDubBSpQhbpTRXRQxcAExRcCxWYG7rgJxZZdeTZbeXNdsIwvtpMH9U%2BZIIENyD%2BYEKkJIBoJIO%2BXdBoP4DdD%2BfoJwOBaQJBYEFwNyDdFwEBT%2BckJbf4JIFwP4CrTdOzRJQhUhShZLehQ5ThY5XhRpURe5Z5RZVEJRRwO0CwAzKkHzEwDlvWFwD%2BdyGbQ1fgEQN9TxbIPxeIEJXtUoAdRJboLaTJUZFFSzWzXBR9Wpf7VpTpeHZHdHbHSnPHYndyAAhAGZS5RZVcBCGYBLXZRhb7UHQkMRR5agOZZMLXVHaaEYPHVwDBf5eSOvJQCFRJTFRFS1avXFQlUlQ4C1Wlf2BlVlSpblflYVcVS1eVSdVVQefgHxLVSBCpY1cgHcIcDeREOSKBQeZ1d1Y8L1YcAeQNUNTeaNeNUoJNZfehHNXwItQoMtatZyC1ZtZnTtcJfILneJQeQXcdbNS9VYJYBdVdfALdapHkA9U9cejg9YO9YeV9ezPfTdf9fjc4BAK4DjSEIGDTVDdaTDYMKw9w3kBw2jQw5jcMHMOTUULjQDQICIysFUMTZTWTYUKDTMCMAI3TTsIzYJaXcpa7ZwCzMQBHVHTHVPY3QnUncLSnSQF3abb3VLaQDLVgIkH9aBUbSbQnRrakI7akKkIEJrZIPRdaeXapYhbYB7X3d7fAL7fhZpcPYPcQCHWwJwOHQZSwAoAzDTAzE3VqEsOxRY2ndaYg9tRILtbIPtegzoCAMEEXXJaVVoy7fBZXQRXcBcNpXoywMk6k%2Bk5k8uEsKZaPR3QkFY4EDY17ZhU5X065TE%2BMxZSAGk16ciBkz%2BciFkwQMOfo/RXwHQAvUFcvQeRvdlTeXs1vclbvaPelZldldfZgHlQVWIGfcNRfZVX/WVTVY4HVQ/aoE1S/bwG/e1RJV/RFb/f1YBIA7wMAxNTGOA7NSMwtQRDAytcWGtQgxnYU9nSU2g4dRU1g6da9TYJ1b9UQ/dZwLiA1BQ29fBTQz9YQ0I4MEDe4GI0o%2BDbI7TQjWUHkLw4jYMKo5TXjcIwoxTRI4w1jSoxDXI6TSMKw1TTI2sJw/TReUzdZQbazdo/UxwK0%2B02k3SV0%2BSD0xACLanVY9ZbZbY/Y3LSzS40kAnYEIEP4N%2BfbdBVa6kEBXUxXcE8hahbYwrakKxR41wFID%2Be4yrVwOkKBYEMqy60a17SzWxc60ExG/ZdsKNTkM4JIEAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/mouldivore/cognate_insert.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_insert.test.hpp)
