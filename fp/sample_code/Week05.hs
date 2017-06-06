module Week05 where

import Prelude hiding (cycle)

main :: IO ()
main = putStrLn "Hello, world!"

put4times :: String -> IO ()
put4times str = do putStrLn str
                   putStrLn str
                   putStrLn str
                   putStrLn str

reverseLine :: IO ()
reverseLine = do line <- getLine
                 putStrLn (reverse line)

reverse2lines :: IO ()
reverse2lines = do line1 <- getLine
                   line2 <- getLine
                   let rev1 = reverse line1
                   let rev2 = reverse line2
                   putStrLn rev2
                   putStrLn rev1

getInteger :: IO Integer
getInteger = do line <- getLine
                return (read line :: Integer)

copy :: IO ()
copy = do line <- getLine
          putStrLn line
          copy

copyN :: Integer -> IO ()
copyN n = if n <= 0
             then return ()
             else do line <- getLine
                     putStrLn line
                     copyN (n - 1)

copyUntilEmpty :: IO ()
copyUntilEmpty = do line <- getLine
                    if line == ""
                        then return ()
                        else do putStrLn line
                                copyUntilEmpty

--
-- ROCK - PAPER - SCISSORS EXAMPLE
--

data Move = Rock | Paper | Scissors
            deriving Show

type Match = ([Move], [Move])

outcome :: Move -> Move -> Integer
outcome mA mB = case (mA, mB) of
    (Rock,     Scissors) ->  1
    (Scissors, Rock)     -> -1
    (Paper,    Rock)     ->  1
    (Rock,     Paper)    -> -1
    (Scissors, Paper)    ->  1
    (Paper,    Scissors) -> -1
    _                    ->  0

matchOutcome :: Match -> Integer
matchOutcome = undefined

showRound :: Move -> Move -> String
showRound mA mB = "A plays: " ++ show mA ++ ", B plays: " ++ show mB

showResult :: Match -> String
showResult = undefined

rock, paper, scissors :: [Move] -> Move
rock     _ = Rock
paper    _ = Paper
scissors _ = Scissors

cycle :: [Move] -> Move
cycle ms = case (length ms) `mod` 3 of
    0 -> Rock
    1 -> Paper
    2 -> Scissors

echo :: [Move] -> Move
echo []         = Rock
echo (latest:_) = latest

convertMove :: Char -> Move
convertMove c
  | c `elem` "rR" = Rock
  | c `elem` "pP" = Paper
  | c `elem` "sS" = Scissors
  | otherwise     = error "unknown move"

playRound :: Match -> IO ()
playRound match@(movesA, movesB) = do
    ch <- getChar
    putStrLn ""
    if ch == '.'
       then putStrLn (showResult match)
       else do let moveA = convertMove ch
               let moveB = echo movesA
               putStrLn (showRound moveA moveB)
               playRound (moveA : movesA, moveB : movesB)

playInteractive :: IO ()
playInteractive = playRound ([], [])

showRounds :: Match -> String
showRounds (x:xs, y:ys) = showRounds (xs, ys) ++ "\n" ++ showRound x y
showRounds _            = ""

showMatch :: Match -> String
showMatch rs = showRounds rs ++ "\n" ++ showResult rs

generateMatch :: Integer -> Match
generateMatch 0 = ([], [])
generateMatch n = step (generateMatch (n - 1))
  where
    step :: Match -> Match
    step (movesA, movesB) = (cycle movesB : movesA, echo movesA : movesB)
