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
CognateInsert
 :: template<auto...> class...
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
/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateInsert<Operation>
::Page<0, 2, 4>
::Page<1, 2, 3>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<0, -1, 2, -3, 4, -5>;

/**** Result ****/
using Result = Metafunction<-1, -3, -5>;

/**** Test ****/
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
                    >::template Road<Omennivore::InsertValues>
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

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIFcZqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJyal2mA45QgRMxAR5Pn5Btpj2pQzNrQTl0XEJSSm2LW0dBd0K08MRo1XjtQCUtqhexMjsHAD0AFQnp2fnF0cHJhoAgsenANQAIphprozIeJgKj2fXdwel2B5wBtxu4LMgQiyG8WEeJkCbi8jlohAAnojsBDzNCGLCvPDEW5kAt0FgqFicYCzo9sKoCK4AGLEWR/U5gxksNIGRnEgjo97MNgAOjFVLuC2IXgcdIZzNZggRAHYrMrnoirHcIVyeUw%2BUjdbzMMSmCjUGKRVjHrCmApfkJMABHLyfTCkR5moiWgBqrTwTFi9AUEtuUplBDljIY6BZsmJjpdbuJfuIAaDP0tVMC2O1qohj0LjyN%2BpNSK9FrFUUwAHdU%2Bng6Gi48vFkjI9lExgJgEYFno9E678WW3NW6/7A8HLR765PM%2BKc5qceql9qaU8/ej2SdOZhucbTebHrOM6Hw7LN8uLI8Fvq8MgbQIFphVGliJ6jwA3MSulUWE/0CYK6BNeQEaiB1L3LSyjEJgNCqNuVw6nueoGm4ApCqw7ofkQoZoMOaSRjBcF4AhiL9gQ0pllq4LricA4ICiBD0Ihu77qWh7eguuZhpREYMUxgEQWuUFPAA8mwDAMHgn4kOwIAAJIMEobR%2Bt4PysRCwo/GkTB7I8EmMNJsmwX%2BkElmhGGMFhWaLpKfGykpKkEGprq/EBargTREJAkcjwWHaPZuIFml3BZI4VpaClng5kZOQkLk/j8xJkiAIARFgqgAPpKEmw7EgptnYnZ4L5nczbhZxqCPGOAHYZF3EFkW55EayRCdt2TWFh5XXNsWKEHuVfXdUivXDYWBwHI8ADqPatj2JgAGwaMR8EFViWbLcW1WMD4CSlgiy1xoIAAqrTdgQIbLVaQ3jUWq2ketOaWsdBBncQF0KKQY3jVZ2mWgFyAANbvZ9P0jTxd23o4D74c%2B360Dh1V4Og6K0BA6zg48k2HRotUTqeW14L8ETaA0jLoI8ETFggPawQQOwMMWgqYDdtx3TjUSoIyNP6rjQiMQQzEmkTJPKS0ggBhTjyxFuCNuVjOMvpRenS1QrIsDTPbhY8unEFhjLEAobMc1NJ0IMTVO/PEojzY8NY9jWdCI7pwOPJgn4JHLBOAbdfU4xERC45e11YwAtNaAuCSafvNsSWPNq9oOYJdaXy6zYrfbH4342mc5Z%2Bzd1FoDIPnSnChp0lWbZxDq60YXw2VeW5qWrcwCwXujCXU242thEwAdl2C19o8WCwlZEAo2jKZMJiSJtx3knd893EY5jwkNyqXmQRVA0cc3XEigvmCd4IIYlc2ffth1w/9jB3OoDfxLH6fl1FXXYEf2Fe9oQ1IoKR6P%2BAApGK0pHLKQSq5ZKSJUrpRjC%2BHKzohx7AKkVD0sCMoINysgkcQD34lR6n7JuwUjxMjwEbAgucGz1SPI6fC6AqH5yRu/P2LUOxtUfkPXqhDN673YnyGuvY3AJyLDjWaLYlC4weqoJ62BNoaG2u7Bge19Y8yWhoJOZdu6h0Ec2aRsiXqKjelor6IiJpTXEXbdR%2BikQgJXlaLaQdgDVT0qye0WtR7Ewlig3RoiprxAIA7RgxYazVWmJ9E2RdCw2LcHYuRYoACyKN0D0GTpdAuUTCx/RsmKEuaSQyCJ7sNaG95Hziw9mIJGVNUbo0xoIiOOYBJC19rwos8dfGFk0R9culd1LTjMY8MhFDGEZgyZkpJ5JUkmN6a6fpHSBwNAEAw2sdUxlRLydMkA6dq6tNrhvLGxC/4vyXufSGvc2wDxvr2fsY9aATynrQGec83DHK7qcoqa865x2At5IhP8IotzFK8s%2BRSJH90Ht2a57CH5P3nu3E%2BJz8HeR%2BZBXyjwABKDQdhZE9o8YKkj/jIX4QCw%2BADmFiiAR6bJooxRiQILTYgg43SnIhGw%2BKqkkrnzcBg%2BB2VsHJiRIVbi6CCDoDSpgvlSCBWxLQQZelCQmXDmNo1PMNE%2BGoRJdVIZCwRn0EAbQxZMZdU0MPnShlxqWWsNitC9qXC/Y8LupVQpo15liLmpI6xsE1qCo2uKRxO1lFsFUQtI6Rj8nqMiVEmJ0V7FdM%2BmsoubqJEhpWl6x6tjfUOIUU4lxyA3G/HlZ428%2BVXX%2BJTkEpmgSwkmMjUXGJcTLQTJSZgfJCbHUs3%2BrkvSpdund2dWc4pLQYZlPhpUis1S0YY3Dtaek0ZYxGKxu03ZfVqU9nZYldSXKzUKqlUqlhy7mxpR1rCtw27iAWv3Zkx4R7/kQpHBs3tFctlVxVcu0Fh6QDHrtW%2Bl1B6ixxp6c%2BvpmcBnasoSsn27oBlNqmY%2BmZGcRRtvGnQpZxrF2Ln2YIw5gKj7wtfpa5dV9LlDyhbc%2B5NSnnPzwyczNWJPkb2%2BdvES6qDwH0rLhxebzQVEbvVC%2B%2BtrOpws42fJFy4mP10/iJNFwU0gKC8CxQl39iX8g7Tkq0JU2Eybk0JX5ol6KOhjKFW4xDV37rYQZymPUUUiRM/8qqRUbQGHcYqvY%2BrD51QI%2BZ1wCZd0oKRB5/BPEHVFls8ptjDnbTuLEu8VRORQVsNeC0Og3CyqEYuczd4ULov7X6DPPOGZlXqeKmqtp1n64sf3uhOz4XuKObtIV4Fy8B1gvbOipgdAoWJfa48oTCK3lFSPSzD%2BZWiUav5NV9CqmaVFbq%2B4jwgh2uRDIBl6y03sD0Boxp61FniTzaS0t4k638OBavL1ULY3DRTYQ9aSLvxsuxYEPF61XXkv2tS3dHjVkssxbvI9pER3EWNQY6V8TZ2JsmauxFpzDXqNcYvkWHj6LUBMEsyPF7PWXmw5E9xQb7xhug7on5E6gp7xiGUKgNIRntIKFdj2VM6JYgyTkmZGzE2/6gP4sTtIpPaDk8p1Zgnxm2ekPIQsDnsouc8758SMDoZguFk%2ByzKFUdmkjmzMiwX2Gg5gbc9VFDMZxeRkl6IXnFOZei4IB6fX6A5fvYR%2Blr75EmnC3NxQ9XYmv5C7CyQ7XFvdcLPobry0Z7PPWuN2Ts3SIdcB6WR6EP%2B75ctYHlZbhI9Z0KnjJdzCbBHjh9N2kYk8ecefqG/DwsN7iV3tdwsK3hqbcYY157yT9dpOoGAMwRkjpgBLyM%2Bd1jPv2M3ehwZH7uWttgMjB4dvpYu9L1O3873WQABemAspxXQXgFfa/LRxN6gllO3WUslcbhN5fq%2BCCWgANLvqLLBF05CNIQCzGYRa5hFoQEv0Ix4QD1h1LS%2BCgACWSUYDX2%2Bxyzi0FQ9CATDkv1Eze0Fwq1/hw0awI0vnSyuSdx2yz1Wzp1aAZyZ1gjSjz2l162O2LxTzL2vU/VvTa2SyRHRyo2EzfnINvSAPJBAIIHdykymiUnwD2F%2BFECZjEAUGqniF1nq0wEph43UR5UykQTyhQR0U3gh2zzLGazYTYKwCZgF090QJHDP1ALJQMIvwpSewn0eE0MYBSlFXFV5XkJwQKigJOze2PxXVP033Pyvxv0LDvy8Af1%2BCf3FBfzfw/y/x/z/w%2B3S3R1AKd3u1%2BwYEcO/xgLgPK3OXBUdxHiwMm1UOPDwMZxMnkmIMjzcDJTwXINL2aw/R1loIx2iM4IbxSwQJC3B0hyBSxya16h4wSU8FR37EsISNIMByK1x2og90wz0xBEmJ3B8lpAUn3FfniKM18imJBDBFG37y10H0aVuxH3AL%2Bx4k0zbw70wHXXn2UOF3c0g1QOamtX404U6hcIOXcK33XxvA8O31MMoLQPBTqKhS03kxjh/WEXmVgRYCYCBlXwlXsOlRjWwCQ0HTFRADBIhKyihP5XygzXsXQ2K0XUEXMycwQEXTtyiWIWMKim8L6jYTuKfnmUTyvU2MtAtQpMiPBQwMyO83mTjl/SvXbRyJ205PGiXR5MyVXTxSOJn0wG7y7mJDqOZOFKoK/UExKMvXlK5OwArw1QxWR3r1PUkmMjkjSnXSgWuNVPL2oMrxPQvVfVNKLA1ONCr38yuJVOFLlOGjtIOhqML1HwgJxNpLKzuk/mB2GieO9yOXaJNL6h4zZP7CEAJPdJ5mpK4UGP6yB1cMDN0z0PszaKYIjKjJIyd0TKVJQJSPTNRRWNBBmKeHpFYB5B7EUwmPLLWO1ChBhDhGHhJAED2EIgI0rPojiP6F7wuK2IOOtX7IgN0zRQSQPyoC8HxAHPrIZKBQ%2BgIy6OnNnMaAED%2BPFMZFOKRDHP2IhDShPQ0A9FSEeEkFDCPKTLcC4FPI9ECEvJABPVuGXJLMJwHC8DSGKEkMxW00jHrJ4yEE/O/PQF/Pk0jFiO9L%2BzcBPMeDDlvMeDPLDmCHPI9DDn8C4Jb1pDAruSM0Rx%2BHAqhSnJaBnLnIgLcHgrQpQvQswt7KJx%2BH/I5FZSHXvCygkLaAgFgQUCwjYq5SAq/MyB/IIruQ9BwvqOwHXgsA4E2FoE4H8F4D8A4C0FIFQE4GEUsGsBvG2F2AWihB4FIAIE0Gks2CBgCEkBFA0AAA4zAzAABOWyrgfwKyyyrgZUZUaQWSjgSQXgFgCQDQE8xS5S1SjgXgCuE8wypS6S0gOAWAGARAEAbYAgNIFEcgSgNAbkOgBIKILCTgVQSyxaMORaSQR4YAZAB8KQEUMwXgSQwgEgFGPQfgQQEQMQdgKQGQQQRQFQdQSK0gXQW8msfWNITgHgGSuShSoylSzgMSFEZKyMVAKgR4PKgqoqkqsqx4CqswR4CADwDK%2Bgd8XELgdYXgCKrQTYCAJAdK7nPa1KiAS6zKxIYAKQVIGgO5BICuCAWICaxnZgYgdEYa3gb6vAsSWIMmBwf60gdKpeMSBgWgP6nqrAWILwYAYKWgWgCubgXgLAMEowcQeGh/RoT2dG5Sl8LFRkcGwOXoCatEWIfWX6jwLACayiPAXyjG0gT2YgWIQS14bG4ANEIwIyzYKgAwYABQH0b4GsbLRS/Sxq4QE3Vq6QGWzqtQCavq/QQwYwawawfQPAWICuSATYCnfodGsOMkciUwDSywMwIK9mtMLAPWjGHoPoHIFwGMWYPwW8sIZYSoaoPQYobIAQN232zIf2hgEYb28YW8%2BoDcgYRYQOyO3ocmJoRYMOsYRISO2OzwToPQW8NoFO1YNOzYEQnYPYCQUajgeS0gQK3gYKxa/Kwq4q0q8q8yzaiAXAWq/avSo6gygWzYWmFHcYB20yyQQIEUWywIdyjQSQMwSQZaDQfwRaWy/QTgby0gXy5IEURaLgRaSy2ylyxafwSQRysexaSuia4K0KkAcKgW6KuK86hKmalKigW61AXarKnKjgVoFgT8ZUMOJgOrdsLgWykULgCy6q/AIgW2hq2QZq8QNqxWpQZWnq3QVIAapgIajGsuiuquyajgaapKlER4ea2u5a4q20ABoBkBhRbal%2Bq6hIBEKEMwLuk6qKu%2Bu666p%2Bth8YMhx6hyk8l6w2d6z6nqwG368GkR9EYG0GiK/SyGruaG2GiahGpGlGtG8GrG9W3G5S/AWCAmn4Cakm5AFEfYfSimzy5S6m2m9Eem/YZSpmlm/S9mzmpQbmjR/ua%2BoWrsUW8WyW8GmWmB%2BW9q%2BQBB7q5S5BtW/m82qwSwbW3W%2BAA2wiHIY202vsSJ6wK26um2lGPR/Wx2xO5wCAVwOOkIGMPOn228v2/oIpipnIUpiO3J6OwYGYTOgoeOp2gQRppYCoVO7OjO/Id2qYIYWpgurYYu1qzB8anqmupa%2Bu/%2BgeQB4BiyratuiB%2Bh5IJhnu0gPurARIB2zyleteoBye5UfwWytywIKemew%2B0%2ByZzgC%2Bq%2ByKs62%2BpARK2am6zh89d%2Bz%2BlalgBQT8B8T8eZ40BYMB9u%2Bq28vxuWiQBW2QJWkJnQJIUgVB9Bkape8uiZoKqah%2Buaha1Qb535/5wF0sBYLana2hjuwIQIdZh56Ki6mh%2B6t5ulvarZZAL8rKAF2yrKIFggLKXFhWugARygIR5S8RsRiIIGkG8mcG2RwQeRuGrRzARG5GsQVR1m9RnGmxzG/GxwQm/R1QUm4x3gUxqmnWyx6xxmtMex3gRxrmvcVx/m6ljxkWsW2sHx1miFlqqFwJ2FlWhFgwCJzW6J6m%2B2%2BJo2zgA4VKVJy262hIW27Jh2qO/oF29wZp/pz2rp/OoOkoHIKp4O/oIZ7OhOhp3prO1pvJmOwZr27p9OoYIpnOzplYMpwu7Skuw61FrBs%2BzgRavFv5x4dlkULlpZ8BkgVZw646jZrZgesu/ZkAOykUCl/wJyw%2B/yil5Ube65jFkK2wS%2B7uh5kykASQfwUe1y5UfyyyyQByrgayl/VFwIdF6u25nd06suqq9d%2B9zd5h3/Nmt652yQIAA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/descend/pagelivore/cognate_insert.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_insert.test.hpp)
