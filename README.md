# Game
In this game you are running against 3 to 6 opponents to a finish line. Your starting position is not set but random.
You can switch lanes, speedup and down in any direction and yell. Your opponts can take the exact same actions as you.

There are two types of obstacles you will come across in your race.
You can come across a knight. Knights stand still and are unmovable. When you yell against a knight that knight has a 50% chance to be afraid and switch lanes.
You can also come across a Rat. Rats move slowly in the direction of the finish line. When you toch them your maximum speed is halved for a while.  When you yell against a rat it has 50% chance to double its speed for while. Giving you a chance to move out of the way.

When you yell a text bubble will appear. While that bubble is up you can not yell again.
You can only switch lanes when the space next to you is free and you are not currently in collision.
The goal of this game is finishing first without hitting anyone.

# Controls
- Move left: arrow left 
- Move right: arrow right
- speed up: arrow up
- slow down: arrow down
- go backwards: arrow down
- Yell: space

# Score
You start with a score of 0.
When you hit an opponent or knight a point is deducted until you are out collision.
When you yell 10 points are deducted.
When you finish you get 100 points for every player behind you.

# Running the game
You can run the game by running the provided script: "turbohiker-game.sh".
This will start the game immediately.
When you finished a run you can see your placement and score.
By pressing R you can restart the game.
When you finish a round the top 10 highscores will be written to a text file.
