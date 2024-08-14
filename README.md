# Age of Empire 1 - ELO Calculator

For multiplayer games, computes balanced team options.

Currently have to manually input players and their ELO, but could use screen capture overlay for the game screen and OCR to automatically generate the list in a future iteration

Further additions also to include if two or more players always want to play on the same team.

# Method

It first finds all the permutations for all teams, computes the team ELO total score, and then finds the closes distance to the average ELO per team.

It then uses a pareto front algorithm to find the best combinations of teams closest to that average.

*It's technically brute force, but the total players per multiplayer game is so low it doesn't matter too much.

# Build Dependencies

Cmake >= 3.26
Ninja > 1.10

https://www.kitware.com/import-cmake-the-experiment-is-over/

https://www.dedicatedcore.com/blog/install-gcc-compiler-ubuntu/

https://godbolt.org/z/aTr8crhcE

https://www.kitware.com/import-std-in-cmake-3-30/
