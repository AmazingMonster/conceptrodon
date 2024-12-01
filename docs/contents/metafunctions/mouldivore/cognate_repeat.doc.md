<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateRepeat`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-1">To Index</a></p>

## Description

`Mouldivore::CognateRepeat` accepts an operation.
Its first layer accepts the times of repetitions and returns a function.
When invoked, the function repeats its argument list the given number of times and uses the result to instantiate the operation.

<pre><code>   Operation
-> N
-> Elements...
-> Operation&lt;Elements...<sub>1</sub>, Elements...<sub>2</sub>, ..., Elements...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateRepeat ::   template<typename...> class...
                -> auto...
                -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateRepeat
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will instantiate `Operation` with four iterations of `Monotony<0>, Monotony<1>`:

```C++
template<auto I>
struct Monotony
{ static constexpr auto value {I}; };

template<typename...>
struct Operation;

using SupposedResult = Operation<
    Monotony<0>, Monotony<1>,
    Monotony<0>, Monotony<1>,
    Monotony<0>, Monotony<1>,
    Monotony<0>, Monotony<1>
>;

using Result = CognateRepeat<Operation>
::Page<4>
::Mold<Monotony<0>, Monotony<1>>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `CognateRepeat` with the help of `TypicalReiterate`, which is implemented using recursion over the total number of parameters.
Each intermediate result will be kept inside a `Capsule`.
When the iteration completes, we transfer the elements from the final `Capsule` to the operation.

- **Base Case:** Handle several numbers of times directly.
- **Recursive Case:**
  1. Iterate several times;
  2. Reduce the total times by the same amount;
  3. Invoke the first layer of `TypicalReiterate` with the times left;
  4. Concatenate two results.

We will use `ExtendBack` to concatenate two parts.

```C++
template<typename...>
struct ExtendBack {};

template<
    template<typename...> class Container,
    typename...Elements
>
struct ExtendBack<Container<Elements...>>
{
    template<typename...Agreements>
    using Mold = Container<Elements..., Agreements...>;
};
```

We will use `TypicalReiterate` to reiterate the elements.

```C++
template<typename...>
struct Capsule;

template<typename...Elements>
struct TypicalReiterate
{
    template<size_t...>
    struct ProtoPage {};

// Base Case:
    template<size_t I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Capsule<>;
    };

    template<size_t I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Capsule<Elements...>;
    };

// Recursive Case:
    template<size_t I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Mold<Elements..., Elements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

We will use `Send` to transfer elements from the final `Capsule`.

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

Here is the entire implementation:

```C++
template<template<typename...> class Operation>
struct CognateRepeat
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = Send
        <
            typename TypicalReiterate<Elements...>
            ::template ProtoPage<Amount>::type
        >
        ::template Road<Operation>;
    };

    template<size_t...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSGgDMpAAOqAqETgwe3r7%2BQemZjgJhEdEscQlcybaY9iUMQgRMxAS5Pn6BdQ3Zza0EZVGx8YkpCi1tHfndEwNDFVVjAJS2qF7EyOwc5knhyN5YANQmSW5ejrSEAJ6n2CYaAIK7%2B4eYJ2fIE%2BhYVHcPzyeAHoAFRgkFHNxMVIKLz0I7gkFAgEETAsVIGVGnNwEa6pRisTAAOhJ/yeE2IXgckOhsPopysTwBoPBR2wqlRDHQFiYyAA1gjwcjgUCjgB1d4AdzotCOXiURwICDwCiOVC8DAc2UVqCOaE1TE5hveBElutSAwURJRaIxxuxuPxzDYJOtSXu5IIlOp7M53N5ApMAHYrEGACIMgE29GYzDYgFHROK22xh14gku0nuvUGBSqjyCJjheKkBNJx0Z4kk7D0NiCBRR90AilUghsjmuHn87EFlrF4jYmtoxgEK1Z%2B5NpkhsuJ1Ex%2B1nCvOqtEx7AYiYYf1smPJNyzJGI4AWU86A%2BYchsiLEQHZyHddHrtIRzXG63j/HkanEaSjMBjxZMEjiEVxBTBYVHjnO0sUXdNl1dHcW2pECuROadwy/f8oNTRcUwXHE4MJBDswOJg80vQt%2B2fJciOrWsRwbSdHiQtsUPQHsr37Qd6PrYiJw9Z5pyePdsPw0SYIIp1aLdbAczI1UAHl8WIQ1sh3PcWKOMNMD7WgZzQv89z3eVwmARV03PI4lPiVSBG498xxkzC92DH8/308S41w%2BcJJozMZLkvNXVfTcH0YgTjIPMyACVUCYM9TgvbTdOxEKHL4kAQArTDXJy4FESOAAVPE8FEWhoswQgbNRMCkWjaCvMkytXXvBjEK9VsipKsqKqqlSsSnQzyzwiTMgAL0wAB9Ag%2BP0zTlGIVAiGUJhgHeYNQzcqMRSOHkFShJQQA8kbGvGqa2wASXUpMNwARy8PAN1VCALvPRKjg0ZY5o66kFqW1AVrW7ErqYlyhN3IzExMw8K0sqEYThRr/l/fTcpRplhOGnzTrwCbpqOEGIpuzB7sezBntexL3q4L7McTebFuW1bGsJ1HwchqGovM/E4dpRH7LC2b0YhxM0fcnaKuQDZMgAN3eA72GO7HsTO/HWbpo47oep6jggMwPjcd6LtpkWjgZ/7AZZ67RfZjnobM2H3t9TsAzTKS2COP6maBs5XoAWiOMw7ky7LQY5kOTuPU8BYYp82R4j8nOFsGtox03POxJgLlQYL11Ctqw850zPeZyyvYB5nUrz9LP2FsXtoAgqPGAZhUQq/FDVqiCM%2B8hq3ea8dAsU5TbIYdrvTbZvW8wdvMENKNbdnE6Vdx86XxYdZBGts2frbcvLbZobIZ7pr4Lohzt8i4uT1oBKkgvNj9Jcs4n45vz3mK1JSrEXrUX6xrWq8U/BrDmRwI7Y09ozCuPs3CPA3hqAgwcsrplfqLQuRlwENSOLFeK2JrL9TUk2ZOSZ65pxEsvM4qsZokjSmFbe9sS5rTLlAg%2BZxaGx1ru5DCdd8qIj4XwiCgEISFXJqOLuzJ%2BGSPAg3F4mo3gGwuHQG4O56o4ShNnAm49OongYP9BgtxBo71UsgPUAgJiYFUKkYgRws5ECODLMQXh1ohiutwiwaFU5YQoafaSWjqT4NHnlR4DChBeFSEUTA6AKp0jbO9AJjR4wax0Xo24ZwNB3GfMkog%2BjsRcAyfpLJAhUluHSe6TJAgUm5PyUkip2TimlOwOU3RdSqllIKbUop2IGlNMqWcPJTFkbi2CVzaJcJYn30vC3Y0s955nHiYQgSmVWFuEkDuTKN92JnEKTktJGSo7NM6X05GE4hlzEcMgSa8l4gEAgN8TKChCSXMYm4UZtACDPlCeEjIkTXmIPdF9X8HBVi0E4AEXgfgOBaFIKgTghtLDWDNusTY60zBJB4KQAgmggWrD5CAAIZgiRBjMJIAAHCSgIGgACc%2BKNAADYSUpBBRwSQvAWCJA0KQCFUKYUcF4AoEAHLMWQqBaQOAsAYCIBAOsAgqQLjkEoGgdEdB4iREJJwVQJLaV%2B1pZII4wBkAmKkESMwvBImEBIHgdAeh%2BCCBEGIdgUgZCCEUCodQwrSC6C4KQSUKlUicB4MC0F4KsXQs4ApC4sq2yoCoEcDVWqdV6oNUcI1%2BsIAeCVfQaxuwaa8CFVoVYEAkCKq/pm%2BVEBi3KoSMAKQZg%2BB0D/vyiAMQQ0xHCK0a4/reCtuYMQa4CkYjaEwA4TtpBFUPgUgwWgHb3VYBiF4YAUJaC0H5dwXgWAWCGGAOIGdZMtRyxXVCixQ6LjbHReEVETKoVXBiCpXtHgsAhq9HgNlq7SBy2IDEb52kN1GCuEYLFqwqAGGAAoAAangTAkprIQvRTa4QZUHXSDgy6tQIbPX6E3Sgaw1h9B4BiPyyAqxUCpEaCuv23xEqmHhZYMw3L33EEteTeAqw7BDsaC4Lk0w/BetCMWRYowvVFCyAILjeghONAWCMaoPQ2N9EmO0TwnQ9Csa1AIfobRJOVAE7YeTomvVzA03xqTEgWNIq2CZ/QQbOUhp5bGzV2rdX6sNZIY1utcDmqzainNGKAOrAQHPLACQIA4pAJIJIRJKVJCDJIDQkhiW0o0BoAItLKWWeZaykAaKiS0q4PSylJLcsBEkFwAIkXaXWfdTyvlAqfPCoLRKwtUqI1yooOW1AGaVVqo4K0FgMsgx%2ByYHJQ8XBKVEi4ESQ9%2BAiAMatV6uDdrxCOuQ0oVD7rdC1p9dCTtgaOBgoq9ysNzWo0xp631gbQ2zIjbGxN3W6aS3xBOKiswyxc0AdFUW9r92yCtYrZmkAp3%2BukSMCNmoda3nxEbc2913b20jph72/tg7h2vrHSOCdU6Q2zvnYu5dI712bu3VC/AG491MfdUeqWqIR3nvqCG69t7rj3u2FCp9L70Xvs/Uob9BPTJvaA6tMDEGoNOhHfNhDEgkOyBQ26qF62MP/qo1YSwuH8PMehSR7IZGKP30V9YWjvBUD0cYwR4LMnVN%2BAgK4PTwQuSaaWIJjIwmciKfyA74o2Q7faZU40dTCm8jcbNz7%2BTnvpMGb90p/TwejNaeqKZjY5maZpb21yg3nAbHEF6/1wbQPLujfGxoNzU2SCPbRS92r%2Ba/MBdGKbplLLSBsqSKN2LQZStBiDEkOLkgdVepT6G3ltgat5pFWKyV0rI1lt%2B51tgnAesJpYAoGWJiZZXdjBMU1ReZvWtkAtxDTr5ArZlzoTL3rfXbaT8Gyrh2ZUXCONG9PLA58L6Xyv40ExbufcrSXpIZeh8Fo%2Bx177BVD/P7RfcJSaZfSlSaVfAgS5DPHVMHBtSgKHKFeHaddFVAxHNjEdVHQQdHadInTAOdBdMQXHV9fHX9ZnNdXdRwfdENCnE9anQQWnd1endtJnR9BjNnXgDnL9NEHnf9OrPgYDQXSDaDUXbfcXJbKXA/NDY/AwBXbDZXa9E3IjDXMxTgIEO5XXGjOjeIGbJjQjQPbIDjdwF3APXjcoYzN3J3a3cTD3aPe3IwtTXTMw5TeoWTZw%2BYBwr3Fw/3ZTKPSwmPCzBQMzB1HbZPGzNPWfXVefRfexF/VEN/CAdzabEvbzX/SveKavHbOvNlMwUbJIJIAIClYrRLQooMelfbVPfvflQVXzUgXFSQIMY1FvLgKQSlZvSLLgIMNLJIC/A7fvDItLE1KovvV7OrVYd9TIZwSQIAA)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/cognate_repeat.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_repeat.test.hpp)
