<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Stockivore::TypicalPaste`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#stockivore-typical-paste">To Index</a></p>

## Description

`Stockivore::TypicalPaste` accepts a list of packed stockrooms.
It concatenates them together and uses the first stockroom to hold the result.

<pre><code>   Stoc<sub><i>0</i></sub>&lt;Seqs<sub><i>0</i></sub>...&gt;, Stoc<sub><i>1</i></sub>&lt;Seqs<sub><i>1</i></sub>...&gt;, ..., Stoc<sub><i>n</i></sub>&lt;Seqs<sub><i>n</i></sub>...&gt;
-> Stoc<sub><i>0</i></sub>&lt;Seqs<sub><i>0</i></sub>..., Seqs<sub><i>1</i></sub>..., ..., Seqs<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
TypicalPaste
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPaste
{
    using type = RESULT;
};
```

## Examples

Here, we paste `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>` together:

```C++
/**** Vessels ****/
template<template<auto...> class...>
struct Stockroom_0;

template<template<auto...> class...>
struct Stockroom_1;

template<template<auto...> class...>
struct Stockroom_2;

/**** Items ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** SupposedResult ****/
using SupposedResult = Stockroom_0<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result = TypicalPaste
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalPaste` using recursion over the total number of packed stockrooms.

- **Base Case:** Handle several amounts directly;
- **Recursive Case:**
  1. Concatenate several packed stockrooms at the front directly and place the result into the first stockroom;
  2. Invoke `TypicalPaste` with the newly packed first stockroom and the unhandled stockrooms.

A simplified version will be as follows:

```C++
template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedStockroom>
struct TypicalPaste<PackedStockroom>
{
    using type = PackedStockroom;
};

// Recursive Case:

template
<
    template<template<auto...> class...> class StockroomA,
    template<template<auto...> class...> class StockroomB,
    template<auto...> class...SequenceAs, 
    template<auto...> class...SequenceBs,
    typename...Others
>
struct TypicalPaste<StockroomA<SequenceAs...>, StockroomB<SequenceBs...>, Others...>
{
    using type = typename TypicalPaste
    <
        StockroomA<SequenceAs..., SequenceBs...>,
        Others...
    >::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAA7AAcpAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJgAzG4CABPJKMViYAB0iLB2D%2Bw2IXgcFwAKtC8KJaMomMNMBcTLErLEACJgqynP7rdYXCxEkluFkgP5/AFAp6YMEQ6GwtgXQnIADWmHQdVQ4uIqFQLGRqII6MxOKSeLEhOJ/NFEqlRFl8sVoJRdPJfwuVouXjSRguUJhpNBlJFTHFkulRoVNM5VN9dPejIASphkMs0gA3Vnszmnbl3Xmc8GW60J4F88HppPgpheIiI%2BHIi7IAwKBSF4ulokKC5esVyhUnUipq3ZkFZwGJjts/OoSumktlitIwfV8t1w0N402VsOrsZ/l5guj7BDmuFoSYACOXkYqxOClIpNO1vnPJ7y/7q/X5c3O73DFWFiPc8dQoRiIA8gQENEFMmZqHiqGIENiuL4tqPb1o2LC/OCW67vumCHgO2DHjBM78ohj7PiORamseP5/sQ%2BFKuatInGetrBMADqCs6rrvswwrqpqBJEiCp7Wvyc5nphTbYQ%2ByGoYiGHCU%2BmAvmhLbcWeVrEf%2BlZyc62AgCA74Br8/qgpR9JfJ8PwfJsFzYKorB3CSrz6QZ%2Bw/JyZigsEpZeFgzpuGgklJAQAGmnGZy7BcABqmDllUtbWfGC45hC0WXn2aG3mRfmnGioGTjK04KgA%2BhoWlcnFmaxReRVXol47JUBaWYgJLDZVw%2BVRSV/LtqVCU3hVaHKqqYG1dlZiNQFlxXNyEWHAVzW5u1BFVSBNU7rlg2tUu03kcBPV1gtDW6f5y1TSuM3deliH9UthUrQda3Vb1C2goNxl1l4SR5JKoYKF4tBgZFJw0faQhPS96BvR9YFgq6fV5QhC0aOJ271bD/UI3dfk7YGQ3bBcwOfS842nL9dFY6DLrgRqkGcXydIpipENCXDkPoSeVHWn121uCdbSbXDA2EXOfXc2zt1rci6maajvzvIFWKhV9uPAU8eLZTW0QEBAwzoOpChworvluITGEA6kr2hSDyJzINHALLQnAAKy8H4HBaKQqCcG41jWBcChLCsJLmKCPCkAQmgWwsYogNbkjwho8RmGYACcsdcNbUfxFwsSxNIVscJIvAsBIGgw/bjvOxwvAKCAMOBw7FukHAsAwIgIBLAQST5uQlBoLcdDRKEcKcKo8QAGwALQD5IFzAMgyAXFI8JmLwkqECQeDq20/CCCIYjsFIMiCIoKjqFXpC6G0ADuxBMEknA8JbNt20HTucF%2B%2BYt2BqBUBc/fD6P4%2BT9PEdmBcCAHhO70GIKSRyXA5i8ErloBYEAkAdw1KAtuEBEFdxiMAKQZg%2BB0ABKRSgER74RGCA0SEV9eDEOYMQSEX4IjaDDJXf2HcHgEC/AwWgZDD5YAiF4YAbJaC0DLtwXgWAWCGGAOILheBiAMLwNGIRjtMCqDDPmNY/tggAkzo7WgeAIjn2oR4LA98VR4FzsI0g0ZiARENpSQE4idFGCDgsKgBhgAKCCngTAJ8vwwntv7Newh8Rb2kAEveah77H30OIlAbtLD6F0WXSACxUDeQyEIoeaswamEsNYMwRdLHEGXqFeACw7CyOcBAVwYxWikECMEPopQBhtDyOkAQ1TcipFaQwaY/QYgTCqOU2oIwmieBaHoMpDhOjDJ6Y0vpthhntImNM%2BpMwmmlK9qsCQN8OC21IIXXgxcP6DxHmPCeU8Z4AIgLgReYDfaQOgU4hYf4mBYBiBAEOIBJCgnhLHUE6cNCSDMJIAe%2BdrYD1jvoTg2dSC5z9vCAeXAB7xFjinAe4dE6/IHns%2B%2BxdS7lwDk4mu9d4GN2fq3CgqCFRIO7r3DgDQWCRliEPJg657RcFjvCLgkd574CIIUleO9AmbwkCE2QYSD6O10Ngs%2BF9yHbN2fsh%2BHAn7N3zBcN%2BRyv5j2rGyjlXKNCAOAdS25jkzBQIJVXOBCCqXoJQWg0BKADBGHZVwGGNBPr/gIUQkh1DyGkEoaQ2h9CHB%2BuYYwVh7DOGO24bw/hgi/WiPsWsaN0jZHyPvkolRAI/UaKqPfHRejSGGOTdAwpZj/aWOsUoWxYijAONAJavgrj3GeO8b4v1ASN7iG3qEpQ4TD5SqiY47JVg4kFsSe8p2qSBDpMyS6EduT8nRH5cUpJ7RBkuAYO4UZ4xalbpmbMZpnSaiLOSMejIB6mnrsmQILoowd01ImTUO9PQVm9PGQsh9H6phvtmVsxYyxNmQMhTsu%2Bh9DmfxOayui7LOWR0Adcvl4C/bmpgcHUgzzXmUG2dC2FHKAWxGtrHNOoJAXAskG0RVuLbD4rQ3A4lSAm4vztTa0BPc2CcHpd/FgChIxT0jLBjMwweU3OXnoTtQSRWCvFREkAoJSAysvsI%2BVYGi6PzJa/d%2BqhuO8f44J3kwxDWseiMh0EqHCUkvtdEFjICBh8eetlATsdspCYINlbTITcGeogIQw%2BAbfXmP8zQuhDDQ0KhYWwjh98Y18LEPG8xia60ltIPgGRkz02H0zeGbN5jc1aN4AW/RkJi3GLLX6ytNi7F1tooSlxTA3EeK8T4xgHbZBduCdJvtEqdByaHcYWJNhx0lKnTUIR6w1YxJyZYPJByClFInaUgZN6/CVK3aeupxR31HvyBkU9LSaiXrmU%2BqZ3RT3Hdvcszbf6lmna/Tdxoh3/2e0A1vFT2LwOcA/jpvjFwnPwlcwh3lJBkP3ItbAp5mAXkDEnZnXDIA47wlBKCa2ScKP5yR7EJF721MlxoxXR5pBQ6SGtj81OsR87xEkAnLg0czBYszqCVTBzOAPMtdsue2Pme47owsSxaRnCSCAA%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/typical_paste/implementation.hpp)
- [Source code](../../../../conceptrodon/stockivore/paste.hpp)
- [Unit test](../../../../tests/unit/metafunctions/stockivore/typical_paste.test.hpp)
