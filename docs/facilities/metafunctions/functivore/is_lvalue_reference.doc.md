<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsLvalueReference`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#is_lvalue_reference">To Index</a></p>

## Description

`Functivore::IsLvalueReference` accepts a function-like type. It returns true if the type is lvalue reference qualified and returns false if otherwise.

## Type Signature

```Haskell
IsLvalueReference
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsLvalueReference
{
    static constexpr bool value {RESULT};
};
```

## Examples

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) &;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) & { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) & { return 0; }
};

/**** Tests ****/
static_assert(! IsLvalueReference<decltype(fun)>::value);
static_assert(IsLvalueReference<AbominableFun>::value);
static_assert(! IsLvalueReference<decltype(FunAddr)>::value);
static_assert(IsLvalueReference<decltype(&Tester::fun)>::value);
static_assert(IsLvalueReference<FO>::value);
```

## Implementation

The implementation of `IsLvalueReference` relies on extracting the qualifiers and specifiers of the function-like type using the metafunction `Analyzer`.

```C++
template <typename F>
struct IsLvalueReference
{
    static constexpr bool value
    { static_cast<bool>((1 << 8) & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsLvalueReference_v
{ static_cast<bool>((1 << 8) & Analyzer<F>::value) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJcAJykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzMFkN4sBcTIC3MhhvhBJDsP9/p9NhcTsxaABPABe0VeO1%2BBEwLESBiJEKhBExd2YbAR/2GxC8DjRGJx0WUxFQRCpdwhAHYrPyrpCrKd/kSSWTMBS3LzGKwZQAlTAEUgXeW0zAAOl1J2IwAU9NOjOZBFZYnZxE53O51MwkLcKoIEH1ht12rmxr%2Bgv%2BF39F0mjmQFzQDGGmFUiWIgYI6BAIC8wQIgLMAH1zQA3MReGUmQVcWWOi6A/MiwFin3lysS4mkpjkx2axUXZ3q5tsD1uo2AxEmghMlnoy2461cnn2x3O10GhQeuYQswANm9%2BcrAdjDbwIbDEajMdhCaTglTGYu2e8eYLRahFwAHAK3BdC47i6XhaKkR%2BK0jTpL60STb2lqFwAGIMN6ppDmyo4gBciReBEtDbhaWKjjaE53I64EIgKQrVr%2BJz/tKQE0i2OG9gyA5mqhVrYQwmzenBCFIShw5oRy452lhUIUX2PrrgGQYobuRL7rG8aJsmp5ZjmDqnBua5%2BhuAYvlCxZmI%2BykqRcEDaTpqk3k%2BgIQgArPxBkqexVoYdxDq8RBvYJheub6RuXoKQGZafuK341n%2BdYkZSwEtgAssS4HtiFbAXHUg4EMs9n8VB5rWaOjrhSw4GxdRDiJQmjGUaczGIchIZpZxtryhlEWOfxSmef6wk7gIe7RhJR7SemsmXvpDUnJZaluMWL78sNjUqXpE2DUZJZmRZlkBhVY5VZOUKZXxzlyW5AYeQNXl%2BYRG5eKkRihgYCgKBm9oUlcOXxYlPlVk9tZSg29lytFMqgQA8t6xCYAAjkmAMvADwN4KDeHmEuv0JqgdzEA2JAQF6P4fv28W0elvF/UVJwlax5UwdEjpYKC8p6cucMgAj0TI8QqNo/VvoTc1oatWJ7WHlJJ7dee20Tf1M35uN%2B06VN4uLUNI3zTtOnLWTmAU/aVOwz98OIwzTMIltvXTbtfWHeKE0ncEwDnUwl3XXykJ3b9L3G38HzfK7PzIrsFwAJJSsSjD1DU%2BLbL8KJu98vyvQBebBWRMWgZBuXml7CgBC5mAqlQ0QPPJAn6ezomRu1ESoJ4Av61La6bsGaaiMMjrF54CJQDLt53guMPY6TvG6yAaft073k/ibRGBe9sodt93oF%2BJDe0N7KdpxnWcMKsaaZl%2BFhV9uNdWwQ9cl7QTcQC3T5t4uS6d8Q2E933AoEcPodhyHnvYKorCkjKbwe2HX8P57VBeBXjUF4v8TjBGQiEC4yYLgAIYBAZM6pkybC9IKC4AMErEAYBcDQoo76ERRBcJgxcWDBCIfQGBgCHDpBAQSf4ZszonGIaQpCmBQKANulAwQ8DBCIMEMg8%2BL0XaXFgVQgQ8FUDJmiDQ4O/xwHBBlEwLwRAwKAJOOgdAMZK4w1gXgoezszie2SJImMyi2AlDxCI4BQdDhUSxgAFWeESK%2BvlBL%2BjkZA6BsDuFqk4QQfhHdK7oOWFgnBFY8G%2BXvvoghlj0gXFQBEbQysCDSJsZjGiDsXH6WgXTJGRBGZzG8bwvx7dlx4TQaqYJ2DcHeQiYIgxlwHHDBSb8ZqaYrZKEaBAMAYB56pzkkvAGK8Prk1oJTWBzM9a5jRpWVp7TogumTn0y8Azs6OkYagEhzAWFsLqpMzA0yqJbmQG0y68yuk9MWYvTAmdBmrCVirO4EAdlqI0RM3uckDn9iOScjpCyF79OucvO5UIRmUxho0pxCZxk3w%2BU9WZpzOmXIBTc1ZuMYWXk%2BScDgCxaCcFMrwPwHAtCkFQJwYalhrCBiWCsPMQIeCkAIJobFCwADWIBTKAm1PyUypl%2BRcFMmYLgd47zlDMNIXFHBJC8BYBIDQGhSCEuJaSjgvAFAgHlYyol2LSBwFgDARAtMlEITVBQCAaASR0GiKERUnBVB3iXAAWiXJIC4wBkAhikNqMwvBMD4DyXgeMbR%2BCCBEGIdgUgZCCEUCodQWrSC6DaAAdyRokTgPAcV4oJUyklnAfpGqUXEqgFw7WOuda691z5JBet0h4C19BNF0rmLwTVWgFgQCQOaxIlqyCms7d2kAwApBmD4HQJxaqIARGzREUhxBMRpt4NO5gs6foJKSfO0g5q2CCB%2BgwLE2asARC8MANwYhaBqu4LwLALBDDAHEHG/AAMqGZmeNmyMyslFrHpZIiVxLkIRCRrOjwWBs0DjwDKi9pBn3EGLkoG416jAQNAFqhYVADCGgAGpPETT9Gk67g3CFEOICN%2BHo1qGzQm/QN6UDWGsPoPAEQ1WQAWAjYBnAHWwjtqYCllgzBKqg8QANL6mPtCSekFwDB3CeBaP4CT0x%2BhlCSCkNIAgxitEU3kdIcnzEKbsKJgQXRRhSfGCJ0RtQRg9HkTMAYExzOqb0JMRoWnZhcAWAoalqwJAZo4PihV2blXFvtU6l1bqPVVs0hAXAhASCLkBC55tTK5gLAQJgJgWAYio1IGyyQnK4iAn5JIDQkgxVLjlaZJcCQJVStIDK2L2olxcCXHeOIIqlymUkPy3LS5fNxuVaq9VDKEs6v1e2w1BBjXkEoH2%2Bt1q2CcAaCwTM/IHVMEtmdeI2ouDamJb6qLAnA2RoI2GiQ0gSNKDI3G3Qw7k1MFTRerzPnFW8GVXmsbBbUBFpLUF1bFt1ubY0DWjZXb60xbME2gbyGdUdsB92ibZrof1pQAYIw8QuDypoKMqRlBJ1xsXQ0OdEHcfLtXQ4ddm7/Y7r3fezAh7j2nvPfSq9N673EofaJ5957tuqHfUSdd37s1/oA5iIDaxiWgfA/SqDMHMBwaZ%2BbQbqGmAYawzhxgeHZChqIyd2QpHY3Esu5Row1HuM2D/YxjLLHqFsY44CK4XGrA8b49EPbQmMu6dM%2BJyTWQ1OBEs/JnISmah2baLkZTDAnPWZMzUAzTQjNqbd1H8z4edO2dj/ZxPvvtOecWMsDzLn9CZu60qzgAXS0utBDe58cQNtbd0pFvJMW4vg9bUllLaXKBeaqzVqvhXuVxH5PyQERXJDOraI9nNKrbD9Zbdq3VBqlivZNZN%2BHVqbUcHm2WlgChMwhkzOt6UwwfV%2BpIAGvQ%2BGNfhq11Gs7uudAgEBKQa7t3035%2B81mnrub83mne8WjfW%2Bd97/emGABzrTxHMEBEBDB2nzbShxAJ7SX1gN7mQESESDXniDTH3wIDTFUGdRHQx2IHHWx2JUJ3x3pWIJXUSRJwgzJ23V3XxxZ2pyPRPVoDPXXUZwQxF0vUhjZxfTjTfWQA/V50ECqH53o0F2FxAwE3F14ElxSGl2JFl0NwhwVyV0wGw1wwgzP0IwvwOx13IzvwN2MBo0sDowY3gGY0SFYw2EPDt2sF4ye340EzN1cyqD0z8AgFcCD1IB9yKD92DwD3SE8JDxqCT3sxcNM2j08Pj06HTx8Mzxs26EiJiL6DiNc3c3DXuzfyLw4B/xdU3233PAAKJCAIiyPwbVi0gISxb1SwGAy0q2lRADMCr3AJ5UK1Rw0HAP5Ea0Lye04D6w1UqMyxAGHy9UkCKzvEkH5BFSFTvE6Jf0BEyJ6InygK829W6PH3i2QwWCg1SGcEkCAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_lvalue_reference/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/is_lvalue_reference.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_lvalue_reference.test.hpp)
