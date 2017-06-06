module Week04 where

import Prelude hiding ((!!), (++), concat, drop, elem, init, last, replicate,
                       reverse, splitAt, take, unzip, unzip3, zip, zip3)

(!!) :: [a] -> Int -> a
[]     !! _ = error "no such element"
(x:xs) !! 0 = x
(x:xs) !! n = xs !! (n - 1)

(++) :: [a] -> [a] -> [a]
[]     ++ ys = ys
(x:xs) ++ ys = x : (xs ++ ys)

elem :: Char -> [Char] -> Bool
elem _ []     = False
elem x (c:cs) = if x == c then True else elem x cs

replicate :: Int -> a -> [a]
replicate _ _ = undefined

last :: [a] -> a
last []     = error "empty list"
last [x]    = x
last (x:xs) = last xs

init :: [a] -> [a]
init _ = undefined

take :: Int -> [a] -> [a]
take 0 _      = []
take _ []     = []
take n (x:xs) = x : take (n - 1) xs

drop :: Int -> [a] -> [a]
drop _ _ = undefined

splitAt :: Int -> [a] -> ([a], [a])
splitAt _ _ = undefined

reverse :: [a] -> [a]
reverse []     = []
reverse (x:xs) = (reverse xs) ++ [x]

concat :: [[a]] -> [a]
concat []       = []
concat (xs:xss) = xs ++ concat xss

zip :: [a] -> [b] -> [(a, b)]
zip (x:xs) (y:ys) = (x, y) : zip xs ys
zip _      _      = []

zip3 :: [a] -> [b] -> [c] -> [(a, b, c)]
zip3 _ _ _ = undefined

unzip :: [(a, b)] -> ([a], [b])
unzip []           = ([], [])
unzip ((x, y):xys) = (x : xs, y : ys)
  where
    (xs, ys) = unzip xys

unzip3 :: [(a, b, c)] -> ([a], [b], [c])
unzip3 _ = undefined

merge :: [Integer] -> [Integer] -> [Integer]
merge xs [] = xs
merge [] ys = ys
merge xs@(x':xs') ys@(y':ys')
  | x' <= y'  = x' : merge xs' ys
  | otherwise = y' : merge xs  ys'

romanNumerals = [("M", 1000), ("CM", 900), ("D", 500), ("CD", 400),
                 ("C",  100), ("XC",  90), ("L",  50), ("XL",  40),
                 ("X",   10), ("IX",   9), ("V",   5), ("IV",   4),
                 ("I",    1)]

toRoman :: Integer -> String
toRoman n = tR n romanNumerals
  where
    tR :: Integer -> [(String, Integer)] -> String
    tR n []              = ""
    tR n xs@((s, k):xs')
      | n >= k    = s ++ tR (n - k) xs
      | otherwise = tR n xs'

fromRoman :: String -> Integer
fromRoman _ = undefined
