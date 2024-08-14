# Age of Empire 1 - ELO Calculator

For multiplayer games, computes balanced team options.

Currently have to manually input players and their ELO, but could use screen capture overlay for the game screen and OCR to automatically generate the list in a future iteration

Further additions also to include if two or more players always want to play on the same team.

# Method

It first finds all the permutations for all teams, computes the team ELO total score, and then finds the closes distance to the average ELO per team.

It then uses a pareto front algorithm to find the best combinations of teams closest to that average.

*It's technically brute force, but the total players per multiplayer game is so low it doesn't matter too much.

**Also testing C++ modules in this code repo for the first time!

# Build Dependencies

For module support;
Cmake >= 3.30
Ninja >= 1.11
GCC >= 14

