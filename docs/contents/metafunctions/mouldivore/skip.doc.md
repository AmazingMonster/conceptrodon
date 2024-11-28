<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Skip`

## Description

`Mouldivore::Skip` accepts an operation and sinks its *0*th layer to the bottom of the invocation order.

<pre><code>   Operation{FirstLayer{...LastLayer}}
-> FirstLayer{...LastLayer{Operation}}</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
-- Skip to Mold
Skip ::   template<typename...> class... 
       -> typename...
       -> ...
       -> template<typename...>

-- Skip to Page
Skip ::   template<typename...> class... 
       -> auto...
       -> ...
       -> template<typename...>

-- Skip to Road
Skip ::   template<typename...> class... 
       -> template<typename...> class...
       -> ...
       -> template<typename...>

-- Skip to Rail
Skip ::   template<typename...> class... 
       -> template<auto...> class...
       -> ...
       -> template<typename...>

-- Skip to Flow
Skip ::   template<typename...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<typename...>

-- Skip to Sail
Skip ::   template<typename...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<typename...>

-- Skip to Snow
Skip ::   template<typename...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<typename...>

-- Skip to Hail
Skip ::   template<typename...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<typename...>

-- Skip to Cool
Skip ::   template<typename...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<typename...>

-- Skip to Calm
Skip ::   template<typename...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<typename...>

-- Skip to Grit
Skip ::   template<typename...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...>

-- Skip to Will
Skip ::   template<typename...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...>

-- Skip to Glow
Skip ::   template<typename...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...>

-- Skip to Dawn
Skip ::   template<typename...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Skip
{
    struct Commit
    {
        template<typename...>
        alias Mold = INITIATION;
    };

    template<typename...>
    alias Mold = RECURSION;

    template<auto...>
    alias Page = RECURSION;

    template<template<typename...> class...>
    alias Road = RECURSION;

    template<template<auto...> class...>
    alias Rail = RECURSION;

    template<template<template<typename...> class...> class...>
    alias Flow = RECURSION;

    template<template<template<auto...> class...> class...>
    alias Sail = RECURSION;

    template<template<template<template<typename...> class...> class...> class...>
    alias Snow = RECURSION;

    template<template<template<template<auto...> class...> class...> class...>
    alias Hail = RECURSION;

    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool = RECURSION;

    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm = RECURSION;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit = RECURSION;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will = RECURSION;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow = RECURSION;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn = RECURSION;
};
```

## Examples

We will move the *0*th layer of `Operation` to the end of its invocation order.

```C++
template<typename...>
struct Operation
{ 
    template<typename...>
    struct ProtoMold
    {
        template<auto...>
        struct ProtoPage {};

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

using SupposedResult = Operation<int>
::Mold<void>
::Page<0>;

template<typename...Args>
using Metafunction = Skip<Operation>::Mold<Args...>;

using Result = Metafunction<void>::Page<0>::Commit::Mold<int>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `Skip` relies on a helper function called `LoadSkip` to keep a record of user inputs.
The record will be passed to `Omennivore::Press` to invoke the previously provided operation.

We will implement `Skip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Page`.

```C++
template<typename...>
struct Capsule;

template<auto...>
struct Shuttle;

// We will use `Items` to keep track of user inputs.
template<template<typename...> class Operation, typename...Items>
struct LoadSkip
{
// If `Mold` is selected, user inputs will be kept
// in a `Capsule` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSkip`,
// waiting for more inputs.
    template<typename...Elements>
    using Mold = LoadSkip<Operation, Items..., Capsule<Elements...>>;

// If `Page` is selected, user inputs will be kept
// in a `Shuttle` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSkip`,
// waiting for more inputs.
    template<auto...Variables>
    using Page = LoadSkip<Operation, Items..., Shuttle<Variables...>>;

    struct Commit
    {
        template<typename...Elements>
// When finally initiating the operation, we invoke the skipped layer.
// Then, we pass the instantiated operation and user inputs
// to Omennivore::Press for further invocations.
        using Mold = Press<Operation<Elements...>>
        ::template Mold<Items...>;
    };
};

template<template<typename...> class Operation>
struct Skip: public LoadSkip<Operation> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEpLBAA6oCoRODB7evgGp6ZkC4ZExLPGJUsF2mA5ZQgRMxAQ5Pn5Btpj2jgINTQQl0XEJSdWNza15HQrjAxFD5SNVAJS2qF7EyOwcAPQAVAd7ANTKxJgKCkeHezsmGgCCBJgsKQZPJoFuBACeKYysmCOAHk/sQmD0GB9sHd7jNiF4HCczhcYSYAOxWB5HbFHJ4vN6YD5fX7/NgAOgpUJhOKOcIRBCOABFMI06Ed0VY0YyPpj7jCdjsjhYmEojqIlCBUVicXjXuDCdLsUTqTSZc85e9Pj8/sxyZTAtgxQYLkcPIImPMyPzBQAVBAJQF4S4CWjfI4CQEpJoAp7EI5e5AAayO9CoBDJKtVuJJuswFLJZqeggUkfZBtTdMRzNZtCJiYtkWIedkjAICnjVPTivZGOtRwA6o6GAA3VCBwEEe1ikjItIMfBGXHqglHNiLP2oKi4ruoUHgrJ1gDuhAQ08BmFUBDBDkw6H9TCDEerNK8GUH2sBH0ZwLnEJAIFlI4Asp50MXBKXy/roYELOzq%2Bi3K/lK9w0o%2B8qpsqx5qviEGfEwXhEBWBpGiKlxCJgACOXiMFspCpjSCFIRSiafpBVagTimYMtmFq5p8GHYbhhKfKRybIT%2B0IARiRynhEwDRn8abXiCCTzs4D7DvKJxMMALFuGxZYcTyNZAbydYAEq1BsGTNoC4rsCBYFSe8AGfARMEavJF6xhxqEmvmlr4Q8AoNoCShemCTxrkcNDEDM%2B5gmwvr7kGvnEKgLA%2BagnYJOWFnYjZALxopCjOZRUZJXqZJArF/nkVxGW0lu9JMiydHvqyhaVZ%2BHGkMCeVfhGFE0hyCW8WeAkXsJSLnCm0FKuZLmCo2RwRK27Y%2BWgxC9gIA5dSZgJjhU7pTrF7q3guw1HMunY%2BRuW4Hk8e4BoGR73K5dqMPVi6emhPnIl4tAMrEB7BkQvUmvwfpUBseVjS2qCiBC8UDaqWWAqJXlZPe4HeS%2BtBvqxJbsd%2B7VUttcgMKeu6hYGlxNICZzIN8yD0Hu32%2BX99p%2BuNQPiQwoNFTSsOLWVOZErlNNNVCsMkjykFcgLDypnDCpFVBzOWQSRJEagdlk/djE4QweHtXLKUo2W6VRolMbJRSXNxQVGYlVm5V0ESyvMTVqPNdg9VG/5yncbyusdfxgmXoE16nH1RIQzeYl3pJsHecosnyalyktbrrNh4CtGW58Ts8wafN/MLEtC8BAHVmLAf69l9zAGczxkbH2J8YOCN7le7MVZ8Jdl2wdu8w%2B/O53yOfqS51ymkwKQKE9gLXLcDwF1qRdxmjDzUQPQ8j1n/L90ICCIQQ9BXIc4%2BPItsuIfLs%2BwmbDJrxv9DL33hxHKEqBMOgQiBngKTbwcu%2BuaNy60LQHWXgAbBoAAkniFMgDcSoCOO2TAr9DphUnH/WmDAUiISZpPL4%2B8p46gNvbeylwoYM3qhDeMIDngpgovPO%2BD8n4v1RLWbaQCpwmEAbXZhGgxqXBqDudA9UcZIJQWWHadBf7xCgTAggdYIhHCYOyQBbhB7D0vuAwwJ0DBbD3OCfa/ZVqyOAaAiMgC6xXQYDdO6Jp1oHVcLjNhpCWBgPYa9MKH02FUMfs/FIbD0quUXBaRwg5KYsBIE2ARTNjIJ0Ltg7K2B6CtzLBjIq1cBK1x6q4mhHiU6bQEPVWxTV6ryMXpfT40Ty5t3TGU3uF1BSMN0RHOSbCOG0i6LUY6vClD8NQUIn%2BRxRHthSBI7aUiZFsPPgQTehJlHaLlOo6RDILHaIQTY/RbCjH2hMTtMxlwLGbisXXQBOT6mOPepAlx983G0MAV4wUPjMj%2BJIKOIJAMQnnTCVZA%2BxEyQADUmh4CYLEeg5DConk6jJOSKTTlpM5pktZOT4z1RGWMokXziA/L%2BecGOP4Kk0nnh4FgLBCCCzdrrdBxCKTFNiQCus9ZVm%2BQiGIV0ANMjznPDOKFpiAYTQ7F2BQ7i/h7gMN8BI51LqrLZV6cxXYIgzEMI4eUe5ZzByyNI7RfDHmoLrB9IErcGB4FbGce8fsvp3N%2Bs0Gm7L6Yg2ebrRJRxkn1wNeQtwBCIREjJbVNGldVTxysja18RIYXusJUqHudC1IgX2DfNJb8bgwmJZg4kkSZ64MViaJ1C4KGnyOGkkA/ovB/LwMgW%2B4L3GQoVQIKENZOShpFtfa4tax4rxvjac4gj601rrXW3eqIzCBAiGTLwWA0xuEQnQQg3x4kxrjSS%2B2MJ56prLSLHiotJ3TxdkVeepwYqoFYa7dq6CNbH3duuiKRBamXlrMG6tUtEpxv3WSZumASlxI9UCz2p6eobpPZHIk97H1pwxYLKtfJ87LoTfGH95L4kvprq%2Bd9x6t2%2BqbqXB95KY7qQvUB%2B41qhBeBSGkJQ6AtKKIZPXOdkJPgRAkRRe8rDPitjwEjQq%2Bqv2fA0JWCpxKV0UnuMQYAFKHjWqfOVX6qsIQ9QhRk0tZHsDUYQ24bjvHUMgWtYRp6xGfY2qE14ETaa3B0YY0xupLH244rxQQGTiMiQUbYyBKVjhkAAH00IJAIBAGY6B7wKABI5h1Knnpwpw3h3cvnKPYGWDyDgqxaCcH8LwPwHAtCkFQJwNw1hrC0nWJsS83aeCkDM/FiLqxAwBEkGSDQkguBokCBofwGgzD/3/mYAAHI1/QnBJC8BYBIDQGhSBxYS0ljgvAFAgB63lrQqw4CwBgIgEA6wCACPIJQNALw6AJCiACTgqhGv/wALT/0kEcYAyAC1SDJGYXgu5CAkHo3ofgggRBiHYFIGQghFAqHUPl0guguCkEXGCFInAeCRei7FzQvABtAkQgInRW3dv7cO8do4p2zBHAgDilIq2/TmECFwZYvAxsRdIBAJAy2Mf0DIBQCApPMcgGAFIMwfA6C%2BmGxAWIYPSCxFpcQb4gPeCc%2BYNzoEsRtDNN56QZbsSgQMFdOzrAsQvDAHkT/Yb3BeBYBYIYYA4hPv4GJo4PSKuEsbm0k8MXFGujs9oHgWIYJuceCwOzrceBOuq9IHpYgsR0iYGZBrowVujBg9WFQAwvGPl4EwIuUScWct3eEKIcQz3Y9vbUOz77%2BhNcoFS5YfQ1vhuQFWLOEGnAdtuavKYSw1gzD9fd8irAeeICrC4XeCArhJh%2BB%2B2EeYZQKh6Dw0UbIng2i98KBCQY3elidG6PUWYbe9BN%2Bn/0MfwxKi2Bn4PvIP2pXNCX%2BOCQjeMtbD361jgMXevs4G0cWHe2DtHZOyVlHEBcBXax9lvHuXA%2BrHtA/EYDfSBFeSGSAAJyBBoiSBlZmCSCALVb/yAHH7takCdY45kj/xcD/yNaAGNaoH%2BDlb%2BDAH/xn6fYDZDYjbv75YTbTbE6zZQ6ISLZU6RRk5rYbYcBNAsDNhog7YyKKyDhcCAFkhcClYXb4BEC163ayAPYJ7SBJ5KAp6fa6AM5/aDy87A4n6g6EGcCQ7zaIQ6IsFsEcGoTcG8H8HsJo70GY7sjdpmBv4E4TYk6mHk60HU7k4gA6HsFcF06AFcA9Y0DPRxSUBs6fb85NA86u6BGC7C6i6u4S6lhS4y466YDy6K50oq45bq6a7a4Ja67NI6rnDs7G7ICITbA5bm5RafZW425BH27bAJZO4u45bu6e5KA%2B5pH8SB58Ah4KBh4R5R5i6x7iFPaSGyDJ4fYJZyHp4B7l5WDZ5lH14F59JZAq4l4EBIyMgTGV7V4JC145H56T5ZHOAt79iz4d79g7494/Z94QiHGkDnFZAnET7z69Br65Dt47F1APGL5d7L5z6PFD6b6zC3GVD74bCH647H6n59bg6cDSLECsHsGcEGAGF8Glao5P7CHmE45WEf6kBf5YCJC/4lHwGIG8FlZoi4FoiVaSAQH7Y/bgmJacDEGjatGTYzZzYLaU6OGMFsCcAsHw52LNgFrNg8FkgEgzCCHP43Y/a9Hx79EvbyDSHDE6AgDBAKEA6q7KFgnn7qHUEMgILckHa8n8mCnCkMgmErbk5omBAYlkFE62GmkJAOF2EjB8m4b2YCmAH2ZGmObQn7aM4%2BH%2BR%2BHs6hHBE5aBlC4i4OBi5RGCAxHBEZHxEK5K60DJFq7PBpFVFq54B67ZGG4XaqAm6FG8DFGW7W627fCVGO7Iq1G8D1Fe5NF%2B4tFWnB6yQdHh6R46g9FiFSlJAylDGp6KljHGBZ42DTHwCzFF67BuaZ4V6WBV7g4170ZbG/73F%2BD7HuDr7PGd6lCfFnEj5ZCXHXHFAfG76b5NKvEMB9ATBrlz4nkQjnlzCblHmr79CXFb53kLCnGAmZZH4lHqlqEcBQksA8kKB8lHCulCnygBSP5CF3LY64746YnYk/7KEEkgBmC8GBCBD%2BA1blbdboVohoEEH9Z0m2AkHWGFYgCSD%2BBAH%2BCNZ1aAGSCAGVYgFcDBAlGBCqGEWDakHjbKHnYEUQmcWkVu5xQwySBAA)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/skip.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/skip.test.hpp)
