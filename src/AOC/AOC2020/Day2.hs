module AOC.AOC2020.Day2 where

import Data.List.Split (splitOn)

part1 :: [String] -> Int
part1 = length . filter (== True) . map (isNice . parseString)

parseString :: String -> ((Int, Int), (Char, String))
parseString str = do
  let (numbers : letter : password : _) = words str
  let (minimal : maximal : _) = splitOn "-" numbers
  ((read minimal, read maximal), (head letter, password))

isNice :: ((Int, Int), (Char, String)) -> Bool
isNice ((minimal, maximal), (letter, password)) = (letterCount <= maximal) && (letterCount >= minimal)
  where
    letterCount = length $ filter (== letter) password
