<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Agent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-agent">To Index</a></p>

## Description

`Pagelivore::Agent` accepts an operation and returns a function.
When invoked by a packed sequence, the function extracts the list of variables from the packed sequence and instantiates the operation with the list.

<pre><code>   Oper
-> Seq&lt;Vs...&gt;
-> Oper&lt;Vs...&gt;</code></pre>

## Type Signature

```Haskell
Agent
 :: template<auto...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<auto...> class>
struct Agent
{
    template<typename>
    alias Mold = RESULT;
};
```

## Examples

- We will create an `Agent` of the `Operation` and invoke the returned function with `Shuttle<0, 1, 2>`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result = Metafunction<Shuttle<0, 1, 2>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will invoke the returned metafunction again with `std::index_sequence<0, 1, 2>`, which is an alias for `std::integer_sequence<size_t, 0, 1, 2>`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation
<
    static_cast<size_t>(0),
    static_cast<size_t>(1),
    static_cast<size_t>(2)
>;

/**** Result ****/
using Result_1 = Metafunction<std::index_sequence<0, 1, 2>>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

## Implementation

`Pagelivore::Agent` uses partial template specialization to extract variables from a packed sequence. Here is the entire implementation:

```C++
template<template<auto...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<auto...> class Sequence, auto...Variables>
    struct Detail<Sequence<Variables...>>
    { using type = Operation<Variables...>; };
    
    // This specialization handles `std::integer_sequence`.
    template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
    struct Detail<Sequence<Type, Variables...>>
    { using type = Operation<Variables...>; };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAA7LGkAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0XEJCnUNTdmtQ109xaUDAJS2qF7EyOwcAPQAVFvbO7t7G2smGgCCm9sA1AAimImujMh4mArnO4cnZ/ufu2/HR79mAGZgshvFhziYAW5kEN0FgqBDsH8/h8vqitj8UecAJIsRL0NiCJjVF7bDFo8kHJEnAiYXEGGkQtw0ulEzCMpheIgAOh5CPOIKYCmeAHlbsQiekEX8hsQvA5zsdgIwCEjYlYTudNedmXjWYyCABPW7MNhSjVamVyghXTB1OjgtUmWKXCHq37mzU6%2BlsyFevWQjnc3kA7D8gxC85CTAARy890wpHOgdQPK5ADV6ngmBF6AozcctedLfLrnbaIyo7H44yM8QszmnqmpSG/oWnRZzl5UkZtUbMOCAZdzqLohKBDXM9nc02WwCO06XXPW1rl5q1mtzgAVBB4Z4KW4PMR4ABeY4Y5wQhnQufBADYNDCQCBgjSlcQAPpKKsMFYme9c1dtVpXUGV9YDvX1PsTQTJNORTYNQwFCNKzjH8YMNY1WH7Tc%2B0TZNU1retc3zQti2tUsmDoCsY1Q39IRw25E0IqdGwQkiVzVTtu2AXtbgHIcR3FaoJzrFiFBnRE5wdRc3UAv1QKZKCsNTRViEwWllTzFsPS44IeIAWU8dB%2BJtMtGVU9SCQIcSEKfDCfVk51XSpU4KVRMkLgAMTwYghnObBVFYPF%2B1eZE3K%2BH4kUBYFQX7Rk0DQxJrPzMKLiEBBOQIegSXRP55J9Nx8LYk4yMjDKCCyhyXMxQSzxyylqXA/1CrgiTpQIWV5Vq4SlxOVKtnOfTbSYKgvB/YlQsalkFPs6CVOIYAtMRE4uz0wbhtG8b0hMxVlUZbrJRDJ9DNodBzIWmyANnWT3h2SMvESXJMHQAAlJ4vFoa1JuOVaeyEB6nte97PpMg7x0hDRE1ac4zGbG7XIuN6FA%2Br7ST%2BX6eKRlGTKGupNocQ63HSzL6EZSHzmh2HZ0k%2BHMU3J5Udykq6kcZB30FJQGggR8QAULD2a0twsc%2BxN/selJnuFlUQ1mZy%2Btu8LPg8gaowS4yAqC7LvpRRXvqioEf1igc3E5OhCANFKFZVgGJaB5GQe%2BjH7vFpQ7ZR98uFBsUzyRSFAImVn31EIZGVSY9MHfaXsAgDR5n9lm8DZ4PpbcMOI6jiAuDjnSA8ToPBRTtPI4RCAzFlvrruqu6pfqn4nalj2cY2saCfB1OCHQJ9giwVRPxo6sIahxMqckmmq4uem/O%2B3O2Y56ICG5junz5tgBcZBvobFwGN4RWXevdY4OHmWhOAAVl4PwOC0UhUE4NxrGsItFmWOLAR4UgCE0I/5gAaxAU/JBcg0AADjMGYAAnOArgp8QHAK4PEaQJ8OCSF4CwCQGhIaX2vrfDgvAFAgEhp/K%2BR9SBwFgDARAIBFgEESJycglA0C4joNEUIWFOCqGAbeAAtLeSQ5xgDIGQBTQBZheDPUICQPAndWj8EECIMQ7ApAyEEIoFQ6hiGkF0K0AA7uKRInAeDHzPhfL%2BN9ODCk5LQ60qAqDnA4dw3h/DBHCK5GYc4EAPBMPoMQcEb9Zi8CIVoeYEAkCMMSMwsgFAIBhIiSAYAUgzB8DoDSXylAIimIiMEeoBoDG8EycwYgBphQRG0JgBwuTSCMKssKBgtAckaKwBELwwBCq0FoPg7gvAsAsEMMAcQDSfJlMcAANyeKYzAqgymclWO/F8lRTG0DwBEcUhSPBYFMR1PAaDOmkFGcQCIEtrg9KMIsowX95hUAMItNMjxtEjkvu/WRwhRDiCUU81RahTFaP0L0lAD9LD6CWfgyA8xUBJXSB0rhMIISXFMJYawZhsF7LrFgYFEB5h2CGekFwDB3CeGaP4XFUw%2BgxFaLkNIAhRgtCSCkClDBiUlH6OMSoWKBCdBGPisYbRWU1GGN0YIvRGWktsHyqlegJgNAZTMLOCwlgrAkEYjg59SBYN4DguxnCeF8IEUIqQrj3G4AkT48wAIs4BPOfMBAmAmBYBiOi0gf9JAAi5OAgEsRJAaEkGYSQ94NCn1vOA/QnAUGkDQaarkt4uC3mAeAuBt4AHQNdbeFVpicF4IIR/c5pCKEhKoZYuhUSYneNYWwTg9QWDDNiFwpgYZekU3AVyLgQCxH4CICivQTz5GvOkO8pQnyNG6ESbopg%2BjOmKuVaqsxHALE0M5OcGxGqHF8IFD2LgDam0aHcZ48J3jfEAjLua4hwTQmoC8dEeh0TT07v6Cu%2BJUDIY0E%2BtEfBEB0kaPydkipH7CnFNKeUnZVTlQ1LqaYxpzTWntIqd03p/Tr74DUgTUZHTr4TKmTSCpcykHX0Wcs7JazVjX02ds9%2BeyDlKCOTBvSWbLlMGubc%2B5FTO0vMUT22QHz1HX0HT8s5cKrAApw2i0F4KBCQuhYOXjCKkXRBRWMkF3LW5%2BAgK4MVrRAgCumEymleR0gqa03SqVmnMUKfZY0Tl1KjPVBMwZ4VErTNZHM3y6zCrZUv2c0gidqbOCLq1bW1d66gEGtbSQPdZrM1Hstda21lBFUhrDQ2z1sRT7gPiACL1PrJCtEnWm2wGbAkkLIZQ6hViL1FpYWwjg5bHEsAUMMoRwy11cm9EMFtRqpEdtkF2ljyj5B9o4zoEAAJSDDtHYYoNSqTEaJwTOqx87bGqCqzVurDWmvWg8VeiJe6AT%2BLC0E0hJ6z2RIYet7xIBauPXfPV8B74Vvvnmz25Jz60kZKyYUr9L2iklKGRUwDghgP1Lg5gJpLSxCQZ2dBk5BGumDMQ2MjRqHkDTIw4IeZGicMrINPhjZdZiO8FI4c2klGzlHr4FchQNzMB3ONIxjrzGJCsZUb1r5A3uPGH%2BTYAT8AhPVA6WsR8EnLCIrVciqRsn7UWexUp3Fum1NFBJTkWl1RdPkuqE55l7Q2WirM%2BKllxnHPqbl%2BMTX9nxV69l0K5zChn7yple5ib2CvN3fONV2r5xLuNdZH5CAhq20he23l2YEWbX9HtUg2LIAIFcgBACU%2BMCMsYKj7EaNKbJucHTYQi1DqQCSFPi6%2BBsQMHAMkFArgoCzDJqQQCO3arU87e/mN0Ryf7e4NrwH3Zz7sWSCAA)$Done$

## Links

- [source code](../../../../conceptrodon/pagelivore/agent.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/agent.test.hpp)
