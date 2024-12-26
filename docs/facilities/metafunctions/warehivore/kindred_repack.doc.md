<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Warehivore::KindredRepack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#warehivore-kindred-repack">To Index</a></p>

## Description

`Warehivore::KindredRepack` accepts a list of packed warehouses and returns a function.
When invoked by an operation, the function concatenates the packed warehouses and instantiates the operation with the result.

<pre><code>   Ware<sub><i>0</i></sub>&lt;Cons<sub><i>0</i></sub>...&gt;, Ware<sub><i>1</i></sub>&lt;Cons<sub><i>1</i></sub>...&gt;, ..., Ware<sub><i>n</i></sub>&lt;Cons<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Cons<sub><i>0</i></sub>..., Cons<sub><i>1</i></sub>..., ..., Cons<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredRepack
 :: typename... 
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredRepack
{
    template<template<template<typename...> class...> class>
    alias Flow = RESULT;
};
```

## Examples

Here, we first concatenate `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>`. Then we pack the result into `Warehouse`:

```C++
/**** New Vessel ****/
template<template<typename...> class...>
struct Warehouse;

/**** Vessels ****/
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

/**** Items ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** SupposedResult ****/
using SupposedResult = Warehouse<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result = KindredRepack
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>::Flow<Warehouse>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Warehivore::KindredRepack` is implemented similarly to [`Warehivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Vehicle`. After all containers are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<template<typename...> class...>
struct Vehicle;

template<typename...>
struct KindredRepack {};

// Base Case:

template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
struct KindredRepack<Warehouse<Containers...>>
{
    template<template<template<typename...> class...> class Operation>
    struct Detail
    {
        using type = Operation<Containers...>;
    };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = Detail<Agreements...>::type;
};

// Recursive Case:

template
<
    template<template<typename...> class...> class WarehouseA,
    template<template<typename...> class...> class WarehouseB,
    template<typename...> class...ContainerAs, 
    template<typename...> class...ContainerBs,
    typename...Others
>
struct KindredRepack<WarehouseA<ContainerAs...>, WarehouseB<ContainerBs...>, Others...>
{
    template<template<template<typename...> class...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Vehicle<ContainerAs..., ContainerBs...>,
            Others...
        >::template Flow<Operation>;
    };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIa0gAOqAqETgwe3r56icmOAkEh4SxRMVxxtpj2uQxCBEzEBOk%2Bflzllak1dQT5YZHRsdIKtfWNmS2Dnd2Fxf0AlLaoXsTI7BwA9ABUm1vbO7vrqyYaAIIbWwDUACKY8a6MyHiYCmfbB8enex87r0eHJ9tnADVMAg8Mh6M8tt8CJgWPEDNCTABmNzQ2HwzBIlEATxuzDYADpCUjsGcwUwFApCfjib9BsQvA5AcDQfQkVZjr93p9uZtvlyzgBJNEwxi1KoQ3mcnnS/a/X6ouFMBHIgg4xisTBUmnHOkMghnADSwXQxEw6AAStcmMgANZnEwAdisDoubLlb1WZws5MwZzcPpA7qOCvRmJDSoxKphiuV2NxGq1iJJZIpieTBgpZwA6nVgQslKQzuHY6r4wSiUnSRnKYSPIImMFogptUddYyjQwTWbLfFrTbMTnTQh85G3HXao3iDXqUmW472Uczkui9HQ1G0RGw6vNyq1XjNRX0%2BTp8Sq8ezgB5G7EJWpFvLs5t/VXCe0X4P%2Bfvh/LrzJIxFtV7URC5L2vW8BExccGxCKc0zdY4PxdeCfgQ5di1HdCtw3Es9wTQ8z1TfCU2nI5gFNEVBGbWdUKXX9gmAM4ADFaFQAB3ICQJfBs32RUjyLYSi0xAEBS0jBdHVdRFxI9M5LWQRZkgAN19f0lEDDljkwjlkS/JdMPXGMMNw8sZyPQjTIIp5BzzX9MCOUhdJXbCMO3HCywPCziLTSzs1zYdbJsRz9LjdUTNPLza1kaDolbQsgtcoz3O8iL8SgycLAUByaIApLCQvAgECbOVqNbAh6XbY1TQtK1bQHPyRx%2BZE0pg1s00Laz/KUKwmqi9KTyTQt8sK2DDzlJ14ucrDDKmtcQv3ZLqwW88r2icCGHvZcn0uTBX0cz9sofOj/1EjjDUq7sav7A7l0xRzv2XIEQTBUdmpi6dC1e4gMrau77svAqmy1a6l2JYT0KYljWMxFabyqGkpL2pCEY0xc0ISmadxRdHd1yzzFqI/H8T4zAKIIKjsEco6GOYtjTq4uhMWJ0n%2BuwMG1WQiSObeGUXilc5sFUVg4V9XnuZ5yUUfMRFgjBLwsCAtw0AYZZ4jJucxc2M5QkwdigQpCoJVlTTsaxyacdCjzwsJlsto6kcub%2Bc49bsJ5ReDE3gtE%2BaCePOCdTKvVfKHEcAH0NAdz2PeMy3KxSm2A8ZO3bJDrgI49qPcat33Rv98r9STpQQ7MB3%2BQFVFXcheUM4tv3Srzv0BDDtOzbmvDTNpBP9TrFPm%2Bm83vfb3PA%2B74vkZQ92W69tv4/r7vERL/4hC8eJsguhQvFofU3aps4l5XpI143/UkRAguXsbjQPsbloG4YIur7v%2BfZzHvnNctdfN8N74d/fo/To7Ls1Vey1W0m4RyZ8m49TvuHAa9psoQNTlAlOD8i7EiyqjJcEDR5jkbk/Cm2lWYgBplDZEZ94bSUdprAAKo8Leld/a3mQCHY80QCAQEGOgYSCgNTMKom4X%2Bm9Cx71XtVD%2BBBiQzAdhwOYtBOAAFZeB%2BA4FoUgqBOBgMsNYR8Cwli%2BiljwUgBBNDSLmDaEAcjJD4g0AADjMGYAAnPYrgcibHWK4A6B00hZEcEkLwFgsRL5KJUWojgvAFAgEvkY5R0jSBwFgDARAIAFgEHiF4Ag5BKBoFhHQaIoQNScFUNYgAbAAWiKZIM4wBkDIDOFIfEZheBmkICQPAnCWj8EECIMQ7ApAyEEIoFQ6homkF0C0ViN54icB4DI%2BRijjGqM4BeNJqT9SoCoGcQppTymVOqbUyxZgzgQA8Nk%2BgxB7RmERFwGYvAolaDmBAJAWT4g5LIBQCATyXkgGAFIMwfA6DQinJQCI8yIjBDqFiKZvBQXMGIFiC8ERtCYAcJC0gWSBIEAvAwWgELhlYAiF4YA/paC0HCdwXgWAWCGGAOIXFeBTQODwMpUlKjMCqCRWklYBjgjQm8So2geAIg3lhR4LA8yyp4H8WS0gyliARAPlcSlRh%2BVGGMXMKgBhgAKABA8ViK0lEGI6cIUQ4hemGoGWoeZoz9BUpQNYaw%2BgBXhMgHMVAqtUikpKRwk%2BphNGWDMMEmVxBWmPHgHMOwSKqguE7CMZopBAiNimH0Fo2QUgCBjVkJIqaGCTF6CUVoEb2hDAaJ4Joehw0MoEB0eoOaihJtsEW9NYwi01umFc%2BYixlgSBmRwBRpAgm8BCRs4pZSKlVJqXUg5EBcDNLOfo65hjVVzEKkwLAMQICmJAJIRE%2BJ7GIk8XEMwkgikaA0HIop9j9CcF8aQfxlz8RFK4EU6x9i3FFIsc43dRS%2B3zJCWEiJC7on3ISQ8pJyy0kZPeagE5uT8kcDqCwRSDoSlMDPP%2BLg9j8RcCsY0/ARAg1tL6Ua7pEhpBmqUBa4ZuhfnjKYJMsl3be39oWRwJZKS0lnDWUOrZFSyRoYw1hjQhzjnPNOecxEZh523JiSBj5pyIOyb6Lx75TjL40E3k2IFIKwWwpRdC8F8LEXIqlWi0UmLsXzLxQSolJKUUUqpTSlR%2BB6WOCZfM1l7LoQou5RUeZ/LBXgpFSsFR4rJUGJlXKpQCr7P0VVXwDVWqdV6pRYarpJrSOyHNUMlRVHrUqp9VYSwDqIhOvXaot1AgPVeuAvl6w/qB2BuDSVsNFQC3OAgK4RtcbOwtrrSmqonW%2BupB63m8tVQq3FoyLG0bhaJgJtzWWhtJbRj1tmwUebbaFA6M7W27xjGf2cC4yO1DDF0OYasYc6deGxNXJuYu0gy7V2UG7de29GG4gOjkfYjxiJJCHvKS0Jjv7bD/qk0B%2BAIHkkrPk1BkTMG2CcHg9slgChFI1MUqd9EgwcMztaXoFLxqenpf6eRrLOgQCIlIDRuj0zL09rmcMkJrGVkcfWaoJHKO0cY4jIMITMOXlicRJJ2LMm%2BdybeQpmIqOV4h3R/YkOmOCAhzZ6R/5GmIDAuGXpnTUqtdwoRRGlFJnBBmZxY5zA%2BLCViBs1KuzSqgvkrpQW1zwz3PyU81K7zvLeB%2BaFViQLYqg2hd4OF%2BVMJosqsA3FpgmrtU6yS1K/HxHTUZZJ5a8nuXjB2sK35prZWqiktWBw21vqLB1dUQ1rAufpttY60t2N8a1u1rzYNtNdeM05CG3NpvZaWsVuqItybPe2iVubV31tK3hht6batno3eNtbZ6Qx%2BnwSDvK7OMj1HZxZf4gVxd3DJBrtC8A0uzAK6%2Bile8S9kADj8SIkRHIlxkhSgaDvw6J936GecD/ZEu7ZjJByJ3XcQdBPWsUkCcS4FsTMC/W8URGXwHS/wAzuW7QaQ/xX1CUQJMWlSbFSE3SAA)$Done$

## Links

- [source code](../../../../conceptrodon/descend/warehivore/kindred_repack.hpp)
- [unit test](../../../../tests/unit/metafunctions/warehivore/kindred_repack.test.hpp)
