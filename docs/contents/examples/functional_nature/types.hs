-- Copyright 2024 Feng Mofan
-- SPDX-License-Identifier: Apache-2.0

module Main where

-- typename
data Typename

-- auto
data Auto

-- *...
data Ellipsis a = Empty | Dots a (Ellipsis a)

-- template<*>
data Template a

-- Template instantiation
instantiate :: Template a -> a -> Typename
instantiate = undefined

-- template<template<typename...> class...>
type TeElTeElTy = Template (Ellipsis (Template (Ellipsis Typename)))

-- template<typename...> class
type TeElTy = Template (Ellipsis Typename)

-- template of type `template<template<typename...> class...>`
tem :: TeElTeElTy
tem = undefined

-- arguments of type `template<typename...>`
arg_0 :: TeElTy
arg_0 = undefined

arg_1 :: TeElTy
arg_1 = undefined

arg_2 :: TeElTy
arg_2 = undefined

arg_3 :: TeElTy
arg_3 = undefined

-- create an argument pack
pack :: Ellipsis TeElTy
pack = Dots arg_0 $ Dots arg_1 $ Dots arg_2 $ Dots arg_3 Empty

-- instantiate `tem` by the `pack`
result :: Typename
result = instantiate tem pack

-- error silencer
main :: IO ()
main = return ()
