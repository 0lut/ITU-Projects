module Week07 where

import Prelude hiding (dropWhile, filter, foldl, foldr, foldr1, map, sum,
                       takeWhile, zipWith)

filter :: (a -> Bool) -> [a] -> [a]
filter f []     = []
filter f (x:xs)
  | f x         = x : filter f xs
  | otherwise   = filter f xs

allOdds :: [Integer] -> [Integer]
allOdds xs = filter odd xs

takeWhile :: (a -> Bool) -> [a] -> [a]
takeWhile f []     = []
takeWhile f (x:xs)
  | f x       = x : takeWhile f xs
  | otherwise = []

dropWhile :: (a -> Bool) -> [a] -> [a]
dropWhile _ _ = undefined

map :: (a -> b) -> [a] -> [b]
map f []     = []
map f (x:xs) = f x : map f xs

floorAll :: [Float] -> [Integer]
floorAll xs = map floor xs

zipWith :: (a -> b -> c) -> [a] -> [b] -> [c]
zipWith f xs ys = map (\(x, y) -> f x y) (zip xs ys)

foldr1 :: (a -> a -> a) -> [a] -> a
foldr1 f [x]    = x
foldr1 f (x:xs) = f x (foldr1 f xs)

foldr :: (a -> b -> b) -> b -> [a] -> b
foldr f s []     = s
foldr f s (x:xs) = f x (foldr f s xs)

sum :: [Integer] -> Integer
sum xs = foldr (+) 0 xs

maxList :: [Integer] -> Integer
maxList xs = foldr1 max xs

howManyAbove :: Float -> [Float] -> Integer
howManyAbove t xs = foldr (\x n -> if x >= t then n + 1 else n) 0 xs

iSort :: [Integer] -> [Integer]
iSort xs = foldr ins [] xs
  where
    ins :: Integer -> [Integer] -> [Integer]
    ins n []          = [n]
    ins n xs@(x':xs')
      | n <= x'       = n : xs
      | otherwise     = x' : ins n xs'

foldl :: (b -> a -> b) -> b -> [a] -> b
foldl f s []     = s
foldl f s (x:xs) = foldl f (f s x) xs

data Edit = Copy | Insert Char | Delete | Change Char
            deriving (Eq, Show)

transform :: String -> String -> [Edit]
transform [] [] = []
transform xs [] = map (\_ -> Delete) xs
transform [] ys = map Insert ys
transform xs@(x':xs') ys@(y':ys')
  | x' == y'  = Copy : transform xs' ys'
  | otherwise = best [Insert y' : transform xs  ys',
                      Delete    : transform xs' ys,
                      Change y' : transform xs' ys']

best :: [[Edit]] -> [Edit]
best [x]    = x
best (x:xs)
  | cost x <= cost b = x
  | otherwise        = b
  where
    b = best xs

cost :: [Edit] -> Int
cost xs = length (filter (\x -> x /= Copy) xs)

qSort :: [Integer] -> [Integer]
qSort []     = []
qSort (x:xs) = qSort smaller ++ [x] ++ qSort larger
  where
    smaller = [a | a <- xs, a <= x]
    larger  = [b | b <- xs, b >  x]
