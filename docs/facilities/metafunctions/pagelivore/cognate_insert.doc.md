<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateInsert`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-insert">To Index</a></p>

## Description

`Pagelivore::CognateInsert` accepts an operation.
Its first layer accepts a list of variables.
Its second layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function inserts its arguments into their corresponding positions, which is indicated by the index list, of the previously provided variable list.
Then, The function instantiates the operation with the inserted list.

<pre><code>   Oper
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>m</sub>
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>k</sub>
-> Oper
   <
             V<sub>0</sub>,
             V<sub>1</sub>,
              &vellip;
       V<sub>I<sub>0</sub>-1</sub>, Arg<sub>0</sub>, V<sub>I<sub>0</sub></sub>,
       V<sub>I<sub>1</sub>-1</sub>, Arg<sub>1</sub>, V<sub>I<sub>1</sub></sub>,
              &vellip;
       V<sub>I<sub>n</sub>-1</sub>, Arg<sub>n</sub>, V<sub>I<sub>n</sub></sub>,
              &vellip;
             V<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateInsert ::   template<auto...> class...
                -> auto...
                -> auto...
                -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateInsert
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page
        {
            template<auto...>
            alias Page = RESULT;
        };
    };
};
```

## Examples

We will insert `-1, -3, -5` to indices `1, 2, 3` of `0, 2, 4` and invoke `Operation` with the result.

```C++
template<auto...>
struct Operation;

template<auto...Args>
using Metafunction = CognateInsert<Operation>
::Page<0, 2, 4>
::Page<1, 2, 3>
::Page<Args...>;

using SupposedResult = Operation<0, -1, 2, -3, 4, -5>;

using Result = Metafunction<-1, -3, -5>;

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

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many variables we must pass to reach the first target position.

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

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

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
template<template<auto...> class Operation>
struct CognateInsert
{
    template<auto...Variables>
    struct ProtoPage
    {
        template<size_t I, size_t...J>
        using Detail_t = Capsule
        <
            std::make_index_sequence<I>,
            std::make_index_sequence<J>...
        >;
        
        struct Slash
        {
            template<size_t...I>
            struct ProtoPage
            {
                template<auto...NewVariables>
                using Page = Send
                <
                    typename Send
                    <
                        typename CognateSegment<Detail_t>
                        ::template Page<I...>
                    >::template Road<InsertValues>
                    ::template Page<NewVariables...>
                    ::template Page<Variables...>
                >
                ::template Rail<Operation>;
            };
        };
        
        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIGYAnMEADqgKhE4MHt6%2BehlZjgLhkTEs8YlmABwatpj2JQxCBEzEBHk%2BfkENTTmt7QRl0XEJSam2bR1dBVxTQyMVVUl1AJS2qF7EyOwc5oERyN5YANQmgW5ejrSEAJ4X2CYaAIIHRyeY55fICgToWCoj2ebzMhwYxy8ZwubgIdzSmAA%2BgRiExCApga8QQB6ABU%2BNxp2wqgIrgAYsRZKcCbjsSDSSw0gZSTC4QjmGwAHTczEvP7ELwOIkk8mUwTnADsVglABELlYsa8GUymCzLsrmZgYUxrqhuZzHqdjkwFApTkJMABHLyMXakU46oj6gBq7TwTFi9AxgSer35goIwtJDHQFNkMIt1ttWsuruI7s9mAU%2BuBPpBJilINO2dOGtVMbcjr13KimAA7nGE17eTnTl4skZTsomMAvhcZearTaIQXSxW3R6vfr7ZXB0mU2nAgq3rL5enXniCacALICVBEBh3akEulKzCMzXa3WnUeJ3n%2BoWrhjrgQPLFS05/VV4ZBGgR/TCqNLEB3HgBuYg2pKFinvQGZylOkoQdOOI0k2xCYDQqjbviu4vHmaqwvCjCsJg9pZAAXkiBC8mgPZpIGygIUh3wdiiNpzoqLyLvi5oINcBD0ChtL0vuKqYUWE6%2Bny9FCkI7EEJxMYwQucEAJIMEoHSut4SbcWhGEFmyOFcjyaZ%2BqJgYKUpBAqTaZoZtK0HzsxcEWCaXyFko6m8Qe%2BZHk63JyeehmnMZCSmYBSYwn86AgCAERYKoiJKFGPYwnJQm8pZWY5ppHmoKcfagXhv6eQa%2BkvLWF6UZSRDNq2qXZilry1rW6W1XV1WXFVTU5ti2KnAA6l89ZtgAbBoVGIXgqgJY8KaDbmmWMD4CT5ucg1hoIAAq7StgQGKDQajVtTmw1IeNPr6stBBrcQG0KKQrV7dpHKYPq9nIAA1udl03TmNZtU%2BjivmRH4AbQeWZXg6B3LQEBrB92YdYtGjZQOZ5TXgZoRNomAOJg6CnBEuYIF8CEENsDC5thO1FW1sNROuXwEAgqpw%2BJHFgcjqOKW0gjuqS2OxFugPmdDpyw5%2BKJMJj2NUJSLB47TfGaqcaTtLhpLEMmguwytCAozjZrxKIfWnGWXxlnQQOKy9pyYH%2BCR84jYG7XVsMREQcNXjem4mNtgsALSGkzkn2xTTUwoLtanW9mCbeF/MPdy10O3tCPxmO8dB3tpxPa962Rwo0dBSmCefZOMlp/VcvuZcgnci8wAIfujCbV9TX1hEwBNi2baBB2WDHNpECg%2BDMJuxuDyXDXddsII3rYEJkNQ1OrXgYxbwO%2Blle6vq4%2BYPXU9N3WDZtxVncdlRN5HzCW875tSUL/e1lMWvhYb159pV5yABSPkCkK/nKUF3puFCuFSKn4YpdmjAlIS%2BF/jAJDKA2K3ZdgwnfjfYSNU06PyLKcMkeBVYECTlWXKWCLRkXQAQlOwMkoOxKvBM%2BHdF6ZkLtmBqpci5uFDu1TqPV94DSGtRUaR0Z48imi7WabBUSkjhuHbOjcvZMLqgdARlxvLHW5NIi6OdU7p04d1XqzlPZ8JGmNS4n9VEGhEZlYAmUxaUlNDLU4%2BAnzxXkbWWG8QCBG0YLmMsmVpiXXJto7MijjFuFMUIzky5QboHoBHTaWjAl3Vwo9MWWcNGN3kXvYqbRfpvnZlbMQwMcZgwhlDeRvsfRsWZlqDJLUXE5nUZdPOqlhwcOzDgvB5DEzxO0ZEgEMSZG5xADHFpdTswkIEGQ8sOVunp0zrEwZwyeQ1KeLfFerDmHlwEs/Tkl9J6N0KntFujYj60QcRjWgfcB60CHmuEeF9a7bz2dPWeax57TlrEvVZrVMHbN2Q3aerUjmHw7qc0%2B5V6FjweVfZMekVkwVnF82SS4ABKGNthZGtqcJyXwaQaU2QWN%2BclX7bPfvaRJulOQAHk6YJEjIg4KhUaG/0CqpABQCIpwOiggiByioGPhgRyqKYC4pIJMXy6l%2BNiB0ujDCgqaDGEYPxRlbBuC/idPoMSl24yQzqqIdsiVCRdUAuob5MFqBz4O3QbdJVNT2GjKFlwvRvDgmCMmhoaalsGBzQkbwhpOcDEBMCS65RE01FijOgMmZe1YbcINgY4NoTQ3mPdS7KxDpkC2LNDShxKMOZIPtW4yOniSYeN8QMwN2iE1hP1L06JmB5lRrauS2OnI5kDMFpknMP0Xy5IBgUrBVzIY%2B0NMSYMoZw0dtqesuqza/KKQCmZBlbgDVSvAT2WVnamrhU0u3SqlwV1GqodO2s278W7oLG2tJCz86wsncJPap63KSItdOkO9q/VRyGTezkjamrtLVVMu2eFWkriif0q9TSbQjOPTmbVkz%2BzJzPMs5egsfn5T%2BbvA5bUgXntOT3C52F%2B7FJudeO5kKJ7/KTY8Oey8PkIpLmXJ9BLflQqeXvHDJz2y0PBXutwGHr63q%2BfRmyLFCSFjSAoLwXFcWuX4lpbC90j00PE5JsCiLbJLgtCGFye4mOsgU0k29Blv6Bi09jFKwmH5KvVNZp%2B%2BVDTGjsdKnsmriychysakSJnOwhgjGu0VbgPOoPTAqxjcnWS2bfg5gwdjKUIgkTkPeNCZSRzRNcy1oXsMH1JgiU5cX5rNBhEFwT7zPqWbWWFw8Nm9Pr3sxUxzsr%2BOedrDh5FaXTkpbaHQe5FGp5CW3dhFD5XZNVdhLZ5tQkjQxbNB4QQaJIhkByzpFt2B6BscZb5MzMJZtdYWzCVb0Lgv3lKxsmrY2zsTdhVNk0Zp8sJYEEl3ynW0sMJO3VHD2k8vxefA9y4B2nk3ze58hjaVxvjYMxS6LN3N6sco1h7MrXUBMHM13U4z3uvkcef8/rIBtJDfvms0TpwVrwhfGIZQqA0g6fQpF7ZX8AzE9J6IWgFOqcWYJyNiudnMr/pIht7zJO0hk5Z5TmEvPkqZYR9lz7XH/ZSRDsXELHPdPhdqzz1VBBXOdlIfToUgvhes7Fxr%2B0cGJdvY%2B9hU5cu1NuHF4ru%2BKGVejawbzrXcHXP6hXZ5mh%2BvmeG8uK77XEz7Re6PVanMFuESL1R6O0U4Z1QQ6%2BL78nov900tVjjvH8PTiPrk%2Beo3eCTcYwmameFyuNOsQ8MAZgpILTAD2dTx%2BaG3NQ9i99wr/OGdV5r5gOveyQtvcfoRYifl8J4CIsifUYTWrJdS91jLb3Ktc%2BH5P7kABpTdpwELWlwWpCAKYzD9XMP1CAa/vhuFOO/V5gscMAAkomMGRF9griXlH2nft7NfgOGHl6X1s9DsOmG96Ee2WnGqOW2Ce7IuEjOQufuqefGgBAmcqA2Ue2eue8sbWGObg6O1ymOh2sK6BC09%2BAIj%2BfOcKImnUCk%2BAuwZoogJMYgCgmU8QCsN2WM%2B8rccM7KICXK/mWociiqF2iej23mxBWAJM7OjuAhqugC4%2BI%2BRKj4shq%2BH8whDOohjAIUAq3Bwq9KCU7%2BR2ac4eTUQ%2BihBA%2BoG%2B2etY2%2BXgu%2BZo%2B%2BPIh%2Bx%2Bp%2B5%2Bl%2B1%2B8iOGOBT%2BXGd2P2DAuhl%2Bn%2B3%2BTEhy0ulusurg%2BmUBbAMBBu8B8hKCBBuOg2FhOYhBkimBuB2Bc%2BtAyIpeP%2Bkhf%2B8mkRLaTW7G2Wq4tAKOHYahvheBAOCRWeZekhRO3e%2BYzKjeYOZ2UW9W02pw3hHewkymqA1erR86HQA%2B3ytO%2BUHmKhQoZqL6dGi%2BoOZ2K%2BRkY%2BE%2Bph3I0%2Bbh2WHhgYXGKmUm1Sr6U6gS/KYUIALATAz0SIWh3K8UIaPov6dU7Klx1xiItxvByCVGyGqye0gsNCQgMWCAHaku6cxh6x%2BoKiwB2iNCcx9C9qhhpxuYkxbmRqm%2BwRHBYBHYW29qHyJxSJRhiePm6AIGfx%2BJBJt0RJLRtemA9eDcMIux6JFJqRXw58vKRmMG2ijwLJpwyKSOJJyioxLKAsyRBJPJbJbgh6HJFJdU4pEKgWQGG6op6cTJW6uOZ66RMIfRr%2B5BCJ5Wfx%2BpbUqGKJMOvW%2By0J72oBIKsuQJ4pZU5q8pTWgRBhw2q8Jp1ciBzWIBmJ1pqOcJvGTpJWSuTRNIoZYZaEROK0SYm01OomYZoZaE6YYIHwUIncVwNw9wyUTuXOXRAxvk2pv2Jczem8F0nmOGy4qWVAXgEIzQpy1JmAzKWp7eOpII4UEp9QpwZg9okgvIbZ8p8wnZ9ogQvZIAEpLwpZzpIIOGQgXgaQRQWMqKqmexqOBZNRbgHZ3sA5XZpw3swQpw0gO5/guRTErWSYUmy5HYFZbQVZNZr%2Bbgm59ou5j5R59uay3ayAiIrBHQEA7KCguEn5ACM5c5mQC5Z5Fy9oi555jwbyHAGwtAnA/gvAfgHAWgpAqAnA7Clg1gj4WwOwbYYIPApABAmgsFGwz0AQZgnIEoZgkgNQNQ/gGgyQ/gZgGg/UNQwQ8FHAkgvALAEgGg9QyFqF6FHAvAuc9QxFKFsFpAcAsAMAiAIAWwBAaQ1w5AlAaAjIdAhquEnAqgNQ/U3s/UkgpwwAyAr4UgnIZgvAWMhAJAoMeg/AggIgYg7AUgMgggigKg6gklpAug8wZYqIaQnAPAcFCFSFJFaFnAlK1wylgYqAVApwul%2Blhlxlplpw5lZgpwEAHgGl9AP4BwXAawvAElWgGwEASA6lQuuVqlEAFVmliQwAUgXZNAFyCQucEAsQ4VsQEQ7QdwQVvAXVzAxAdwlKsQ6MDgfVpA6leylKDAtAvV3lWAsQXgwAhYtAtAuc3AvAWAlxRg4gC1u%2BDgeA1sG1qFn4aKpIE1zsjQ4VtwsQqIQ1HgWA4VKIeAvFm1pA1sxAsQIFKWO1wAtwRgJFGwVABgwACgzoeA5Y%2BWyFhFDlwgzOLl0gcNHlag4Vvl%2Bghgxg1g1g%2BgeAsQuckAGwlOzQG13soU7YpgWFlgLFvAqAn18YWABNkMfQGMzQLgIYswfg8wYQEQowlQ4w8wRQ2QAgnNhQmQwtDASwYwiQ8wdgrNAw0wnQng3Qegcth1AggwHQUt/NMtCwMwytcwetwwvNywAtGwjB2wuwEgIVHAiFpAgltNnACVelBlRlJlZlkgFlmVuANleVBFhVRFQNGw%2BMyO4wzN5FkggQnIqQEokgGgkgNFg0Gg/g/UyQ%2BgnA3FpAvFgQXAnI/UXAbFyQNQBd/gkgXA/gqQ/U9t4VwlolIA4lQN0lclZVCl0VKlFANVqAOVWlbAnA7QLAf4Eo3sTA12jYXAyQnIudp1%2BARADN9lsgTl4grlyNSgqN3lugXZ/lTAgVm1NtdtDtEVHAUVSl1wpwcVDoxAA9Q9I9xoY9E9U9mV2VlVCQ5wYIZgAdxVUlLdtVVVHdP94w/dg93st9DVyQXA9QzVKsbVHV3lA1PVE1cDQ1I1Y1ElhFU1DcM1c14Vi1y1q161E121mNe1qF%2BACEh1x14VZ1yA1wewhFV1nFqFt191dwj1ewqFL1b1hFn131Sgv1RDrcjdINLY4NkNZY0NE1cNi9iNbl8gq9XlqFG9GNgNlNVglguN%2BN8ARNFEOQpN5NXcKj1gNNaF9NoMSYmjLN6tfgEArgot3NIY2tKwgt4tzQtjpAQtzQDjAtFjzQmtSt%2BQXN3jCtiwJt0tqtitrjT4WtITOt1tmwltLle9YV3lwlF9V9w9o9bc49k9nI7qEAPts9r9OdH9QdpAIdWAiQzNnFmd2dE98dEoFdEoEogQCdkghl8wB9tdtg9dgdklpVzdSAilMV1V/9xAUQ2lHA/dyVLACgf4r4f4WTmofwVlM9tlYU8wkjCNEgSNsgKN8jOgIAwQW9O9wV6dttSTQlkVbdsV8VkzRl0zszpw8zE9izgYWVXdz9ftgQgQxTvT0l5V7zdVwzALuVQyyAc5iITziILzn5l9hlfAdAUDlAMDqFiD81hFqLyDrNE16DggmD81JDmAS1K1Yg%2BD71hDu1bDW1B1jgFD3lVDNDl1gg113lTDPVrDz18YnDvA3DP1%2B4/DgNvzQjYNENUN7IEjC9mzy9OzcjaNBzSjWNVNNgt1TNWjJNnA2IQCBj1NQlJjjN5jatbN1jHNBtATPN5QoTTjxQOQrj7jOQnjutBrQT%2Bt/jqtjQ8tGtit9rYTQwETnr0Tjj5tuFVtBVpz%2B9NdTttzpw9zczCz%2BYfw3tKznzBVRVJTZTYdNt1TEwnIXz/gDFZd/FXzEobF1dyTnAddDdvTZFIAkgEoFl9TXAUgyQdTqQXAEopzgQ5zjtIlPTJVNtllJbFz3bn9ryH1rVOQ1bQAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/pagelivore/cognate_insert.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_insert.test.hpp)
