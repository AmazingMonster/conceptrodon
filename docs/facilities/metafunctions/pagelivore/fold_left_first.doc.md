<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::FoldLeftFirst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-fold-left-first">To Index</a></p>

## Description

`Pagelivore::FoldLeftFirst` accepts an operation and returns a function.
When invoked, the function left-folds its argument list using the operation with the first argument as the initiator.

<pre><code>   Oper
-> Init, Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, Arg<sub>0</sub>
   &gt;::value, Arg<sub>1</sub>
   &gt;::value, Arg<sub>2</sub>
      &vellip;
   &gt;::value, Arg<sub>n</sub>
   &gt;::value</code></pre>

## Type Signature

```Haskell
FoldLeftFirst
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct FoldLeftFirst
{
    template<auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };
        
    template<auto...>
    static constexpr auto Page_v 
    {RESULT};
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
/**** Subtract ****/
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A-B };
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction 
= FoldLeftFirst<Subtract>::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<1, 3, 4, 3>::value == -9);
```

## Implementation

We will implement `FoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class Operation>
struct FoldLeftFirst
{
    template<auto...Variables>
    struct ProtoPage {};

    // Base Case:

    // Fold once.
    template<auto Initiator, auto Variable>
    struct ProtoPage<Initiator, Variable>
    {
        static constexpr auto value 
        { Operation<Initiator, Variable>::value };
    };

    // Fold twice.
    template<auto Initiator, auto First, auto Second>
    struct ProtoPage<Initiator, First, Second>
    {
        static constexpr auto value {
            Operation<
            Operation<
                Initiator, First
            >::value, Second
            >::value
        };
    };

    // Recursive Case:

    // Fold twice, handle the first three parameters,
    // and recurse using the rest.
    template<auto Initiator, auto First, auto Second, auto...Others>
    struct ProtoPage<Initiator, First, Second, Others...>
    {
        static constexpr auto value {
            ProtoPage<
                Operation<
                Operation<
                    Initiator, First
                >::value, Second
                >::value, Others...
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxCAA7NIADqgKhE4MHt6%2BASlpGQKh4VEssfFJtpj2jgJCBEzEBNk%2BfoFVNZn1jQTFkTFxidIKDU0tue0jPX2l5UMAlLaoXsTI7BwA9ABUO7t7%2Bwe7GyYaAILbuwDUAJIsyfRsgky1DJd7x2cXh9%2BHH6cnpwImDuBiBJgAzG4gSDnpgIW4mF4iAA6VEQ7CXZAGBQKS4AeWScWemXRAJGxC8DkuADFPOhgpgqARqXhiCMASYElYzpdeZdofdYfDESjUQA1Rp4JjRegKUk8vnkykES7KYioIjKJjATCXTlWBIAEQh3P%2BCt5Gw2lwsTCUlwRShAHPNl0tNLplwEa2RAL5/OBgrBkJFqBuDAyzxIpEuIcuEuIUplcPB2F9ioIFKpao1qC1Ovh13DjkjZDjkul9Hlpz9%2BrTft5U0cyExAhGmFUyWIMaRoYAbmIvLq6/X9fjCcRiQIC0WpURS/HE5WUyAQP3vEOjSbh5zjeDTcO3bTaOh%2BQB3PDe4cC0HJhE9sMRufR2MstkEZ/3oSYNAMdBVv1Klm6qatqt6Fo%2BUY0qyIzRl%2BP5/im25csOAENE2LYMG2HZdrGa6DnqyEuvWfIEkSLzwihxFjmRJKQpRVF8uBxZPlBb70SOy6rgOmCwd%2BAh/kRVHoiueFwoJvI7luLqSXuzrVnyboAErfis6S9rqDrsHJfqHh6BDnms0YIIY6D0PyCC6jQb7mcQmC6skjSsJgQJsqQB5WiZly2cgqm6l46RGOZuq2SMPouteQrBveTGzpBL7Qe%2B3ZEJccH8R%2BorIniBAWWy/7ppmKrZiB%2BaQjFJbRq%2BMEpXxv7RllOUKKiPqIdJhHycRjYXhhWGdklfbcQRpoMX6RW5qBFHicNpETuRdGTQx02TgwE3tcNDFlSxlUEOxDHCVx668fBO1CZxol1dlcSNWi818ntonsTJQ23ZuslnFeAY3sKPZNacwC2cCjAEHKLWrf5YTAKqoF6uChqqsBY0lW4v3/Y8QNNaSr3/C9%2B6fD83x/F8WyXNgqisPcurvAChN40ccmEylXjRBmTBUpTZwRUGd7Jac6WhlYIOASqQiM8zDgcm1qHEs2P49Th973a1FiXKcAC0SuPeLu44%2BceyXAAss5TBUF4DAOJkby0%2BzH2RVzqA/cQwDA6mZxg4FBsNMbpsvHqb0w%2B6x4MkyW3wsLTMTmLnF5repwO1dzWppjVO6wAKpgIwWzsfydcgAD6tpKE0EDu0bJtm1OkJcNG4LRtIlzgndA0QrusMqwAnPMJocIstCcP4vB%2BBwWikKgnBuNY1iXAoyyrEOZjgjwpAEJoXeLAA1nkyIaAAHGYZit63XD%2BNvW9cAklQ9xwki8CwEgaBopAD0PI8cLwCggPfS%2BD13pBwLAMCICAZYBBkhInIJQNAdw6BxAiE5Tgqgt4ADYVYIMkJcYAyBmxSGRGYXgmB8BzjwOgPQ/BBAiDEOwKQMhBCKBUOoL%2BpBdCV1PBOZInAeDd17v3Zew9OB4iRCAlUqAqCXHgUglBaCMGXCwWYS4EAPCQPoF2cw895i8E/loRYEAkAQOSFAsgFAIA6L0SAYAUgzB8DoC5N%2BEBojcOiGERoABPNhvB7HMGII4vE0RtDfk/gvCBqM8QMFoM4%2BhWBoheGAAiWgtA37cF4FgFghhgDiDCayXxeB1JxKHu2FSQIXHkEENUbhtA8DRAnB4jwWBuEZjwDfeJpB1LEGiGkTAhpgTJNKUYZeiwqAGEdmKPAmBTykQHgvEhwhRDiEoRMmhahuGMP0MklA49LD6DKW/SAixUDJBeHElWIwEKGlMJYawZgn5NITFgTZEBFh2Ayc4CArhxh%2BEriEMI/QyiDErqkdILwXl6F%2BYUBgMwBjxErvcsuDBuhjE8K0PQkKXgwt6B82Y3zbCjGaHC3IELMWgq%2BeCu5081gSA4RwPuD9uHPxEYg5BqD0GYMkNg2RuBCAkD1HPLgqjF49MWBZJgWB4i3NIOvSQ4JkSt3BEkDQkgzCSAQXffwCDW76E4FfUgN957IgQVwBBW9W4nwQYEQ%2BkqEGUvoc/V%2B78eVf00f/LRgD%2BGgIMUYxRMC2CcEaCwXsCQVZMExAYQKXBW7Ii4JvXB%2BCSCEOIbIMh0zpCzKUPM%2BhuhzHMKYKw%2BJZKKWP14M/PhwCkSemEaIulAbklSJDWGjQsj5G6MURy8EZhuXqO/g611cQwGGNQAowYWJknBq4PfGgtArGUFsfQtxTiClTo8V4nxDgCkBMBkEkJ3DwmROibEgpiTOnrCHvgbyjgsncNyT5fJDSwhAgvkPUp5SnFVP3WohM9SF5NJaUodpSSjBdNALavg/SFCDOGaMgpEy40UITbIOZdCh6pqWd0k5Vg1l3puds3ZmR9mHKbkhs5Fy4hXLTvAO51QHl%2BCeb%2BAFbzfz4rmD8go/zsWvNIECl4tH0WIq6JiqjHQyPIvY%2BCjFPQeNTCaAJ0lSwVgkq5aq8lXCLWcBpWI1B/ag1Vs3iyyNSjOUtt5aQflgrKBkvVZqkNMqEj%2BFbmfcEsr5WSErrmnhL9bDWtbXa%2BADqgECK7R24g7r1hevESwBQvZmy9mDciG8IwI1squTG0hUzINUPkEm2DOgQDV3TZm9hsmc1Ut4U6wRJagshbCxFqLKo5E9vrXERt4JdP/vbdVvRPnmuKNXMgZIyQc7hdbjnCrOdVAoIsaOy6467EOI8TOybnjvG%2BKXT2wJwTQkHswBEqJYht0NN3T%2Bp9pBD0ZJPfQs9SJ1gLyvcU%2Bhd6KmOMfTUl9BT32tK/Z08GPSAPaiA0MkZhIxm8HA4liQUHqGpYWRlhDxhVk2FQ8R4eGHWycA2IclZpzLDnLzZcwhRGtm8ahS4SjTG9DvJKGCwFDHMg8dY5kcTELSNQuRSJunSK8WotJ7i4ThP2didZwSiTU8pMUOzfJp%2BimhuoOC6Fy4vXIuwnThAVlc5G1crUXpgzgxhUXxMyAPeyJwTgn8Efezd89cJD1eakXzm34fz06K/wErT4JDvlvSQB8uA7zMGai%2B4Jhd5s4Cr21ZKcHm9985tziwmnpGcJIIAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/pagelivore/fold_left_first.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/fold_left_first.test.hpp)
