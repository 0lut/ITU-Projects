module Week10A (
  Set,
  empty,       -- Set a
  add,         -- Ord a => Set a -> a -> Set a
  makeSet,     -- Ord a => [a] -> Set a
  contains,    -- Ord a => Set a -> a -> Bool
  union,       -- Ord a => Set a -> Set a -> Set a
  card,        -- Set a -> Int,
  mapSet       -- Ord b => (a -> b) -> Set a -> Set b
) where

data Set a = OrderedList [a]
             deriving Show

empty :: Set a
empty = OrderedList []

add :: Ord a => Set a -> a -> Set a
add (OrderedList xs) x = OrderedList (insert xs x)

insert :: Ord a => [a] -> a -> [a]
insert []          y = [y]
insert xs@(x':xs') y
  | y < x'           = y  : xs
  | y > x'           = x' : insert xs' y
  | otherwise        = xs

makeSet :: Ord a => [a] -> Set a
makeSet = foldl add empty

contains :: Ord a => Set a -> a -> Bool
contains (OrderedList xs) = search xs

search :: Ord a => [a] -> a -> Bool
search []     _ = False
search (x:xs) y
  | y == x      = True
  | y <  x      = False
  | otherwise   = search xs y

union :: Ord a => Set a -> Set a -> Set a
-- union s1  (OrderedList []) = s1
union (OrderedList [])     s2 = s2
union (OrderedList (x:xs)) s2 = ((OrderedList xs) `union` s2) `add` x

card :: Set a -> Int
card = length . makeList

makeList :: Set a -> [a]
makeList (OrderedList xs) = xs

mapSet :: Ord b => (a -> b) -> Set a -> Set b
mapSet f = makeSet . map f . makeList
