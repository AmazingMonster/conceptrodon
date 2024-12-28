<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Stockivore::Paste`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#stockivore-paste">To Index</a></p>

## Description

`Stockivore::Paste` accepts a list of packed stockrooms.
It concatenates them together and uses the first stockroom to hold the result.

<pre><code>   Stoc<sub><i>0</i></sub>&lt;Seqs<sub><i>0</i></sub>...&gt;, Stoc<sub><i>1</i></sub>&lt;Seqs<sub><i>1</i></sub>...&gt;, ..., Stoc<sub><i>n</i></sub>&lt;Seqs<sub><i>n</i></sub>...&gt;
-> Stoc<sub><i>0</i></sub>&lt;Seqs<sub><i>0</i></sub>..., Seqs<sub><i>1</i></sub>..., ..., Seqs<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
Paste
 :: template<typename...>
```

## Structure

```C++
template<typename...>
using Paste = RESULT;
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
using Result = Paste
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Stockivore::Paste` is implemented as a shortcut to the member `type` of [`Stockivore::TypicalPaste`](./typical_paste.doc.md).

```C++
template<typename...Args>
using Paste = TypicalPaste<Args...>::type;
```

[*Run this snippet on GodBolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAHACspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIphJrozIeJgKF7tHp%2BcHX3vvJ8cnBEwLCSBkBJgAzG4CABPO7MNgAOiREOw/2GxC8DguABVYXhRLRlExhpgLiYAOxWclXCFWU7/dbrC4WYmktyskD/f6A4GgzAQqGwxisUlE5AAa0w6DqqAlxFQqBYKLRBAxWNxSXxYiJJIFYsl0qIcoVSvBqPplP%2BF2tFy8aSMFxhdzJ4KuF31UplxsVtK51N99I%2BTIASphkMs0gA3NkcrmnHkgphg%2BmQq02hN8gUZpP8yFMLxEJEIlEXZAGBQKIslsvEl5e8XyxUnUhp63ZsGQ9u59kF1BVs2l8uV5EDmsVi71xssGytx1AxMdnuFkfYQe1otCTAARy8D0wJwUpDJpxtc95OYF%2BeXxdHQ43293DFWFkPs6dwsRSIA8gQENEFFyZoqmqBA4niBI6ouk4mn8kKbjue4Hv22BHtBipWHBD57i%2ByFHj%2Bf7EMON7mn8lonjadrBMAjpCi6brvvCpIalqhLEsmJyngKs6nmhLCwW48GPqsSFIqhWFPpgOEri25Gnta%2BH/lWskutgIAgO%2BAakTS4J0n8HzfAZPwMrsFwAJK8kCjD1DUrw7L8nyGQZvzcvOmadkKjFFicxDAABQGnJRDqQaSEJusxEFsd23m%2BchakaTpcZnI5Rn6Zc2CqKwIKkm8xnJXZiXmOCwRll4WAum4aASUkBB%2BSRuXbBcABqzx2C8OXxq5F6dp1i5Xn2K5rhWyHAZioG8QA%2Bhomkueei5dpevbIYNRHKqc6KjRORoNia41cNNHWzd2815otA1jit/kHqqG0TWY%2B1JZcpk8m1%2BUHQu3Z9cNa3XVi8GTfdx1Lv1xEjb9267QDPUfadIPfSBE7g3dCWBgCUMLdeq1XfDf3gvdDkTl4SR5FKoYKF4tCge1JyBdRQiE8T6Ck%2BToGhZtsrbYq/2YVuk1iTzbQIzzZh8%2BNuNAcjekPQ1TMU7Z2y/DTFwyyzrrupFgFuLOE1TdzXMoceHE2hNe26wLf1IyhWtbVO41IwJ4Ni3V4u6fVmw4s8lOvVdSb4uNtbRAQEDDOgakKCKft%2BW4yuofTqQk88zMonM90cAstCcPEvB%2BBwWikKgnCa5Y1gXAoSwrCFZjgjwpAEJoqcLOKIDxJICIaLEZhmAAnJ3XDxG3sRcOS5LSOnHCSLwLASBoGikNnuf5xwvAKCAM%2B1znqekHAsAwIgIBLAQSQFuQlBoMCdDRKEIqcKosQAGwALS35IFzAMgyAXFICJmLwUqECQeAhzaPwQQIgxDsCkDIQQigVDqHXqQXQbQADuxAmBJE4DwNOGcs51zzpwL8BZD6gVQFQC4N8H5Pxfm/D%2BLczAXAgB4M%2B9BiBkkrlwOYvA15aAWBAJAp9NRMOPhAPh58YjACkMLGgFN/yUAiDgiIwQGjQnQbweRzBiDQi/BEbQYY17V1PmwQQX4GC0CUXArAEQvDAHZLQWgy9uC8CwCwQwwBxBmLwMQHReBox2NzpgVQYYCxrGrsEQEo9c60DwBEFB6iPBYBwaqPAk97GkGjMQCIccbhOKMBEowdcFhUAML5RqTxEFfjhMoyBwgCTgOkMA%2BQSg1A4IQfoZxKBrDWH0JE5ekAFioGqhkOx99g6hVMEXSwZh56pOIAA548AFh2E8c4CArgxitFIIEYIfRSgDDaHkdIAhVm5FSPshg0x%2BgxAmFURZtQRhNE8C0PQCyHCdFuWc7ZFzbC3MORMV5myZg7PmWXVYEhMEcEzrPHBC9SF30fs/V%2B79P60IgLgP%2BzDCpsI4XkhYf4mBYBiBABuIBJDggRJ3cEw8NCSDMJIW%2B094i307voTg49SCTyrgiW%2BXBb6xE7gPW%2Bzde5ktvhCuBC8l4rxrnkzeO8eF7wIUfCgQjFT8IvlfDgDQWCRnJPfJga4HRcE7giLgrcf74CINMwBlTQHiAgXU6BjS4G6GFsg1ByjQXgrnrwBe%2BCD4FguMQ6F5Dn41n1Ya41Gg6EMJVWiyuZh2GSvXtw3hyqRGCOEUwlABgjAGq4DPSRgJCIyLkQo9RFTVGKM0dohwFT9FWSMSYnB5jLHWNsRUxxzjXG53wB4553icF%2BICYCCpISqg4IiVExRsS1i5wSUk6uqT0lKEyR2qiUqClMCKSUspjAKl1OtTUyp9rYG5ydS03JoyrCWE6REbpBK879IEIM4ZroL3WAmV6qZMzb3zKuc8pZKz7njHWQwdAbzZi7OOTUb5yRIMZDAzs9o1yuijEA2sp5NRkM9D%2Becx5XzUO4amNh95ILFjLGBWwplYLsGis4IG2FerqIGqNa3OhKLzUsKrvGzh9dSA4rxZQUFLK2WGspeSeInch7gipTSyQbRPW4MXrYCV3HuEyqQPvQhaaU1MMvmwTgGqKEsAUJGd%2BkYmN8mGKa1FAC9B7uqRIWpsgj1NJAOCUgLq0H2PddR%2BeeD5VEJIaoQzxnTPmZzMMSN2nogcfBFxqVsr03RC04wgYJmibjTM53caFmCDjSC7UugBbl4QFkXA8tpbknlY0VonRNbFQGIIPW0xXbMAWKsWIVtyT23ZOnQ49xni%2B1wIHeGIdySR1hN4OO6J0Ip3xOmXO3gC6MlAhXbkxNfBCkKGKZgUp5Tkl2bAQ5w9DTj06Fc2e4w7Sr3ju/femodj1jBzaWMiw7686fqwLd9DGQXAgegxs4oOGIP5AyNBvZNR4MfO%2BwITD0Hoc3MI4D4jPzuhw9%2BUj8DgKyPgO8yK3zHBSHBZMxcTLCIcusbNSQDjGKE1cOxZgXFAw72jyEyALuCJwTgniH3WT09Ofkm5Xjr1nBxWryxaQRukh4iksHuSaesRJA9y4O3MwwrR7gh88LxTKnQXfyFwpzFiaFipLSM4SQQA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/paste/implementation.hpp)
- [Source code](../../../../conceptrodon/stockivore/paste.hpp)
- [Unit test](../../../../tests/unit/metafunctions/stockivore/paste.test.hpp)
