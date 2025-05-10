<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::GetReturnType`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#get_invoke_return_type">To Index</a></p>

## Description

`Functivore::GetInvokeReturnType` accepts a function-like type and returns a metafunction.
When invoked by a list of argument types, the function returns the return type of the function-like type called by objects of these argument types.

## Type Signature

```Haskell
GetInvokeReturnType
 :: template<typename...>
 :: template<typename...>
```

## Structure

```C++
template<typename...>
struct GetInvokeReturnType
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will extract the return type from several function-like type.

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
    double operator()(int, int*, int**) const { return 0; }
    void operator()(int, int*, int**, int***) volatile & { return 0; }
};

/**** SupposedReturnType ****/
using SupposedReturnType = int;

/**** Tests ****/
static_assert(std::same_as<GetInvokeReturnType<decltype(fun)>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<AbominableFun>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(FunAddr)>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(&Tester::fun)>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<FO>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<FO>::Mold<int, int*, int**>, double>);
```

Note that since `std::invoke_result` does not work with volatile lvalue reference qualified(`volatile &`) member functions.

```C++
// This will fail.
static_assert(std::same_as<std::invoke_result_t<FO, int, int*, int**, int***>, void>);
```

The following code will not compile:

```C++
static_assert(std::same_as<GetInvokeReturnType<FO>::Mold<int, int*, int**, int***>, void>);
```

## Implementation

```C++
template<typename Fn>
struct GetInvokeReturnType
{
    template<typename...Args>
    using Mold = std::invoke_result_t<GetVariadicTypeSignature<Fn>, Args...>;
};

template<typename Fn>
requires std::is_class_v<Fn>
struct GetInvokeReturnType<Fn>
{
    template<typename...Args>
    using Mold = std::invoke_result_t<Fn, Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAJxmpK4AMngMmAByPgBGmMQSZkEADqgKhE4MHt6%2BASlpGQJhEdEscQlcSbaY9o4CQgRMxATZPn6B1bWZDU0ExVGx8YlBCo3Nrbkdo739peXDAJS2qF7EyOwcAPQAVLt7%2BweH25smGgCCO3sA1AAimMmujMh4mApX%2Byfnl0c/B59npwBZgAzOFkN4sFcTMC3AQAJ4PAD6BGITEICmh2EBgO%2B2yuZ2YtDhAC94u89v8CJgWMkDFSoTD4Q9mGxMYDRsQvA58YSSfFlMRUEQmZgoQB2Kxim7QqznQFUml00XQ2EIxisUUAJUwBFIVxFLMwADoTWdiMAMcCsecOVyCDyxHziAKhUK1SrtQQIGaLSajQs2XKJYCrqGrl50kYrgA3Jp4Jj4ZDItWI9LAZgEVbK4E3K6e73mhR%2BgPA2UAqUy7HnBW0pj0lUGjV5nV6xtsP0%2By3Ws627kEx2k52C4XumH5zt%2BvXFwPlsth8OR4AxuMJvBJkWpvDputZhm58eFydXael7EV09y6vU2v1xlqw3N3X6%2B8ajuFme9%2B39omDl0jh4ejqBa%2BiaCxXGgDCjDOJjBuc84RuES6xsQ8aJsmSJphmu7QvuQETqBlZBtKF4Aleip1tmqrMk2nqti%2B7amu%2BVrsiidoOj%2B/LDm6AFjnhh4mlOoHgQIUHMUGc5hghUbIaha7oZgm7bpmxDZrhXr4Uagn%2BoR5bEWW8rXkqDb0aKABiDAfqxfa8oOIBXMkXgxLQa7sU6f7cZgKrmZi4qSnpVZnDWRl3tRbBXN5Yk9lZX42fEXkMNsM52Q5Tkud%2BblcSK8U%2BTBfk6QZ5FUsZoWigAstS5l0SVVwNJyDhZpZdUxQOcUwuVLDmTV0VZiAICJZFyWOc5yCub%2BmWjm47URdgvkwf5l6BYZFHFeqYWmQA8jOKkAI5eHgKlvDte0HbNZgAGwbb1qAPKiRDEBAJZ5Ta0Wja1bgbUl9lDWlsXECqWDgiKEDmBd61XTddYkA9JYzblc35V8%2BxXAAKgia5iAA4jqABqK6JqjDxCFuWEqeSuyUktRUhatZkWZFn4o2joi0FjBC4yhq7IATmBE0pDXiQuiHPg8e6vX9MLTb1Mmc/Jikk55p7nvpiPXKz7OyVzaq8/LZPHAVN4K1RNNvhaM5SUuat42u3PazupM4YzyToyzONW5rhPE3bhsaZivVZSROK/EHfyB9cACSirUowjR1Awuv/Liwe/P8%2BvBUbD7TSxTVXKzYcMNGqAANaYJ6qwMNzZ4SaGQXLdThom12IaSYuVylZ46Ci6M6C9eEBfF4iB1eLQBDIiqlsc/jWue8phvTXqPvMQHSsBTXVPp02mfnEd%2B2vFcXc9woiLgkwCiH9G2X0y9uf50XJc6mXFcS3T3Zw3BYar4bbbGoxpuRfBLdt1oB3B2%2B8QC91vgPV4Q8R4EHivPfiRo2RL3mqRC4ScQ4q12FcbAqhWC0lFB8UO6DyYBXMKCBg4IvCQhVBBdYyQCCNwWriK4VAvAUNjm8Qh5xwjOQiFccI9pWEMAgAIvUAjtgBglFcFSyk44aBlOKaUTCkZMBiKgFg4RVH0BYWwhwmROEUkBObfEaiNHMCcpgUybDRYCJEYIMRggJHCUgrAgOmC8RCL0QIeyqABHxAMSQ7hDBeGiiYF4Ig4U2FnHQOgYgvkoTnSEYohGaDripD8XEiJbAyhkk8Rw%2BOWc2LI1eFSP64km6hh4eEUUAidHCNEfwxxYEIKjHiTIsuVx5GlmSURFJzC8mZCuKgGI2hMAOACXrZ62cPrlLfpUwQQyIZ3QenYp84jmkiXtLlaR99iByIUfDOZVx0ArAsYs%2BIkN7oLFWQ4gg2xbm7A2S4tpuz9ndMObpPpSMhBeGSKkJQ6BS57O5gU84xifl/LSJgQFryQUOwEV864xTRgTP%2BNMRwSYT5KGaBAUBCgNSIhPmPHUec%2B531kY/NwANh5qmoGwmGvVAHoBVA08RmI9QQv%2BdCoF5dRzYEeixOscksXxC9HiglRKYTXzJTyylZxTGaIsVY5%2BjL24svsY0u57Kaq/K5TCilfKBXPSFZi0%2BorcUEG7iAfFbBCWWjcNK2%2BsqJrUqBsq6JsSGUgCZeqtZjjtWcqhfqh%2BhqdLouFWanF4rbWSodSSm%2BxdnU8SpWMmlDxgbnWRaU3qQivU%2BphKy/1VoOW6qDUmhW/Kw0xwjdisVlreo2oUrGx1ibYUTQ%2BlaVVQDfUPIDaWgF5bMRGqiiau1taLVWsbXa4lBBSVOrbcmjt2Au3MoLRq8RDz%2BrYD1CcoaFbh04k2CjBAeA3gAHc6C0BYWiWgiDjUYrHea6NTb7WgPAf3Qew9R4S3Wrch5m7N1br1AXPAq7K1uIuEe5GJ7z2XuvXQVsqBUB3pHQ%2BkVUb63Wolfalt5KQ2Ls2p271aq11%2BruQBzVextUgbA49DgSxaCcAAKy8D8BwLQpBUCcDcNYawe8VhrGVCCHgpACCaHo0sQuIBJAAA4jTAn8P4MUwIZPKbMDJpjkhgTSEYxwSQvAWASA0BoUgbGONcY4LwBQIATNifY/R0gcBYAwEQCAFYBAHK6goBANANI6DxEiBqTgqgZNnQALRnUkFcYAyARpSCNGYXg0LCAkFA3ofgggRBiHYFIGQghFAqHUPZ0guguCkDPaiZInAeAMeY6x8TnHODrXCZ5oZVArghfC5F6LsWrjxbMFcCAHg/P0DiWQrgCxeB2a0EsCASBfNO1G%2BQSgC3/MJGAFIIINBh7%2BMoDEBrMRNHEDhNV3gh3mDHfWiMsZdmRO%2BbYIIdawSTvFawDELwwA3BiFoNZ7gvAsAsEMMAcQr2d56OjK8BrmBVBjPCRsETfjdMcecjEVEx2PBYAayiPAhm/ukAh8QNRSg7iA6MLw0A9mlhUAMBabGLwz3rWZKdvLwhmY5ekBl%2BQSg1ANdK/oIHKBeOWH0HgGI1nIBLGuhwzgYWu44VMJYawZhzME5QlgcXD1Og3cyC4Bg7hPBtD0KEapcwhhlf%2BYULIBvcjm4KLHWYgwKha68QwHo4xrd%2BDK3YbX9Qxh9BN47vQ0x3c5E97YP3DuckVCWAoAT6wJC1Y4Cx0zDWLMddCxFqLMW4uSAS4N3AKWxvCcm6J8TCwlgIEwAmIYmupNaaNP4YEYpJAaEkGYSQZ1jNMbOv4fQnB9OkEM8CLgRozpcDOjJ/wMnx%2Baa4ExxvZ0U/FYs1ZmzpfKeOZc3NtzLXwnLZ8%2BoxbAWgscCaCwaMYowtMHAgYKMXB/BGhHxx5Ld00tlc51l8QuXOcFZ58V3QQQFWTAVWf2ieyeZmvAFmzWHm4SbW6eXWUWx8d%2BD%2BT%2Bg2w2R%2BRewIZgJe02Dm2%2Bq2S23mBBQwSBG2/gXAJm22pS1mEA%2B2xW52TQL2ImDBl212DgzO920cT2RIDWb2H2X2tAP2zOAOQOIOHG%2BAKk4OkOxW0OsOVIzOiODWKOaOcIGOGwHG2OuOImBOROmAJOohiEZefANOCgdOmADOTOeOH%2BbOEgHOsgv%2BRWHGAB/ORgguiuwuKOGuku9C%2BiMucuOYCuVglgyukBquoGkOEuzuscuu%2BuoeRueuke8wtu6QscEwYeFu9uAeUeQeNQPurufuaRORXQvuMwWRSR4evQhRXuEeZRZuMeceOWYB9Wy%2BnA8BmeN%2BQOfWKBRoGg%2Be%2BAd0CSw%2BOBZeFeVeWACQmuumA%2BQ%2BD%2BreYo8%2BYoymbeHekgZWEBjWlmtga%2BuBs2W%2BSA7mnm%2B%2BxBxAgWbAnAZ%2B3WLACg0YI00Y9%2BRoSoowSW/RqW3c7%2Bsgn%2B7OLODhvOIAwI5WlWp2TRS%2B5mTWu%2B9oqA7Wqglx1xtx9xjx9oQ2h%2Ba2gxwIwxG%2B%2BByJhBK2WJQwNxfyiIdx/giICJiI0JHOdA1Be2B2R2TBZ2tJV2oy7BeOnBj2z2vBmA72n232v2ImIhZO6h/2YOjgEOv2z%2BMOyAcOChggNQShouKhahWOKEWhvAOhUK%2BhZOhhG%2B1OTAtO9OjOjAzO1h2Wth3x3OjhOgfxLhxgQuNgnh8A3h0uWw%2B8gRSuKu8QauERmu3uLuMRVRwQCRtRTuGRmQ/pIZRQQZRReRbuLQHuUZLuMZiRZuFRIehu1RpRJQgeE2ywqw8e2Zum4BqerR5JVwVxNxMY8JFErSEABeAx426JM2ox1eExie0xIAZgD%2BwIwITGTGreFBGgXZYoE%2BIJkBnAq%2BtmIxpAUmTGI%2BneGg50lQZ0YoUg3ePZfeHAwIzRoJmxOxieiWI5GxU2k5BO6QzgkgQAA)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/get_invoke_return_type/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/get_invoke_return_type.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/get_invoke_return_type.test.hpp)
