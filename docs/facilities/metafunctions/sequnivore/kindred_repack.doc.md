<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sequnivore::KindredRepack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#sequnivore-kindred-repack">To Index</a></p>

## Description

`Sequnivore::KindredRepack` accepts a list of packed sequences and returns a function.
When invoked by an operation, the function concatenates the packed sequences and instantiates the operation with the result.

<pre><code>   Seq<sub><i>0</i></sub>&lt;Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Vs<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

`Sequnivore::KindredRepack` can also handle `std::integer_sequence`. The function first `static_cast` integers to `std::make_signed_t<size_t>`. Then, it uses the result to invoke an operation.

<pre><code>   Seq<sub><i>0</i></sub>&lt;Type<sub>0</sub>, Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Type<sub>1</sub>, Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Type<sub>n</sub>, Vs<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredRepack :: typename... -> template<template<auto...> class...>
```

## Structure

```C++
template<typename...>
struct KindredRepack
{
    template<template<auto...> class>
    alias Rail = RESULT;
};
```

## Examples

Here, we first concatenate `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>`. Then we pack the result into `Sequence`:

```C++
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct Sequence;

using SupposedResult = Sequence<0, 1, 2, 3>;

using Result = KindredRepack
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::Road<Sequence>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Sequnivore::KindredRepack` is implemented similarly to [`Sequnivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Shuttle` or `std::integer_sequence<std::make_signed_t<size_t>, *>`.
After all variables are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<auto...>
struct Shuttle;

template<typename...>
struct KindredRepack {};

// Base Case:

template<template<auto...> class Sequence, auto...Variables>
struct KindredRepack<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
struct KindredRepack<Sequence<Type, Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation
        <static_cast<std::make_signed_t<size_t>>(Variables)...>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

// Recursive Case:

template
<
    template<auto...> class SequenceA,
    template<auto...> class SequenceB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct KindredRepack<SequenceA<VariableAs...>, SequenceB<VariableBs...>, Others...>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Shuttle<VariableAs..., VariableBs...>,
            Others...
        >::template Road<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template
<
    template<typename, auto...> class SequenceA,
    template<typename, auto...> class SequenceB,
    typename TA,
    typename TB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct KindredRepack<SequenceA<TA, VariableAs...>, SequenceB<TB, VariableBs...>, Others...>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            std::integer_sequence
            <
                std::make_signed_t<std::size_t>,
                static_cast<std::make_signed_t<std::size_t>>(VariableAs)...,
                static_cast<std::make_signed_t<std::size_t>>(VariableBs)...
            >,
            Others...
        >::template Road<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEhoAHKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHOaBEcjeWADUJoFuXo60hACeZ9gmGgCCewdHmKfnyJPoWFT3jxezwImBYaQMILObiYl1QADoEQDnpNiF4HMchAhLgR6GcrM9ASCwRDMFCCDc0oxWJgEXCkU8UWiCMcANIRdDETDoABKmDSTGQAGtTgB2KwigAieMBgIA9LLjhYmEpjtClCAZcDQeCmJDzkSdXrobDafdjodlQoMZgAI5eRjbUjHGFEWkANTaeCYsXoCnpjPRbIYHK5vP5QqhQlt9oY2yhHuIXp9mAUpsCD3TMrFgOOueOBpJZO1hfOLvhiPT5oMCitAHlKcRdTl6XnjgHmRLMK06Dm8yZs89W62vFkjPmKR8zhLjvWEk2BPHPd7fWmM/inq3%2B1LAuve7mC7rSfri4eoWXV1XLbSnsBOaDGAQ/ZnB3mRxFgMduagmOhPtPO92tBQjed5sIIqYVtgIAgOSlLSgSkrwUCTwHkaqFHm4sFUmwTrnpBl41tadoOpgTpYcwbDHAAKhOuEmgiCZJr6/oEKigbspyPJ8gKgqRtGJFQjRlJOoxy4pqu9L9uurboUWxKnqW9F0pWFqEbOjZNC2ebtscAFMD2L65lJe5Dm%2BY5YX%2BM4NvODAmZu5zzI4yAAPqiJMUI/NBLBMIKmDOVkwCROgzkEB5eAAF5%2BaFmbphAonJgoKwSTuJlbkhJmyce8lGnhynYAREFwiBmD3uBWm5mZH5fj%2Bll6T25zFaVj6rtBWHpYhKUEs88qfpgyCbFkABuHxquwmooSekIEucGWTRhuVmqpVpRsRsaYE8pCzdl81KYt1bLfxa02CZuXxfQDJOidSlnZgFgKJthnjpSFE0gitYEAgCR%2BtNDzIqxTKshxobcRG5wrTG2wvOcN0MquTrgyRVjQ0uyZ3XDM4fV9EkIdJeaZZhc1nrtKn7VZc6ac%2BG7af96J1UBj3GY9w6jh%2BFlToDwacWGPF2X2M1M0OuaYtiuLI4mYmwwiIko/QaOQQ9VOC6272fcQhW80Z6atXNn7fugULqTZAKdYrorbruj34/jC0k1eCKNWBj7lcclW6zV7N08Bt4lY76tazBE7teb42ydNbhbYaGHkdSdGuvhS1ERD60KzJhP6hOL2x%2BWeUFYniMp3jGfUtRG0ZUXlFUcdj2nTL633ac1fXbXd0F/u5evXCKtfTKlM6UGIZceGvFg4dkOCRtxww372Dw6Pt2CTYk/N9PTpd2r2MvAOptW2nxpxznCeGxTv2mzpnsM1vSsuyzT2ToE0791zIO8QLmvh6/Q6eSAEQgsACT%2BXPDyBB0BeR8n5AKQUQpAJASALIkUoHpmluLZMks4RIKYrdFeGshxr3Vh/e42ttpu31ucI%2BzYYq4yMh1C229d7W2JvlJa15vZNSfCfZm75iG1S7PpICDUWG%2BxagHOCJs0qiO6gAKikdImRsjZRyhkdRFMj5jgyPkZI2RmjpHqOQvjL%2B3lfL%2BTwIFLkCC3BfzgVFe415iDADYYCTkdo8CcitBASxqAqC0ggE8WxiU/zs0kCsQEOkEZrXSs8V2QgvBpGKMDBQXhaDMnZqEuM5wNBOi4E6MwTpAjGxoa7Xk8TEmWUfsDIePd36n2AdBH%2BmA/7EAAatVJbgf5Og0PcS6j0v7skwKoRpScoSZOOGYDpJlunBl6f0gS5xcmUwISAaqJC3ApKPGucajk8AuUtAkAgbjqmwOpM5ZUUJCkJIIPDaJsSuJFOitgIJO4OBrFoJwfwvA/AcC0KQVAnBw6WGsG2DYWxJxmECDwUgBBNCPLWIKAI/g4SBH8FwMwyQNCBAAGwijRQATiCJIfw%2BhOCSF4CwJI6T3mfO%2BRwXgCgQDpIhR8x5pA4CwBgIgEAGwCBpEuOQSgaAwR0ASFEaknBVDJDRQAWjRZIY4wBkDIGOFIOEZheBckICQPAIDMn8EECIMQ7ApAyEEIoFQ6gGWkF0JkgA7o2NInAeBPJeW8yFXzOC1kuFy5kHjjiiolVKmVcqFWSCVccCAHh%2BX0GIKcEFXAVi8HpVoNYEAkB8rSAKsgFAIAprTSAYAUhsk0ESV9SgsRnWxAiG0G4dreBluYMQG4tZYjaD6vSsFfLHa1gYLQStZqsCxC8MAaEtBaA0u4LwLA3kjDiB7c45teBhojs%2Bb0vqlwdhgtqc8s11xYiNjrR4LAzrWJ4BJaO0gw1iCxEyJgTsE7gDXCMJCtYVADB2LdHgTAlrZzvLBdq4QohxAGp/catQzqLX6EMMYaw1h9B4FiDSyAaxUBpCaCO8VPwpymD%2BZYMwFKz2JiwHBiAaw7CzucBAVwMw/CZLCBEEYVQxiZOKNkAQFG9CMaaIsUYNRegkeaFMDonguh6GIw4fofGON0a4/MaYAmCiZKk0MGjSx6NEcBdsCQDqOCvNIOS3glLvVisldK2V8rFVmBDbgNVka9gxrjQ%2BtYn0fxjEI6QGFkhAhwixYEEUkgNCSDMJINFGgND%2BGxQSjgRLSAktBXCNFXA0XJCxckOL/hJBcH8J5tF2nnWUupbS8FD6mWsqTey913KM1ZojUKtgnA2gsEGiKcVTBLxji4FiuEXA4SLvwEQPDegf26v/dIQDShgNmt0Nk61TBbWjo01pnTLqOBus5ZcY4Xrav1ca81j8rX2udZDWG1NEao2BDMLG/LDLE3JtQOGhIPLM3XcO2MdbDWLRGFa7UPgdAQRq2LaW8tdaq2kBrRWhtTaHCA7bQ%2BDtXbnW9v7YO4dgPx3ganZ8/AnIRPzudUu/qIJAfrudVundNw907E%2BYe49YKz0XqUNelH74CtPqYC%2Bt9H7nqA/63%2B/VQ3ZBAdNZ88bYH70YasJYaDsH4AIaQzkFDaH74i%2BsNh3TuGNUpkl9xkTpHyMycoyEYM4nlgMcyEx3IOvWPG/Y4pzjQmGg8YGNJ/IuvhNNHtwpio1u5N8ZY57hYVuJPqfWJsNTMawtzey5wZ0xA6sNaa697bbWOsaHM91kgx2bPnYTfZzAjnEjOY3RFqLbXfMinSyKEUgQ/MBdS1ls1OXbB5fjYy5lbKOUeruxVwVwqOC1b9SwBQg15WDR2ySSYKqU%2B9a1bIAb3PDXyBG/znQIBgiTem/a0PTra%2ButK56qgkeWC9/74P4fh5Jj7Ye2m47gQzuN8uygc/Eb2/37GAPmJzkh9YuciPggRyo9Ss%2B4Wn7CAEtM1YHAHE9UA%2BtRtZtCHa7dtTtbtNHTAPtAdMQRHE9ZHSdMnMdGdTHNXM1HHFdfHQQBoQnGDYnUnA9RMSnXganS9OnSdBnC7PgZ9BQV9d9T9DnKfLnCQHnI1efEDJfIXCDTDGwLdAjKXZDTgWUTyBXLDHDBIPDNXeDDXJoFwYMb3PXdAA3ejdIC3HIDQtjHIbQyTW3TXXjQYDQ53UTX3d3f3H3B3QTewt3WjQ3FTIPfVWbDfClCPHvaVPvAfY4d/OEL/ZPSzNPa/OzUgBzLAXPDTAvEAMwNrQIBFfwXzWoVFLzeLGvbwqlevOlSI1zINKVZIEUVrNFE7QIXzNFfwfFDdQILw3TTgWzC7DTZVbIxo3Im/NYM9LIZwSQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/sequnivore/kindred_repack.hpp)
- [unit test](../../../../tests/unit/metafunctions/sequnivore/kindred_repack.test.hpp)
