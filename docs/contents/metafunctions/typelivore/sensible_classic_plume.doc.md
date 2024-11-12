<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensibleClassicPlume`

## Description

`Typelivore::SensibleClassicPlume` accepts a list of elements.
Its first layer accepts an operation and returns a function.
When invoked by containers, the function places the elements into the containers via a process similar to pack expansion;
then, it collects every packed container and instantiates the operation with the collection.

Check out **Examples** for more information.

<pre><code>   Element
-> Operation
-> ...Container<sub><i>i</i></sub>...
-> Operation&lt;...Container<sub><i>i</i></sub>&lt;Element&gt;::type...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Operation
-> Container
-> Operation&lt;...Container&lt;Element<sub><i>i</i></sub>&gt;::type...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Operation
-> ...Container<sub><i>i</i></sub>...
-> Operation<...Container<sub><i>i</i></sub>&lt;Element<sub><i>i</i></sub>&gt;::type...&gt;</code></pre>

## Type Signature

```Haskell
SensibleClassicPlume ::   typename... 
                       -> template<typename...> class...
                       -> template<template<typename...> class...>
```

## Structure

```C++
template<typename>
struct SensibleClassicPlume
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct SensibleClassicPlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct SensibleClassicPlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Typelivore::SensibleClassicPlume`:

- We will pack `int` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
template<typename Element>
struct ZeroStar { using type = Element; };

template<typename Element>
struct OneStar { using type = Element*; };

template<typename Element>
struct TwoStars { using type = Element**; };

template<typename...>
struct Operation;

using SupposedResult = Operation<int, int*, int**>;

using Result = SensibleClassicPlume<int>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `int`, `float`, and `double`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<int*, float*, double*>;

using Result_1 = SensibleClassicPlume<int, float, double>
::Road<Operation>
::Road<OneStar>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will pack `int`, `float`, and `double` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<int, float*, double**>;

using Result_2 = SensibleClassicPlume<int, float, double>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Typelivore::SensibleClassicPlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

[*Check out this test to see how it works.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACcXKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcBJgsaQa7JoFuBACeaYysmAB0d9j0bIIKx9gA1CYaAIITxF4ObyEjCysXobgMCiyyGU%2BUwny%2BJgA7FZvm80W9dvtDnCTpiDkwjriLlc2Hcbq83sgIQo3gB5S7EAk5V7w9FvX7/AhvZTEVBEABKqCY6FZ6KRKK%2BbLZeOxx1Oe3xhNOxOYpLuFKpTEhZI8CjYjmQL0C2FFUvZBD%2BAIAIpgWnRTVLxQ6zWivFkjBjiR9Ala6QymQJnS65edLqrMG9dfq8Ia5Q89owCEbsCAQKHburjccJS6Poirdn4UG0TKCTj5ViyyGVdcyRrqZHMtHTFnUS6OdbbUx7Sco7aYyy22anUPc283RFgJ7Lt7ffSEgGGMXHUSw9dG3r%2By23PGnknXqn03Ws4Ec8H84XvsvS0qb%2BX0%2BHj%2B9Ndq7n2DcnlxOPYLhbO3jadq0HK74xgoT6HsSl6SmKF6nkWo53iGCqyquJIZuSxqUtSZJfMAxCYAmzyDjBrrulOv7oP%2BPJ8qglFynhBFEUmT7QUiBbwVeXFfEhaHhm8u6JiRHZckCDAgmC1IxjCPjloJggkSOpEYihVa4qpt41mqmHPg286Mo0JFsiJ3K8gKQoiqOSm5rxFaKveWkYfWWrgW%2BTZbp%2Bo5st%2BFEWf%2B%2BmLtWa5sBuzZGjujxCcakGXKxnHKexbGIRp94pUF6FPthLm4fhhF7p5yk%2BW8lHUWZdEWQxuXMa5OlsXBEoIV8AD0ABUbXtR1TXwq1bUACrYEIvXtV13w9R1nWNeYgQRFSXhYN6bhoAwWxpPurYIt8tkPuu8kEMJFqcm8ABaCSoP0xB5hY47kdOEbHL6u3ZnmHENZtaV8TtkUKetJm0pE52Xddk63f%2Bu0tU9iXxfCW2OQJX17T9B0Ar1ADuZ2TDS4pAx66ag/DbUQ/VjUw8FTmI5aXIBYZUOjU1by9ZgExvBojVFUIXhpMUmDoPyjNeLQXL3X6C7U24EQEKQbziy1kvS%2BDJ6vV8RW8wo/OCz6gLAngoKYOCLnSbCcriyRqb0ScVPMutpsVScJ28udkt/ZgDv02j52fjTPwtAaAD6LkJAQEATOgqYKNcfvhSrauS%2BznOZNzUcC68yxJc1dMM0zXCszdsdczzfMCz7XD%2Bf6ovS5LVC0EKBAy286DrDr8smp7ysFwQRf/mJEm61J0KGyc4sV1XBKS/XXg6ybIBm24FuBlbU82zP/2TCyntzL7/ttEHBAhyAYdsBHcqJxLgIc3nx/J6nTXp4zXJmNnwO5/H%2Beq4XZglyLlti4IQ/V7XY%2BNybqnVur927vyFl3bWkl9Z91kkbH%2BbxK7V1Hg3egk9p6zyXPPaedt0atEdsvfBrs8HEA9ordeMYI5KC3sHUO4ctRHzbjHM%2Bz8L7GhTqeDgqxaCcH8LwPw3BeCoE4G4aw1h2TrE2HdMwgQeCkAIJoLhqwADWARJA3A0JILgiJAgaH8BoMwAA2QxZgAAcpj9CcEkLwFgEgNAaFIAIrQpBhEcF4AoEADiFEcC0KsOAsAYCIBAOsAgaQvASwoBANA%2Bw6AJCiNcTgqhTGGIALSGMkG8YAyBkBvCkDcMwvBuaEBIHgEOqR%2BCCBEGIdgUgZCCEUCodQPidB6BRoyNInAeDcN4fwxRLjOC0nCWErkqAqBvCSak9JmTsm5PUe/CAHgYn0AulNLgyxeDeN8aQCASBolpFiWQSJeyDkgGAFIMwfA6C7FIZQWIfTYgRFaGcTpvAHnMGIGcWksRtCYAcC80g0S9x/VoM85ppAsCxC8MANwYhaAeMEeCvYhhgDiDBfgAiDg8AADdGZ9MwKoX54TthyPFvUPptBtaMg%2BR4LAfSLR4FsQinFxBYjxxtCwZFFKjCKNWJXJgwAFAADU8CYBRvOARciKnCFEOIWpUqGlqD6boVIBhuWmEsNYfQ2sPGQFWKgVaOR4UpODvddVVhLBmGcagZlxBSm4t1T0X5jQXAMHcJ4ToegwgRGGFUUYqRijZAENMPw/rMiBoYAsEYiRxj1CdX0SY7R3UFBjb0AQ51BjesWH62wCbg16DmG0SNvro2rAUJIrYEhukcD4Y4vprjxnJLSRkrJOS8nzNwMUlZMi1kbJ5asBAmBhSjAgCokAkhAg3CSIEREkhNFmEkIY%2Bx/hDFJEsRwaxpBbGyJuIYrghjTFJFMXu/wWj/BTsMbWsFrj3GePkTy7ZgSdnBKGeE8glBjnLPiWwTgrQWBYsRCkpgWUPRcCSDcLgGjCn4CILaspdTpXVIkNIeVShFVgt0BctpTAOmCKrTWpxQiBkvpGWM39/7APAanKB8DGi3gLNQEshIHwZFmHWXe5pfjdkMf2cst9UTuMnLIwBzURhQNcAcTQAWCQPEQDuWCt5Tz/kKY%2BV8n5fyEWAsTMC0FziIVQphbQOF/ysAcqMKi3TeAMWOBxfC5x%2BLCW7H%2BaSnhYKKWxCpWcGl2xnH0sZXI5lrKlDss5ZOe9fKBXCtFeK/5UqqmyuQ7IBVTTnEYf0MilAYjLBatiDqkdLiDUCCNSan0ZrrCWqETau1uXS2xsxc4CArg82pC9RUKNegA2NCa%2BkMNjQi1LBTXGtNuak0hsdXVpoCa%2BvZoLYm/Io2ZtTZLWsDYFa1lrvw3WzgbwhMUZE1RsDEGNB0Y7TB5jsi2ObKUaQAdQ7Eh5ZcxurdYHNGIjPYiHRkh53pNSAR/pbjbC3su34x9SAQnDL4x%2BuJCSOC/qmSwBQWKclYuo9iCYUHO2lL0LFmVNSEv1NQ8llpwQsM4a6et3pV6iOhPCW8UZ23iAsDhwjpHKOyxM3o4xrtgRAgXfvU%2ByHhz30CeWSARHnMfbI6SD7VH7dYfIaudJ259zHkfKUyrz53ynX/M04IbTfS9PQthfCuRJnOXed4OiuNNm8UEuQESpzggyWucpU8rzdLbV%2Bd4AFtlSKzOhY43wAwEWRVirDDF2QcXcfwaS0qkAwRVXGEyzYNz1X8uNHhU1WhpWLVWsq1gVPdhBt%2BAa66rrLWfX9e6yUHIXWOs5EW/m2rjR01dcL%2BN9NDfxjDbm/mybma2trbLStmpeGKdWq23Lt48PEdvElzcGXx3oMkDOz29jvj%2B2DqwHdqtj2QBmDA9z/w%2BitH2O54ifdl7x//Y8V4vtpBVGSH8JO/wpijFJEkEkHR06uDx84IEMfhG/2QOVaBSl%2BgBvaHGqwzKWQzgkgQAA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/sensible_classic_plume.hpp)
- [unit test](../../../../tests/unit/typelivore/sensible_classic_plume.test.hpp)
