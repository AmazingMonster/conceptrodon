<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Flip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-flip">To Index</a></p>

## Description

`Mouldivore::Flip` accepts an operation and flips its *0*th layer and the *1*th layer.

<pre><code>ZerothLayer{FirstLayer} -> FirstLayer{ZerothLayer}</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
-- flip with Mold
Flip ::   template<typename...> class... 
       -> typename...
       -> template<typename...>

-- flip with Page
Flip ::   template<typename...> class... 
       -> auto...
       -> template<typename...>

-- flip with Road
Flip ::   template<typename...> class... 
       -> template<typename...> class...
       -> template<typename...>

-- flip with Rail
Flip ::   template<typename...> class... 
       -> template<auto...> class...
       -> template<typename...>

-- flip with Flow
Flip ::   template<typename...> class... 
       -> template<template<typename...> class...> class...
       -> template<typename...>

-- flip with Sail
Flip ::   template<typename...> class... 
       -> template<template<auto...> class...> class...
       -> template<typename...>

-- flip with Snow
Flip ::   template<typename...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> template<typename...>

-- flip with Hail
Flip ::   template<typename...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> template<typename...>

-- flip with Cool
Flip ::   template<typename...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> template<typename...>

-- flip with Calm
Flip ::   template<typename...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> template<auto...>

-- flip with Grit
Flip ::   template<typename...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> template<typename...>

-- flip with Will
Flip ::   template<typename...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> template<typename...>

-- flip with Glow
Flip ::   template<typename...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> template<typename...>

-- flip with Dawn
Flip ::   template<typename...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Flip
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
    };

    template<auto...>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };

    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<auto...> class...>
    alias Rail
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<typename...> class...> class...>
    alias Flow
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<auto...> class...> class...>
    alias Sail
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<typename...> class...> class...> class...>
    alias Snow
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<auto...> class...> class...> class...>
    alias Hail
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will flip `Operation` and its member `Mold`.

```C++
template<typename...>
struct Operation
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

using SupposedResult = Operation<void>
::Mold<int, int*>;

template<typename...Args>
using Metafunction = Flip<Operation>
::Mold<Args...>;

using Result = Metafunction<int, int*>::Mold<void>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Although there are many cases to consider, the implementation for each case is straightforward.
We will implement the one where the function flips the operation and its member `Mold`.

```C++
template<template<typename...> class Operation>
struct Flip
{
    template<typename...Elements>
    struct ProtoMold 
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>
        ::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIJJcpAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmgW47eweYRycAnqmMrJgAdE9H2ADUyAYKCq8A8rfETAaLxMGgAguNiF4HK8AGK0PCpEGgkwAdisYNemNep32gIuxwINzubCeD2w9DYggUwIxWIhUIIr2UxFQRAAsp50K8kVjuWiebysTjzpdCbdmCSnqDgMRMLtGARqYFsALBa8vJkjK8ObQuUcACK/f6A7KXaWy%2BVU0k00FqzEgEDCvHazmXcmWxXW5VHdG2rGo/U%2BpGq7G7XGHAlEiWPJ7uymKm28jURYAu3XcwKG5ms1A69BuikKhRelWBX0BoNgpEAegAVPWG42m9Wa43XgAVTDjb6NltgutNwcNvvIqtmQIRD5eLAZtxoBibVIJ71VsFOiPXcX3EtI%2BnQv4JE0CYP82mY9f4zfEmMPRN0giQ6HZ9mcvlWFGBsvBs%2Bhs540VRtuUrEMASoqj%2ByZanmGZZiyL66maIHFs83pflWH6VqOoKQamQheKkRSYOgABKXZeLQjIGkah5AscABuqB4PmK6gg6eaXBEBCkK8nG1sCaFYReAFbpKDygkhNo4dqmDNFQXgLg0MGwvCiLHAeAK0eBrEgOxxziaBO4CUiUmkQo5GUZm0myfJDimscnHcbxLxsa69GMcxpblmCsyOMgAD6TBfAkBAQOM6AOgo9wBUqbimeZ3F4QRGREXFFEvEsPocCstCcP4vB%2BBwWikKgnBuNY1ivAoawbJg3LjjwpAEJoWUrAA1gEkgPBoyQooEGj%2BBoZgAGxDWYAAcY36Jwki8CwEgaBopAFUVJUcLwCggItTWFVlpBwLAMCICAawEKkXhcRQEBoHsdAJFE9ycKoY1DQAtENkivMAyDIK8UgPGYvBEYQJBMXo/CCCIYjsFIMiCIoKjqDtpC6CkADuAKpJwPDZbl%2BXNcVnA/OdZ2MqgVCvE9r3vZ932/Z1ZivBAHg3fQxB1YEXBLLw21aCsEBINdqS3WQl2C8LIDAFIZh8HQOzEBtECxPjsQRC0VxY7wKvMMQVw/LE2iYA4GukNd8Y/AwtDq0jWCxF4wBuGItAbdwvBYCwhjAOI1t4LKtl0V2%2BOYKohvnVsDWcXU%2BPwrEAI6x4WD4w%2BeBzS7pD%2B8QsTJfquwe/CRjNSsVAGKBABqeCYKjB4FQ14PCKI4gw7X8NqPjKP6B7KDlZY%2Bh4LEG2QCsqBLtkzsvWFBqmJY1hmCt6fEExAcD90hsNC4DDuJ4HR6GEERDJUIwpEUWQCFMfiHxkx8MPMwyJGMdQr70ExtJv%2BR3z0Ah9K01/77fthP6fehZhf13gsA%2BKwqrrE2BIHGHA8pLXxqtCmz03ofS%2Bj9P6DMIC4GBmzcwHMuaNQLisBAmAmBYESBANqSRAgPAAJyBBRJIbqZhJBDQWv4IatCpocBmqQOaHMHhDS4ENMatCxrCP8Mkfw9ChrwKRqtdam1CE7T5odfmx1ibnXIJQMWrN7psE4C0FgdEUQvSYO8AwWouC0IeFwLqgN8BEHnuFFItdIYN2kE3JQLcka6GlujJgmMXYwLgctXgq0ianXOq8MmrwjEmLMRYj2v0bF2I0IzZmQtWbszMAQnmu11G6ISNoq6qAWYjHiaYj4HtrFcEWjQCiCQFZKyRlrNWxs2k6z1gbI2qdTYKnNpbfGNs7YO1oE7Y2btc5bCKvgX2jh/bOyKkHEOOxjYRxykjaOscrjxxmdzeeKcGrp0zkobO7sjB51ACovgxcFBlwrlXY2bj67Q08bIZuiMip%2BPbvnSeVhu7R37pQ4qw8BCj3Hpmf509Z4JGcYvEFdgH7OAgK4ABKQd7lBvnoI%2BDR0VpAvg0b%2Biw37IsaP/F%2BZ9l62Q/k/YlB8/79HxUAgYIDsWc1WJA6GIS8byM4HE4gxjTHmOqVY1JXVGbYKcezTm3MiGkBIWQkYILNm8P4TY7qKJpEol6pIFh70UhhIJmtWwSj8mqPgOok6JMSlFOIPorYRjqYsAUHRH6dFrEPHOOMBxODQauNkO4t5sN5DeK%2BToEAwQAlBOxtw0JCDCaaNJuTJ1H0XVuteB6mx3rGRMzKVkhI7NAh5ILntAW%2Bbha2orazEAbqCJ%2BSzX5HNAVBXvRlo0%2BWlAWlFU6VbBqvbukr2Nv0wQgyrazMwLbe2jtnYNSmZc/ZpA5kP0WYHYOyBQ7rMEJHLZvcdl7MToc42Jys450uSmUtRcmCl3LpXcUzzA2vIkO8uGYbW6Rt%2BcYLuNggXwEHmChgztqxhU7lPSwM9wlzwXsC8B98aV%2BFRevfFmK94koJcUbI%2BLcXZHpb/JF8HP7PzyFS/DDRCO4cARS4jlG5hsp/tAzlNUGObPjXyjgAqWDOtde6z1ObJWOJIDKktKjiGkPIZQGBaqQBmBsYEQI/gBrJAWnJlEIi5ErU4Iora8r2qSH8HQ/wY1hq0MkLQ3qDCuDBE2YEXlGmTXmpgQDdT4TNPKN5isdOmRnCSCAA)

## Links

- [source code](../../../../conceptrodon/mouldivore/flip.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/flip.test.hpp)
